/**
 * @ingroup optimal_pre_pump_efficiency_calculator
 * @file optimal_pre_pump_efficiency.h
 * @brief Flow/style pump-efficiency estimate before viscosity and specific-speed corrections.
 */
#pragma once

#include "motorDriven/pump/Pump.h"
#include "util/pchip.h"

/** @ingroup optimal_pre_pump_efficiency_calculator
 * @brief Stateless empirical pre-correction efficiency estimate.
 */
namespace optimal_pre_pump_efficiency {

/** @brief Required pump classification and duty, using HI 20.3-2020 table ranges. */
struct Input {
    Pump::Style style; ///< Unitless pump-style classification; uses the existing Pump enum.
    double flow_rate; ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
};

/**
 * @brief Estimates pump efficiency before viscosity and specific-speed corrections.
 * @param[in] input Pump style and flow in US gpm; not modified.
 * @return Efficiency @unitb{\percent}, not a fraction. No clamping is applied.
 * @details Interpolates HI 20.3-2020 points without extrapolation. Returns NaN for nonfinite
 * or out-of-range flow and for specified, positive-displacement or unknown styles.
 * Axial flow uses the vertical-turbine base table.
 * @see @ref optimal_pre_pump_efficiency_calculator for coefficients, units and applicability limits.
 */
double calculate(const Input& input);

/** @brief Returns inclusive reference flow bounds in US gpm; NaNs for unsupported styles.
 * @param style Unitless pump-style classification.
 * @return Lower and upper flow in US gpm, derived from the calculation table.
 */
pchip::Range flowLimits(Pump::Style style);

} // namespace optimal_pre_pump_efficiency
