/**
 * @ingroup optimal_deviation_factor_calculator
 * @file optimal_deviation_factor.h
 * @brief Stateless flow-based multiplier for the maximum pump-efficiency estimate.
 * @see @ref optimal_deviation_factor_calculator for the empirical equation and interpretation limits.
 */
#pragma once

#include "util/pchip.h"

/**
 * @ingroup optimal_deviation_factor_calculator
 * @namespace optimal_deviation_factor
 * @brief Estimates the relative increase from average to maximum pump efficiency.
 */
namespace optimal_deviation_factor {

/**
 * @brief Calculates the multiplier applied to an average pump-efficiency estimate.
 * @param[in] flow_rate Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
 * @return Dimensionless multiplier @unitb{\unitless}; multiply the average efficiency by this value.
 * @details Interpolates the HI 20.3-2020 positive-deviation table against raw flow in US gpm.
 * Returns 1 + deviation-percent/100 for inclusive flow range 35–100000 US gpm.
 * Nonfinite and out-of-range flow return NaN. No extrapolation or output clamping is applied.
 * @see @ref optimal_deviation_factor_calculator for coefficients, a worked example and provenance limits.
 */
double calculate(double flow_rate);

/** @return Inclusive positive-deviation table flow bounds in US gpm. */
pchip::Range flowLimits();

} // namespace optimal_deviation_factor
