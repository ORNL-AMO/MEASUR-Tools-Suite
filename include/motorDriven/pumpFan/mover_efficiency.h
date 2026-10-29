#pragma once

/**
 * @ingroup mover_efficiency_calculator
 * @file mover_efficiency.h
 * @brief Stateless pump and fan calculations of fluid power relative to shaft input.
 * @details Inputs are complete operating duties. Callers own validation and user-facing
 * unit conversion; results are dimensionless fractions, not percentage points.
 * @see @ref mover_efficiency_calculator for formulas, examples and interpretation limits.
 */

/**
 * @ingroup mover_efficiency_calculator
 * @namespace mover_efficiency
 * @brief Calculates the fraction of mover shaft power delivered to the fluid.
 */
namespace mover_efficiency {

/** @brief Complete required pump duty and shaft-power inputs. */
struct PumpInput {
    double specific_gravity;  ///< Fluid specific gravity @unitb{\unitless}.
    double flow_rate;         ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;              ///< Pump head in feet of the pumped fluid @unitb{\foot}.
    double mover_shaft_power; ///< Power supplied at the pump shaft @unitb{\horsepower}.
};

/** @brief Complete required fan duty and shaft-power inputs. */
struct FanInput {
    double flow_rate;              ///< Gas volumetric flow @unitb{\cubicFoot\per\minute}.
    double mover_shaft_power;      ///< Power supplied at the fan shaft @unitb{\horsepower}.
    double inlet_pressure;         ///< Inlet gauge pressure @unitb{\inchWaterColumn}.
    double outlet_pressure;        ///< Outlet gauge pressure @unitb{\inchWaterColumn}.
    double compressibility_factor; ///< Supplied fan compressibility correction @unitb{\unitless}.
    double velocity_pressure;      ///< Velocity pressure subtracted from the rise @unitb{\inchWaterColumn}.
};

/**
 * @brief Calculates the fraction of pump shaft input delivered to the liquid.
 * @param[in] input Complete duty and shaft-power data; units documented per member; not modified.
 * @return Mover efficiency @unitb{\unitless}, a fraction (0.75 means 75%), not percentage points.
 * @details Divides fluid power in kW by 0.746, then by shaft power in hp. No validation,
 * defaults or clamping are applied; above-one, signed and nonfinite results are retained.
 * @see @ref mover_efficiency_calculator for formulas, examples and interpretation limits.
 */
double calculatePump(const PumpInput& input);

/**
 * @brief Calculates the fraction of fan shaft input delivered to the gas.
 * @param[in] input Complete duty and shaft-power data; units documented per member; not modified.
 * @return Mover efficiency @unitb{\unitless}, a fraction (0.75 means 75%), not percentage points.
 * @details Uses outlet minus inlet minus velocity pressure and the supplied compressibility
 * correction. Divides fluid power in kW by 0.746, then by shaft power in hp. No validation,
 * defaults or clamping are applied; above-one, signed and nonfinite results are retained.
 * @see @ref mover_efficiency_calculator for formulas, examples and interpretation limits.
 */
double calculateFan(const FanInput& input);

} // namespace mover_efficiency
