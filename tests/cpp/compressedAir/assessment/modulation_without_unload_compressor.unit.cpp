#include "compressedAir/assessment/modulation_without_unload_compressor.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Modulation without unload compressor assessment preserves legacy expected values", "[compressed-air][assessment]") {
    auto cMWOuL   = ModulationWithoutUnloadCompressor(85.4, 473, 55.3);
    auto resMWOuL = cMWOuL.calculateFromPowerFraction(0.89);
    CHECK(resMWOuL.powerKw == Approx(76.006));
    CHECK(resMWOuL.airflowAcfm == Approx(325.38));
    CHECK(resMWOuL.powerFraction == Approx(0.89));
    CHECK(resMWOuL.airflowFraction == Approx(0.6879));
    resMWOuL = cMWOuL.calculateFromCapacityFraction(1.66173);
    CHECK(resMWOuL.powerKw == Approx(85.4));
    CHECK(resMWOuL.airflowAcfm == Approx(786));
    CHECK(resMWOuL.powerFraction == Approx(1));
    CHECK(resMWOuL.airflowFraction == Approx(1.66173));
    resMWOuL = cMWOuL.calculateFromMeasuredPower(75.9);
    CHECK(resMWOuL.powerKw == Approx(75.9));
    CHECK(resMWOuL.airflowAcfm == Approx(323.7142857143));
    CHECK(resMWOuL.powerFraction == Approx(0.88875));
    CHECK(resMWOuL.airflowFraction == Approx(0.68438));
    resMWOuL = cMWOuL.calculateFromMeasuredCapacity(786);
    CHECK(resMWOuL.powerKw == Approx(85.4));
    CHECK(resMWOuL.airflowAcfm == Approx(786));
    CHECK(resMWOuL.powerFraction == Approx(1));
    CHECK(resMWOuL.airflowFraction == Approx(1.66173));
    resMWOuL = cMWOuL.calculateFromElectrical(440, 2.467, 50);
    CHECK(resMWOuL.powerKw == Approx(94.0026));
    CHECK(resMWOuL.powerFraction == Approx(1.10073));

    cMWOuL.applyPressureInletCorrection(473, 105, 1.4, 100, 14.5, 0.917, 110, 110, 14.7, true, 14.7);
    CHECK(cMWOuL.adjustedFullLoadPowerKw() == Approx(90.0736));
    CHECK(cMWOuL.adjustedFullLoadAirflowAcfm() == Approx(469.46));

    resMWOuL = cMWOuL.calculateFromPowerFraction(0.63);
    CHECK(resMWOuL.powerKw == Approx(56.74637));
    CHECK(resMWOuL.airflowAcfm == Approx(19.52675));
    CHECK(resMWOuL.powerFraction == Approx(0.63));
    CHECK(resMWOuL.airflowFraction == Approx(0.04159394));

    resMWOuL = cMWOuL.calculateFromPowerFraction(0.89);
    CHECK(resMWOuL.powerKw == Approx(80.16551));
    CHECK(resMWOuL.airflowAcfm == Approx(335.697));
    CHECK(resMWOuL.powerFraction == Approx(0.89));
    CHECK(resMWOuL.airflowFraction == Approx(0.71506));
    resMWOuL = cMWOuL.calculateFromCapacityFraction(1.66173);
    CHECK(resMWOuL.powerKw == Approx(90.0736));
    CHECK(resMWOuL.airflowAcfm == Approx(780.116));
    CHECK(resMWOuL.powerFraction == Approx(1));
    CHECK(resMWOuL.airflowFraction == Approx(1.66173));
    resMWOuL = cMWOuL.calculateFromMeasuredPower(75.9);
    CHECK(resMWOuL.powerKw == Approx(75.9));
    CHECK(resMWOuL.airflowAcfm == Approx(278.1105));
    CHECK(resMWOuL.powerFraction == Approx(0.8426441883));
    CHECK(resMWOuL.airflowFraction == Approx(0.5924));
    resMWOuL = cMWOuL.calculateFromMeasuredCapacity(786);
    CHECK(resMWOuL.powerKw == Approx(90.0736));
    CHECK(resMWOuL.airflowAcfm == Approx(786));
    CHECK(resMWOuL.powerFraction == Approx(1));
    CHECK(resMWOuL.airflowFraction == Approx(1.67426));
    resMWOuL = cMWOuL.calculateFromElectrical(440, 2.467, 50);
    CHECK(resMWOuL.powerKw == Approx(94.00257));
    CHECK(resMWOuL.powerFraction == Approx(1.04362));
}

TEST_CASE("Modulation helper mode inverts requested power over the modulation curve",
          "[compressed-air][assessment]") {
    auto helper = ModulationWithoutUnloadCompressor(166.5, 1048, 107.5, 1.0, false, CompressorType::Screw, 0.7,
                                                   175.5);

    auto low = helper.calculateFromPowerFraction(0.94);
    CHECK(low.powerKw == Approx(156.51));
    CHECK(low.airflowAcfm == Approx(670.0034));
    CHECK(low.powerFraction == Approx(0.94));
    CHECK(low.airflowFraction == Approx(0.6393162));
    auto low_round_trip = helper.calculateFromCapacityFraction(low.airflowFraction);
    CHECK(low_round_trip.powerKw == Approx(low.powerKw));
    CHECK(low_round_trip.airflowAcfm == Approx(low.airflowAcfm));
    CHECK(low_round_trip.powerFraction == Approx(low.powerFraction));
    CHECK(low_round_trip.airflowFraction == Approx(low.airflowFraction));

    auto high = helper.calculateFromPowerFraction(0.98);
    CHECK(high.powerKw == Approx(163.17));
    CHECK(high.airflowAcfm == Approx(802.5709));
    CHECK(high.powerFraction == Approx(0.98));
    CHECK(high.airflowFraction == Approx(0.765812));
    auto high_round_trip = helper.calculateFromCapacityFraction(high.airflowFraction);
    CHECK(high_round_trip.powerKw == Approx(high.powerKw));
    CHECK(high_round_trip.airflowAcfm == Approx(high.airflowAcfm));
    CHECK(high_round_trip.powerFraction == Approx(high.powerFraction));
    CHECK(high_round_trip.airflowFraction == Approx(high.airflowFraction));
}
