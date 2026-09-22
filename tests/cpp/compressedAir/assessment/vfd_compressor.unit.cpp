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

TEST_CASE("Variable frequency drive boundaries reproduce their engineering anchors",
          "[compressed-air][assessment][vfd]") {
    VariableFrequencyDriveCompressor compressor(174.4, 115, 55.8, 11.2, 1009, 605, 202);

    const auto no_load = compressor.calculateFromCapacityFraction(0.0);
    CHECK(no_load.powerKw == Approx(11.2));
    CHECK(no_load.airflowAcfm == 0.0);

    const auto below_no_load = compressor.calculateFromPowerFraction(11.1 / 174.4);
    CHECK(below_no_load.powerKw == 0.0);
    CHECK(below_no_load.airflowAcfm == 0.0);

    const auto turndown = compressor.calculateFromCapacityFraction(202.0 / 1009.0);
    CHECK(turndown.powerKw == Approx(55.8));
    CHECK(turndown.airflowAcfm == Approx(202.0));
    const auto inverse_turndown = compressor.calculateFromPowerFraction(55.8 / 174.4);
    CHECK(inverse_turndown.airflowAcfm == Approx(202.0));

    const auto full_load = compressor.calculateFromCapacityFraction(1.0);
    CHECK(full_load.powerKw == Approx(174.4));
    CHECK(full_load.airflowAcfm == Approx(1009.0));
}
