#pragma once

/**
 * @ingroup motor_power_factor_calculator
 * @file motor_power_factor.h
 * @brief Declares the stateless motor power-factor calculation.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup motor_power_factor_calculator
 * @namespace motor_power_factor
 * @brief Estimates fractional motor power factor from real and apparent electrical power.
 */
namespace motor_power_factor {

/** @brief Complete motor model and operating inputs; no defaults are applied. */
struct Input {
    Motor::LineFrequency line_frequency;      ///< Nominal line frequency; used only near zero load.
    double motor_rpm;                         ///< Motor speed @unitb{\revolution\per\minute}; used only near zero load.
    Motor::EfficiencyClass efficiency_class;  ///< Efficiency model selection; used only near zero load.
    double specified_efficiency;              ///< Specified efficiency fraction @unitb{\unitless}; model input near zero load.
    double motor_rated_power;                 ///< Rated shaft power @unitb{\horsepower}.
    double load_factor;                       ///< Fraction of rated shaft load @unitb{\unitless}.
    double motor_current;                     ///< Motor line current @unitb{\ampere}.
    double motor_efficiency;                  ///< Operating efficiency fraction @unitb{\unitless}; ignored near zero load.
    double rated_voltage;                     ///< Supplied line-to-line voltage @unitb{\volt}; ignored near zero load.
};

/**
 * @brief Calculates the real-to-apparent electrical power ratio as a fraction.
 * @details For abs(load_factor) < 0.001, uses modeled zero-load loss and a retained fixed
 * 460 V apparent-power denominator. Otherwise uses supplied load, efficiency and voltage.
 * Inputs are unvalidated; signed, unclamped and nonfinite arithmetic results are retained.
 * The near-zero efficiency model requires valid motor characteristics, including 2/4/6 poles
 * for PREMIUM and positive specified efficiency for a physically meaningful SPECIFIED result.
 * @param[in] input Complete motor and operating data; not modified.
 * @return Motor power factor as a dimensionless fraction, not percentage points.
 * @throws std::runtime_error In the near-zero branch when SPECIFIED has negative specified efficiency,
 * as propagated from the motor-efficiency model.
 * @see @ref motor_power_factor_calculator
 */
double calculate(const Input& input);

} // namespace motor_power_factor
