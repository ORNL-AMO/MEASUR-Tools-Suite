#include "treasureHunt/insulated_tank_reduction.h"

#include <array>
#include <cmath>
#include <string>

#include "physics/constants.h"

namespace insulated_tank_reduction {

// ── Air property polynomial coefficients (T^4 … T^0) ────────────────────────
// Each array holds 5 coefficients for a 4th-order polynomial fit of the named
// air property as a function of temperature (°R, U.S. customary units).
static constexpr std::array<double, 5> kAirSpecificHeatCoeffs = {
    -1.82109557e-14,  5.27958269e-11, -3.22287031e-8,  8.06185737e-6,  2.38303755e-1
};
static constexpr std::array<double, 5> kAirDensityCoeffs = {
     5.53240532e-12, -2.97098117e-8,   5.96315645e-5, -5.57665211e-2,  2.43046430e1
};
static constexpr std::array<double, 5> kAirKinViscosityCoeffs = {
    -6.67800412e-13,  2.42855319e-9,   7.21312269e-8,  3.56111381e-3, -5.82727939e-1
};
static constexpr std::array<double, 5> kAirThermalCondCoeffs = {
    -1.63898601e-15,  7.98394765e-12, -1.80852621e-8,  3.85957991e-5, -1.49489778e-3
};

// Assumed inner-surface natural convection coefficient for tank contents.
static constexpr double kInnerConvectionCoeff = 10.0;

// Empirical correlation coefficient for turbulent natural convection from a vertical surface.
static constexpr double kNaturalConvectionCorrelation = 0.125;

// ── Internal helpers ─────────────────────────────────────────────────────────

static void validateInput(const InsulatedTankInput& input) {
    if (input.tank_emissivity < 0.0 || input.tank_emissivity > 1.0) {
        throw std::string("ERROR : Tank - tank emissivity out of acceptable range");
    }
    if (input.jacket_emissivity < 0.0 || input.jacket_emissivity > 1.0) {
        throw std::string("ERROR : Tank - jacket emissivity out of acceptable range");
    }
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

// Bundles air properties evaluated at a given temperature.
struct AirProperties {
    double conductivity;
    double density;
    double kin_viscosity;
    double specific_heat;
};

static AirProperties computeAirProperties(double temp) {
    return {
        polyFit(kAirThermalCondCoeffs,  temp),
        polyFit(kAirDensityCoeffs,      temp) * 1e-2,
        polyFit(kAirKinViscosityCoeffs, temp) * 1e-4 / 3600.0,
        polyFit(kAirSpecificHeatCoeffs, temp),
    };
}

// ── Public API ───────────────────────────────────────────────────────────────

double rayleighNumber(double thermal_expansion, double surface_temperature,
                      double ambient_temperature, double diameter,
                      double kin_viscosity, double thermal_diffusivity) {
    double delta_t = std::fabs(surface_temperature - ambient_temperature);
    double d_cubed = std::pow(diameter, 3);
    return (physics::us::kGravityFtPerSec2 * thermal_expansion * delta_t * d_cubed)
         / (kin_viscosity * thermal_diffusivity);
}

double naturalConvectionCoefficient(double rayleigh, double conductivity, double diameter) {
    return kNaturalConvectionCorrelation * std::pow(rayleigh, 1.0 / 3.0)
         * conductivity / diameter;
}

InsulatedTankOutput insulatedTankHeatLoss(const InsulatedTankInput& input) {
    AirProperties ap           = computeAirProperties(input.ambient_temperature);
    double thermal_diffusivity = ap.conductivity / (ap.density * ap.specific_heat) / 3600.0;
    double thermal_expansion   = 1.0 / input.ambient_temperature;

    double ra    = rayleighNumber(thermal_expansion, input.surface_temperature,
                                  input.ambient_temperature, input.tank_diameter,
                                  ap.kin_viscosity, thermal_diffusivity);
    double h_nat = naturalConvectionCoefficient(ra, ap.conductivity, input.tank_diameter);

    double r_inner     = input.tank_diameter / 2.0;
    double r_outer_tank = r_inner + input.tank_thickness;
    double r_outer_ins  = r_outer_tank + input.insulation_thickness;
    double tank_area    = input.tank_diameter * input.tank_height * physics::kPi;

    double overall_coeff =
        1.0 /
        (r_inner / r_outer_ins  * 1.0 / h_nat
         + r_inner / input.insulation_conductivity * std::log(r_outer_ins  / r_outer_tank)
         + r_inner / input.tank_conductivity       * std::log(r_outer_tank / r_inner)
         + 1.0 / kInnerConvectionCoeff);

    double delta_t        = input.surface_temperature - input.ambient_temperature;
    double conv_cond_loss = overall_coeff * tank_area * delta_t / 1e5;
    double rad_loss       = physics::us::kStefanBoltzmann * input.jacket_emissivity
                          * (std::pow(input.surface_temperature, 4) - std::pow(input.ambient_temperature, 4))
                          / 1e5;
    double heat_loss        = conv_cond_loss + rad_loss;
    double annual_heat_loss = (heat_loss * static_cast<double>(input.operating_hours) / 10.0)
                            / input.system_efficiency;
    return {heat_loss, annual_heat_loss};
}

InsulatedTankOutput bareTankHeatLoss(const InsulatedTankInput& input) {
    AirProperties ap           = computeAirProperties(input.ambient_temperature);
    double thermal_diffusivity = ap.conductivity / (ap.density * ap.specific_heat) / 3600.0;
    double thermal_expansion   = 1.0 / input.ambient_temperature;

    double ra    = rayleighNumber(thermal_expansion, input.tank_temperature,
                                  input.ambient_temperature, input.tank_diameter,
                                  ap.kin_viscosity, thermal_diffusivity);
    double h_nat = naturalConvectionCoefficient(ra, ap.conductivity, input.tank_diameter);

    double r_inner      = input.tank_diameter / 2.0;
    double r_outer_tank = r_inner + input.tank_thickness;
    double tank_area    = input.tank_diameter * input.tank_height * physics::kPi;

    double overall_coeff =
        1.0 /
        (r_inner / r_outer_tank * 1.0 / h_nat
         + r_inner / input.tank_conductivity * std::log(r_outer_tank / r_inner)
         + 1.0 / kInnerConvectionCoeff);

    double delta_t        = input.tank_temperature - input.ambient_temperature;
    double conv_cond_loss = overall_coeff * tank_area * delta_t / 1e5;
    double rad_loss       = physics::us::kStefanBoltzmann * input.tank_emissivity
                          * (std::pow(input.tank_temperature, 4) - std::pow(input.ambient_temperature, 4))
                          / 1e5;
    double heat_loss        = conv_cond_loss + rad_loss;
    double annual_heat_loss = (heat_loss * static_cast<double>(input.operating_hours) / 10.0)
                            / input.system_efficiency;
    return {heat_loss, annual_heat_loss};
}

InsulatedTankOutput calculate(const InsulatedTankInput& input) {
    validateInput(input);
    if (input.insulation_thickness <= 0.0) {
        return bareTankHeatLoss(input);
    }
    return insulatedTankHeatLoss(input);
}

} // namespace insulated_tank_reduction
