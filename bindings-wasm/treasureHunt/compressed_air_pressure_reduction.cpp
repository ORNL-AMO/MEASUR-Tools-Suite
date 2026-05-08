#include <emscripten/bind.h>

#include "treasureHunt/compressed_air_pressure_reduction.h"

using namespace emscripten;
using namespace compressed_air_pressure_reduction;

EMSCRIPTEN_BINDINGS(compressedAirPressureReduction_module) {
    // CompressedAirPressureReductionInput:
    //   isBaseline (bool)
    //   hoursPerYear (hours/year)
    //   electricityCost ($/kWh)
    //   compressorPower (kW)
    //   pressure (psi)
    //   proposedPressure (psi)
    //   atmosphericPressure (psi)
    //   pressureRated (psi)
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

    // CompressedAirPressureReductionOutput:
    //   energyUse (kWh/year)
    //   energyCost ($/year)
    value_object<CompressedAirPressureReductionOutput>("CompressedAirPressureReductionOutput")
        .field("energyUse", &CompressedAirPressureReductionOutput::energy_use)
        .field("energyCost", &CompressedAirPressureReductionOutput::energy_cost);

    // compressedAirPressureReduction(input_vec: CompressedAirPressureReductionInputV) -> CompressedAirPressureReductionOutput
    //   input_vec: vector of compressed air pressure reduction inputs
    //   returns: total annual energy use and annual energy cost
    function("compressedAirPressureReduction", &compressedAirPressureReduction);
}
