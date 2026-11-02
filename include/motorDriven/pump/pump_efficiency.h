/**
 * @ingroup pump_efficiency_calculator
 * @file pump_efficiency.h
 * @brief Achievable average and maximum pump-efficiency estimates for a supplied duty.
 */
#pragma once

#include "motorDriven/pump/Pump.h"

/** @ingroup pump_efficiency_calculator
 * @brief Stateless composition of corrected efficiency and the flow-dependent deviation factor.
 */
namespace pump_efficiency {

/** @brief Complete pump duty; no defaults, conversion or validation. */
struct Input {
    Pump::Style style;          ///< Unitless pump-style classification from the existing Pump enum.
    double rpm;                 ///< Pump rotational speed @unitb{\revolutionsPerMinute}.
    double kinematic_viscosity; ///< Fluid kinematic viscosity in centistokes (cSt).
    double stage_count;         ///< Dimensionless stage count; fractional values are retained.
    double flow_rate;           ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;                ///< Total pump head across all stages @unitb{\foot}.
};

/** @brief Empirical efficiency estimates; both values are dimensionless fractions. */
struct Result {
    double average; ///< Corrected average pump-efficiency estimate, dimensionless fraction.
    double max;     ///< Average estimate multiplied by the deviation factor, dimensionless fraction.
};

/**
 * @brief Estimates achievable average and maximum pump efficiency at the supplied duty.
 * @param[in] input Pump style, rpm, viscosity in cSt, dimensionless stages, US gpm and total head in ft;
 * not modified.
 * @return Average and maximum estimates as dimensionless fractions; no clamping is applied.
 * @details Composes the corrected efficiency with the flow-based deviation factor using unrounded values.
 * Evaluates signed, zero and nonfinite inputs directly. A zero pre-efficiency fallback is not an override:
 * subsequent corrections can produce negative estimates for specified-efficiency or positive-displacement styles.
 * @see @ref pump_efficiency_calculator for the engineering interpretation and applicability limits.
 */
Result calculate(const Input& input);

} // namespace pump_efficiency
