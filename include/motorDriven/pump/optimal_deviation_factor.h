/**
 * @ingroup optimal_deviation_factor_calculator
 * @file optimal_deviation_factor.h
 * @brief Stateless flow-based multiplier for the maximum pump-efficiency estimate.
 * @see @ref optimal_deviation_factor_calculator for the empirical equation and interpretation limits.
 */
#pragma once

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
 * @details The empirical expression uses the numerical flow in US gpm. Callers convert units
 * and validate the duty; no defaults, validation or clamping are applied. Both signed zeros
 * yield positive infinity, negative flow and NaN yield NaN, and positive infinity yields
 * 1.0010805906. A finite positive flow gives a multiplier above one, not an efficiency fraction.
 * @see @ref optimal_deviation_factor_calculator for coefficients, a worked example and provenance limits.
 */
double calculate(double flow_rate);

} // namespace optimal_deviation_factor
