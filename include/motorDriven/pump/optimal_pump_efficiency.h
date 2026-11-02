/**
 * @ingroup optimal_pump_efficiency_calculator
 * @file optimal_pump_efficiency.h
 * @brief Pump-efficiency estimate after viscosity and specific-speed corrections.
 */
#pragma once

#include "motorDriven/pump/Pump.h"

/**
 * @ingroup optimal_pump_efficiency_calculator
 * @brief Stateless corrected pump-efficiency estimate.
 */
namespace optimal_pump_efficiency {

/** @brief Required pump classification and duty; no defaults, conversion or validation. */
struct Input {
    Pump::Style style;          ///< Unitless pump-style classification from the existing Pump enum.
    double rpm;                 ///< Pump rotational speed @unitb{\revolutionsPerMinute}.
    double kinematic_viscosity; ///< Liquid kinematic viscosity @unitb{cSt}.
    double stage_count;         ///< Number of pump stages, dimensionless; fractional values are retained.
    double flow_rate;           ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;                ///< Total pump head across all stages @unitb{\foot}.
};

/**
 * @brief Estimates efficiency by adjusting the flow/style estimate for viscosity and specific speed.
 * @param[in] input Pump style and duty in rpm, cSt, dimensionless stages, US gpm and ft; not modified.
 * @return Efficiency as a dimensionless fraction, not a percentage; no final clamping is applied.
 * @details The viscosity factor is capped with fmin at one. The specific-speed correction is
 * subtracted afterward. Specified-optimal, positive-displacement and unknown native styles retain
 * their zero pre-efficiency fallback and can produce negative results. Signed, zero and nonfinite
 * inputs are evaluated directly, with retained fmin/fmax arithmetic rather than new validation.
 * @see @ref optimal_pump_efficiency_calculator for the formulas, unit conventions and applicability limits.
 */
double calculate(const Input& input);

} // namespace optimal_pump_efficiency
