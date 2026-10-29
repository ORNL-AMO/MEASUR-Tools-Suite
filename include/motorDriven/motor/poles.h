#pragma once

/**
 * @ingroup poles_calculator
 * @file poles.h
 * @brief Declares motor pole-count classification from operating speed and line frequency.
 * @details The calculation maps measured motor speed to the supported even pole counts for
 *          50 Hz and 60 Hz motors while preserving the established fallback behavior.
 * @see @ref poles_calculator for formulas, speed bands, and assumptions.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup poles_calculator
 * @namespace poles
 * @brief Classifies an AC motor's pole count from its operating speed and line frequency.
 */
namespace poles {

/**
 * @brief Calculates the motor pole count.
 * @param[in] motor_rpm Measured motor operating speed @unitb{\revolutionsPerMinute}. Must be positive.
 * @param[in] line_frequency Motor supply frequency @unitb{\hertz}.
 * @return Motor pole count @unitb{\unitless}.
 */
int calculate(double motor_rpm, Motor::LineFrequency line_frequency);

} // namespace poles
