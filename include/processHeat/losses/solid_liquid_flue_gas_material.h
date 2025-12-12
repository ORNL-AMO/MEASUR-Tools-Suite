#pragma once

/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @file solid_liquid_flue_gas_material.h
 * @authors Gina Accawi, Preston Shires, Omer Aziz, Mark Root
 *
 * @copybrief solid_liquid_flue_gas_material
 */

/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @namespace solid_liquid_flue_gas_material
 * @brief Contains functions for flue gas material calculations.
 */
namespace solid_liquid_flue_gas_material {

/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @brief Calculates total heat loss for solid/liquid fuel flue gas.
 * @param[in] flue_gas_temperature Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] excess_air Excess air as fraction (e.g. 0.09 for 9%) @unitb{\unitless}
 * @param[in] combustion_air_temperature Combustion air temperature @unitb{\degreeFahrenheit}
 * @param[in] fuel_temperature Fuel temperature @unitb{\degreeFahrenheit}
 * @param[in] moisture_in_air_combustion Moisture in air combustion @unitb{\percent}
 * @param[in] ash_discharge_temperature Ash discharge temperature @unitb{\degreeFahrenheit}
 * @param[in] unburned_carbon_in_ash Unburned carbon in ash as fraction @unitb{\unitless}
 * @param[in] carbon Percent carbon in fuel @unitb{\percent}
 * @param[in] hydrogen Percent hydrogen in fuel @unitb{\percent}
 * @param[in] sulphur Percent sulphur in fuel @unitb{\percent}
 * @param[in] inert_ash Percent inert ash in fuel @unitb{\percent}
 * @param[in] o2 Percent oxygen in fuel @unitb{\percent}
 * @param[in] moisture Percent moisture in fuel @unitb{\percent}
 * @param[in] nitrogen Percent nitrogen in fuel @unitb{\percent}
 * @param[in] ambient_air_temp_f Ambient air temperature @unitb{\degreeFahrenheit} (default: 60)
 * @return Total heat loss @unitb{\btu\per\hour}
 */
double totalHeatLoss(
    const double flue_gas_temperature,
    const double excess_air,
    const double combustion_air_temperature,
    const double fuel_temperature,
    const double moisture_in_air_combustion,
    const double ash_discharge_temperature,
    const double unburned_carbon_in_ash,
    const double carbon,
    const double hydrogen,
    const double sulphur,
    const double inert_ash,
    const double o2,
    const double moisture,
    const double nitrogen,
    const double ambient_air_temp_f = 60);
    
/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @brief Calculates excess air percentage given flue gas O2 levels using iterative algorithm.
 * @param[in] flue_gas_o2 O2 percentage in flue gas @unitb{\percent}
 * @param[in] carbon Percent carbon in fuel @unitb{\percent}
 * @param[in] hydrogen Percent hydrogen in fuel @unitb{\percent}
 * @param[in] sulphur Percent sulphur in fuel @unitb{\percent}
 * @param[in] inert_ash Percent inert ash in fuel @unitb{\percent}
 * @param[in] o2 Percent oxygen in fuel @unitb{\percent}
 * @param[in] moisture Percent moisture in fuel @unitb{\percent}
 * @param[in] nitrogen Percent nitrogen in fuel @unitb{\percent}
 * @param[in] moisture_in_air_combustion Percent moisture in combustion air @unitb{\percent}
 * @return Calculated excess air percentage @unitb{\unitless}
 */
double calculateExcessAirFromFlueGasO2(double flue_gas_o2, double carbon, double hydrogen, double sulphur,
                                       double inert_ash, double o2, double moisture, double nitrogen,
                                       double moisture_in_air_combustion);

/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @brief Calculates flue gas O2 fraction given excess air and fuel composition.
 * @param[in] excess_air Excess air as fraction (e.g. 0.09 for 9%) @unitb{\unitless}
 * @param[in] carbon Percent carbon in fuel @unitb{\percent}
 * @param[in] hydrogen Percent hydrogen in fuel @unitb{\percent}
 * @param[in] sulphur Percent sulphur in fuel @unitb{\percent}
 * @param[in] inert_ash Percent inert ash in fuel @unitb{\percent}
 * @param[in] o2 Percent oxygen in fuel @unitb{\percent}
 * @param[in] moisture Percent moisture in fuel @unitb{\percent}
 * @param[in] nitrogen Percent nitrogen in fuel @unitb{\percent}
 * @param[in] moisture_in_air_combustion Percent moisture in combustion air @unitb{\percent}
 * @return Calculated O2 fraction in flue gas @unitb{\unitless}
 */
double calculateFlueGasO2(double excess_air, double carbon, double hydrogen, double sulphur, double inert_ash,
                          double o2, double moisture, double nitrogen, double moisture_in_air_combustion);

/**
 * @ingroup solid_liquid_flue_gas_material_calculator
 * @brief Calculates the heating value of the fuel based on composition.
 * @param[in] carbon Percent carbon in fuel @unitb{\percent}
 * @param[in] hydrogen Percent hydrogen in fuel @unitb{\percent}
 * @param[in] sulphur Percent sulphur in fuel @unitb{\percent}
 * @param[in] inert_ash Percent inert ash in fuel @unitb{\percent}
 * @param[in] o2 Percent oxygen in fuel @unitb{\percent}
 * @param[in] moisture Percent moisture in fuel @unitb{\percent}
 * @param[in] nitrogen Percent nitrogen in fuel @unitb{\percent}
 * @return Heating value of the fuel @unitb{\btu\per\pound}
 */
double calculateHeatingValueFuel(double carbon, double hydrogen, double sulphur, double inert_ash, double o2,
                                 double moisture, double nitrogen);

}; // namespace solid_liquid_flue_gas_material
