
#pragma once

/**
 * @ingroup liquid_cooling_heat_loss_calculator
 * @file liquid_cooling_heat_loss.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief liquid_cooling_heat_loss
 */

/**
 * @ingroup liquid_cooling_heat_loss_calculator
 * @namespace liquid_cooling_heat_loss
 * @copybrief liquid_cooling_heat_loss_calculator
 */
namespace liquid_cooling_heat_loss {

/**
 * @ingroup liquid_cooling_heat_loss_calculator
 * @brief Calculates the total heat loss due to liquid cooling in process heating equipment.
 * @details This function computes the heat loss removed by a cooling liquid, based on flow rate, liquid density, initial temperature, outlet temperature, specific heat, and a correction factor. The calculation assumes no phase change and uses sensible heat only.
 * @param[in] flow_rate Cooling liquid flow rate @unitb{\gallon\per\minute}
 * @param[in] density Liquid density @unitb{\pound\per\cubic\foot}
 * @param[in] initial_temperature Initial/inlet liquid temperature @unitb{\degreeFahrenheit}
 * @param[in] outlet_temperature Outlet liquid temperature @unitb{\degreeFahrenheit}
 * @param[in] specific_heat Specific heat of liquid @unitb{\btu\per\pound\per\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - liquid_cooling_heat_loss_formula
 */
double totalHeatLoss(double flow_rate, double density, double initial_temperature, double outlet_temperature, double specific_heat, double correction_factor);

} // namespace liquid_cooling_heat_loss
