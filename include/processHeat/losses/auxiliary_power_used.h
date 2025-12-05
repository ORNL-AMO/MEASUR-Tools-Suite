
#pragma once

/**
 * @ingroup auxiliary_power_used_calculator
 * @file auxiliary_power_used.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief auxiliary_power_used
 */

/**
 * @ingroup auxiliary_power_used_calculator
 * @namespace auxiliary_power_used
 * @copybrief auxiliary_power_used_calculator
 */
namespace auxiliary_power_used {

/**
 * @ingroup auxiliary_power_used_calculator
 * @brief Calculates the auxiliary power used by electrical systems associated with process heating equipment.
 * @details This function computes the energy use of motors and other auxiliary systems using electricity, based on electrical parameters and operating time.
 * @param[in] motor_phase Motor phase @unitb{\unitless}
 * @param[in] supply_voltage Supply voltage @unitb{\volt}
 * @param[in] avg_current Average current @unitb{\ampere}
 * @param[in] power_factor Power factor @unitb{\unitless}
 * @param[in] operating_time Operating time (percent, 0-100) @unitb{\percent}
 * @return Auxiliary power used @unitb{\btu\per\hour}
 * @see auxiliary_power_used_formula
 */
double calculatePowerUsed(double motor_phase, double supply_voltage, double avg_current, double power_factor, double operating_time);

} // namespace auxiliary_power_used

