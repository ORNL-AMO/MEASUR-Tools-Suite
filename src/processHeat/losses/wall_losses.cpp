#include "processHeat/losses/wall_losses.h"

#include <cmath>

#include "physics/constants.h"

double WallLosses::convectiveHeatLoss() const {
    using namespace physics::conversions;

    // Empirical constants (unit-sensitive)
    constexpr double kConvectionExponent      = 0.2;
    constexpr double kMeanTempExponent        = 0.181;
    constexpr double kDeltaTempExponent       = 0.266;
    constexpr double kWindVelocityCoefficient = 1.277;

    const double duty_factor = std::pow((1.0 / kHoursPerDay), kConvectionExponent);

    const double delta_temperature = surface_temperature_ - ambient_temperature_;
    const double mean_temperature  = 0.5 * (surface_temperature_ + ambient_temperature_);

    const double delta_temperature_factor = std::pow(delta_temperature, kDeltaTempExponent);
    const double mean_temperature_factor  = std::pow((1.0 / mean_temperature), kMeanTempExponent);

    const double wind_factor = std::sqrt(1.0 + (kWindVelocityCoefficient * wind_speed_));

    const double convective_heat_loss =
        (shape_factor_ * duty_factor * delta_temperature_factor * mean_temperature_factor * wind_factor) *
        surface_area_ * delta_temperature;

    return convective_heat_loss;
}

double WallLosses::radiativeHeatLoss() const {
    using namespace physics::customary;
    using namespace physics::conversions;

    // Difference of fourth powers of surface and ambient absolute temperatures (Rankine)
    const double t4_difference = std::pow(fahrenheitToRankine(surface_temperature_), 4.0) -
                                 std::pow(fahrenheitToRankine(ambient_temperature_), 4.0);

    // Stefan-Boltzmann law for radiative heat transfer
    const double radiative_heat_loss = surface_area_ * surface_emissivity_ * kStefanBoltzmann * t4_difference;

    return radiative_heat_loss;
}

double WallLosses::totalHeatLoss() const { return (convectiveHeatLoss() + radiativeHeatLoss()) * correction_factor_; }