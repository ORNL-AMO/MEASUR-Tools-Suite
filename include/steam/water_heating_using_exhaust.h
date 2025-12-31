
#pragma once

/**
 * @ingroup water_heating_using_exhaust_calculator
 * @file water_heating_using_exhaust.h
 * 
 * @copybrief water_heating_using_exhaust
 */

/**
 * @ingroup water_heating_using_exhaust_calculator
 * @namespace water_heating_using_exhaust
 * @brief Water heating using exhaust calculations for process heating systems.
 */
namespace water_heating_using_exhaust {

/**
 * @ingroup process_heat
 * @struct WaterHeatingUsingExhaustResults
 * @brief Results of the water heating using exhaust calculation.
 * @details Contains all output values from the water heating using exhaust calculation.
 */
struct WaterHeatingUsingExhaustResults {
    double recovered_heat = 0;        ///< Recovered heat @unitb{Btu/hr}
    double hot_water_flow = 0;        ///< Hot water flow @unitb{gal/hr}
    double tons_refrigeration = 0;    ///< Tons of refrigeration @unitb{Tons}
    double capacity_chiller = 0;      ///< Chiller capacity @unitb{Tons}
    double electrical_energy = 0;     ///< Electrical energy @unitb{Btu/hr}
};

/**
 * @brief Calculates energy savings from using exhaust gas (waste) heat to provide energy for an absorption chiller in place of a compressor.
 * @details Uses process parameters to estimate the benefit of using waste heat for water heating and chiller operation.
 *
 * @param[in] available_heat Fraction of available heat (percentage as fraction)
 * @param[in] heat_input Heat input @unitb{Btu/hr}
 * @param[in] hx_efficiency Heat exchanger efficiency (fraction)
 * @param[in] chiller_in_temperature Chiller inlet temperature @unitb{\degreeFahrenheit}
 * @param[in] chiller_out_temperature Chiller outlet temperature @unitb{\degreeFahrenheit}
 * @param[in] cop_chiller Coefficient of performance for chiller (fraction)
 * @param[in] chiller_efficiency Chiller efficiency (fraction)
 * @param[in] cop_compressor Coefficient of performance for compressor (fraction)
 * @return WaterHeatingUsingExhaustResults struct with all calculated outputs.
 */
WaterHeatingUsingExhaustResults waterHeatingUsingExhaust(
    double available_heat,
    double heat_input,
    double hx_efficiency,
    double chiller_in_temperature,
    double chiller_out_temperature,
    double cop_chiller,
    double chiller_efficiency,
    double cop_compressor
);

} // namespace water_heating_using_exhaust

