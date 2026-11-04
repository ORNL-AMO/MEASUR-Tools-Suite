#include "motorDriven/pump/pump_efficiency.h"

#include <cmath>
#include <limits>

#include "catch.hpp"
#include "../../../fixtures/pump_efficiency_hi_2020_reference.h"

TEST_CASE("HI 2020 pump_efficiency matches independent full-duty goldens", "[pump_efficiency]") {
    for (const auto& row : hi2020_reference::composite) {
        const pump_efficiency::Input input{static_cast<Pump::Style>(row[0]), row[1], row[2], row[3], row[4], row[5]};
        const auto result = pump_efficiency::calculate(input);
        CAPTURE(row[0], row[1], row[2], row[3], row[4], row[5]);
        CHECK(result.average == Catch::Approx(row[6]).epsilon(1e-13).margin(1e-14));
        CHECK(result.max == Catch::Approx(row[7]).epsilon(1e-13).margin(1e-14));
    }
}

TEST_CASE("HI pump_efficiency propagates unavailable estimates and invalid inputs", "[pump_efficiency]") {
    const pump_efficiency::Input valid{Pump::Style::END_SUCTION_ANSI_API, 2000, 1.107, 1, 2000, 137};
    for (const auto member : {&pump_efficiency::Input::rpm, &pump_efficiency::Input::kinematic_viscosity,
                              &pump_efficiency::Input::stage_count, &pump_efficiency::Input::flow_rate, &pump_efficiency::Input::head}) {
        for (double invalid : {-1., std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
            auto input = valid;
            input.*member = invalid;
            const auto result = pump_efficiency::calculate(input);
            CHECK(std::isnan(result.average));
            CHECK(std::isnan(result.max));
        }
    }
    for (int style : {11, 12, -1}) {
        auto input = valid;
        input.style = static_cast<Pump::Style>(style);
        const auto result = pump_efficiency::calculate(input);
        CHECK(std::isnan(result.average));
        CHECK(std::isnan(result.max));
    }
}

TEST_CASE("Pump efficiency limits describe the actual tables", "[pump_efficiency]") {
    const auto ansi = pump_efficiency::getLimits(Pump::Style::END_SUCTION_ANSI_API);
    CHECK(ansi.supported);
    CHECK(ansi.minimum_flow_rate == 100);
    CHECK(ansi.maximum_flow_rate == 5000);
    CHECK(ansi.minimum_specific_speed == 630);
    CHECK(ansi.maximum_specific_speed == 6300);
    const auto vertical = pump_efficiency::getLimits(Pump::Style::VERTICAL_TURBINE);
    CHECK(vertical.minimum_specific_speed == 1717.2);
    CHECK(vertical.maximum_specific_speed == 17172);
    const auto axial = pump_efficiency::getLimits(Pump::Style::AXIAL_FLOW);
    CHECK(axial.minimum_flow_rate == vertical.minimum_flow_rate);
    CHECK(axial.minimum_specific_speed == 630);
    const auto api = pump_efficiency::getLimits(Pump::Style::API_DOUBLE_SUCTION);
    CHECK(api.minimum_flow_rate == 300);
    CHECK(api.maximum_flow_rate == 1300);
    for (int style : {11, 12, -1}) {
        const auto limits = pump_efficiency::getLimits(static_cast<Pump::Style>(style));
        CHECK_FALSE(limits.supported);
        CHECK(std::isnan(limits.minimum_flow_rate));
        CHECK(std::isnan(limits.maximum_flow_rate));
        CHECK(std::isnan(limits.minimum_specific_speed));
        CHECK(std::isnan(limits.maximum_specific_speed));
    }
}
