#include "compressedAir/assessment/vfd_compressor.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Variable frequency drive compressor assessment preserves legacy VFD expected values",
          "[compressed-air][assessment][vfd]") {
    VariableFrequencyDriveCompressor compressor(174.4, 115, 55.8, 11.2, 1009, 605, 202);

    const auto result = compressor.calculateFromCapacityFraction(0.31);

    CHECK(result.powerKw == Approx(72.0695));
    CHECK(result.airflowAcfm == Approx(312.79));
    CHECK(result.powerFraction == Approx(0.4132).epsilon(0.001));
    CHECK(result.airflowFraction == Approx(0.31));
}
