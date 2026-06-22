#include <emscripten/bind.h>

#include "compressedAir/assessment/modulation_without_unload_compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(modulation_without_unload_compressor_assessment)
{
    class_<ModulationWithoutUnloadCompressor>("ModulationWithoutUnloadCompressor")
        .constructor<double, double, double>()
        .constructor<double, double, double, double, bool, CompressorType, double, double>()
        .function("calculateFromPowerFraction", &ModulationWithoutUnloadCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &ModulationWithoutUnloadCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &ModulationWithoutUnloadCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &ModulationWithoutUnloadCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &ModulationWithoutUnloadCompressor::calculateFromElectrical)
        .function("applyPressureInletCorrection",
                  &ModulationWithoutUnloadCompressor::applyPressureInletCorrection)
        .property("adjustedFullLoadPowerKw", &ModulationWithoutUnloadCompressor::adjustedFullLoadPowerKw)
        .property("adjustedFullLoadAirflowAcfm", &ModulationWithoutUnloadCompressor::adjustedFullLoadAirflowAcfm)
        .property("adjustedMaxPowerKw", &ModulationWithoutUnloadCompressor::adjustedMaxPowerKw)
        .property("adjustedMaxAirflowAcfm", &ModulationWithoutUnloadCompressor::adjustedMaxAirflowAcfm);
}
