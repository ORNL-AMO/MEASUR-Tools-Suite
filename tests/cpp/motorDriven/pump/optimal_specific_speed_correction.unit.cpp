#include "motorDriven/pump/optimal_specific_speed_correction.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "../../../fixtures/pump_efficiency_hi_2020_reference.h"

TEST_CASE("HI 2020 optimal_specific_speed_correction matches independent SciPy samples", "[optimal_specific_speed_correction]") {
    for (const auto& row : hi2020_reference::correction) {
        CAPTURE(row[0], row[1], row[2]);
        CHECK(optimal_specific_speed_correction::calculate({static_cast<Pump::Style>(row[0]), row[1]}) == Catch::Approx(row[2]).epsilon(1e-13).margin(1e-13));
    }
}

TEST_CASE("HI speed correction category, plateaus and inclusive bounds", "[optimal_specific_speed_correction]") {
    for (int i = 0; i <= 12; ++i) {
        const auto style = static_cast<Pump::Style>(i);
        const auto range = optimal_specific_speed_correction::speedLimits(style);
        CHECK(std::isfinite(optimal_specific_speed_correction::calculate({style, range.minimum})));
        CHECK(std::isfinite(optimal_specific_speed_correction::calculate({style, range.maximum})));
        for (double speed : {std::nextafter(range.minimum, -std::numeric_limits<double>::infinity()), std::nextafter(range.maximum, std::numeric_limits<double>::infinity()), 0., -1., std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
            CHECK(std::isnan(optimal_specific_speed_correction::calculate({style, speed})));
        }
    }
    CHECK(optimal_specific_speed_correction::calculate({Pump::Style::VERTICAL_TURBINE, 4500}) == 0);
    CHECK(optimal_specific_speed_correction::calculate({Pump::Style::VERTICAL_TURBINE, 5000}) == 0);
    CHECK(optimal_specific_speed_correction::calculate({Pump::Style::AXIAL_FLOW, 990}) ==
          optimal_specific_speed_correction::calculate({Pump::Style::END_SUCTION_SEWAGE, 990}));
    CHECK(optimal_specific_speed_correction::calculate({Pump::Style::END_SUCTION_SEWAGE, 630}) == Catch::Approx(0.13014));
}
