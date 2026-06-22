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
