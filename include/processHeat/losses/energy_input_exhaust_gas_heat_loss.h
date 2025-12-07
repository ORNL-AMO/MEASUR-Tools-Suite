

#pragma once

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @file energy_input_exhaust_gas_heat_loss.h
 * @authors Autumn Ferree, Preston Shires, Mark Root
 *
 * @copybrief energy_input_exhaust_gas_heat_loss
 */

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @namespace energy_input_exhaust_gas_heat_loss
 * @copybrief energy_input_exhaust_gas_heat_loss_calculator
 */
namespace energy_input_exhaust_gas_heat_loss {

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @brief Calculates available heat for a non-EAF electric furnace.
 * @details Computes the available heat percentage based on excess air, combustion air temperature, exhaust gas
 * temperature, and total heat input. If total heat input is zero, available heat is set to 100%.
 * @param[in] excess_air Excess air as percent @unitb{\percent}
 * @param[in] combustion_air_temp Temperature of combustion air @unitb{\degreeFahrenheit}
 * @param[in] exhaust_gas_temp Temperature of exhaust gas @unitb{\degreeFahrenheit}
 * @param[in] total_heat_input Total heat input from all sources @unitb{\btu\per\hour}. If zero, available heat is 100%.
 * @return Available heat percent @unitb{\percent}
 * @see energy_input_exhaust_gas_heat_loss_formula
 */
double availableHeat(double excess_air, double combustion_air_temp, double exhaust_gas_temp,
                     double total_heat_input = 1);

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @brief Calculates heat delivered for a non-EAF electric furnace.
 * @details Computes the heat delivered to the furnace based on available heat percentage and total heat input.
 * @param[in] available_heat Available heat percent @unitb{\percent}
 * @param[in] total_heat_input Total heat input from all sources @unitb{\btu\per\hour}
 * @return Heat delivered @unitb{\btu\per\hour}
 * @see energy_input_exhaust_gas_heat_loss_formula
 */
double heatDelivered(double available_heat, double total_heat_input);

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @brief Calculates exhaust gas losses for a non-EAF electric furnace.
 * @details Computes the exhaust gas losses based on heat delivered and available heat percentage.
 * @param[in] heat_delivered Heat delivered @unitb{\btu\per\hour}
 * @param[in] available_heat Available heat percent @unitb{\percent}
 * @return Exhaust gas losses @unitb{\btu\per\hour}
 * @see energy_input_exhaust_gas_heat_loss_formula
 */
double totalHeatLoss(double heat_delivered, double available_heat);

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @struct EnergyInputExhaustGasResult
 * @brief Result struct for energy input exhaust gas heat loss calculations.
 * @details Holds the results for available heat, heat delivered, and exhaust gas losses as computed by
 *          @ref energy_input_exhaust_gas_heat_loss::calculate.
 */
struct EnergyInputExhaustGasResult {
    double available_heat;        ///< Available heat percent @unitb{\percent}
    double heat_delivered;        ///< Heat delivered @unitb{\btu\per\hour}
    double exhaust_gas_losses;    ///< Exhaust gas losses @unitb{\btu\per\hour}
};

/**
 * @ingroup energy_input_exhaust_gas_heat_loss_calculator
 * @brief Calculates available heat, heat delivered, and exhaust gas losses for a non-EAF electric furnace.
 * @details Computes all three quantities and returns them as a tuple.
 * @param[in] excess_air Excess air as percent @unitb{\percent}
 * @param[in] combustion_air_temp Temperature of combustion air @unitb{\degreeFahrenheit}
 * @param[in] exhaust_gas_temp Temperature of exhaust gas @unitb{\degreeFahrenheit}
 * @param[in] total_heat_input Total heat input from all sources @unitb{\btu\per\hour}. If zero, available heat is 100%.
 * @return EnergyInputExhaustGasResult struct containing: available_heat @unitb{\percent}, heat_delivered @unitb{\btu\per\hour}, and exhaust_gas_losses @unitb{\btu\per\hour}
 * @see energy_input_exhaust_gas_heat_loss_formula
 */
EnergyInputExhaustGasResult calculate(double excess_air, double combustion_air_temp, double exhaust_gas_temp,
                                            double total_heat_input = 1);

} // namespace energy_input_exhaust_gas_heat_loss
