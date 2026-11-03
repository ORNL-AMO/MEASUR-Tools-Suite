/**
 * @ingroup optimal_specific_speed_calculator
 * @file optimal_specific_speed.h
 * @brief Pump specific speed from rotational speed, flow and head per stage.
 */
#pragma once

/**
 * @ingroup optimal_specific_speed_calculator
 * @brief Stateless US customary pump specific-speed calculation.
 */
namespace optimal_specific_speed {

/** @brief Required pump duty; no defaults, conversion or validation. */
struct Input {
    double rpm;         ///< Pump rotational speed @unitb{\revolutionsPerMinute}.
    double flow_rate;   ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;        ///< Total pump head across all stages @unitb{\foot}.
    double stage_count; ///< Number of pump stages, dimensionless; fractional values are retained.
};

/**
 * @brief Calculates specific speed using total head divided by the stage count.
 * @param[in] input Speed in rpm, flow in US gpm, total head in ft and dimensionless stage count; not modified.
 * @return US customary specific speed in rpm*sqrt(US gpm)/ft^(3/4), not a dimensionless speed.
 * @details Evaluates the supplied values directly, including signed, zero and nonfinite inputs.
 * No flow-halving adjustment for double-suction pumps or result clamping is applied.
 * @see @ref optimal_specific_speed_calculator for the unit convention and applicability limits.
 */
double calculate(const Input& input);

} // namespace optimal_specific_speed
