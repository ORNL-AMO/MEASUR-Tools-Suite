#pragma once

/**
 * @ingroup optimal_motor_power_calculator
 * @file optimal_motor_power.h
 * @brief Declares electrical operating-point estimation for a required motor shaft output.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup optimal_motor_power_calculator
 * @namespace optimal_motor_power
 * @brief Stateless electrical demand estimation for a supplied shaft-power requirement.
 */
namespace optimal_motor_power {

/** @brief Complete required motor nameplate and proposed operating data. */
struct Input {
    double motor_rated_power;                 ///< Nameplate shaft power @unitb{\horsepower}.
    double motor_rpm;                         ///< Nameplate speed @unitb{\revolution\per\minute}.
    Motor::LineFrequency line_frequency;      ///< Nominal electrical line-frequency selection.
    Motor::EfficiencyClass efficiency_class;  ///< Efficiency model; PREMIUM current model supports 2/4/6 poles.
    double specified_efficiency;              ///< Efficiency fraction @unitb{\unitless}; used for SPECIFIED only.
    double rated_voltage;                     ///< Nameplate line-to-line voltage @unitb{\volt}.
    double field_voltage;                     ///< Operating line-to-line voltage @unitb{\volt}.
    double optimal_motor_shaft_power;         ///< Required mechanical motor output @unitb{\horsepower}.
};

/** @brief Estimated electrical operating point; plain values requiring no cleanup. */
struct Result {
    double power;         ///< Real electrical input @unitb{\kilo\watt}.
    double efficiency;    ///< Mechanical-output to real-input efficiency fraction @unitb{\unitless}.
    double current;       ///< Operating line current @unitb{\ampere}.
    double power_factor;  ///< Real-to-apparent electrical power ratio @unitb{\unitless}.
    double load_factor;   ///< Interpolated fraction of rated shaft load @unitb{\unitless}.
};

/**
 * @brief Estimates electrical demand for a supplied mechanical shaft-power requirement.
 * @details Retains the empirical 1% load search, voltage adjustments and interpolation.
 * Search starts at zero and ends on strict shaft-power exceedance or load greater than 1.5;
 * the result may extrapolate beyond the search range. No numerical validation, defaults or
 * clamping are applied; degenerate inputs retain nonfinite arithmetic and dependency errors.
 * "Optimal" describes the supplied requirement, not a motor-sizing or optimization procedure.
 * @param[in] input Complete motor and operating data; units documented per member; not modified.
 * @return Electrical input in kW, current in A, and dimensionless efficiency, power factor and load.
 * @see @ref optimal_motor_power_calculator for formulas, worked example and model limits.
 */
Result calculate(const Input& input);

} // namespace optimal_motor_power
