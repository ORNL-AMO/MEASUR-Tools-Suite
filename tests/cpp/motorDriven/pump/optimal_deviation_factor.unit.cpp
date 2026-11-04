#include "motorDriven/pump/optimal_deviation_factor.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "../../../fixtures/pump_efficiency_hi_2020_reference.h"

TEST_CASE("HI 2020 optimal_deviation_factor matches independent SciPy samples", "[optimal_deviation_factor]") {
    for (const auto& row : hi2020_reference::deviation) {
        CAPTURE(row[0], row[1], row[2]);
        CHECK(optimal_deviation_factor::calculate(row[1]) == Catch::Approx(row[2]).epsilon(1e-13).margin(1e-13));
    }
}

TEST_CASE("HI positive deviation uses raw flow and does not extrapolate", "[optimal_deviation_factor]") {
    CHECK(optimal_deviation_factor::calculate(35) == 1.08);
    CHECK(optimal_deviation_factor::calculate(100000) == 1.01);
    CHECK(optimal_deviation_factor::calculate(500) == Catch::Approx(1.0451101945288));
    for (double flow : {std::nextafter(35., -std::numeric_limits<double>::infinity()), std::nextafter(100000., std::numeric_limits<double>::infinity()), 0., -0., -1., std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
        CHECK(std::isnan(optimal_deviation_factor::calculate(flow)));
    }
}
