#include <string>
#include <emscripten/bind.h>
#include "steam/water_heating_using_exhaust.h"

using namespace emscripten;
using namespace water_heating_using_exhaust;

EMSCRIPTEN_BINDINGS(water_heating_using_exhaust_class) {
	value_object<WaterHeatingUsingExhaustResults>("WaterHeatingUsingExhaustOutput")
		.field("recoveredHeat", &WaterHeatingUsingExhaustResults::recovered_heat)
		.field("hotWaterFlow", &WaterHeatingUsingExhaustResults::hot_water_flow)
		.field("tonsRefrigeration", &WaterHeatingUsingExhaustResults::tons_refrigeration)
		.field("capacityChiller", &WaterHeatingUsingExhaustResults::capacity_chiller)
		.field("electricalEnergy", &WaterHeatingUsingExhaustResults::electrical_energy);

	// Parameters for waterHeatingUsingExhaust:
	//   available_heat (fraction)
	//   heat_input (Btu/hr)
	//   hx_efficiency (fraction)
	//   chiller_in_temperature (°F)
	//   chiller_out_temperature (°F)
	//   cop_chiller (fraction)
	//   chiller_efficiency (fraction)
	//   cop_compressor (fraction)
	function("waterHeatingUsingExhaust", &waterHeatingUsingExhaust);
}
