#include <emscripten/bind.h>

#include "compressedAir/assessment/start_stop_compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(start_stop_compressor_assessment)
{
    class_<StartStopCompressor>("StartStopCompressor")
        .constructor<double, double, double, double>()
        .function("calculateFromPowerFraction", &StartStopCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &StartStopCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &StartStopCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &StartStopCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &StartStopCompressor::calculateFromElectrical)
        .function("applyPressureInletCorrection", &StartStopCompressor::applyPressureInletCorrection)
        .property("adjustedFullLoadPowerKw", &StartStopCompressor::adjustedFullLoadPowerKw)
        .property("adjustedFullLoadAirflowAcfm", &StartStopCompressor::adjustedFullLoadAirflowAcfm)
        .property("adjustedMaxPowerKw", &StartStopCompressor::adjustedMaxPowerKw)
        .property("adjustedMaxAirflowAcfm", &StartStopCompressor::adjustedMaxAirflowAcfm);
}
