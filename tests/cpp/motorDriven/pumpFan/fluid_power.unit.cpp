#include "motorDriven/pumpFan/fluid_power.h"

#include <cmath>
#include <limits>

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Fluid power preserves the six original pump and fan goldens", "[fluid_power]") {
    CHECK(fluid_power::calculatePump({1.02, 1000, 280.0}) == Approx(53.7836814443));
    CHECK(fluid_power::calculatePump({1.02, 1200, 280.0}) == Approx(64.5404177332));
    CHECK(fluid_power::calculateFan({2000, 20, 25, 1.4, 0}) == Approx(1.6416221314));
    CHECK(fluid_power::calculateFan({1200, 25, 35, 1.4, 0}) == Approx(1.9699465577));
    CHECK(fluid_power::calculateFan({129691, -16.36, 1.1, 0.988, 0}) == Approx(262.3349690747));
    CHECK(fluid_power::calculateFan({151961, -8.92, 2.28, 0.995, 0}) == Approx(198.5721824055));
}

TEST_CASE("Fluid power preserves captured duty and boundary results", "[fluid_power]") {
    // Frozen outputs captured from the unchanged FluidPower.h at 1998e82, compiled with -O3.
    const struct {
        fluid_power::PumpInput input;
        double expected;
    } pumps[] = {
        {{1, 0, 100}, 0},
        {{1, 1000, 0}, 0},
        {{0, 1000, 100}, 0},
        {{1, -1000, 100}, -18.831821234014409},
        {{1, 1000, -100}, -18.831821234014409},
        {{-1, 1000, 100}, -18.831821234014409},
        {{0.85, 100, 25}, 0.40017620122280612},
        {{2.5, 125000, 5000}, 294247.20678147511},
    };
    const struct {
        fluid_power::FanInput input;
        double expected;
    } fans[] = {
        {{2000, 20, 25, 1.4, 1}, 1.3132977051241745},
        {{0, 20, 25, 1.4, 1}, 0},
        {{2000, 20, 25, 0, 1}, 0},
        {{2000, 20, 25, 1.4, 5}, 0},
        {{2000, 20, 25, 1.4, 6}, -0.32832442628104364},
        {{-2000, 20, 25, 1.4, 1}, -1.3132977051241745},
        {{2000, 20, 25, -1.4, 1}, -1.3132977051241745},
        {{2000, 25, 20, 1.4, 0}, -1.6416221314052184},
        {{2000, -20, -15, 1.4, 1}, 1.3132977051241745},
    };
    for (const auto& golden : pumps) {
        CHECK(fluid_power::calculatePump(golden.input) == Approx(golden.expected).epsilon(1e-12));
    }
    for (const auto& golden : fans) {
        CHECK(fluid_power::calculateFan(golden.input) == Approx(golden.expected).epsilon(1e-12));
    }
}

TEST_CASE("Fluid power retains nonfinite arithmetic and has no call state", "[fluid_power]") {
    const double infinity = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    CHECK(fluid_power::calculatePump({1, infinity, 100}) == infinity);
    CHECK(fluid_power::calculatePump({1, -infinity, 100}) == -infinity);
    CHECK(std::isnan(fluid_power::calculatePump({1, infinity, 0})));
    CHECK(std::isnan(fluid_power::calculatePump({nan, 1000, 100})));
    CHECK(std::signbit(fluid_power::calculatePump({1, -0.0, 100})));
    CHECK(fluid_power::calculateFan({infinity, 20, 25, 1, 1}) == infinity);
    CHECK(fluid_power::calculateFan({infinity, 20, 25, 1, 6}) == -infinity);
    CHECK(std::isnan(fluid_power::calculateFan({infinity, 20, 25, 1, 5})));
    CHECK(std::isnan(fluid_power::calculateFan({2000, infinity, infinity, 1, 0})));
    CHECK(std::isnan(fluid_power::calculateFan({2000, 20, 25, nan, 0})));
    CHECK(std::signbit(fluid_power::calculateFan({-0.0, 20, 25, 1, 0})));

    const fluid_power::PumpInput pump = {1.02, 1000, 280};
    const fluid_power::FanInput fan = {2000, 20, 25, 1.4, 1};
    const double pump_first = fluid_power::calculatePump(pump);
    const double fan_first = fluid_power::calculateFan(fan);
    fluid_power::calculatePump({2.5, 125000, 5000});
    fluid_power::calculateFan({2000, 20, 25, 1.4, 6});
    CHECK(fluid_power::calculatePump(pump) == pump_first);
    CHECK(fluid_power::calculateFan(fan) == fan_first);
}
