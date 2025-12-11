#pragma once
#include "physics/gas_composition.h"
using namespace gas_composition;

/**
 * @ingroup gas_flue_gas_material_heat_loss_calculator
 * @file gas_flue_gas_material_heat_loss.h
 * @authors Gina Accawi, Preston Shires, Omer Aziz, Mark Root
 *
 * @copybrief gas_flue_gas_material_heat_loss
 */

/**
 * @ingroup gas_flue_gas_material_heat_loss_calculator
 * @namespace gas_flue_gas_material_heat_loss
 * @brief Contains functions for flue gas heat loss calculations.
 */
namespace gas_flue_gas_material_heat_loss {

/**
 * @ingroup process_heat_loss_calculator
 * @brief Calculates the total heat loss for flue gas using the provided parameters.
 * @param[in] flue_gas_temperature Furnace Flue Gas Temperature @unitb{\degreeFahrenheit}
 * @param[in] excess_air_percentage Percent Excess Air (e.g. 9 for 9%) @unitb{\unitless}
 * @param[in] combustion_air_temperature Combustion Air Temperature @unitb{\degreeFahrenheit}
 * @param[in] compositions User defined gas compositions
 * @param[in] fuel_temperature Temperature of fuel @unitb{\degreeFahrenheit}
 * @return Total heat loss @unitb{\btu\per\hour}
 */
double totalHeatLoss(double flue_gas_temperature,
                     double excess_air_percentage,
                     double combustion_air_temperature,
                     const GasComposition& compositions,
                     double fuel_temperature);

} // namespace gas_flue_gas_material_heat_loss
