#pragma once

/**
 * @ingroup motor_power_calculator
 * @file motor_power.h
 * @brief Declares a stateless calculation of three-phase motor electrical input power.
 * @see @ref motor_power_calculator for the engineering relationship, units, and limits.
 */

/**
 * @ingroup motor_power_calculator
 * @namespace motor_power
 * @brief Calculates motor real electrical input power from line voltage, current, and power factor.
 */
namespace motor_power {

/**
 * @brief Calculates real electrical input power for balanced sinusoidal three-phase conditions.
 * @details Uses the supplied voltage directly, without an efficiency adjustment or input validation.
 * Physical consuming-motor inputs are nonnegative voltage/current and power factor from 0 to 1.
 * Signed and out-of-range values retain their arithmetic result; no clamping is performed.
 * @param[in] rated_voltage RMS line-to-line motor voltage @unitb{\volt}; use the voltage appropriate
 * to the operating point, which may differ from the nameplate rating.
 * @param[in] motor_current RMS motor line current @unitb{\ampere}.
 * @param[in] power_factor Real-to-apparent power ratio @unitb{\unitless}, expressed as a fraction.
 * @return Real electrical input power @unitb{\kilo\watt}; distinct from motor shaft power.
 * @see @ref motor_power_calculator
 */
double calculate(double rated_voltage, double motor_current, double power_factor);

} // namespace motor_power
