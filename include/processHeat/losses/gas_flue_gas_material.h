#pragma once
#include "physics/gas_composition.h"
using namespace gas_composition;

/**
 * @ingroup gas_flue_gas_material_calculator
 * @file gas_flue_gas_material.h
 * @authors Gina Accawi, Preston Shires, Omer Aziz, Mark Root
 *
 * @copybrief gas_flue_gas_material
 */

/**
 * @ingroup gas_flue_gas_material_calculator
 * @namespace gas_flue_gas_material
 * @brief Contains functions for flue gas material calculations.
 */
namespace gas_flue_gas_material {

/**
 * @ingroup gas_flue_gas_material_calculator
 * @brief Calculates the total heat loss for flue gas using the provided parameters.
 * @param[in] stoich_air Stoichiometric air required for complete combustion (SCF air/SCF fuel)
 * @param[in] excess_air Percent Excess Air (e.g. 9 for 9%) @unitb{\unitless}
 * @param[in] available_heat Available heat from combustion @unitb{\Btu\per\hour}
 * @param[in] specific_heat Specific heat of the gas @unitb{\Btu\per\hour\per\degreeFahrenheit}
 * @param[in] total_generated Total mass generated @unitb{\pound\per\hour}
 * @param[in] heat_value_fuel Heating value of the fuel gas mixture @unitb{\Btu\per\hour}
 * @param[in] flue_gas_o2 Oxygen in flue gas @unitb{\percent}
 */
struct ProcessHeatProperties {
    double stoich_air;
    double excess_air;
    double available_heat;
    double specific_heat;
    double total_generated;
    double heat_value_fuel;
    double flue_gas_o2;
};

/**
 * @brief Calculates process heat properties for the fuel gas mixture and operating conditions.
 * @param[in] compositions Instance of GasComposition representing the fuel gas mixture and its constituent properties
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] flue_gas_o2 Oxygen percentage in flue gas @unitb{\percent}
 * @param[in] comb_air_temp Combustion air temperature @unitb{\degreeFahrenheit}
 * @param[in] fuel_temp Fuel temperature @unitb{\degreeFahrenheit}
 * @param[in] ambient_air_temp Ambient air temperature @unitb{\degreeFahrenheit} (default: 60)
 * @param[in] comb_air_moisture Combustion air moisture @unitb{\percent} (default: 0)
 * @param[in] excess_air Excess air percentage @unitb{\percent} (default: 0)
 * @return ProcessHeatProperties struct with calculated properties
 */
ProcessHeatProperties processHeatProperties(const GasComposition compositions, const double flue_gas_temp,
                                              const double flue_gas_o2, const double comb_air_temp,
                                              const double fuel_temp, const double ambient_air_temp = 60,
                                              const double comb_air_moisture = 0, const double excess_air = 0);

/**
 * @ingroup process_heat_loss_calculator
 * @brief Calculates the total heat loss for flue gas using the provided parameters.
 * @param[in] flue_gas_temperature Furnace Flue Gas Temperature @unitb{\degreeFahrenheit}
 * @param[in] excess_air_percentage Percent Excess Air (e.g. 9 for 9%) @unitb{\unitless}
 * @param[in] combustion_air_temperature Combustion Air Temperature @unitb{\degreeFahrenheit}
 * @param[in] compositions Instance of GasComposition representing the fuel gas mixture and its constituent properties
 * @param[in] fuel_temperature Temperature of fuel @unitb{\degreeFahrenheit}
 * @return Total heat loss @unitb{\btu\per\hour}
 */
double totalHeatLoss(double flue_gas_temperature, double excess_air_percentage, double combustion_air_temperature,
                     const GasComposition& compositions, double fuel_temperature);

} // namespace gas_flue_gas_material
