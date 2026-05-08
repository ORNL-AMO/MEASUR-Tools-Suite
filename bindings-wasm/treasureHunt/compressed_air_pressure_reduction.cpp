#include <emscripten/bind.h>

#include "treasureHunt/compressed_air_pressure_reduction.h"

using namespace emscripten;
using namespace compressed_air_pressure_reduction;

EMSCRIPTEN_BINDINGS(compressedAirPressureReduction_module) {
    value_object<CompressedAirPressureReductionInput>("CompressedAirPressureReductionInput")
        .field("isBaseline", &CompressedAirPressureReductionInput::is_baseline)
        .field("hoursPerYear", &CompressedAirPressureReductionInput::hours_per_year)
        .field("electricityCost", &CompressedAirPressureReductionInput::electricity_cost)
        .field("compressorPower", &CompressedAirPressureReductionInput::compressor_power)
        .field("pressure", &CompressedAirPressureReductionInput::pressure)
        .field("proposedPressure", &CompressedAirPressureReductionInput::proposed_pressure)
        .field("atmosphericPressure", &CompressedAirPressureReductionInput::atmospheric_pressure)
        .field("pressureRated", &CompressedAirPressureReductionInput::pressure_rated);

    register_vector<CompressedAirPressureReductionInput>("CompressedAirPressureReductionInputV");

    value_object<CompressedAirPressureReductionOutput>("CompressedAirPressureReductionOutput")
        .field("energyUse", &CompressedAirPressureReductionOutput::energy_use)
        .field("energyCost", &CompressedAirPressureReductionOutput::energy_cost);

    function("compressedAirPressureReduction", &compressedAirPressureReduction);
    function("baselineReduction", &baselineReduction);
    function("modificationReduction", &modificationReduction);
}
