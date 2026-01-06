#include <string>
#include <emscripten/bind.h>
#include "steam/water_heating_using_flue.h"

using namespace emscripten;
using namespace water_heating_using_flue;

EMSCRIPTEN_BINDINGS(water_heating_using_flue_class) {
	value_object<WaterHeatingUsingFlueResults>("WaterHeatingUsingFlueOutput")
		.field("flowFlueGas", &WaterHeatingUsingFlueResults::flue_gas_mass_flow)
		.field("effBoiler", &WaterHeatingUsingFlueResults::boiler_available_heat)
		.field("enthalpySteam", &WaterHeatingUsingFlueResults::steam_specific_enthalpy)
		.field("enthalpyFW", &WaterHeatingUsingFlueResults::feedwater_specific_enthalpy)
		.field("flowSteam", &WaterHeatingUsingFlueResults::steam_mass_flow)
		.field("flowFW", &WaterHeatingUsingFlueResults::feedwater_mass_flow)
		.field("specheatFG", &WaterHeatingUsingFlueResults::flue_gas_specific_heat)
		.field("heatCapacityFG", &WaterHeatingUsingFlueResults::flue_gas_heat_capacity)
		.field("specheatFW", &WaterHeatingUsingFlueResults::feedwater_specific_heat)
		.field("heatCapacityFW", &WaterHeatingUsingFlueResults::feedwater_heat_capacity)
		.field("heatCapacityMin", &WaterHeatingUsingFlueResults::min_heat_capacity)
		.field("ratingHeatRecFW", &WaterHeatingUsingFlueResults::recovered_heat)
		.field("tempFlueGasOut", &WaterHeatingUsingFlueResults::flue_gas_exit_temp)
		.field("tempFWOut", &WaterHeatingUsingFlueResults::feedwater_exit_temp)
		.field("energySavingsBoiler", &WaterHeatingUsingFlueResults::annual_energy_savings)
		.field("costSavingsBoiler", &WaterHeatingUsingFlueResults::annual_cost_savings);

	enum_<SteamCondition>("SteamConditionType")
		.value("Superheated", SteamCondition::Superheated)
		.value("Saturated", SteamCondition::Saturated);

	
	// Parameters for waterHeatingUsingFlue:
	//   gas_compositions (Fuel gas composition for flue gas calculations)
	//   temp_flue_gas_f (Flue gas temperature, °F)
	//   perc_o2 (Oxygen percentage in flue gas, fraction)
	//   temp_comb_air_f (Combustion air temperature, °F)
	//   moist_comb_air (Combustion air moisture, fraction)
	//   rating_boiler (Boiler rating, GJ/hr)
	//   pr_steam (Steam pressure, MPa)
	//   temp_ambient_air_f (Ambient air temperature, °F)
	//   temp_steam_f (Steam temperature, °F)
	//   temp_fw (Feedwater temperature, °F)
	//   perc_blow_down (Blowdown percentage, fraction)
	//   eff_hx (Heat exchanger efficiency, fraction)
	//   op_hours (Operating hours, hr)
	//   cost_fuel (Fuel cost, $/GJ)
	//   hhv_fuel (Fuel higher heating value, kJ/Nm3)
	//   cond_steam (Steam condition, Superheated or Saturated)
	//   fuel_temp_f (Fuel temperature, °F; default: 60)
	function("waterHeatingUsingFlue", &waterHeatingUsingFlue);
}
