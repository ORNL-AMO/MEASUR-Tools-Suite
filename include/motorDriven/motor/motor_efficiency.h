#pragma once

/**
 * @ingroup motor_efficiency_calculator
 * @file motor_efficiency.h
 * @brief Declares the stateless motor-efficiency calculation.
 */

#include <stdexcept>

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup motor_efficiency_calculator
 * @namespace motor_efficiency
 * @brief Estimates motor efficiency from motor characteristics and operating load.
 */
namespace motor_efficiency {

/** Inputs for the motor-efficiency calculation. */
struct Input {
    Motor::LineFrequency line_frequency;      ///< Nominal electrical line frequency.
    double motor_rpm;                         ///< Measured motor speed @unitb{\revolutionsPerMinute}.
    Motor::EfficiencyClass efficiency_class;  ///< Motor efficiency classification.
    double motor_rated_power;                 ///< Rated motor power @unitb{\horsepower}.
    double load_factor;                       ///< Motor load as a dimensionless fraction.
    double specified_efficiency = -1.0;       ///< Specified motor efficiency as a dimensionless fraction.
};

/** Results from the motor-efficiency calculation. */
struct Result {
    double efficiency;            ///< Estimated motor efficiency as a dimensionless fraction.
    double zero_load_power_loss;  ///< Estimated electrical loss at zero load @unitb{\kilo\watt}.
};

/**
 * @brief Estimates motor efficiency at the requested load.
 * @param[in] input Motor characteristics and operating load.
 * @return Estimated efficiency and zero-load power loss.
 * @throws std::runtime_error When the specified efficiency class is selected without a nonnegative specified
 * efficiency.
 */
Result calculate(const Input& input);

} // namespace motor_efficiency
