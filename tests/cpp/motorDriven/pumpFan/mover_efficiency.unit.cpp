#include "motorDriven/pumpFan/mover_efficiency.h"

#include <cmath>
#include <limits>

#include "catch.hpp"

TEST_CASE("Mover efficiency preserves original pump goldens", "[mover_efficiency]") {
    struct Fixture {
        mover_efficiency::PumpInput input;
        double expected;
    };
    // All 22 rows from the legacy test, previously repeated in a second identical test case.
    const Fixture fixtures[] = {
        {{0.5, 1000, 125, 125}, 0.126218641},
        {{1.5, 1000, 125, 125}, 0.3786559229},
        {{3.5, 1000, 125, 125}, 0.8835304869},
        {{9.5, 1000, 125, 125}, 2.3981541786},
        {{20.5, 1000, 125, 125}, 5.1749642801},
        {{50.5, 1000, 125, 125}, 12.7480827388},
        {{1.5, 500, 125, 125}, 0.1893279615},
        {{1.5, 700, 125, 125}, 0.2650591461},
        {{1.5, 1100, 125, 125}, 0.4165215152},
        {{1.5, 1800, 125, 125}, 0.6815806613},
        {{1.5, 2800, 125, 125}, 1.0602365842},
        {{1.5, 1000, 25, 125}, 0.0757311846},
        {{1.5, 1000, 75, 125}, 0.2271935538},
        {{1.5, 1000, 125, 125}, 0.3786559229},
        {{1.5, 1000, 195, 125}, 0.5907032398},
        {{1.5, 1000, 225, 125}, 0.6815806613},
        {{1.5, 1000, 325, 125}, 0.9845053996},
        {{1.5, 1000, 125, 25}, 1.8932796147},
        {{1.5, 1000, 125, 75}, 0.6310932049},
        {{1.5, 1000, 125, 155}, 0.3053676798},
        {{1.5, 1000, 125, 255}, 0.1856156485},
        {{1.5, 1000, 125, 425}, 0.1113693891},
    };
    for (const auto& fixture : fixtures) {
        CAPTURE(fixture.input.specific_gravity, fixture.input.flow_rate, fixture.input.head,
                fixture.input.mover_shaft_power);
        CHECK(mover_efficiency::calculatePump(fixture.input) == Catch::Approx(fixture.expected));
    }
}

TEST_CASE("Mover efficiency preserves captured fan duties", "[mover_efficiency]") {
    struct Fixture {
        mover_efficiency::FanInput input;
        double expected;
    };
    // Captured at -O3 from unchanged MoverEfficiency at base 7b5b760 before removing the class.
    const Fixture fixtures[] = {
        {{129691, 590.622186263, -16.36, 1.1, 0.988, 0}, 0.59539831503577312},
        {{129691, 590.622186263, -16.36, 1.1, 0.988, 1}, 0.56129760970726372},
        {{2000, 5, 20, 25, 1.4, 0}, 0.44011317195850364},
        {{2000, 5, 20, 25, 1.4, 1}, 0.35209053756680281},
        {{2000, 1, 20, 25, 1.4, 1}, 1.7604526878340141},
        {{2000, -5, 20, 25, 1.4, 1}, -0.35209053756680281},
        {{2000, 5, 20, 25, 1.4, 5}, 0},
        {{2000, 5, 20, 25, 1.4, 6}, -0.088022634391700702},
        {{2000, 5, 20, 25, 0, 1}, 0},
        {{0, 5, 20, 25, 1.4, 1}, 0},
        {{2000, 5, -20, -15, 1.4, 1}, 0.35209053756680281},
        {{-2000, 5, 20, 25, 1.4, 1}, -0.35209053756680281},
        {{2000, 5, 20, 25, -1.4, 1}, -0.35209053756680281},
    };
    for (const auto& fixture : fixtures) {
        CAPTURE(fixture.input.flow_rate, fixture.input.mover_shaft_power, fixture.input.inlet_pressure,
                fixture.input.outlet_pressure, fixture.input.compressibility_factor, fixture.input.velocity_pressure);
        CHECK(mover_efficiency::calculateFan(fixture.input) ==
              Catch::Approx(fixture.expected).epsilon(1e-12).margin(1e-14));
    }
}

TEST_CASE("Mover efficiency retains signed and nonfinite arithmetic", "[mover_efficiency]") {
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();

    SECTION("Pump duty and shaft boundaries") {
        CHECK(mover_efficiency::calculatePump({1, 0, 100, 125}) == 0);
        CHECK(mover_efficiency::calculatePump({0, 1000, 100, 125}) == 0);
        CHECK(mover_efficiency::calculatePump({1, 1000, 0, 125}) == 0);
        CHECK(mover_efficiency::calculatePump({1.5, 1000, 125, -125}) == Catch::Approx(-0.3786559229));
        CHECK(mover_efficiency::calculatePump({1.5, -1000, 125, 125}) == Catch::Approx(-0.3786559229));
        CHECK(mover_efficiency::calculatePump({1.5, 1000, -125, 125}) == Catch::Approx(-0.3786559229));
        CHECK(mover_efficiency::calculatePump({-1.5, 1000, 125, 125}) == Catch::Approx(-0.3786559229));
        CHECK(mover_efficiency::calculatePump({1, 1000, 100, 0}) == inf);
        CHECK(mover_efficiency::calculatePump({1, 1000, 100, -0.0}) == -inf);
        CHECK(std::isnan(mover_efficiency::calculatePump({1, 0, 100, 0})));
        const double negativeFlowZero = mover_efficiency::calculatePump({1, -0.0, 100, 125});
        CHECK(negativeFlowZero == 0);
        CHECK(std::signbit(negativeFlowZero));
        const double negativeShaftZero = mover_efficiency::calculatePump({1, 0, 100, -125});
        CHECK(negativeShaftZero == 0);
        CHECK(std::signbit(negativeShaftZero));
        CHECK(mover_efficiency::calculatePump({1, inf, 100, 125}) == inf);
        CHECK(std::isnan(mover_efficiency::calculatePump({1, inf, 0, 125})));
        CHECK(std::isnan(mover_efficiency::calculatePump({nan, 1000, 100, 125})));
        CHECK(std::isnan(mover_efficiency::calculatePump({1, 1000, 100, nan})));
        CHECK(mover_efficiency::calculatePump({1, 1000, 100, inf}) == 0);
        CHECK(std::isnan(mover_efficiency::calculatePump({1, inf, 100, inf})));
    }

    SECTION("Fan duty and shaft boundaries") {
        CHECK(mover_efficiency::calculateFan({2000, 0, 20, 25, 1.4, 1}) == inf);
        CHECK(mover_efficiency::calculateFan({2000, -0.0, 20, 25, 1.4, 1}) == -inf);
        CHECK(mover_efficiency::calculateFan({2000, 0, 20, 25, 1.4, 6}) == -inf);
        CHECK(std::isnan(mover_efficiency::calculateFan({0, 0, 20, 25, 1.4, 1})));
        CHECK(std::isnan(mover_efficiency::calculateFan({2000, 0, 20, 25, 1.4, 5})));
        const double negativeFlowZero = mover_efficiency::calculateFan({-0.0, 5, 20, 25, 1.4, 1});
        CHECK(negativeFlowZero == 0);
        CHECK(std::signbit(negativeFlowZero));
        const double negativeShaftZero = mover_efficiency::calculateFan({0, -5, 20, 25, 1.4, 1});
        CHECK(negativeShaftZero == 0);
        CHECK(std::signbit(negativeShaftZero));
        CHECK(mover_efficiency::calculateFan({inf, 5, 20, 25, 1.4, 1}) == inf);
        CHECK(std::isnan(mover_efficiency::calculateFan({inf, 5, 20, 25, 1.4, 5})));
        CHECK(std::isnan(mover_efficiency::calculateFan({2000, 5, inf, inf, 1.4, 1})));
        CHECK(std::isnan(mover_efficiency::calculateFan({2000, 5, 20, 25, nan, 1})));
        CHECK(std::isnan(mover_efficiency::calculateFan({2000, nan, 20, 25, 1.4, 1})));
        CHECK(mover_efficiency::calculateFan({2000, inf, 20, 25, 1.4, 1}) == 0);
        CHECK(std::isnan(mover_efficiency::calculateFan({inf, inf, 20, 25, 1.4, 1})));
    }
}
