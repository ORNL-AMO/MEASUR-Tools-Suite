#pragma once

/**
 * @ingroup dryer_operating_cost_calculator
 * @file dryer_operating_cost.h
 * @brief Declarations for compressed-air dryer annual operating-cost calculations.
 * @details Provides a stateless namespace function that calculates moisture removal,
 *          resolved equipment sizing, and annual operating cost for a selected dryer type.
 *          The caller owns validation, dryer-type defaults, and user-facing unit conversion.
 * @see @ref dryer_operating_cost_calculator for formula derivations and symbol definitions.
 */

/**
 * @ingroup dryer_operating_cost_calculator
 * @namespace dryer_operating_cost
 * @brief Compressed-air dryer annual operating-cost calculations.
 */
namespace dryer_operating_cost {

/** @brief Supported compressed-air dryer types. */
enum class DryerType {
    Heatless,
    HeatedExternally,
    BlowerPurgeWithSweep,
    BlowerPurgeWithoutSweep,
    HeatOfCompressionHC,
    HeatOfCompressionSP,
    Refrigerated
};

/** @brief Selects how purge airflow is supplied. */
enum class PurgeInputMode {
    PercentOfDryerCapacity,
    DirectFlow
};

/** @brief Inputs for the annual dryer operating-cost calculation. */
struct Input {
    DryerType dryer_type;               ///< Dryer configuration to evaluate.
    double flow_rate;                    ///< Inlet airflow @unitb{\scfm}.
    double pressure;                     ///< Inlet gauge pressure @unitb{psig}.
    double temperature;                  ///< Inlet temperature @unitb{\degreeFahrenheit}.
    double annual_operating_hours;       ///< Annual dryer operating time @unitb{\hour\per\year}.
    double cost_of_electricity;          ///< Electricity rate @unitb{\dollar\per\kilowatt\hour}.
    double cost_of_compressed_air;       ///< Compressed-air rate in dollars per 1,000 standard cubic feet.
    double cost_of_cooling_water;        ///< Cooling-water rate in dollars per 1,000 gallons.
    double heater_power;                 ///< Manual heater load @unitb{\kilowatt}; zero selects automatic sizing.
    double heating_hours_per_day;        ///< Heater operating time per 24 hours @unitb{\hour}.
    double purge_rate;                   ///< Purge airflow as dryer-capacity percentage points @unitb{\percent}.
    double purge_flow_rate;              ///< Direct purge airflow @unitb{\scfm}.
    double design_ddc_percentage;        ///< Design desiccant capacity percentage points @unitb{\percent}.
    double regeneration_cycle_length;    ///< Regeneration half-cycle length @unitb{\hour}.
    double motor_power;                  ///< Manual motor size @unitb{\horsepower}; zero selects automatic sizing.
    PurgeInputMode purge_input_mode;     ///< Active purge input representation.
};

/** @brief Resolved annual dryer operating-cost results. */
struct Result {
    double water_removed;                ///< Water removed @unitb{\pound\per\hour}.
    double total_cost_per_year;          ///< Total annual operating cost @unitb{\dollar\per\year}.
    double heater_power;                 ///< Heater load used by the calculation @unitb{\kilowatt}.
    double heating_hours_per_day;        ///< Heater operating time per 24 hours @unitb{\hour}.
    double purge_rate;                   ///< Effective purge percentage points @unitb{\percent}.
    double design_ddc_percentage;        ///< Design desiccant capacity percentage points @unitb{\percent}.
    double purge_flow_rate;              ///< Purge airflow used by the calculation @unitb{\scfm}.
    double motor_power;                  ///< Motor power used by the calculation @unitb{\horsepower}.
    double regeneration_cycle_length;    ///< Regeneration half-cycle length @unitb{\hour}.
};

/**
 * @brief Calculates annual operating cost for the selected dryer type.
 * @param input Frontend-validated operating conditions, rates, type, and type assumptions.
 * @return Resolved water-removal, sizing, and annual-cost values.
 */
Result calculate(const Input& input);

} // namespace dryer_operating_cost
