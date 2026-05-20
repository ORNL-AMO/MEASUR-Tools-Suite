#include "treasureHunt/insulated_pipe_reduction.h"

#include <array>
#include <cmath>
#include <string>
#include <vector>

#include "physics/constants.h"

namespace insulated_pipe_reduction {

// ── Air property polynomial coefficients (T^4 … T^0) ────────────────────────
// Each array holds the 5 coefficients for a 4th-order polynomial fit of the
// named air property as a function of temperature (K).
static constexpr std::array<double, 5> kAirSpecificHeatCoeffs        = { 3.03724e-13, -1.1132e-9,    1.44382e-6,  -0.000565339, 1.07223839  };
static constexpr std::array<double, 5> kAirViscosityCoeffs           = {-1.586e-10,   5.115e-7,     -7.246e-4,     7.978e-1,   -1.850       };
static constexpr std::array<double, 5> kAirKinematicViscosityCoeffs  = { 2.25852e-11, -8.32093e-8,   0.000172673,  0.01063728, -0.76108359  };
static constexpr std::array<double, 5> kAirThermalConductivityCoeffs = { 3.17176e-11, -5.90229e-8,   4.58531e-6,   0.088867888, 0.520072239 };
static constexpr std::array<double, 5> kAirAlphaCoeffs               = { 1.35569e-10, -3.80588e-7,   0.000446483, -0.035935528, 2.254489164 };
static constexpr std::array<double, 5> kAirPrandtlCoeffs             = {-2.08438e-13, -1.72787e-11,  8.00624e-7,  -0.000694606, 0.845781218 };

// ── Internal helpers ─────────────────────────────────────────────────────────

static void validateInput(const InsulatedPipeInput& input) {
    if (input.pipe_emissivity < 0.0 || input.pipe_emissivity > 1.0)
        throw std::string("ERROR : Pipe - pipe emissivity out of acceptable range");
    if (input.jacket_emissivity < 0.0 || input.jacket_emissivity > 1.0)
        throw std::string("ERROR : Pipe - jacket emissivity out of acceptable range");
    if (input.pipe_material_coefficients.size() != 5)
        throw std::string("ERROR : Pipe - expected exactly 5 pipe material coefficients, received ") +
              std::to_string(input.pipe_material_coefficients.size());
    if (input.insulation_material_coefficients.size() != 5)
        throw std::string("ERROR : Pipe - expected exactly 5 insulation material coefficients, received ") +
              std::to_string(input.insulation_material_coefficients.size());
}

// Evaluates a 4th-order polynomial: c[0]*T^4 + c[1]*T^3 + c[2]*T^2 + c[3]*T + c[4]
template <typename Coefficients>
static double polyFit(const Coefficients& c, double temp) {
    return c[0] * std::pow(temp, 4)
         + c[1] * std::pow(temp, 3)
         + c[2] * std::pow(temp, 2)
         + c[3] * temp
         + c[4];
}

// Bundles all air properties at a given film temperature.
struct AirProperties {
    double conductivity;
    double kinematic_viscosity;
    double prandtl;
    double expansion_coefficient;
    double alpha;
};

static AirProperties computeAirProperties(double film_temperature) {
    return {
        polyFit(kAirThermalConductivityCoeffs, film_temperature) / 1e3,
        polyFit(kAirKinematicViscosityCoeffs,  film_temperature) / 1e6,
        polyFit(kAirPrandtlCoeffs,             film_temperature),
        1.0 / film_temperature,
        polyFit(kAirAlphaCoeffs,               film_temperature) / 1e6,
    };
}

// ── Convergence iterations ───────────────────────────────────────────────────

static double insulatedIteration(const InsulatedPipeInput& input,
                                  double inner_pipe_diameter,
                                  double insulation_outer_diameter,
                                  double surface_temperature,
                                  double interface_temperature,
                                  double heat_length,
                                  int iteration) {
    double film_temperature = (surface_temperature + input.ambient_temperature) / 2.0;
    AirProperties ap        = computeAirProperties(film_temperature);

    // Convection and radiation on insulation outer surface
    double re  = reynoldsNumber(insulation_outer_diameter, input.wind_velocity, ap.kinematic_viscosity);
    double ra  = rayleighNumber(ap.expansion_coefficient, surface_temperature,
                                input.ambient_temperature, insulation_outer_diameter,
                                ap.kinematic_viscosity, ap.alpha);
    double h_rad     = radiativeHeatTransferCoefficient(input.jacket_emissivity,
                                                        surface_temperature,
                                                        input.ambient_temperature);
    double nu_forced = nusseltForcedConvection(re, ap.prandtl);
    double nu_free   = nusseltFreeConvection(ra, ap.prandtl);
    double nu        = nusseltNumber(nu_forced, nu_free);
    double h_conv    = convectiveHeatTransferCoefficient(nu, ap.conductivity, insulation_outer_diameter);
    double h_air     = h_rad + h_conv;

    // Pipe wall resistance
    double k_pipe       = polyFit(input.pipe_material_coefficients, input.pipe_temperature);
    double r_pipe       = thermalResistance(insulation_outer_diameter,
                                            input.pipe_diameter,
                                            inner_pipe_diameter,
                                            k_pipe);

    // Insulation resistance
    double insulation_temperature = (surface_temperature + interface_temperature) / 2.0;
    double k_insulation           = polyFit(input.insulation_material_coefficients, insulation_temperature);
    double r_insulation           = thermalResistance(insulation_outer_diameter,
                                                      insulation_outer_diameter,
                                                      input.pipe_diameter,
                                                      k_insulation);

    // Total resistance and heat flow
    double r_total      = r_insulation + r_pipe + (1.0 / h_air);
    double heat_flow    = (input.pipe_temperature - input.ambient_temperature) / r_total;

    // Update temperatures
    interface_temperature  = input.pipe_temperature - (heat_flow * r_pipe);
    surface_temperature    = interface_temperature  - (heat_flow * r_insulation);
    double heat_length_new = heat_flow * physics::kPi * insulation_outer_diameter;

    if (std::fabs(heat_length_new - heat_length) < 0.0001)
        return (heat_length + heat_length_new) / 2.0;
    if (iteration > 30)
        throw std::string("ERROR : Pipe, Insulation - recursion limit exceeded");

    return insulatedIteration(input, inner_pipe_diameter, insulation_outer_diameter,
                               surface_temperature, interface_temperature,
                               heat_length_new, iteration + 1);
}

static double bareIteration(const InsulatedPipeInput& input,
                             double inner_pipe_diameter,
                             double insulation_outer_diameter,
                             double surface_temperature,
                             double interface_temperature,
                             double heat_length,
                             int iteration) {
    double film_temperature = (surface_temperature + input.ambient_temperature) / 2.0;
    AirProperties ap        = computeAirProperties(film_temperature);

    // Convection and radiation directly on bare pipe outer surface
    double re  = reynoldsNumber(input.pipe_diameter, input.wind_velocity, ap.kinematic_viscosity);
    double ra  = rayleighNumber(ap.expansion_coefficient, surface_temperature,
                                input.ambient_temperature, input.pipe_diameter,
                                ap.kinematic_viscosity, ap.alpha);
    double h_rad     = radiativeHeatTransferCoefficient(input.pipe_emissivity,
                                                        surface_temperature,
                                                        input.ambient_temperature);
    double nu_forced = nusseltForcedConvection(re, ap.prandtl);
    double nu_free   = nusseltFreeConvection(ra, ap.prandtl);
    double nu        = nusseltNumber(nu_forced, nu_free);
    double h_conv    = convectiveHeatTransferCoefficient(nu, ap.conductivity, input.pipe_diameter);
    double h_air     = h_rad + h_conv;

    // Pipe wall resistance (no insulation layer)
    double k_pipe    = polyFit(input.pipe_material_coefficients, input.pipe_temperature);
    double r_pipe    = thermalResistance(input.pipe_diameter, input.pipe_diameter,
                                        inner_pipe_diameter, k_pipe);

    // Total resistance and heat flow
    double r_total      = r_pipe + (1.0 / h_air);
    double heat_flow    = (input.pipe_temperature - input.ambient_temperature) / r_total;

    // Update temperatures
    interface_temperature  = input.pipe_temperature - heat_flow * r_pipe;
    surface_temperature    = interface_temperature;
    double heat_length_new = heat_flow * physics::kPi * input.pipe_diameter;

    if (std::fabs(heat_length_new - heat_length) < 0.0001)
        return (heat_length + heat_length_new) / 2.0;
    if (iteration > 30)
        throw std::string("ERROR : Pipe, No Insulation - recursion limit exceeded");

    return bareIteration(input, inner_pipe_diameter, insulation_outer_diameter,
                         surface_temperature, interface_temperature,
                         heat_length_new, iteration + 1);
}

// ── Public API ───────────────────────────────────────────────────────────────

InsulatedPipeOutput calculate(const InsulatedPipeInput& input) {
    validateInput(input);
    if (input.insulation_thickness <= 0)
        return bareInsulatedPipeHeatLoss(input);
    return insulatedPipeHeatLoss(input);
}

InsulatedPipeOutput insulatedPipeHeatLoss(const InsulatedPipeInput& input) {
    double inner_pipe_diameter       = input.pipe_diameter - input.pipe_thickness;
    double insulation_outer_diameter = input.pipe_diameter + (2.0 * input.insulation_thickness);
    double surface_temperature       = input.ambient_temperature + 1.0;
    double interface_temperature     = input.pipe_temperature - 1.0;

    double heat_length = insulatedIteration(input, inner_pipe_diameter, insulation_outer_diameter,
                                             surface_temperature, interface_temperature, 0.0, 0);
    double annual_heat_loss = heat_length * input.pipe_length
                            * input.operating_hours / input.system_efficiency;
    return {heat_length, annual_heat_loss};
}

InsulatedPipeOutput bareInsulatedPipeHeatLoss(const InsulatedPipeInput& input) {
    double inner_pipe_diameter       = input.pipe_diameter - input.pipe_thickness;
    double insulation_outer_diameter = input.pipe_diameter + (2.0 * input.insulation_thickness);
    double surface_temperature       = input.ambient_temperature + 1.0;
    double interface_temperature     = input.pipe_temperature - 1.0;

    double heat_length = bareIteration(input, inner_pipe_diameter, insulation_outer_diameter,
                                        surface_temperature, interface_temperature, 0.0, 0);
    double annual_heat_loss = heat_length * input.pipe_length
                            * input.operating_hours / input.system_efficiency;
    return {heat_length, annual_heat_loss};
}

double thermalResistance(double diameter_a, double diameter_b, double diameter_c,
                         double thermal_conductivity) {
    return diameter_a * std::log(diameter_b / diameter_c) / (2.0 * thermal_conductivity);
}

double reynoldsNumber(double diameter, double wind_velocity, double kinematic_viscosity) {
    return diameter * wind_velocity / kinematic_viscosity;
}

double rayleighNumber(double expansion_coefficient, double surface_temperature,
                      double ambient_temperature, double diameter,
                      double kinematic_viscosity, double alpha) {
    constexpr double g    = 9.81;
    double delta_t        = std::fabs(surface_temperature - ambient_temperature);
    double d_cubed        = std::pow(diameter, 3);
    return g * expansion_coefficient * delta_t * d_cubed / (kinematic_viscosity * alpha);
}

double nusseltNumber(double nusselt_forced, double nusselt_free) {
    return std::pow(std::pow(nusselt_forced, 4) + std::pow(nusselt_free, 4), 0.25);
}

double nusseltForcedConvection(double reynolds, double prandtl) {
    double term1 = 0.62 * std::pow(reynolds, 0.5) * std::pow(prandtl, 1.0 / 3.0);
    double term2 = std::pow(1.0 + std::pow(reynolds / 282000.0, 5.0 / 8.0), 4.0 / 5.0);
    double term3 = std::pow(1.0 + std::pow(0.4 / prandtl, 2.0 / 3.0), 0.25);
    return 0.3 + term1 * term2 / term3;
}

double nusseltFreeConvection(double rayleigh, double prandtl) {
    double inner = 0.387 * std::pow(rayleigh, 1.0 / 6.0)
                 / std::pow(1.0 + std::pow(0.559 / prandtl, 9.0 / 16.0), 8.0 / 27.0);
    return std::pow(0.6 + inner, 2);
}

double radiativeHeatTransferCoefficient(double emissivity, double surface_temperature,
                                        double ambient_temperature) {
    return physics::si::kStefanBoltzmann * emissivity
         * (std::pow(surface_temperature, 4) - std::pow(ambient_temperature, 4))
         / (surface_temperature - ambient_temperature);
}

double convectiveHeatTransferCoefficient(double nusselt, double air_conductivity, double diameter) {
    return nusselt * air_conductivity / diameter;
}

} // namespace insulated_pipe_reduction
