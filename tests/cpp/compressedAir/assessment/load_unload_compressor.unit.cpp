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

    auto cMULHelper = ModulationWithUnloadCompressor(
        166.5, 1048, 1048 / 7.481, 175.5, 107.5, 100, 110, 5, 14.7, 90);
    auto helperResult = cMULHelper.calculateFromPowerFraction(0.996);
    CHECK(helperResult.powerKw == Approx(165.834));
    CHECK(helperResult.airflowAcfm == Approx(946.9248));
    CHECK(helperResult.powerFraction == Approx(0.996));
    CHECK(helperResult.airflowFraction == Approx(0.9035542));

    helperResult = cMULHelper.calculateFromCapacityFraction(0.9035542);
    CHECK(helperResult.powerKw == Approx(165.834));
    CHECK(helperResult.airflowAcfm == Approx(946.9248));
    CHECK(helperResult.powerFraction == Approx(0.996));
    CHECK(helperResult.airflowFraction == Approx(0.9035542));
}

TEST_CASE("Load/unload measured power above full load uses the high-end load/unload curve",
          "[compressed-air][assessment]") {
    auto compressor = LoadUnloadCompressor(4.6, 12, 200.52093668342548, 4.7, 175, 185, 0, 1.7 / 4.6, 14.7,
                                           CompressorType::Screw, CompressorLubricant::Injected,
                                           CompressorControl::LoadUnload, 1.7, 100, 40, 15, 0);

    const auto result = compressor.calculateFromMeasuredPower(5);

    CHECK(result.powerKw == Approx(5));
    CHECK(result.airflowAcfm == Approx(13.9871));
    CHECK(result.powerFraction == Approx(1.0869565217));
    CHECK(result.airflowFraction == Approx(1.165591));
}

TEST_CASE("Load/unload pressure inlet correction uses compressor type and refreshes unload state",
          "[compressed-air][assessment]") {
    const double storage_volume = 1048 / 7.481;
    auto corrected = LoadUnloadCompressor(166.5, 1048, storage_volume, 175.5, 110, 120, 5, 10.1, 14.7,
                                          CompressorType::Reciprocating);

    corrected.applyPressureInletCorrection(473, 105, 1.4, 100, 14.5, 0.917, 110, 120, 14.7, true, 14.7);

    CHECK(corrected.adjustedFullLoadPowerKw() == Approx(89.3967));
    CHECK(corrected.adjustedFullLoadAirflowAcfm() == Approx(469.4614));
    CHECK(corrected.adjustedMaxPowerKw() == Approx(93.7547));
    CHECK(corrected.adjustedMaxAirflowAcfm() == Approx(465.9138));

    auto expected = LoadUnloadCompressor(corrected.adjustedFullLoadPowerKw(), corrected.adjustedFullLoadAirflowAcfm(),
                                         storage_volume, corrected.adjustedMaxPowerKw(), 110, 120, 5, 10.1, 14.7,
                                         CompressorType::Reciprocating);

    auto corrected_result = corrected.calculateFromCapacityFraction(0.8);
    auto expected_result  = expected.calculateFromCapacityFraction(0.8);
    CHECK(corrected_result.powerKw == Approx(expected_result.powerKw));
    CHECK(corrected_result.airflowAcfm == Approx(expected_result.airflowAcfm));
    CHECK(corrected_result.powerFraction == Approx(expected_result.powerFraction));
    CHECK(corrected_result.airflowFraction == Approx(expected_result.airflowFraction));
}
