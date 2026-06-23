#include "compressedAir/assessment/compressor_eem.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Compressor EEM assessment preserves legacy expected values", "[compressed-air][assessment]") {
    auto redAirLeak = compressor_eem::reduceAirLeaks(473, 100, 10, 0.5);
    CHECK(redAirLeak.reducedLeakAirflowAcfm == Approx(5));
    CHECK(redAirLeak.adjustedUseAirflowAcfm == Approx(95));
    CHECK(redAirLeak.adjustedUseFraction == Approx(0.20084).epsilon(0.005));

    auto endUseEff = compressor_eem::improveEndUseEfficiency(473, 236, 20);
    CHECK(endUseEff.reducedAirflowAcfm == Approx(216));
    CHECK(endUseEff.reducedAirflowFraction == Approx(0.45666));

    auto redAirPressure = compressor_eem::reduceSystemAirPressure(473, 100, 100, 85.4, 5, 14.7, 14.7);
    CHECK(redAirPressure.adjustedFullLoadPressurePsig == Approx(95));
    CHECK(redAirPressure.adjustedFullLoadPowerKw == Approx(82.972));
    CHECK(redAirPressure.adjustedUseAirflowAcfm == Approx(97.384));
    CHECK(redAirPressure.adjustedUseFraction == Approx(0.2059).epsilon(0.005));

    auto cascadingSetPoint = compressor_eem::adjustCascadingSetPoint(2578, 1000, 100, 414.4, 105, 14.7, 14.7);
    CHECK(cascadingSetPoint.adjustedFullLoadPowerKw == Approx(425.82));
    CHECK(cascadingSetPoint.adjustedUseAirflowAcfm == Approx(1026.16));
    CHECK(cascadingSetPoint.adjustedUseFraction == Approx(0.39804313));

    auto pressureReductionSaving = compressor_eem::pressureReductionSaving(8760, 0.066, 75, 125, 110, 100, 14.7, 14.7);
    CHECK(pressureReductionSaving.powerSavingsKw == Approx(3.6031));
    CHECK(pressureReductionSaving.energySavingsKwh == Approx(31563.3423));
    CHECK(pressureReductionSaving.costSavings == Approx(2083.18));

    CHECK(compressor_eem::adjustedPower(75, 125, 110, 14.7, 14.7) == Approx(69.9653));
    CHECK(compressor_eem::pressureReducedAirflow(1000, 95, 14.7, 100, 14.7) == Approx(973.8448));

    auto sequencerSetPoints = compressor_eem::automaticSequencerSetPoints(100, 4);
    CHECK(sequencerSetPoints.fullLoadPressurePsig == Approx(96));
    CHECK(sequencerSetPoints.upperPressurePsig == Approx(104));
}
