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

/** @brief Complete pump duty; units are explicit and no defaults or conversion are applied. */
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

/** @brief Inclusive HI 2020 composite-estimate limits derived from its reference tables. */
struct Limits {
    bool supported;              ///< Whether this style supports an HI estimate.
    double minimum_flow_rate;    ///< Inclusive minimum flow in US gpm; NaN if unsupported.
    double maximum_flow_rate;    ///< Inclusive maximum flow in US gpm; NaN if unsupported.
    double minimum_specific_speed; ///< Inclusive minimum in rpm*sqrt(US gpm)/ft^(3/4); NaN if unsupported.
    double maximum_specific_speed; ///< Inclusive maximum in rpm*sqrt(US gpm)/ft^(3/4); NaN if unsupported.
};

/** @brief Returns composite flow/speed bounds without duplicating table constants.
 * @param style Unitless pump-style classification.
 * @return Supported flag and inclusive reference bounds; unsupported bounds are NaN.
 */
Limits getLimits(Pump::Style style);

/**
 * @brief Estimates achievable average and maximum pump efficiency at the supplied duty.
 * @param[in] input Pump style, rpm, viscosity in cSt, dimensionless stages, US gpm and total head in ft;
 * not modified.
 * @return Average and maximum estimates as dimensionless fractions; no clamping is applied.
 * @details Composes the corrected efficiency with the flow-based deviation factor using unrounded values.
 * Both fields are NaN if a required estimate is unavailable. Nonfinite inputs, nonpositive
 * rpm/head/stages, negative viscosity and duties outside reference flow/speed ranges are unavailable.
 * Specified-efficiency and positive-displacement styles are not HI estimates; use supplied efficiency.
 * @see @ref pump_efficiency_calculator for the engineering interpretation and applicability limits.
 */
Result calculate(const Input& input);

} // namespace pump_efficiency
