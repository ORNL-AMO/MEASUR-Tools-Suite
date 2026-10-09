#pragma once

/**
 * @ingroup pump_result_calculator
 * @file pump_result.h
 * @brief Declares existing- and modified-condition pump assessment result calculations.
 * @details The calculation follows power through the motor, drive, and pump and reports
 *          operating performance, annual energy use, and annual electricity cost.
 * @see @ref pump_result_calculator for the engineering derivation and worked examples.
 */

#include "motorDriven/motor/MotorData.h"
#include "motorDriven/pump/Pump.h"

/**
 * @ingroup pump_result_calculator
 * @namespace pump_result
 * @brief Calculates existing and modified pump-system operating results.
 */
namespace pump_result {

/** @brief Equipment, hydraulic duty, and operating data shared by existing and modified calculations. */
struct SystemInput {
    Pump::Style pump_style;                        ///< Pump hydraulic-power model selector.
    Motor::Drive drive;                            ///< Motor-to-pump drive type.
    double specified_drive_efficiency;             ///< Specified drive efficiency @unitb{\unitless}.
    double specific_gravity;                       ///< Pumped-fluid specific gravity @unitb{\unitless}.
    double flow_rate;                              ///< Pump flow rate @unitb{\gallon\per\minute}.
    double head;                                   ///< Pump head @unitb{\foot}.
    double differential_pressure;                  ///< Positive-displacement pressure rise @unitb{\psi}.
    double motor_rated_power;                      ///< Motor nameplate power @unitb{\horsepower}.
    double motor_rated_speed;                      ///< Motor nameplate speed @unitb{\revolution\per\minute}.
    Motor::LineFrequency line_frequency;           ///< Electrical line frequency selector.
    Motor::EfficiencyClass motor_efficiency_class; ///< Motor efficiency class selector.
    double specified_motor_efficiency;             ///< Specified motor efficiency @unitb{\unitless}.
    double motor_rated_voltage;                    ///< Motor nameplate voltage @unitb{\volt}.
    double operating_voltage;                      ///< Measured or expected operating voltage @unitb{\volt}.
    double operating_hours;                        ///< Annual operating time @unitb{\hour\per\year}.
    double unit_cost;                              ///< Electricity rate @unitb{\dollar\per\kilowatt\hour}.
};

/** @brief Shared system data and motor measurements used to estimate an existing condition. */
struct ExistingInput {
    SystemInput system;                                 ///< Shared pump-system and operating data.
    double motor_full_load_amps;                        ///< Motor nameplate full-load current @unitb{\ampere}.
    Motor::LoadEstimationMethod load_estimation_method; ///< Measured power or measured current method.
    double measured_motor_power;                        ///< Measured three-phase motor input power @unitb{\kilowatt}.
    double measured_motor_current;                      ///< Measured motor current @unitb{\ampere}.
};

/** @brief Shared system data and proposed pump efficiency used to estimate a modified condition. */
struct ModifiedInput {
    SystemInput system;     ///< Shared pump-system and operating data.
    double pump_efficiency; ///< Proposed pump efficiency @unitb{\unitless}.
};

/** @brief Motor, drive, pump, energy, and cost results for one operating condition. */
struct Result {
    double pump_efficiency;        ///< Pump hydraulic efficiency @unitb{\unitless}.
    double motor_rated_power;      ///< Motor nameplate power @unitb{\horsepower}.
    double motor_shaft_power;      ///< Motor shaft output power @unitb{\horsepower}.
    double mover_shaft_power;      ///< Pump shaft input power @unitb{\horsepower}.
    double motor_efficiency;       ///< Motor efficiency @unitb{\unitless}.
    double motor_power_factor;     ///< Motor power factor @unitb{\unitless}.
    double motor_current;          ///< Motor current @unitb{\ampere}.
    double motor_power;            ///< Motor electrical input power @unitb{\kilowatt}.
    double annual_energy;          ///< Annual electrical energy use @unitb{\mega\watt\hour\per\year}.
    double annual_cost;            ///< Annual electricity cost @unitb{\kilo\dollar\per\year}.
    double load_factor;            ///< Motor load factor @unitb{\unitless}.
    double drive_efficiency;       ///< Drive efficiency @unitb{\unitless}.
    double estimated_full_load_amps; ///< Estimated motor full-load current @unitb{\ampere}.
};

/**
 * @brief Calculates pump-system results from existing measured motor data.
 * @param[in] input Existing motor, drive, pump, operating-time, and electricity-rate inputs.
 * @return Existing-condition pump-system results.
 */
Result calculateExisting(const ExistingInput& input);

/**
 * @brief Calculates pump-system results for a proposed pump efficiency and operating condition.
 * @param[in] input Modified motor, drive, pump, operating-time, and electricity-rate inputs.
 * @return Modified-condition pump-system results.
 */
Result calculateModified(const ModifiedInput& input);

} // namespace pump_result
