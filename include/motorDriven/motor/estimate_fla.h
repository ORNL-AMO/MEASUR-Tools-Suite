#pragma once

/**
 * @ingroup estimate_fla_calculator
 * @file estimate_fla.h
 * @brief Declares the stateless estimated full-load-current calculation.
 */

#include <array>

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup estimate_fla_calculator
 * @namespace estimate_fla
 * @brief Estimates motor full-load current and retained partial-load current anchors.
 */
namespace estimate_fla {

/** @brief Inputs used to estimate full-load motor current. */
struct Input {
    double motor_rated_power;                 ///< Motor nameplate power @unitb{\horsepower}.
    double motor_rpm;                         ///< Motor nameplate speed @unitb{\revolution\per\minute}.
    Motor::LineFrequency line_frequency;      ///< Nominal electrical line-frequency selection.
    Motor::EfficiencyClass efficiency_class;  ///< Motor efficiency-class selection.
    double specified_efficiency;              ///< Specified efficiency @unitb{\unitless}.
    double rated_voltage;                     ///< Motor nameplate voltage @unitb{\volt}.
};

/** @brief Estimated motor current results. */
struct Result {
    double estimated_fla;  ///< Estimated full-load current @unitb{\ampere}.
    /**
     * Retained partial-load current anchors @unitb{\ampere}, ordered as 0, 25, 50, 75, 100, and 125 percent load.
     * These retain the legacy coefficient-curve values before the full-load voltage and specified-efficiency adjustment.
     */
    std::array<double, 6> partial_load_currents;
};

/**
 * @brief Estimates full-load motor current and six partial-load current anchors.
 * @param[in] input Motor nameplate and efficiency-class inputs.
 * @return Estimated full-load current and retained partial-load current anchors.
 */
Result calculate(const Input& input);

} // namespace estimate_fla
