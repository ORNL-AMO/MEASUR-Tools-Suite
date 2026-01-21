#include <string>
#include <emscripten/bind.h>
#include "processHeat/air_heating_using_exhaust.h"

using namespace emscripten;
using namespace air_heating_using_exhaust;

EMSCRIPTEN_BINDINGS(air_heating_using_exhaust_module) {
	// Bind the result struct
	value_object<AirHeatingUsingExhaustResults>("AirHeatingUsingExhaustResults")
		.field("hxColdAir", &AirHeatingUsingExhaustResults::hx_cold_air)
		.field("hxOutletExhaust", &AirHeatingUsingExhaustResults::hx_outlet_exhaust)
		.field("energySavings", &AirHeatingUsingExhaustResults::energy_savings)
		.field("heatCapacityFlue", &AirHeatingUsingExhaustResults::heat_capacity_flue)
		.field("heatCapacityAir", &AirHeatingUsingExhaustResults::heat_capacity_air);

	// Parameters for airHeatingUsingExhaustWithGasComposition:
	//   gas_composition (GasComposition)
	//   flue_temperature (°F)
	//   excess_air (fraction)
	//   fire_rate (MMBtu/hr)
	//   airflow (scfm)
	//   inlet_temperature (°F)
	//   heater_efficiency (fraction)
	//   hx_efficiency (fraction)
	//   operating_hours (hr)
	function("airHeatingUsingExhaustWithGasComposition", &airHeatingUsingExhaustWithGasComposition);

	// Parameters for airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial:
	//   material (SolidLiquidFlueGasMaterial)
	//   flue_temperature (°F)
	//   excess_air (fraction)
	//   fire_rate (MMBtu/hr)
	//   airflow (scfm)
	//   inlet_temperature (°F)
	//   heater_efficiency (fraction)
	//   hx_efficiency (fraction)
	//   operating_hours (hr)
	function("airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial", &airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial);
}
