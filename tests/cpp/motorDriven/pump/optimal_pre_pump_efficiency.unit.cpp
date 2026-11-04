#include "motorDriven/pump/optimal_pre_pump_efficiency.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "../../../fixtures/pump_efficiency_hi_2020_reference.h"

TEST_CASE("HI 2020 optimal_pre_pump_efficiency matches independent SciPy samples", "[optimal_pre_pump_efficiency]") {
    for (const auto& row : hi2020_reference::base) {
        CAPTURE(row[0], row[1], row[2]);
        CHECK(optimal_pre_pump_efficiency::calculate({static_cast<Pump::Style>(row[0]), row[1]}) == Catch::Approx(row[2]).epsilon(1e-13).margin(1e-13));
    }
}

TEST_CASE("HI base curves include endpoints and refuse unsupported duties", "[optimal_pre_pump_efficiency]") {
    for (int i = 0; i <= 10; ++i) {
        const auto style = static_cast<Pump::Style>(i);
        const auto range = optimal_pre_pump_efficiency::flowLimits(style);
        CHECK(std::isfinite(optimal_pre_pump_efficiency::calculate({style, range.minimum})));
        CHECK(std::isfinite(optimal_pre_pump_efficiency::calculate({style, range.maximum})));
        for (double flow : {std::nextafter(range.minimum, -std::numeric_limits<double>::infinity()), std::nextafter(range.maximum, std::numeric_limits<double>::infinity()), 0., -1., std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
            CHECK(std::isnan(optimal_pre_pump_efficiency::calculate({style, flow})));
        }
    }
    for (int i : {11, 12, -1, 100}) {
        CHECK(std::isnan(optimal_pre_pump_efficiency::calculate({static_cast<Pump::Style>(i), 1000})));
        CHECK(std::isnan(optimal_pre_pump_efficiency::flowLimits(static_cast<Pump::Style>(i)).minimum));
    }
    CHECK(optimal_pre_pump_efficiency::calculate({Pump::Style::API_DOUBLE_SUCTION, 1000}) == 81);
    CHECK(optimal_pre_pump_efficiency::calculate({Pump::Style::END_SUCTION_STOCK, 1000}) == 75.5);
    CHECK(optimal_pre_pump_efficiency::calculate({Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, 1000}) == 74.5);
    CHECK(optimal_pre_pump_efficiency::calculate({Pump::Style::END_SUCTION_SEWAGE, 1000}) == 72);
    CHECK(optimal_pre_pump_efficiency::calculate({Pump::Style::AXIAL_FLOW, 1000}) ==
          optimal_pre_pump_efficiency::calculate({Pump::Style::VERTICAL_TURBINE, 1000}));
}
