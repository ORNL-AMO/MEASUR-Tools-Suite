#pragma once
/**
 * @ingroup atmosphere_heat_loss_calculator
 * @file atmosphere_heat_loss.h
 * @authors Gina Accawi, Liam White
 *
 * @copybrief atmosphere_heat_loss
 */

#include <array>
#include <string>
#include <vector>

/**
 * @ingroup atmosphere_heat_loss_calculator
 * @namespace atmosphere_heat_loss
 * @copybrief atmosphere_heat_loss_calculator
 */
namespace atmosphere_heat_loss {

/**
 * @ingroup atmosphere_heat_loss_calculator
 * @struct GasType
 * @brief Represents a gas type and its associated specific heat at a reference temperature of
 * @qty{60;\degreeFahrenheit}.
 * @see specific_heat_values
 */
struct GasType {
    std::string gas_description; ///< Description of the gas type.
    double      specific_heat;   ///< Specific heat @unitb{\btu\per\standardCubicFeet\degreeFahrenheit}.
};

/**
 * @ingroup atmosphere_heat_loss_calculator
 * @brief A collection of specific heat values for common atmospheric gases at a reference temperature of
 * @qty{60;\degreeFahrenheit}.
 * @see specific_heat_values
 */
inline const std::array<GasType, 6> kGasTypes {{
    {"Nitrogen", 0.0185},
    {"Hydrogen", 0.0182},
    {"Exothermic Gas", 0.0185},
    {"Endothermic Gas", 0.0185},
    {"Air", 0.0184},
    {"Water Vapor", 0.0212},
}};

/**
 * @ingroup atmosphere_heat_loss_calculator
 * @brief Returns the predefined specific heat values for common atmospheric gases at a reference temperature of
 * @qty{60;\degreeFahrenheit}.
 * @return A vector of GasType structs containing gas descriptions and their associated specific heat values.
 * @see specific_heat_values
 */
inline const std::vector<GasType>& gasTypes() {
    static const std::vector<GasType> gas_types_vector(kGasTypes.begin(), kGasTypes.end());
    return gas_types_vector;
}

/**
 * @ingroup atmosphere_heat_loss_calculator
 * @brief Calculates the total heat loss from escaping atmospheric gas.
 * @param[in] flow_rate Flow rate of gas @unitb{\standardCubicFeet\per\hour}
 * @param[in] specific_heat Specific heat of gas @unitb{\btu\per\standardCubicFeet\degreeFahrenheit}
 * @param[in] inlet_temperature %Inlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] outlet_temperature Outlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - atmosphere_total_heat_loss_formula
 * - specific_heat_values
 */
double totalHeatLoss(double flow_rate, double specific_heat, double inlet_temperature, double outlet_temperature,
                     double correction_factor);

} // namespace atmosphere_heat_loss