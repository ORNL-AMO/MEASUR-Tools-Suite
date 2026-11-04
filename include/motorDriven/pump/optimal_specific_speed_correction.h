/**
 * @ingroup optimal_specific_speed_correction_calculator
 * @file optimal_specific_speed_correction.h
 * @brief Empirical pump-efficiency decrement from pump style and specific speed.
 */
#pragma once

#include "motorDriven/pump/Pump.h"
#include "util/pchip.h"

/**
 * @ingroup optimal_specific_speed_correction_calculator
 * @brief Stateless specific-speed correction for the pump-efficiency estimate.
 */
namespace optimal_specific_speed_correction {

/** @brief Required style and specific speed within its HI 20.3-2020 reference range. */
struct Input {
    Pump::Style style;     ///< Unitless pump-style classification from the existing Pump enum.
    double specific_speed; ///< US customary specific speed in rpm*sqrt(US gpm)/ft^(3/4).
};

/**
 * @brief Calculates the efficiency fraction to subtract from the viscosity-adjusted estimate.
 * @param[in] input Pump style and US customary specific speed; not modified.
 * @return Efficiency decrement as a dimensionless fraction, not percentage points.
 * @details PCHIP interpolates HI 20.3-2020 correction points and divides by 100.
 * Only vertical turbine uses V (1717.2–17172); all others, including axial flow, use
 * nonvertical (630–6300). Nonfinite or out-of-range speeds return NaN. Endpoints are included.
 * @see @ref optimal_specific_speed_correction_calculator for coefficients, units and applicability limits.
 */
double calculate(const Input& input);

/** @brief Returns inclusive reference speed bounds in rpm*sqrt(US gpm)/ft^(3/4).
 * @param style Unitless pump-style classification; only vertical turbine selects V.
 * @return Lower and upper US customary specific speed from the correction table.
 */
pchip::Range speedLimits(Pump::Style style);

} // namespace optimal_specific_speed_correction
