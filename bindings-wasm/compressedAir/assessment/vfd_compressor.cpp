#include <emscripten/bind.h>

#include "compressedAir/assessment/vfd_compressor.h"

using namespace emscripten;
using namespace compressed_air::assessment;

EMSCRIPTEN_BINDINGS(vfd_compressor_assessment)
{
    class_<VariableFrequencyDriveCompressor>("VariableFrequencyDriveCompressor")
        .constructor<double, double, double, double, double, double, double>()
        .function("calculateFromPowerFraction", &VariableFrequencyDriveCompressor::calculateFromPowerFraction)
        .function("calculateFromCapacityFraction", &VariableFrequencyDriveCompressor::calculateFromCapacityFraction)
        .function("calculateFromMeasuredPower", &VariableFrequencyDriveCompressor::calculateFromMeasuredPower)
        .function("calculateFromMeasuredCapacity", &VariableFrequencyDriveCompressor::calculateFromMeasuredCapacity)
        .function("calculateFromElectrical", &VariableFrequencyDriveCompressor::calculateFromElectrical);
}
