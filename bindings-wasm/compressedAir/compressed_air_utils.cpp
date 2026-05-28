#include "compressedAir/compressed_air_utils.h"

#include <emscripten/bind.h>

using namespace emscripten;
using compressed_air_utils::CompressorElectricityData;

EMSCRIPTEN_BINDINGS(compressedAir_types) {
    value_object<CompressorElectricityData>("CompressorElectricityData")
        .field("compressorControlAdjustment", &CompressorElectricityData::compressor_control_adjustment)
        .field("compressorSpecificPower",     &CompressorElectricityData::compressor_specific_power);
}
