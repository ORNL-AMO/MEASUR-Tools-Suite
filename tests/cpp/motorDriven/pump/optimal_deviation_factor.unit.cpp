#include "motorDriven/pump/optimal_deviation_factor.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "motorDriven/pumpFan/PumpEfficiency.h"

TEST_CASE("Optimal deviation factor preserves captured multipliers", "[optimal_deviation_factor]") {
    struct Fixture {
        double flow_rate;
        double expected;
    };
    // Captured from the unchanged class at 892065d with Apple clang 21, -O3 -DNDEBUG -std=gnu++20.
    const Fixture fixtures[] = {
        {0.001, 6.3254019222916433},
        {1, 1.4871053405999999},
        {100, 1.0996840790246096},
        {1000, 1.0455029577240247},
        {2000, 1.0360243794198285},
        {10000, 1.0210964032018048},
        {100000, 1.0101006042969669},
        {1e-300, 4.042960209397273e104},
        {std::numeric_limits<double>::min(), 1.9418237299496365e107},
        {std::numeric_limits<double>::denorm_min(), 5.9329646185546964e112},
        {std::numeric_limits<double>::max(), 1.0010805906},
    };
    for (const auto& fixture : fixtures) {
        const double actual = optimal_deviation_factor::calculate(fixture.flow_rate);
        CAPTURE(fixture.flow_rate, fixture.expected, actual);
        CHECK(actual == Catch::Approx(fixture.expected).epsilon(1e-14));
    }
}

TEST_CASE("Optimal deviation factor preserves nonfinite boundaries and stateless calls", "[optimal_deviation_factor]") {
    const double infinity = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (const double zero_flow : {0.0, -0.0}) {
        const double actual = optimal_deviation_factor::calculate(zero_flow);
        CHECK(std::isinf(actual));
        CHECK_FALSE(std::signbit(actual));
    }
    CHECK(std::isnan(optimal_deviation_factor::calculate(-1)));
    CHECK(std::isnan(optimal_deviation_factor::calculate(-infinity)));
    CHECK(std::isnan(optimal_deviation_factor::calculate(nan)));
    CHECK(optimal_deviation_factor::calculate(infinity) == 1.0010805906);

    const double original = optimal_deviation_factor::calculate(2000);
    optimal_deviation_factor::calculate(1);
    optimal_deviation_factor::calculate(nan);
    CHECK(optimal_deviation_factor::calculate(2000) == original);
}

TEST_CASE("Optimal deviation migration preserves its composite consumer", "[optimal_deviation_factor]") {
    struct Fixture {
        Pump::Style style;
        double flow_rate;
        double rpm;
        double viscosity;
        double stages;
        double head;
        double average;
        double maximum;
    };
    // Full-precision legacy PumpEfficiency captures at the same base/settings as the scalar fixtures.
    const Fixture fixtures[] = {
        {Pump::Style::END_SUCTION_ANSI_API, 2000, 2000, 1.107, 1, 137, 0.83933686357794668, 0.86957345321252744},
        {Pump::Style::VERTICAL_TURBINE, 10000, 1800, 10, 3, 200, 0.88589634859567956, 0.90458557516066063},
        {Pump::Style::END_SUCTION_SLURRY, 100, 1200, 1, 1, 75, 0.30297122881577326, 0.33317263673122788},
        {Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY, 2000, 2000, 1.107, 1, 137,
         -0.00037158021756460174, -0.00038496616430705135},
        {Pump::Style::POSITIVE_DISPLACEMENT, 2000, 2000, 1.107, 1, 137,
         -0.00037158021756460174, -0.00038496616430705135},
    };
    for (const auto& fixture : fixtures) {
        const auto result = PumpEfficiency(fixture.style, 0.90, fixture.rpm, fixture.viscosity,
                                           fixture.stages, fixture.flow_rate, fixture.head).calculate();
        CAPTURE(fixture.style, fixture.flow_rate, result.average, result.max);
        CHECK(result.average == Catch::Approx(fixture.average).epsilon(1e-14));
        CHECK(result.max == Catch::Approx(fixture.maximum).epsilon(1e-14));
    }
}
