#pragma once

/**
 * @ingroup motor_current_calculator
 * @file motor_current.h
 * @brief Declares stateless motor-current calculations at a selected fractional load.
 */

#include "motorDriven/motor/MotorData.h"

/**
 * @ingroup motor_current_calculator
 * @namespace motor_current
 * @brief Interpolates supplied-FLA-normalized or raw-model motor current.
 */
namespace motor_current {

/** @brief Required motor nameplate and load inputs shared by both current calculations. */
struct Input {
    double motor_rated_power;                 ///< Motor nameplate power @unitb{\horsepower}.
    double motor_rpm;                         ///< Motor nameplate speed @unitb{\revolution\per\minute}.
    Motor::LineFrequency line_frequency;      ///< Nominal electrical line-frequency selection.
    Motor::EfficiencyClass efficiency_class;  ///< Efficiency class; PREMIUM supports only 2-, 4-, or 6-pole motors.
    /** Efficiency fraction @unitb{\unitless}; positive for SPECIFIED, ignored otherwise. */
    double specified_efficiency;
    double load_factor;                       ///< Fraction of rated load @unitb{\unitless}; evaluation is capped above 1.5.
    double rated_voltage;                     ///< Motor nameplate voltage @unitb{\volt}; must be positive.
};

/** @brief Calculated current and the independently estimated full-load current. */
struct Result {
    double current;        ///< Current at the selected load, normalized to supplied FLA @unitb{\ampere}.
    double estimated_fla;  ///< EstimateFLA's full-load estimate @unitb{\ampere}, independent of supplied FLA.
};

/**
 * @brief Calculates motor current using anchors normalized to supplied full-load current.
 * @details Retains the empirical model and its unvalidated preconditions: positive rated voltage,
 * positive specified efficiency for SPECIFIED, and 2/4/6 poles for PREMIUM.
 * Loads above 1.5 evaluate at 1.5; negative loads retain lower-curve extrapolation.
 * @param[in] input Motor nameplate and fractional-load inputs; not modified.
 * @param[in] full_load_amps Supplied full-load current @unitb{\ampere}; zero produces zero current.
 * @return Selected-load current and independently estimated full-load current, both @unitb{\ampere}.
 * @see @ref motor_current_calculator
 */
Result calculate(const Input& input, double full_load_amps);

/**
 * @brief Calculates raw-model current for the optimal-motor calculation path.
 * @details Uses the unadjusted EstimateFLA anchors without supplied-FLA or voltage normalization.
 * Field-voltage adjustment is the consumer's responsibility. The same unvalidated model preconditions
 * and load evaluation boundaries as calculate() apply.
 * @param[in] input Motor nameplate and fractional-load inputs; not modified.
 * @return Raw-model selected-load current @unitb{\ampere}.
 * @see @ref motor_current_calculator
 */
double calculateOptimal(const Input& input);

} // namespace motor_current
