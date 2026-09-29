#include <emscripten/bind.h>

#include "compressedAir/assessment/centrifugal_compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(centrifugal_compressor_assessment)
{
    class_<CentrifugalLoadUnloadCompressor>("CentrifugalLoadUnloadCompressor")
        .constructor<double, double, double>()
        .function("calculateFromPowerFraction", &CentrifugalLoadUnloadCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &CentrifugalLoadUnloadCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &CentrifugalLoadUnloadCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &CentrifugalLoadUnloadCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &CentrifugalLoadUnloadCompressor::calculateFromElectrical)
        .function("adjustDischargePressure", &CentrifugalLoadUnloadCompressor::adjustDischargePressure)
        .property("adjustedFullLoadAirflowAcfm", &CentrifugalLoadUnloadCompressor::adjustedFullLoadAirflowAcfm);

    class_<CentrifugalModulationUnloadCompressor>("CentrifugalModulationUnloadCompressor")
        .constructor<double, double, double, double, double, double>()
        .function("calculateFromPowerFraction", &CentrifugalModulationUnloadCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction",
                  &CentrifugalModulationUnloadCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &CentrifugalModulationUnloadCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity",
                  &CentrifugalModulationUnloadCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &CentrifugalModulationUnloadCompressor::calculateFromElectrical)
        .function("adjustDischargePressure", &CentrifugalModulationUnloadCompressor::adjustDischargePressure)
        .property("adjustedFullLoadAirflowAcfm",
                  &CentrifugalModulationUnloadCompressor::adjustedFullLoadAirflowAcfm)
        .property("adjustedMaxAirflowAcfm", &CentrifugalModulationUnloadCompressor::adjustedMaxAirflowAcfm);

    class_<CentrifugalBlowOffCompressor>("CentrifugalBlowOffCompressor")
        .constructor<double, double, double, double>()
        .function("calculateFromPowerFraction", &CentrifugalBlowOffCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &CentrifugalBlowOffCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &CentrifugalBlowOffCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &CentrifugalBlowOffCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &CentrifugalBlowOffCompressor::calculateFromElectrical)
        .function("adjustDischargePressure", &CentrifugalBlowOffCompressor::adjustDischargePressure)
        .property("adjustedFullLoadAirflowAcfm", &CentrifugalBlowOffCompressor::adjustedFullLoadAirflowAcfm);
}
