#include "motorDriven/pump/optimal_specific_speed.h"

#include <cmath>
#include <limits>

#include "catch.hpp"

namespace {
constexpr double relative_tolerance = 1e-14;
constexpr double absolute_tolerance = 1e-12;

void check_result(double actual, double expected) {
    if (std::isnan(expected)) {
        CHECK(std::isnan(actual));
    } else if (std::isinf(expected)) {
        CHECK(actual == expected);
    } else if (expected == 0.0) {
        CHECK(actual == expected);
        CHECK(std::signbit(actual) == std::signbit(expected));
    } else {
        CHECK(std::abs(actual - expected) <= absolute_tolerance + std::abs(expected) * relative_tolerance);
    }
}
} // namespace

TEST_CASE("Optimal specific speed preserves captured duties and fractional stages", "[optimal_specific_speed]") {
    struct Fixture {
        optimal_specific_speed::Input input;
        double expected;
    };
    // Immutable legacy captures at 23b58b0, Apple clang 21, -O3 -DNDEBUG -std=gnu++20.
    // Portable tolerances allow compiler/libm rounding; exact same-platform comparisons are separate.
    const Fixture fixtures[] = {
        {{2000, 2000, 137, 1}, 2233.5957167946208},
        {{1800, 1000, 100, 1}, 1800},
        {{1800, 1000, 100, 3}, 4103.1127025185997},
        {{1800, 1000, 100, 1.5}, 2439.7254097465811},
        {{1750.5, 750.25, 122.5, 2.25}, 2392.2135126507915},
        {{1200, 0.001, 75, 1}, 1.4889677745633594},
        {{3600, 100000, 1000, 6}, 24542.338315697987},
        {{900, 100, 0.001, 1}, 1600451.4690350306},
        {{-1800, 1000, 100, 1}, -1800},
        {{1800, 1000, -100, -2}, 3027.2270949133722},
    };
    for (const auto& fixture : fixtures) {
        const double actual = optimal_specific_speed::calculate(fixture.input);
        CAPTURE(fixture.input.rpm, fixture.input.flow_rate, fixture.input.head, fixture.input.stage_count);
        check_result(actual, fixture.expected);
    }
}

TEST_CASE("Optimal specific speed preserves signed zero and nonfinite arithmetic", "[optimal_specific_speed]") {
    const double infinity = std::numeric_limits<double>::infinity();
    const double quiet_nan = std::numeric_limits<double>::quiet_NaN();
    struct Fixture {
        optimal_specific_speed::Input input;
        double expected;
    };
    const Fixture fixtures[] = {
        {{1800, 0.0, 100, 1}, 0.0},
        {{1800, -0.0, 100, 1}, -0.0},
        {{0.0, 1000, 100, 1}, 0.0},
        {{-0.0, 1000, 100, 1}, -0.0},
        {{1800, 1000, 0.0, 1}, infinity},
        {{1800, 1000, -0.0, 1}, infinity},
        {{1800, 1000, 100, 0.0}, 0.0},
        {{1800, 1000, 100, -0.0}, 0.0},
        {{1800, -1, 100, 1}, quiet_nan},
        {{1800, 1000, -100, 1}, quiet_nan},
        {{1800, 1000, 100, -1}, quiet_nan},
        {{1800, 1000, 0.0, 0.0}, quiet_nan},
        {{infinity, 1000, 100, 1}, infinity},
        {{1800, infinity, 100, 1}, infinity},
        {{1800, 1000, infinity, 1}, 0.0},
        {{1800, 1000, 100, infinity}, infinity},
        {{quiet_nan, 1000, 100, 1}, quiet_nan},
        {{1800, quiet_nan, 100, 1}, quiet_nan},
        {{1800, 1000, quiet_nan, 1}, quiet_nan},
        {{1800, 1000, 100, quiet_nan}, quiet_nan},
        {{std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 100, 1}, infinity},
        {{std::numeric_limits<double>::min(), std::numeric_limits<double>::denorm_min(), 100, 1}, 0.0},
    };
    for (const auto& fixture : fixtures) {
        CAPTURE(fixture.input.rpm, fixture.input.flow_rate, fixture.input.head, fixture.input.stage_count);
        check_result(optimal_specific_speed::calculate(fixture.input), fixture.expected);
    }
}

TEST_CASE("Optimal specific speed leaves input unchanged and retains no state", "[optimal_specific_speed]") {
    const optimal_specific_speed::Input input{1800, 1000, 100, 1.5};
    const double original = optimal_specific_speed::calculate(input);
    optimal_specific_speed::calculate({900, 100, 10, 3});
    optimal_specific_speed::calculate({1800, -1, 100, 1});
    CHECK(optimal_specific_speed::calculate(input) == original);
    CHECK(input.rpm == 1800);
    CHECK(input.flow_rate == 1000);
    CHECK(input.head == 100);
    CHECK(input.stage_count == 1.5);
}
