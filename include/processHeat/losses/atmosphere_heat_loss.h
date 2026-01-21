#pragma once
/**
 * @ingroup atmosphere_heat_loss_calculator
 * @file atmosphere_heat_loss.h
 * @authors Gina Accawi, Liam White
 *
 * @copybrief atmosphere_heat_loss
 */

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
 * @brief Calculates the total heat loss from escaping atmospheric gas.
 * @param[in] flow_rate Flow rate of gas @unitb{\standardCubicFeet\per\hour}
 * @param[in] specific_heat Specific heat of gas @unitb{\btu\per\standardCubicFeet\degreeFahrenheit}
 * @param[in] inlet_temperature %Inlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] outlet_temperature Outlet temperature of gas @unitb{\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 * @see
 * - atmosphere_heat_loss_formula
 * - atmosphere_specific_heat_values
 */
double totalHeatLoss(double flow_rate, double specific_heat, double inlet_temperature, double outlet_temperature,
                     double correction_factor);

} // namespace atmosphere_heat_loss