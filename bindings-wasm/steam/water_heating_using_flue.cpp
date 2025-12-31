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

	function("waterHeatingUsingFlue", &waterHeatingUsingFlue);
}
