#include "compressedAir/assessment/load_unload_compressor.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Load/unload compressor assessment preserves legacy expected values", "[compressed-air][assessment]") {
    auto cLUL   = LoadUnloadCompressor(166.5, 1048, 1048 / 7.481, 175.5, 100, 110, 5, 10.1, 14.7, CompressorType::Screw,
                                         CompressorLubricant::Injected);
    auto resLUL = cLUL.calculateFromPowerFraction(0.94);
    CHECK(resLUL.powerKw == Approx(156.51));
    CHECK(resLUL.powerFraction == Approx(0.94));
    resLUL = cLUL.calculateFromCapacityFraction(0.895);
    CHECK(resLUL.airflowAcfm == Approx(937.96));
    CHECK(resLUL.airflowFraction == Approx(0.895));
    resLUL = cLUL.calculateFromMeasuredPower(156);
    CHECK(resLUL.powerKw == Approx(156));
    CHECK(resLUL.powerFraction == Approx(0.93693));
    resLUL = cLUL.calculateFromMeasuredCapacity(937);
    CHECK(resLUL.airflowAcfm == Approx(937));
    CHECK(resLUL.airflowFraction == Approx(0.89408));
    resLUL = cLUL.calculateFromElectrical(440, 2.467, 50);
    CHECK(resLUL.powerKw == Approx(94.002568));
    CHECK(resLUL.powerFraction == Approx(0.56458));

    // MODULATION W/ UNLOAD
    auto cMUL   = ModulationWithUnloadCompressor(166.5, 1048, 1048 / 7.481, 175.5, 107.5, 100, 110, 5, 14.7);
    auto resMUL = cMUL.calculateFromPowerFraction(0.94);
    CHECK(resMUL.powerKw == Approx(156.51));
    CHECK(resMUL.powerFraction == Approx(0.94));
    resMUL = cMUL.calculateFromCapacityFraction(0.895);
    CHECK(resMUL.airflowAcfm == Approx(937.96));
    CHECK(resMUL.airflowFraction == Approx(0.895));
    resMUL = cMUL.calculateFromMeasuredPower(156);
    CHECK(resMUL.powerKw == Approx(156));
    CHECK(resMUL.powerFraction == Approx(0.93693));
    resMUL = cMUL.calculateFromMeasuredCapacity(937);
    CHECK(resMUL.airflowAcfm == Approx(937));
    CHECK(resMUL.airflowFraction == Approx(0.89408));
    resMUL = cMUL.calculateFromElectrical(440, 2.467, 50);
    CHECK(resMUL.powerKw == Approx(0));
    CHECK(resMUL.powerFraction == Approx(0));

    resMUL = cMUL.calculateFromCapacityFraction(0.97);
    CHECK(resMUL.airflowAcfm == Approx(1016.56));
    CHECK(resMUL.airflowFraction == Approx(0.97));
}
