#include <emscripten/bind.h>

#include "compressedAir/assessment/load_unload_compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(load_unload_compressor_assessment)
{
    class_<LoadUnloadCompressor>("LoadUnloadCompressor")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, CompressorType,
                     CompressorLubricant, CompressorControl, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, CompressorType,
                     CompressorLubricant, CompressorControl, double, double, double, double, double>()
        .function("calculateFromPowerFraction", &LoadUnloadCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &LoadUnloadCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &LoadUnloadCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &LoadUnloadCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &LoadUnloadCompressor::calculateFromElectrical)
        .function("applyPressureInletCorrection", &LoadUnloadCompressor::applyPressureInletCorrection)
        .property("adjustedFullLoadPowerKw", &LoadUnloadCompressor::adjustedFullLoadPowerKw)
        .property("adjustedFullLoadAirflowAcfm", &LoadUnloadCompressor::adjustedFullLoadAirflowAcfm)
        .property("adjustedMaxPowerKw", &LoadUnloadCompressor::adjustedMaxPowerKw)
        .property("adjustedMaxAirflowAcfm", &LoadUnloadCompressor::adjustedMaxAirflowAcfm);

    class_<ModulationWithUnloadCompressor, base<LoadUnloadCompressor>>("ModulationWithUnloadCompressor")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, double,
                     CompressorControl, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, double,
                     CompressorControl, double, double, double>()
        .function("calculateFromPowerFraction", &ModulationWithUnloadCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &ModulationWithUnloadCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &ModulationWithUnloadCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &ModulationWithUnloadCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &ModulationWithUnloadCompressor::calculateFromElectrical)
        .function("applyPressureInletCorrection", &ModulationWithUnloadCompressor::applyPressureInletCorrection)
        .property("adjustedFullLoadPowerKw", &ModulationWithUnloadCompressor::adjustedFullLoadPowerKw)
        .property("adjustedFullLoadAirflowAcfm", &ModulationWithUnloadCompressor::adjustedFullLoadAirflowAcfm)
        .property("adjustedMaxPowerKw", &ModulationWithUnloadCompressor::adjustedMaxPowerKw)
        .property("adjustedMaxAirflowAcfm", &ModulationWithUnloadCompressor::adjustedMaxAirflowAcfm);
}
