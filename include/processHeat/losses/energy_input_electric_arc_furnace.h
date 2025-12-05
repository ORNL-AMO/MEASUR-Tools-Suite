#pragma once

/**
 * @ingroup energy_input_electric_arc_furnace_calculator
 * @file energy_input_electric_arc_furnace.h
 * @authors Autumn Ferree, Mark Root
 *
 * @copybrief energy_input_electric_arc_furnace
 */

/**
 * @ingroup energy_input_electric_arc_furnace_calculator
 * @namespace energy_input_electric_arc_furnace
 * @copybrief energy_input_electric_arc_furnace_calculator
 */
namespace energy_input_electric_arc_furnace {

/**
 * @ingroup energy_input_electric_arc_furnace_calculator
 * @brief Calculates the total chemical energy input for an Electric Arc Furnace (EAF).
 * @details Computes the total chemical energy input from natural gas, coal/carbon injection, electrodes, and other fuels.
 * @param[in] natural_gas_heat_input Total heat input from natural gas @unitb{\mega\mega\btu\per\hour}
 * @param[in] coal_carbon_injection Mass of coal/carbon injection @unitb{\pound\per\hour}
 * @param[in] coal_heating_value Heating value of coal/carbon @unitb{\btu\per\pound}
 * @param[in] electrode_use Electrode use @unitb{\pound\per\hour}
 * @param[in] electrode_heating_value Electrode heating value @unitb{\btu\per\pound}
 * @param[in] other_fuels Heat supplied from other sources @unitb{\mega\mega\btu\per\hour}
 * @return Total chemical energy input @unitb{\btu\per\hour}
 */
double totalChemicalEnergyInput(double natural_gas_heat_input, double coal_carbon_injection, double coal_heating_value,
                               double electrode_use, double electrode_heating_value, double other_fuels);

/**
 * @ingroup energy_input_electric_arc_furnace_calculator
 * @brief Calculates the total heat delivered to the EAF.
 * @details Computes the total heat delivered to the EAF, including electric power supplied.
 * @param[in] total_chemical_energy_input Total chemical energy input @unitb{\btu\per\hour}
 * @param[in] electricity_input Total electric power supplied @unitb{\kilowatt\hour\per\hour}
 * @return Total heat delivered to EAF @unitb{\btu\per\hour}
 */
double totalHeatDelivered(double total_chemical_energy_input, double electricity_input);

} // namespace energy_input_electric_arc_furnace
