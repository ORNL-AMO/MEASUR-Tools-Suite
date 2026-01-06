#pragma once
#include "physics/gas_composition.h"

/**
 * @ingroup water_heating_using_flue_calculator
 * @namespace water_heating_using_flue
 * @brief Water heating using flue calculations for process heating systems.
 */
namespace water_heating_using_flue {

/**
 * @ingroup water_heating_using_flue_calculator
 * @enum SteamCondition
 * @brief Steam condition for calculation (Superheated or Saturated).
 */
enum class SteamCondition { Superheated, Saturated };

/**
 * @ingroup water_heating_using_flue_calculator
 * @struct WaterHeatingUsingFlueResults
 * @brief Results of the water heating using flue calculation.
 * @details Contains all output values from the water heating using flue calculation.
 */
struct WaterHeatingUsingFlueResults {
    double flue_gas_mass_flow = 0;        ///< Flue gas mass flow @unitb{kg/hr}
    double boiler_available_heat = 0;     ///< Boiler available heat (fraction)
    double steam_specific_enthalpy = 0;   ///< Steam specific enthalpy @unitb{kJ/kg}
    double feedwater_specific_enthalpy = 0; ///< Feedwater specific enthalpy @unitb{kJ/kg}
    double steam_mass_flow = 0;           ///< Steam mass flow @unitb{kg/hr}
    double feedwater_mass_flow = 0;       ///< Feedwater mass flow @unitb{kg/hr}
    double flue_gas_specific_heat = 0;    ///< Flue gas specific heat @unitb{kJ/kg\kelvin}
    double flue_gas_heat_capacity = 0;    ///< Flue gas heat capacity @unitb{kJ/hr\kelvin}
    double feedwater_specific_heat = 0;   ///< Feedwater specific heat @unitb{kJ/kg\kelvin}
    double feedwater_heat_capacity = 0;   ///< Feedwater heat capacity @unitb{kJ/hr\kelvin}
    double min_heat_capacity = 0;         ///< Minimum heat capacity @unitb{kJ/hr\kelvin}
    double recovered_heat = 0;            ///< Recovered heat @unitb{kJ/hr}
    double flue_gas_exit_temp = 0;        ///< Flue gas exit temperature @unitb{\kelvin}
    double feedwater_exit_temp = 0;       ///< Feedwater exit temperature @unitb{\kelvin}
    double annual_energy_savings = 0;     ///< Annual energy savings @unitb{GJ/yr}
    double annual_cost_savings = 0;       ///< Annual cost savings @unitb{$/yr}
};

/**
 * @ingroup water_heating_using_flue_calculator
 * @brief Calculates energy and cost savings from using flue gas (waste) heat to heat boiler feed water using a non-condensing heat exchanger.
 * @details Uses process parameters to estimate the benefit of using waste heat for water heating and boiler operation.
 *
 * @param[in] gas_compositions Fuel gas composition for flue gas calculations.
 * @param[in] temp_flue_gas_f Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] perc_o2 Oxygen percentage in flue gas (fraction)
 * @param[in] temp_comb_air_f Combustion air temperature @unitb{\degreeFahrenheit}
 * @param[in] moist_comb_air Combustion air moisture (fraction)
 * @param[in] rating_boiler Boiler rating @unitb{GJ/hr}
 * @param[in] pr_steam Steam pressure @unitb{MPa}
 * @param[in] temp_ambient_air_f Ambient air temperature @unitb{\degreeFahrenheit}
 * @param[in] temp_steam_f Steam temperature @unitb{\degreeFahrenheit}
 * @param[in] temp_fw Feedwater temperature @unitb{\degreeFahrenheit}
 * @param[in] perc_blow_down Blowdown percentage (fraction)
 * @param[in] eff_hx Heat exchanger efficiency (fraction)
 * @param[in] op_hours Operating hours @unitb{hr}
 * @param[in] cost_fuel Fuel cost @unitb{dollar/GJ}
 * @param[in] hhv_fuel Fuel higher heating value @unitb{kJ/Nm3}
 * @param[in] cond_steam Steam condition (Superheated or Saturated)
 * @param[in] fuel_temp_f Fuel temperature @unitb{\degreeFahrenheit} (default: 60)
 * @return WaterHeatingUsingFlueResults struct with all calculated outputs.
 */
WaterHeatingUsingFlueResults waterHeatingUsingFlue(
    const gas_composition::GasComposition& gas_compositions,
    double temp_flue_gas_f,
    double perc_o2,
    double temp_comb_air_f,
    double moist_comb_air,
    double rating_boiler,
    double pr_steam,
    double temp_ambient_air_f,
    double temp_steam_f,
    double temp_fw,
    double perc_blow_down,
    double eff_hx,
    double op_hours,
    double cost_fuel,
    double hhv_fuel,
    SteamCondition cond_steam = SteamCondition::Superheated,
    double fuel_temp_f = 60
);

} // namespace water_heating_using_flue

