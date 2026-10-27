#include "motorDriven/pumpFan/optimal_pump_shaft_power.h"

#include <cmath>
#include <limits>

#include "catch.hpp"

namespace {

void checkArithmetic(double actual, double expected) {
    if (std::isnan(expected)) {
        CHECK(std::isnan(actual));
    } else {
        CHECK(actual == expected);
        CHECK(std::signbit(actual) == std::signbit(expected));
    }
}

} // namespace

TEST_CASE("Optimal shaft power preserves captured pump duties", "[optimal_pump_shaft_power]") {
    struct Fixture {
        optimal_pump_shaft_power::PumpInput input;
        double expected;
    };
    // Captured at -O3 from unchanged OptimalPumpShaftPower at base 8d34462 before class removal.
    const Fixture fixtures[] = {
        {{1840, 174.85, 1, 0.8}, 101.51891512553706},
        {{1000, 125, 1.5, 0.75}, 63.109320489324432},
        {{1000, 125, 1.5, 0.5}, 94.663980733986648},
        {{1000, 125, 1.5, 1}, 47.331990366993324},
        {{1000, 125, 1.5, 1.5}, 31.554660244662216},
        {{1000, 125, 1.5, -0.75}, -63.109320489324432},
        {{1000, 125, 0.5, 0.75}, 21.036440163108143},
        {{0, 125, 1.5, 0.75}, 0},
        {{1000, 0, 1.5, 0.75}, 0},
        {{1000, 125, 0, 0.75}, 0},
        {{-1000, 125, 1.5, 0.75}, -63.109320489324432},
        {{1000, -125, 1.5, 0.75}, -63.109320489324432},
        {{1000, 125, -1.5, 0.75}, -63.109320489324432},
        {{1e-150, 1e-150, 1, 0.75}, 3.3658304260973025e-304},
        {{1e+150, 1e+150, 1, 0.75}, 3.3658304260973029e+296},
    };
    for (const auto& fixture : fixtures) {
        const double actual = optimal_pump_shaft_power::calculatePump(fixture.input);
        CAPTURE(fixture.expected, actual);
        if (fixture.expected == 0) {
            checkArithmetic(actual, fixture.expected);
        } else {
            CHECK(actual == Catch::Approx(fixture.expected).epsilon(1e-12));
        }
    }
}

TEST_CASE("Optimal shaft power preserves captured fan duties", "[optimal_pump_shaft_power]") {
    struct Fixture {
        optimal_pump_shaft_power::FanInput input;
        double expected;
    };
    // Captured at -O3 from unchanged OptimalPumpShaftPower at base 8d34462 before class removal.
    const Fixture fixtures[] = {
        {{129691, -16.36, 1.1, 0.988, 0.595398315, 0}, 590.62218629848621},
        {{129691, -16.36, 1.1, 0.988, 0.595398315, 1}, 556.79502786214664},
        {{2000, 20, 25, 1.4, 0.75, 1}, 2.347270250445352},
        {{2000, 20, 25, 1.4, 0.5, 1}, 3.5209053756680282},
        {{2000, 20, 25, 1.4, 1, 1}, 1.7604526878340141},
        {{2000, 20, 25, 1.4, 1.5, 1}, 1.173635125222676},
        {{2000, 20, 25, 1.4, -0.75, 1}, -2.347270250445352},
        {{2000, 20, 25, 1.4, 0.75, 0}, 2.9340878130566908},
        {{2000, 20, 25, 1.4, 0.75, 5}, 0},
        {{2000, 20, 25, 1.4, 0.75, 6}, -0.586817562611338},
        {{2000, 20, 25, 0, 0.75, 1}, 0},
        {{0, 20, 25, 1.4, 0.75, 1}, 0},
        {{2000, -20, -15, 1.4, 0.75, 1}, 2.347270250445352},
        {{-2000, 20, 25, 1.4, 0.75, 1}, -2.347270250445352},
        {{2000, 20, 25, -1.4, 0.75, 1}, -2.347270250445352},
    };
    for (const auto& fixture : fixtures) {
        const double actual = optimal_pump_shaft_power::calculateFan(fixture.input);
        CAPTURE(fixture.expected, actual);
        if (fixture.expected == 0) {
            checkArithmetic(actual, fixture.expected);
        } else {
            CHECK(actual == Catch::Approx(fixture.expected).epsilon(1e-12));
        }
    }
}

TEST_CASE("Optimal shaft power retains signed and nonfinite arithmetic", "[optimal_pump_shaft_power]") {
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double max = std::numeric_limits<double>::max();
    const double tiny = std::numeric_limits<double>::denorm_min();

    SECTION("Pump boundaries") {
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, 1, 0}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, 1, -0.0}), -inf);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({0, 100, 1, 0}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({-0.0, 100, 1, 0.8}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({0, 100, 1, -0.8}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({inf, 100, 1, 0.8}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({inf, 0, 1, 0.8}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, nan, 0.8}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, 1, nan}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, 1, inf}), 0);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({1000, 100, 1, -inf}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({inf, 100, 1, inf}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({max, max, 1, 1}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculatePump({tiny, 1, 1, max}), 0);
    }
    SECTION("Fan boundaries") {
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, 0, 1}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, -0.0, 1}), -inf);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, 0, 6}), -inf);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({0, 20, 25, 1.4, 0, 1}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, 0, 5}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({-0.0, 20, 25, 1.4, 0.8, 1}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({0, 20, 25, 1.4, -0.8, 1}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({inf, 20, 25, 1.4, 0.8, 1}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({inf, 20, 25, 1.4, 0.8, 5}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, inf, inf, 1.4, 0.8, 1}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, nan, 0.8, 1}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, nan, 1}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, inf, 1}), 0);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({2000, 20, 25, 1.4, -inf, 1}), -0.0);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({inf, 20, 25, 1.4, inf, 1}), nan);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({max, 0, max, 1, 1, 0}), inf);
        checkArithmetic(optimal_pump_shaft_power::calculateFan({tiny, 0, 1, 1, max, 0}), 0);
    }
}
