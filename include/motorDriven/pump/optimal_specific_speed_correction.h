/**
 * @ingroup optimal_specific_speed_correction_calculator
 * @file optimal_specific_speed_correction.h
 * @brief Empirical pump-efficiency decrement from pump style and specific speed.
 */
#pragma once

#include "motorDriven/pump/Pump.h"

/**
 * @ingroup optimal_specific_speed_correction_calculator
 * @brief Stateless specific-speed correction for the pump-efficiency estimate.
 */
namespace optimal_specific_speed_correction {

/** @brief Required pump style and specific speed; no defaults or validation. */
struct Input {
    Pump::Style style;     ///< Unitless pump-style classification from the existing Pump enum.
    double specific_speed; ///< US customary specific speed in rpm*sqrt(US gpm)/ft^(3/4).
};

/**
 * @brief Calculates the efficiency fraction to subtract from the viscosity-adjusted estimate.
 * @param[in] input Pump style and US customary specific speed; not modified.
 * @return Efficiency decrement as a dimensionless fraction, not percentage points.
 * @details Only vertical-turbine style uses the vertical curves. All other native styles use the
 * nonvertical curves, including axial flow and unknown values. Equality at the speed threshold
 * selects the upper curve. The polynomial is lower-clamped with fmax before division by 100;
 * there is no upper clamp or input validation. NaN arithmetic follows the retained fmax behavior.
 * @see @ref optimal_specific_speed_correction_calculator for coefficients, units and applicability limits.
 */
double calculate(const Input& input);

} // namespace optimal_specific_speed_correction
