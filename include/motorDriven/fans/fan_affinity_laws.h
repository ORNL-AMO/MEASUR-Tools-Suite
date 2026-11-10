#pragma once

/**
 * @ingroup fan_affinity_laws_calculator
 * @file fan_affinity_laws.h
 * @brief Stateless fan control and diameter-change energy calculations.
 * @details Desktop/callers own input validation; this module performs arithmetic without checks or clamping.
 * @see @ref fan_affinity_laws_calculator for equations, examples, and limits.
 */

/**
 * @ingroup fan_affinity_laws_calculator
 * @namespace fan_affinity_laws
 * @brief Estimates annual fan energy and savings from a delivered baseline power.
 */
namespace fan_affinity_laws {

/** @brief Fan motor control; None retains the uncontrolled diameter-change path. */
enum class MotorControlType {
    OnOff = 0,    ///< Full-speed operation while on.
    TwoSpeed = 1, ///< Full-speed, half-speed, and off time sharing.
    VSD = 2,      ///< Variable-speed control using the cubic flow law.
    None = 3      ///< No speed adjustment; control factor is one.
};

/** @brief Representation of the desired flow. */
enum class FlowMode {
    Percent = 0, ///< Percentage of the original fan's rated flow.
    Volume = 1   ///< Volume flow in the same units as rated flow.
};

/** @brief Complete caller-validated baseline and modification data; percentages use 0-100 values. */
struct Input {
    double electricity_cost;                     ///< Electricity rate @unitb{\dollar\per\kilowatt\hour}.
    double drive_efficiency;                     ///< Drive efficiency @unitb{\percent}, greater than zero and at most 100.
    double motor_efficiency;                     ///< Motor efficiency @unitb{\percent}, greater than zero and at most 100.
    double flow_percent_baseline;                ///< Baseline flow as percent of rated flow @unitb{\percent}; positive for VSD/Two-Speed.
    double operating_hours;                      ///< Annual operating time @unitb{\hour\per\year}, greater than zero and at most 8760.
    double motor_power;                          ///< Delivered fan power at the baseline operating point @unitb{\kilowatt}.
    double rated_flow;                           ///< Rated volume flow; any consistent flow unit, e.g. CFM or cubic meters per second.
    MotorControlType motor_control_type_current; ///< Baseline motor control.
    MotorControlType motor_control_type_new;     ///< Modified motor control.
    FlowMode flow_mode;                          ///< Desired-flow representation.
    double desired_flow_rate;                    ///< Desired flow in the rated-flow unit, or percentage points when Percent is selected.
};

/** @brief Annual electrical energy and savings; a passive value without cleanup. */
struct Result {
    double annual_energy_baseline; ///< Baseline electrical energy @unitb{\kilowatt\hour\per\year}.
    double annual_energy_new;      ///< Modified electrical energy @unitb{\kilowatt\hour\per\year}.
    double annual_cost_savings;    ///< Signed annual savings @unitb{\dollar\per\year}; negative means increased cost.
};

/** @brief Two-speed average power factor and time shares; dimensionless fractions for flow in [0,1]. */
struct TimeFactorResult {
    double factor;                ///< Average power divided by full-speed power @unitb{\unitless}.
    double time_above_50_percent; ///< Time at full speed @unitb{\unitless}, from zero to one.
    double time_at_50_percent;    ///< Time at half speed @unitb{\unitless}, from zero to one.
    double time_at_0_percent;     ///< Time off @unitb{\unitless}, from zero to one.
};

/**
 * @brief Calculates energy and savings without changing fan diameter.
 * @param[in] input Complete input data with units documented per member; not modified.
 * @return Annual baseline/new electrical energy in kWh/year and savings in dollars/year.
 * @details Motor power is delivered baseline power, not full-speed rated power. Percentages
 * are converted to fractions internally. OnOff/None ignore the baseline flow factor.
 * No input validation, defaults, or clamping are applied; invalid inputs can produce
 * nonphysical values, infinity, or NaN. Desktop/callers own all input validation.
 */
Result calculate(const Input& input);

/**
 * @brief Calculates energy and savings with a fan diameter change.
 * @param[in] input Complete input data; desired flow remains referenced to the original rated flow.
 * @param[in] fan_diameter_current Original fan diameter @unitb{\inch}, greater than zero.
 * @param[in] fan_diameter Modified fan diameter @unitb{\inch}, greater than zero.
 * @return Annual baseline/new electrical energy in kWh/year and savings in dollars/year.
 * @details Rated flow scales with the diameter ratio cubed and power with its fifth power.
 * Both VSD and Two-Speed use desired flow divided by the resized fan's rated flow.
 * Diameter and input validation belong to Desktop/callers; no checks or clamping are applied.
 */
Result changeFanSize(const Input& input, double fan_diameter_current, double fan_diameter);

/**
 * @brief Resolves full-speed, half-speed, and off time shares for a Two-Speed fan.
 * @param[in] flow_percent Desired average flow divided by rated flow, dimensionless fraction [0,1].
 * @return Dimensionless average power factor and time shares; for caller-supplied flow in [0,1],
 * the three time shares are in [0,1] and sum to one.
 * @details Half-speed power is one eighth of full-speed power. Zero flow is valid here,
 * but cannot normalize a positive delivered baseline power in the annual calculation.
 * No input validation or clamping is applied; Desktop/callers own the input domain.
 * Out-of-range flow can produce negative time shares; nonfinite arithmetic is propagated.
 */
TimeFactorResult get50PercentTimeFactor(double flow_percent);

} // namespace fan_affinity_laws
