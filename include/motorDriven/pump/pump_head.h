#pragma once

/**
 * @ingroup pump_head_calculator
 * @file pump_head.h
 * @brief Declares calculations of the total dynamic head developed by an operating pump.
 * @details The calculation resolves total pump head into elevation, pressure, velocity, and
 *          estimated suction- and discharge-line friction components. Suction conditions may be
 *          defined by either a pressure gauge or a pressurized tank.
 * @see @ref pump_head_calculator for formula derivations, units, and assumptions.
 */

/**
 * @ingroup pump_head_calculator
 * @namespace pump_head
 * @brief Calculates total dynamic pump head from measured system operating conditions.
 */
namespace pump_head {

/** @brief Inputs for a pump system whose suction condition is measured by a gauge. */
struct SuctionGaugeInput {
    double specific_gravity;                 ///< Fluid specific gravity @unitb{\unitless}.
    double flow_rate;                        ///< Volumetric flow rate @unitb{\gallon\per\minute}.
    double suction_pipe_diameter;            ///< Suction-pipe inside diameter @unitb{\inch}.
    double suction_gauge_pressure;           ///< Suction gauge pressure @unitb{psig}.
    double suction_gauge_elevation;          ///< Suction-gauge elevation @unitb{\foot}.
    double suction_line_loss_coefficients;   ///< Aggregate suction-line loss coefficient @unitb{\unitless}.
    double discharge_pipe_diameter;          ///< Discharge-pipe inside diameter @unitb{\inch}.
    double discharge_gauge_pressure;         ///< Discharge gauge pressure @unitb{psig}.
    double discharge_gauge_elevation;        ///< Discharge-gauge elevation @unitb{\foot}.
    double discharge_line_loss_coefficients; ///< Aggregate discharge-line loss coefficient @unitb{\unitless}.
};

/** @brief Inputs for a pump system supplied from a pressurized suction tank. */
struct SuctionTankInput {
    double specific_gravity;                     ///< Fluid specific gravity @unitb{\unitless}.
    double flow_rate;                            ///< Volumetric flow rate @unitb{\gallon\per\minute}.
    double suction_pipe_diameter;                ///< Suction-pipe inside diameter @unitb{\inch}.
    double suction_tank_gas_over_pressure;       ///< Suction-tank gas overpressure @unitb{psig}.
    double suction_tank_fluid_surface_elevation; ///< Suction-tank fluid-surface elevation @unitb{\foot}.
    double suction_line_loss_coefficients;       ///< Aggregate suction-line loss coefficient @unitb{\unitless}.
    double discharge_pipe_diameter;              ///< Discharge-pipe inside diameter @unitb{\inch}.
    double discharge_gauge_pressure;             ///< Discharge gauge pressure @unitb{psig}.
    double discharge_gauge_elevation;            ///< Discharge-gauge elevation @unitb{\foot}.
    double discharge_line_loss_coefficients;     ///< Aggregate discharge-line loss coefficient @unitb{\unitless}.
};

/** @brief Component heads and total operating pump head. */
struct Result {
    double differential_elevation_head;       ///< Discharge-minus-suction elevation head @unitb{\foot}.
    double differential_pressure_head;        ///< Discharge-minus-suction pressure head @unitb{\foot}.
    double differential_velocity_head;        ///< Discharge-minus-suction velocity head @unitb{\foot}.
    double estimated_suction_friction_head;   ///< Estimated suction-line friction head @unitb{\foot}.
    double estimated_discharge_friction_head; ///< Estimated discharge-line friction head @unitb{\foot}.
    double pump_head;                          ///< Total operating pump head @unitb{\foot}.
};

/**
 * @brief Calculates pump head from suction- and discharge-gauge measurements.
 * @param[in] input Fluid, flow, pipe, pressure, elevation, and line-loss data for the operating system.
 * @return Component heads and total operating pump head, all @unitb{\foot}.
 */
Result calculateFromSuctionGauge(const SuctionGaugeInput& input);

/**
 * @brief Calculates pump head for a system supplied from a pressurized suction tank.
 * @param[in] input Fluid, flow, pipe, tank, discharge, elevation, and line-loss data for the operating system.
 * @return Component heads and total operating pump head, all @unitb{\foot}.
 */
Result calculateFromSuctionTank(const SuctionTankInput& input);

} // namespace pump_head
