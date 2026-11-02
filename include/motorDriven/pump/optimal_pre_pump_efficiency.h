/**
 * @ingroup optimal_pre_pump_efficiency_calculator
 * @file optimal_pre_pump_efficiency.h
 * @brief Flow/style pump-efficiency estimate before viscosity and specific-speed corrections.
 */
#pragma once

#include "motorDriven/pump/Pump.h"

/** @ingroup optimal_pre_pump_efficiency_calculator
 * @brief Stateless empirical pre-correction efficiency estimate.
 */
namespace optimal_pre_pump_efficiency {

/** @brief Required pump classification and duty; no defaults or validation. */
struct Input {
    Pump::Style style; ///< Unitless pump-style classification; uses the existing Pump enum.
    double flow_rate; ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
};

/**
 * @brief Estimates pump efficiency before viscosity and specific-speed corrections.
 * @param[in] input Pump style and flow in US gpm; not modified.
 * @return Efficiency @unitb{\percent}, not a fraction. No clamping is applied.
 * @details Equality at a flow threshold selects the upper interval. Specified-optimal,
 * positive-displacement and unknown native styles return zero for every flow. Other styles
 * evaluate the empirical curves directly, including zero, negative and nonfinite flows.
 * @see @ref optimal_pre_pump_efficiency_calculator for coefficients, units and applicability limits.
 */
double calculate(const Input& input);

} // namespace optimal_pre_pump_efficiency
