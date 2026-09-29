#include "compressedAir/assessment/start_stop_compressor.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Start/stop compressor assessment preserves legacy expected values", "[compressed-air][assessment]") {
    auto cSS   = StartStopCompressor(89.5, 560, 1.05, 1);
    auto resSS = cSS.calculateFromPowerFraction(0.205);
    CHECK(resSS.powerKw == Approx(18.3475));
    CHECK(resSS.airflowAcfm == Approx(112));
    CHECK(resSS.powerFraction == Approx(0.205));
    CHECK(resSS.airflowFraction == Approx(0.2));
    resSS = cSS.calculateFromCapacityFraction(0.2);
    CHECK(resSS.powerKw == Approx(18.3475));
    CHECK(resSS.airflowAcfm == Approx(112));
    CHECK(resSS.powerFraction == Approx(0.205));
    CHECK(resSS.airflowFraction == Approx(0.2));
    resSS = cSS.calculateFromMeasuredPower(18.35);
    CHECK(resSS.powerKw == Approx(18.35));
    CHECK(resSS.airflowAcfm == Approx(112.015));
    CHECK(resSS.powerFraction == Approx(0.20502).epsilon(0.005));
    CHECK(resSS.airflowFraction == Approx(0.200027));
    resSS = cSS.calculateFromMeasuredCapacity(112);
    CHECK(resSS.powerKw == Approx(18.3475));
    CHECK(resSS.airflowAcfm == Approx(112));
    CHECK(resSS.powerFraction == Approx(0.205));
    CHECK(resSS.airflowFraction == Approx(0.2));
    resSS = cSS.calculateFromElectrical(440, 2.467, 50);
    CHECK(resSS.powerKw == Approx(94.0026));
    CHECK(resSS.airflowAcfm == Approx(573.827));
    CHECK(resSS.powerFraction == Approx(1.0503));
    CHECK(resSS.airflowFraction == Approx(1.0247));

    cSS.applyPressureInletCorrection(473, 105, 1.4, 100, 14.5, 0.917, 110, 110, 14.7, true, 14.7);
    CHECK(cSS.adjustedFullLoadPowerKw() == Approx(90.0736));
    CHECK(cSS.adjustedFullLoadAirflowAcfm() == Approx(469.46));

    resSS = cSS.calculateFromPowerFraction(0.205);
    CHECK(resSS.powerKw == Approx(18.46509));
    CHECK(resSS.airflowAcfm == Approx(93.891998291));
    CHECK(resSS.powerFraction == Approx(0.205));
    CHECK(resSS.airflowFraction == Approx(0.2));
    resSS = cSS.calculateFromCapacityFraction(0.2);
    CHECK(resSS.powerKw == Approx(18.46501));
    CHECK(resSS.airflowAcfm == Approx(93.892));
    CHECK(resSS.powerFraction == Approx(0.205));
    CHECK(resSS.airflowFraction == Approx(0.2));
    resSS = cSS.calculateFromMeasuredPower(18.35);
    CHECK(resSS.powerKw == Approx(18.35));
    CHECK(resSS.airflowAcfm == Approx(93.3070665796));
    CHECK(resSS.powerFraction == Approx(0.2037222774));
    CHECK(resSS.airflowFraction == Approx(0.1987534414));
    resSS = cSS.calculateFromMeasuredCapacity(112);
    CHECK(resSS.powerKw == Approx(22.0261988222));
    CHECK(resSS.airflowAcfm == Approx(112));
    CHECK(resSS.powerFraction == Approx(0.2445355524));
    CHECK(resSS.airflowFraction == Approx(0.238572));
    resSS = cSS.calculateFromElectrical(440, 2.467, 50);
    CHECK(resSS.powerKw == Approx(94.0026));
    CHECK(resSS.airflowAcfm == Approx(477.9893));
    CHECK(resSS.powerFraction == Approx(1.04362));
    CHECK(resSS.airflowFraction == Approx(1.01816));
}
