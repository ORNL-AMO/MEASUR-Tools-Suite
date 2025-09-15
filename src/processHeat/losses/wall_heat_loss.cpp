#include "processHeat/losses/wall_heat_loss.h"

#include <cmath>

#include "physics/constants.h"

namespace wall_heat_loss {

double totalHeatLoss(double surface_area, double ambient_temperature, double surface_temperature, double wind_speed,
                     double surface_emissivity, double shape_factor, double correction_factor) {

    // Calculate convective heat loss
    const double convective_loss =
        convectiveHeatLoss(shape_factor, wind_speed, surface_area, surface_temperature, ambient_temperature);

    // Calculate radiative heat loss
    const double radiative_loss =
        radiativeHeatLoss(surface_emissivity, surface_area, surface_temperature, ambient_temperature);

    // Total heat loss is the sum of convective and radiative losses, adjusted by the correction factor
    return (convective_loss + radiative_loss) * correction_factor;
}

double convectiveHeatLoss(double shape_factor, double wind_speed, double surface_area, double surface_temperature,
                          double ambient_temperature) {
    using namespace physics::conversions;

    // Empirical constants (unit-sensitive)
    constexpr double kConvectionExponent      = 0.2;
    constexpr double kMeanTempExponent        = 0.181;
    constexpr double kDeltaTempExponent       = 0.266;
    constexpr double kWindVelocityCoefficient = 1.277;

    const double duty_factor = std::pow((1.0 / kHoursPerDay), kConvectionExponent);

    const double delta_temperature = surface_temperature - ambient_temperature;
    const double mean_temperature  = 0.5 * (surface_temperature + ambient_temperature);

    const double delta_temperature_factor = std::pow(delta_temperature, kDeltaTempExponent);
    const double mean_temperature_factor  = std::pow((1.0 / mean_temperature), kMeanTempExponent);

    const double wind_factor = std::sqrt(1.0 + (kWindVelocityCoefficient * wind_speed));

    const double convection_coefficient =
        shape_factor * duty_factor * delta_temperature_factor * mean_temperature_factor * wind_factor;

    const double convective_heat_loss = convection_coefficient * surface_area * delta_temperature;

    return convective_heat_loss;
}

double radiativeHeatLoss(double surface_emissivity, double surface_area, double surface_temperature,
                         double ambient_temperature) {
    using namespace physics::us;
    using namespace physics::conversions;

    // Difference of fourth powers of surface and ambient absolute temperatures (Rankine)
    const double t4_difference = std::pow(fahrenheitToRankine(surface_temperature), 4.0) -
                                 std::pow(fahrenheitToRankine(ambient_temperature), 4.0);

    // Stefan-Boltzmann law for radiative heat transfer
    const double radiative_heat_loss = surface_area * surface_emissivity * kStefanBoltzmann * t4_difference;

    return radiative_heat_loss;
}

} // namespace wall_heat_loss
