#pragma once

/**
 * @ingroup exhaust_gas_heat_loss_electric_arc_furnace_calculator
 * @file exhaust_gas_heat_loss_electric_arc_furnace.h
 * @authors Autumn Ferree, Mark Root
 *
 * @copybrief exhaust_gas_heat_loss_electric_arc_furnace
 */

/**
 * @ingroup exhaust_gas_heat_loss_electric_arc_furnace_calculator
 * @namespace exhaust_gas_heat_loss_electric_arc_furnace
 * @copybrief exhaust_gas_heat_loss_electric_arc_furnace_calculator
 */
namespace exhaust_gas_heat_loss_electric_arc_furnace {

/**
 * @ingroup exhaust_gas_heat_loss_electric_arc_furnace_calculator
 * @brief Calculates the total heat loss due to exhaust gases in an Electric Arc Furnace (EAF).
 * @details This function computes the heat loss caused by exhaust gases leaving the EAF, based on gas temperature, composition, flow rate, and dust loading.
 * @param[in] off_gas_temp Temperature of exhaust gases before mixing with outside air @unitb{\degreeFahrenheit}
 * @param[in] co_percent Percent of CO in exhaust gas @unitb{\percent}
 * @param[in] h2_percent Percent of H2 in exhaust gas @unitb{\percent}
 * @param[in] combustible_gases_percent Average percent of combustible gases in exhaust @unitb{\percent}
 * @param[in] volume_flow_rate Total volume of exhaust gases @unitb{\cubic\foot\per\minute}
 * @param[in] dust_loading Dust loading for exhaust gases @unitb{\pound\per\cubic\foot}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - exhaust_gas_heat_loss_electric_arc_furnace_formula
 */
double totalHeatLoss(double off_gas_temp, double co_percent, double h2_percent, double combustible_gases_percent,
                        double volume_flow_rate, double dust_loading);

} // namespace exhaust_gas_heat_loss_electric_arc_furnace
