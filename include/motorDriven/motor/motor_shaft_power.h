#pragma once

/**
 * @ingroup motor_shaft_power_calculator
 * @file motor_shaft_power.h
 * @brief Declares motor shaft-power estimation from measured electrical power or current.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup motor_shaft_power_calculator
 * @namespace motor_shaft_power
 * @brief Stateless motor operating-point and mechanical shaft-power estimation.
 */
namespace motor_shaft_power {

/** @brief Complete required motor nameplate and measured operating data. */
struct Input {
    double motor_rated_power;                 ///< Nameplate shaft power @unitb{\horsepower}.
    double motor_measured_power;              ///< Measured real electrical input @unitb{\kilo\watt}; ignored in CURRENT mode.
    double motor_rpm;                         ///< Nameplate speed @unitb{\revolution\per\minute}.
    Motor::LineFrequency line_frequency;      ///< Nominal electrical line-frequency selection.
    Motor::EfficiencyClass efficiency_class;  ///< Efficiency model; current-model PREMIUM supports 2/4/6 poles.
    double specified_efficiency;              ///< Efficiency fraction @unitb{\unitless}; used for SPECIFIED only.
    double rated_voltage;                     ///< Nameplate line-to-line voltage @unitb{\volt}.
    double full_load_amps;                    ///< Supplied full-load current @unitb{\ampere}; zero is not an estimation sentinel.
    double field_voltage;                     ///< Measured operating line-to-line voltage @unitb{\volt}.
    Motor::LoadEstimationMethod load_estimation_method; ///< POWER selects measured kW; otherwise uses measured current.
    double field_current;                     ///< Measured line current @unitb{\ampere}; ignored in POWER mode.
};

/** @brief Estimated operating point; all members are plain values without cleanup. */
struct Result {
    double shaft_power;    ///< Mechanical motor output @unitb{\horsepower}.
    double current;        ///< Operating line current @unitb{\ampere}.
    double power_factor;   ///< Real-to-apparent electrical power ratio @unitb{\unitless}.
    double efficiency;     ///< Mechanical-output to real-input efficiency fraction @unitb{\unitless}.
    double power;          ///< Real electrical input @unitb{\kilo\watt}.
    double estimated_fla;  ///< Independently estimated full-load current @unitb{\ampere}, not the supplied FLA.
    double load_factor;    ///< Interpolated fraction of rated shaft load @unitb{\unitless}.
};

/**
 * @brief Estimates motor shaft power and the corresponding electrical operating point.
 * @details Retains the empirical 1% load search, interpolation, voltage corrections and dependency behavior.
 * POWER starts at 0.01 load; CURRENT starts at zero. Search ends on a strict measurement exceedance
 * or load greater than 1.5, but the interpolated result is not clamped to that search range.
 * Callers supply physically appropriate nameplate and measurement data; no numerical validation or
 * defaults are applied. Degenerate inputs retain nonfinite arithmetic and dependency exceptions.
 * @param[in] input Complete motor and operating data with units documented per member; not modified.
 * @return Shaft power in hp, electrical input in kW, current/estimated FLA in A, and fractional results.
 * @see @ref motor_shaft_power_calculator for formulas, worked examples and model limits.
 */
Result calculate(const Input& input);

} // namespace motor_shaft_power
