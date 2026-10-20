#include "compressedAir/assessment/centrifugal_compressor.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air::assessment;

TEST_CASE("Centrifugal compressor assessment preserves legacy expected values", "[compressed-air][assessment]") {
    auto ccBlow  = CentrifugalBlowOffCompressor(452.3, 3138, 370.9, 2510);
    auto resBOff = ccBlow.calculateFromPowerFraction(0.82, 0.6798);
    CHECK(resBOff.powerKw == Approx(370.886));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.82));
    CHECK(resBOff.airflowFraction == Approx(0.120073));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));
    resBOff = ccBlow.calculateFromCapacityFraction(0.01);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(31.38));
    CHECK(resBOff.powerFraction == Approx(0.820031));
    CHECK(resBOff.airflowFraction == Approx(0.01));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2478.62));
    CHECK(resBOff.blowOffFraction == Approx(0.789873));
    resBOff = ccBlow.calculateFromMeasuredPower(370.9, 0.6798);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.8200309));
    CHECK(resBOff.airflowFraction == Approx(0.120073));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));
    resBOff = ccBlow.calculateFromMeasuredCapacity(31.38);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(31.38));
    CHECK(resBOff.powerFraction == Approx(0.820031));
    CHECK(resBOff.airflowFraction == Approx(0.01));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2478.62));
    CHECK(resBOff.blowOffFraction == Approx(0.789873));
    resBOff = ccBlow.calculateFromElectrical(440, 2.152, 0.5, 0.6798);
    CHECK(resBOff.powerKw == Approx(0.82));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.0018129518));
    CHECK(resBOff.airflowFraction == Approx(0.120073));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));

    ccBlow.adjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100);
    resBOff = ccBlow.calculateFromPowerFraction(0.82, 0.6798);
    CHECK(resBOff.powerKw == Approx(370.886));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.82));
    CHECK(resBOff.airflowFraction == Approx(0.120073));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));
    resBOff = ccBlow.calculateFromCapacityFraction(0.01);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(31.38));
    CHECK(resBOff.powerFraction == Approx(0.820031));
    CHECK(resBOff.airflowFraction == Approx(0.01));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2478.62));
    CHECK(resBOff.blowOffFraction == Approx(0.789873));
    resBOff = ccBlow.calculateFromMeasuredPower(370.9, 0.6798);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.8200309));
    CHECK(resBOff.airflowFraction == Approx(0.120073));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));
    resBOff = ccBlow.calculateFromMeasuredCapacity(31.38);
    CHECK(resBOff.powerKw == Approx(370.9));
    CHECK(resBOff.airflowAcfm == Approx(31.38));
    CHECK(resBOff.powerFraction == Approx(0.820031));
    CHECK(resBOff.airflowFraction == Approx(0.01));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2478.62));
    CHECK(resBOff.blowOffFraction == Approx(0.789873));
    resBOff = ccBlow.calculateFromElectrical(440, 2.152, 0.5, 0.6798);
    CHECK(resBOff.powerKw == Approx(0.82));
    CHECK(resBOff.airflowAcfm == Approx(376.788));
    CHECK(resBOff.powerFraction == Approx(0.0018129518));
    CHECK(resBOff.airflowFraction == Approx(0.1200725303));
    CHECK(resBOff.blowOffAirflowAcfm == Approx(2133.21));
    CHECK(resBOff.blowOffFraction == Approx(0.6798));

    auto cclUL  = CentrifugalLoadUnloadCompressor(452.3, 3138, 71.3);
    auto resLul = cclUL.calculateFromPowerFraction(0.36);
    CHECK(resLul.powerKw == Approx(162.828));
    CHECK(resLul.airflowAcfm == Approx(753.8448));
    CHECK(resLul.powerFraction == Approx(0.36));
    CHECK(resLul.airflowFraction == Approx(0.24023));
    resLul = cclUL.calculateFromCapacityFraction(0.24);
    CHECK(resLul.powerKw == Approx(162.74));
    CHECK(resLul.airflowAcfm == Approx(753.12));
    CHECK(resLul.powerFraction == Approx(0.3598).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.24));
    resLul = cclUL.calculateFromMeasuredPower(162.828);
    CHECK(resLul.powerKw == Approx(162.828));
    CHECK(resLul.airflowAcfm == Approx(753.8448));
    CHECK(resLul.powerFraction == Approx(0.36));
    CHECK(resLul.airflowFraction == Approx(0.24023));
    resLul = cclUL.calculateFromMeasuredCapacity(753.12);
    CHECK(resLul.powerKw == Approx(162.74));
    CHECK(resLul.airflowAcfm == Approx(753.12));
    CHECK(resLul.powerFraction == Approx(0.3598).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.24));
    resLul = cclUL.calculateFromElectrical(440, 215.2, 0.5);
    CHECK(resLul.powerKw == Approx(82));
    CHECK(resLul.airflowAcfm == Approx(88.126));
    CHECK(resLul.powerFraction == Approx(0.1813).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.02808).epsilon(0.005));

    cclUL.adjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100);
    resLul = cclUL.calculateFromPowerFraction(0.36);
    CHECK(resLul.powerKw == Approx(162.828));
    CHECK(resLul.airflowAcfm == Approx(753.8448));
    CHECK(resLul.powerFraction == Approx(0.36));
    CHECK(resLul.airflowFraction == Approx(0.24023));
    resLul = cclUL.calculateFromCapacityFraction(0.24);
    CHECK(resLul.powerKw == Approx(162.74));
    CHECK(resLul.airflowAcfm == Approx(753.12));
    CHECK(resLul.powerFraction == Approx(0.3598).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.24));
    resLul = cclUL.calculateFromMeasuredPower(162.828);
    CHECK(resLul.powerKw == Approx(162.828));
    CHECK(resLul.airflowAcfm == Approx(753.84478));
    CHECK(resLul.powerFraction == Approx(0.36));
    CHECK(resLul.airflowFraction == Approx(0.24023));
    resLul = cclUL.calculateFromMeasuredCapacity(753.12);
    CHECK(resLul.powerKw == Approx(162.74));
    CHECK(resLul.airflowAcfm == Approx(753.12));
    CHECK(resLul.powerFraction == Approx(0.3598).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.24));
    resLul = cclUL.calculateFromElectrical(440, 215.2, 0.5);
    CHECK(resLul.powerKw == Approx(82));
    CHECK(resLul.airflowAcfm == Approx(88.126));
    CHECK(resLul.powerFraction == Approx(0.1813).epsilon(0.005));
    CHECK(resLul.airflowFraction == Approx(0.02808).epsilon(0.005));

    auto ccMuL  = CentrifugalModulationUnloadCompressor(452.3, 3138, 71.3, 3005, 411.9, 2731);
    auto resMuL = ccMuL.calculateFromPowerFraction(0.94);
    CHECK(resMuL.powerKw == Approx(425.162));
    CHECK(resMuL.airflowAcfm == Approx(2820.95));
    CHECK(resMuL.powerFraction == Approx(0.94));
    CHECK(resMuL.airflowFraction == Approx(0.898963));
    resMuL = ccMuL.calculateFromCapacityFraction(0.24);
    CHECK(resMuL.powerKw == Approx(165.226));
    CHECK(resMuL.airflowAcfm == Approx(753.12));
    CHECK(resMuL.powerFraction == Approx(0.365302));
    CHECK(resMuL.airflowFraction == Approx(0.24));
    resMuL = ccMuL.calculateFromMeasuredPower(425.162);
    CHECK(resMuL.powerKw == Approx(425.162));
    CHECK(resMuL.airflowAcfm == Approx(2820.95));
    CHECK(resMuL.powerFraction == Approx(0.94));
    CHECK(resMuL.airflowFraction == Approx(0.898963));
    resMuL = ccMuL.calculateFromMeasuredCapacity(753.12);
    CHECK(resMuL.powerKw == Approx(165.226));
    CHECK(resMuL.airflowAcfm == Approx(753.12));
    CHECK(resMuL.powerFraction == Approx(0.365302));
    CHECK(resMuL.airflowFraction == Approx(0.24));
    resMuL = ccMuL.calculateFromElectrical(440, 215.2, 0.5);
    CHECK(resMuL.powerKw == Approx(82));
    CHECK(resMuL.airflowAcfm == Approx(85.7932));
    CHECK(resMuL.powerFraction == Approx(0.1813).epsilon(0.005));
    CHECK(resMuL.airflowFraction == Approx(0.027340));

    ccMuL.adjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100, 58.23);
    resMuL = ccMuL.calculateFromPowerFraction(0.94);
    CHECK(resMuL.powerKw == Approx(425.162));
    CHECK(resMuL.airflowAcfm == Approx(2820.95));
    CHECK(resMuL.powerFraction == Approx(0.94));
    CHECK(resMuL.airflowFraction == Approx(0.898963));
    resMuL = ccMuL.calculateFromCapacityFraction(0.24);
    CHECK(resMuL.powerKw == Approx(165.226));
    CHECK(resMuL.airflowAcfm == Approx(753.12));
    CHECK(resMuL.powerFraction == Approx(0.365302));
    CHECK(resMuL.airflowFraction == Approx(0.24));
    resMuL = ccMuL.calculateFromMeasuredPower(425.162);
    CHECK(resMuL.powerKw == Approx(425.162));
    CHECK(resMuL.airflowAcfm == Approx(2820.95));
    CHECK(resMuL.powerFraction == Approx(0.94));
    CHECK(resMuL.airflowFraction == Approx(0.898963));
    resMuL = ccMuL.calculateFromMeasuredCapacity(753.12);
    CHECK(resMuL.powerKw == Approx(165.226));
    CHECK(resMuL.airflowAcfm == Approx(753.12));
    CHECK(resMuL.powerFraction == Approx(0.365302));
    CHECK(resMuL.airflowFraction == Approx(0.24));
    resMuL = ccMuL.calculateFromElectrical(440, 246.7, 0.5);
    CHECK(resMuL.powerKw == Approx(94.003));
    CHECK(resMuL.airflowAcfm == Approx(182.033));
    CHECK(resMuL.powerFraction == Approx(0.20783));
    CHECK(resMuL.airflowFraction == Approx(0.058).epsilon(0.005));
}

TEST_CASE("Centrifugal modulation selects curve segments by airflow", "[compressed-air][assessment]") {
    constexpr double full_load_power   = 452.3;
    constexpr double full_load_airflow = 3138.0;
    constexpr double no_load_power     = 71.3;
    constexpr double max_airflow       = 3005.0;
    constexpr double unload_power      = 411.9;
    constexpr double unload_airflow    = 2731.0;

    auto compressor = CentrifugalModulationUnloadCompressor(full_load_power, full_load_airflow, no_load_power,
                                                             max_airflow, unload_power, unload_airflow);
    const double unload_fraction = unload_airflow / full_load_airflow;
    const double max_fraction    = max_airflow / full_load_airflow;
    const double unload_power_fraction = unload_power / full_load_power;
    const double no_load_power_fraction = no_load_power / full_load_power;

    const auto below = compressor.calculateFromCapacityFraction(unload_fraction - 0.001);
    const auto at    = compressor.calculateFromCapacityFraction(unload_fraction);
    const auto above = compressor.calculateFromCapacityFraction(unload_fraction + 0.001);

    const auto low_segment_power = [&](double airflow_fraction) {
        return no_load_power_fraction +
               (unload_power_fraction - no_load_power_fraction) * airflow_fraction / unload_fraction;
    };
    const auto high_segment_power = [&](double airflow_fraction) {
        return unload_power_fraction +
               (1.0 - unload_power_fraction) * (airflow_fraction - unload_fraction) /
                   (max_fraction - unload_fraction);
    };

    CHECK(below.powerFraction == Approx(low_segment_power(unload_fraction - 0.001)));
    CHECK(at.powerFraction == Approx(unload_power_fraction));
    CHECK(above.powerFraction == Approx(high_segment_power(unload_fraction + 0.001)));

    const auto from_power = compressor.calculateFromPowerFraction(0.94);
    const auto round_trip = compressor.calculateFromCapacityFraction(from_power.airflowFraction);
    CHECK(from_power.airflowFraction == Approx(from_power.airflowAcfm / full_load_airflow));
    CHECK(round_trip.powerFraction == Approx(from_power.powerFraction));
    CHECK(round_trip.airflowFraction == Approx(from_power.airflowFraction));
    CHECK(round_trip.airflowAcfm == Approx(from_power.airflowAcfm));
}
