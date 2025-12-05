
#pragma once

/**
 * @ingroup gas_cooling_heat_loss_calculator
 * @file gas_cooling_heat_loss.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief gas_cooling_heat_loss
 */

/**
 * @ingroup gas_cooling_heat_loss_calculator
 * @namespace gas_cooling_heat_loss
 * @copybrief gas_cooling_heat_loss_calculator
 */
namespace gas_cooling_heat_loss {

/**
 * @ingroup gas_cooling_heat_loss_calculator
 * @brief Calculates the total heat loss due to gas (including air) cooling in process heating equipment.
 * @details This function computes the heat loss removed by a cooling gas, based on flow rate, initial temperature, final temperature, specific heat, correction factor, and gas density. The calculation assumes no phase change and uses sensible heat only.
 * @param[in] flow_rate Gas volumetric flow rate @unitb{\foot\cubed\per\minute}
 * @param[in] initial_temperature Inlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] final_temperature Outlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] specific_heat Specific heat of gas @unitb{\btu\per\scf\per\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @param[in] gas_density Gas density @unitb{\pound\per\foot\cubed}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - gas_cooling_heat_loss_formula
 */
double totalHeatLoss(double flow_rate, double initial_temperature, double final_temperature, double specific_heat, double correction_factor, double gas_density);

} // namespace gas_cooling_heat_loss
