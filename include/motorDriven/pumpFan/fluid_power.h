#pragma once

/**
 * @ingroup fluid_power_calculator
 * @file fluid_power.h
 * @brief Declares stateless pump and fan fluid-power calculations.
 */

/**
 * @ingroup fluid_power_calculator
 * @namespace fluid_power
 * @brief Power delivered to the fluid at a supplied pump or fan duty.
 */
namespace fluid_power {

/** @brief Complete required pump hydraulic-duty inputs. */
struct PumpInput {
    double specific_gravity; ///< Fluid specific gravity @unitb{\unitless}.
    double flow_rate;        ///< Liquid volumetric flow @unitb{\gallon\per\minute}, US gallons.
    double head;             ///< Pump head @unitb{\foot} of the pumped fluid.
};

/** @brief Complete required fan operating-duty inputs. */
struct FanInput {
    double flow_rate;              ///< Gas volumetric flow @unitb{\cubicFoot\per\minute}.
    double inlet_pressure;         ///< Inlet gauge pressure @unitb{\inchWaterColumn}.
    double outlet_pressure;        ///< Outlet gauge pressure @unitb{\inchWaterColumn}.
    double compressibility_factor; ///< Supplied fan compressibility correction @unitb{\unitless}.
    double velocity_pressure;      ///< Velocity pressure subtracted from the rise @unitb{\inchWaterColumn}.
};

/**
 * @brief Calculates power delivered to the liquid at a pump duty.
 * @param[in] input Complete hydraulic-duty data, with units documented per member; not modified.
 * @return Fluid power @unitb{\kilo\watt}, excluding pump, drive and motor losses.
 * @details Retains the 3961.38 divisor and 0.746 hp-to-kW conversion. No validation,
 * defaults or clamping are applied; signed and nonfinite arithmetic is preserved.
 * @see @ref fluid_power_calculator for formulas, examples and interpretation limits.
 */
double calculatePump(const PumpInput& input);

/**
 * @brief Calculates power delivered to the gas at a fan duty.
 * @param[in] input Complete fan-duty data, with units documented per member; not modified.
 * @return Fluid power @unitb{\kilo\watt}, excluding fan, drive and motor losses.
 * @details Uses outlet minus inlet minus velocity pressure, the supplied compressibility
 * correction, the 6362 divisor and 0.746 hp-to-kW conversion. No validation, defaults or
 * clamping are applied; signed and nonfinite arithmetic is preserved.
 * @see @ref fluid_power_calculator for formulas, examples and interpretation limits.
 */
double calculateFan(const FanInput& input);

} // namespace fluid_power
