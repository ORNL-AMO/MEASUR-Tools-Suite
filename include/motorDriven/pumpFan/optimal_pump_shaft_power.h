#pragma once

/**
 * @ingroup optimal_pump_shaft_power_calculator
 * @file optimal_pump_shaft_power.h
 * @brief Stateless pump and fan shaft-power calculations at a supplied efficiency.
 * @details Callers provide a complete duty, validate inputs and convert user-facing units.
 * Efficiencies are fractions, not percentage points. No efficiency optimization is performed.
 * @see @ref optimal_pump_shaft_power_calculator for formulas, examples and interpretation limits.
 */

/**
 * @ingroup optimal_pump_shaft_power_calculator
 * @namespace optimal_pump_shaft_power
 * @brief Calculates shaft input required at a supplied pump or fan duty and efficiency.
 */
namespace optimal_pump_shaft_power {

/** @brief Complete required pump duty and supplied efficiency. */
struct PumpInput {
    double flow_rate;        ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;             ///< Pump head in feet of the pumped fluid @unitb{\foot}.
    double specific_gravity; ///< Fluid specific gravity @unitb{\unitless}.
    double pump_efficiency;  ///< Supplied pump efficiency fraction @unitb{\unitless}; 0.80 means 80%.
};

/** @brief Complete required fan duty and supplied efficiency. */
struct FanInput {
    double flow_rate;              ///< Gas volumetric flow @unitb{\cubicFoot\per\minute}.
    double inlet_pressure;         ///< Inlet gauge pressure @unitb{\inchWaterColumn}.
    double outlet_pressure;        ///< Outlet gauge pressure @unitb{\inchWaterColumn}.
    double compressibility_factor; ///< Supplied fan compressibility correction @unitb{\unitless}.
    double fan_efficiency;         ///< Supplied fan efficiency fraction @unitb{\unitless}; 0.80 means 80%.
    double velocity_pressure;      ///< Velocity pressure subtracted from the rise @unitb{\inchWaterColumn}.
};

/**
 * @brief Calculates pump shaft input required at the supplied duty and efficiency.
 * @param[in] input Complete duty and efficiency data; units documented per member; not modified.
 * @return Required pump shaft power @unitb{\horsepower}, excluding motor and drive losses.
 * @details Divides fluid power in kW by the efficiency fraction, then by 0.746 kW/hp.
 * No validation, defaults or clamping are applied; signed and nonfinite results are retained.
 * @see @ref optimal_pump_shaft_power_calculator for formulas, examples and interpretation limits.
 */
double calculatePump(const PumpInput& input);

/**
 * @brief Calculates fan shaft input required at the supplied duty and efficiency.
 * @param[in] input Complete duty and efficiency data; units documented per member; not modified.
 * @return Required fan shaft power @unitb{\horsepower}, excluding motor and drive losses.
 * @details Uses outlet minus inlet minus velocity pressure and the supplied compressibility
 * correction. Divides fluid power in kW by the efficiency fraction, then by 0.746 kW/hp.
 * No validation, defaults or clamping are applied; signed and nonfinite results are retained.
 * @see @ref optimal_pump_shaft_power_calculator for formulas, examples and interpretation limits.
 */
double calculateFan(const FanInput& input);

} // namespace optimal_pump_shaft_power
