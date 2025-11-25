#include "processHeat/losses/leakage_heat_loss.h"
#include <cmath>

namespace leakage_heat_loss {

// Calculates total heat loss from hot gas leakage
double totalHeatLoss(double draft_pressure, double opening_area, double leakage_gas_temperature, double ambient_temperature,
                     double coefficient_discharge, double specific_gravity, double correction_factor) {
    // Constants for algorithm
    constexpr double kSquareInchesPerSquareFoot = 144.0; ///< Conversion factor: 1 ft^2 = 144 in^2
    constexpr double kVolumetricFlowFactor = 1655.0;     ///< Empirical factor for volumetric flow (cfh)
    constexpr double kStandardTempNumerator = 520.0;     ///< Standard temperature numerator (R)
    constexpr double kStandardTempOffset = 460.0;        ///< Standard temperature offset (R)
    constexpr double kSpecificHeatCoeffA = 0.2371;       ///< Specific heat polynomial coefficient A
    constexpr double kSpecificHeatCoeffB = 9e-6;         ///< Specific heat polynomial coefficient B
    constexpr double kSpecificHeatCoeffC = 7e-8;         ///< Specific heat polynomial coefficient C
    constexpr double kSpecificHeatCoeffD = 3e-11;        ///< Specific heat polynomial coefficient D
    constexpr double kCubicFootConversion = 0.0793;      ///< Conversion factor to specific heat per cubic foot

    // Apply correction_factor to coefficient as in the header API
    double adjusted_coefficient = coefficient_discharge * correction_factor;

    // Calculate volumetric flow rate (cubic feet per hour)
    const double opening_area_square_inches = opening_area * kSquareInchesPerSquareFoot;
    const double volumetric_flow_cfh = kVolumetricFlowFactor * adjusted_coefficient * opening_area_square_inches * std::pow(draft_pressure / specific_gravity, 0.5);

    // Convert to standard cubic feet per hour
    const double standard_volumetric_flow_scfh = volumetric_flow_cfh * std::pow(kStandardTempNumerator / (kStandardTempOffset + leakage_gas_temperature), 0.5);

    // Calculate average temperature for specific heat
    const double average_temperature = (ambient_temperature + leakage_gas_temperature) / 2.0;
    const double specific_heat_gas = kSpecificHeatCoeffA
        - (kSpecificHeatCoeffB * average_temperature)
        + (kSpecificHeatCoeffC * average_temperature * average_temperature)
        - (kSpecificHeatCoeffD * std::pow(average_temperature, 3));
    const double specific_heat_per_cubic_foot = kCubicFootConversion * specific_heat_gas;

    // Calculate total heat loss
    double heat_loss_btu_per_hour = specific_heat_per_cubic_foot * standard_volumetric_flow_scfh * (leakage_gas_temperature - ambient_temperature);
    return heat_loss_btu_per_hour;
}

} // namespace leakage_heat_loss