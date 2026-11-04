#include "motorDriven/pump/optimal_pump_efficiency.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "../../../fixtures/pump_efficiency_hi_2020_reference.h"

TEST_CASE("HI 2020 optimal_pump_efficiency matches independent full-duty goldens", "[optimal_pump_efficiency]") {
    for (const auto& row : hi2020_reference::composite) {
        const optimal_pump_efficiency::Input input{static_cast<Pump::Style>(row[0]), row[1], row[2], row[3], row[4], row[5]};
        const auto result = optimal_pump_efficiency::calculate(input);
        CAPTURE(row[0], row[1], row[2], row[3], row[4], row[5]);
        CHECK(result == Catch::Approx(row[6]).epsilon(1e-13).margin(1e-14));
    }
}

TEST_CASE("HI optimal_pump_efficiency propagates unavailable estimates and invalid inputs", "[optimal_pump_efficiency]") {
    const optimal_pump_efficiency::Input valid{Pump::Style::END_SUCTION_ANSI_API, 2000, 1.107, 1, 2000, 137};
    for (const auto member : {&optimal_pump_efficiency::Input::rpm, &optimal_pump_efficiency::Input::kinematic_viscosity,
                              &optimal_pump_efficiency::Input::stage_count, &optimal_pump_efficiency::Input::flow_rate, &optimal_pump_efficiency::Input::head}) {
        for (double invalid : {-1., std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
            auto input = valid;
            input.*member = invalid;
            const auto result = optimal_pump_efficiency::calculate(input);
            CHECK(std::isnan(result));
        }
    }
    for (int style : {11, 12, -1}) {
        auto input = valid;
        input.style = static_cast<Pump::Style>(style);
        const auto result = optimal_pump_efficiency::calculate(input);
        CHECK(std::isnan(result));
    }
}
