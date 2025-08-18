/**
 * @file
 * @brief Contains the implementation of the wall leakage losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include <cmath>
#include "processHeat/losses/WallLosses.h"

/**
 * @brief Calculates the total heat loss from a wall due to convection and radiation.
 *
 * This function computes the heat loss from a wall surface to the environment, accounting for both
 * convective and radiative losses. The calculation uses the wall's surface area, temperatures, wind velocity,
 * surface emissivity, and correction/condition factors.
 *
 * @return double Total heat loss (BTU/hr or appropriate units based on input).
 */
double WallLosses::getHeatLoss() {
    // Constants
    constexpr double kStefanBoltzmannFtLb = 0.1713e-8; // Stefan-Boltzmann constant in BTU/(hr·ft²·°R⁴)
    constexpr double kHoursPerDay = 24.0;
    constexpr double kConvectionExponent = 0.2;
    constexpr double kTemperatureExponent = 0.181;
    constexpr double kDeltaTempExponent = 0.266;
    constexpr double kWindVelocityCoefficient = 1.277;

    // Convective heat loss calculation
    double wind_velocity_factor = 1.0 + (kWindVelocityCoefficient * windVelocity);
    double condition_factor_component = conditionFactor * std::pow((1.0 / kHoursPerDay), kConvectionExponent);
    double mean_temperature = (ambientTemperature + surfaceTemperature) / 2.0;
    double mean_temperature_component = std::pow((1.0 / mean_temperature), kTemperatureExponent);
    double delta_temperature = surfaceTemperature - ambientTemperature;
    double delta_temperature_component = std::pow(delta_temperature, kDeltaTempExponent);
    double wind_velocity_sqrt = std::sqrt(wind_velocity_factor);
    double convective_heat_loss = (condition_factor_component * mean_temperature_component * delta_temperature_component * wind_velocity_sqrt)
        * surfaceArea * delta_temperature;

    // Radiative heat loss calculation
    double surface_temp_rankine = surfaceTemperature + RAD_CONSTANT;
    double ambient_temp_rankine = ambientTemperature + RAD_CONSTANT;
    double surface_temp_rankine_4 = std::pow(surface_temp_rankine, 4.0);
    double ambient_temp_rankine_4 = std::pow(ambient_temp_rankine, 4.0);
    double radiative_heat_loss = surfaceEmissivity * kStefanBoltzmannFtLb * (surface_temp_rankine_4 - ambient_temp_rankine_4) * surfaceArea;

    // Total heat loss
    heatLoss = (convective_heat_loss + radiative_heat_loss) * correctionFactor;
    return heatLoss;
}