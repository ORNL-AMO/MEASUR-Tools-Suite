#include "catch.hpp"

#include "compressedAir/leak_survey/orifice_method.h"

using namespace Catch;
using namespace orifice_method;

// Primary test case: values verified against CompressedAirLeakSurvey expected output.
// Input: 550°F, 14.7 psia atm, Cd=1.0, 0.375 in diameter, 100 psig, 4 orifices, 8640 hr/yr.
TEST_CASE("OrificeMethod - Leak Rate Estimate (survey reference case)",
          "[CompressedAir][OrificeMethod][LeakRate]") {
    const auto r = calculate({8640, 550.0, 14.7, 1.0, 0.375, 100.0, 4});

    // Verified from CompressedAirLeakSurvey test: totalFlowRate == 1295.1250307181
    CHECK(r.leak_rate_estimate == Approx(1295.1250307181).epsilon(1e-6));
}

TEST_CASE("OrificeMethod - Annual Consumption", "[CompressedAir][OrificeMethod][AnnualConsumption]") {
    const auto r = calculate({8640, 550.0, 14.7, 1.0, 0.375, 100.0, 4});

    // annualConsumption = 8640 * 1295.1250307181 * 60 / 1000 = 671392.816 kscf
    CHECK(r.annual_consumption == Approx(671392.8159242).epsilon(1e-5));
}

TEST_CASE("OrificeMethod - Intermediate Values (survey reference case)",
          "[CompressedAir][OrificeMethod][Intermediate]") {
    const auto r = calculate({0, 550.0, 14.7, 1.0, 0.375, 100.0, 4});

    // Standard density: rho_std = 14.7 * 144 / (53.34 * 1009.67) ≈ 0.039302 lb/ft³
    CHECK(r.standard_density == Approx(0.039302).epsilon(0.001));

    // Per-orifice volumetric flow (leakRateEstimate / numOrifices)
    CHECK(r.leak_rate_scfm == Approx(r.leak_rate_estimate / 4.0).epsilon(1e-9));

    // Sonic velocity at 1009.67 °R should be approximately 1422 ft/s
    CHECK(r.leak_velocity == Approx(1422.0).epsilon(0.01));

    // Mass flow per orifice ≈ 12.73 lbm/min
    CHECK(r.leak_rate_lbm_min == Approx(12.73).epsilon(0.01));
}

TEST_CASE("OrificeMethod - Number of Orifices Scales Estimate",
          "[CompressedAir][OrificeMethod][Scaling]") {
    const auto single = calculate({8640, 550.0, 14.7, 1.0, 0.375, 100.0, 1});
    const auto quad   = calculate({8640, 550.0, 14.7, 1.0, 0.375, 100.0, 4});

    CHECK(quad.leak_rate_estimate == Approx(single.leak_rate_estimate * 4.0).epsilon(1e-9));
    CHECK(quad.annual_consumption == Approx(single.annual_consumption * 4.0).epsilon(1e-9));

    // Intermediate per-orifice values must not change with num_orifices
    CHECK(quad.standard_density  == Approx(single.standard_density).epsilon(1e-9));
    CHECK(quad.sonic_density     == Approx(single.sonic_density).epsilon(1e-9));
    CHECK(quad.leak_velocity     == Approx(single.leak_velocity).epsilon(1e-9));
    CHECK(quad.leak_rate_lbm_min == Approx(single.leak_rate_lbm_min).epsilon(1e-9));
    CHECK(quad.leak_rate_scfm    == Approx(single.leak_rate_scfm).epsilon(1e-9));
}

TEST_CASE("OrificeMethod - Operating Time Scales Annual Consumption Only",
          "[CompressedAir][OrificeMethod][OperatingTime]") {
    const auto r_8640 = calculate({8640, 550.0, 14.7, 1.0, 0.375, 100.0, 4});
    const auto r_4320 = calculate({4320, 550.0, 14.7, 1.0, 0.375, 100.0, 4});

    // Flow rates must not change with operating_time
    CHECK(r_8640.leak_rate_estimate == Approx(r_4320.leak_rate_estimate).epsilon(1e-9));

    // Annual consumption scales linearly with operating_time
    CHECK(r_8640.annual_consumption == Approx(r_4320.annual_consumption * 2.0).epsilon(1e-9));
}
