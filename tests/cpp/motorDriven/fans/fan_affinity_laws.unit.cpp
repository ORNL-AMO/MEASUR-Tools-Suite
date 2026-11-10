#include "motorDriven/fans/fan_affinity_laws.h"

#include <cmath>
#include <limits>

#include "catch.hpp"

namespace fal = fan_affinity_laws;

namespace {

void checkResult(const fal::Result& actual, const fal::Result& expected) {
    CHECK(actual.annual_energy_baseline == Catch::Approx(expected.annual_energy_baseline).margin(0.01));
    CHECK(actual.annual_energy_new == Catch::Approx(expected.annual_energy_new).margin(0.01));
    CHECK(actual.annual_cost_savings == Catch::Approx(expected.annual_cost_savings).margin(0.01));
}

fal::Input exampleInput() {
    return {0.07, 97, 96, 90, 6240, 10, 30000,
        fal::MotorControlType::TwoSpeed, fal::MotorControlType::TwoSpeed, fal::FlowMode::Percent, 55};
}

} // namespace

TEST_CASE("Fan affinity laws annual regression scenarios", "[fanAffinityLaws]") {
    struct Scenario {
        int original_case;
        fal::Input input;
        double current_diameter;
        double new_diameter;
        fal::Result expected;
    };
    const Scenario scenarios[] = {
        {1, {0.07, 95, 93, 0, 6240, 2, 8000, fal::MotorControlType::OnOff,
                fal::MotorControlType::VSD, fal::FlowMode::Volume, 5000},
            0, 0, {14125.64, 3448.64, 747.39}},
        {2, {0.07, 97, 96, 100, 6240, 10, 30000, fal::MotorControlType::OnOff,
                fal::MotorControlType::TwoSpeed, fal::FlowMode::Percent, 55},
            0, 0, {67010.31, 14239.69, 3693.94}},
        {3, {0.05, 90, 92, 100, 8760, 5, 15000, fal::MotorControlType::OnOff,
                fal::MotorControlType::None, fal::FlowMode::Volume, 0},
            20, 18, {52898.55, 31236.07, 1083.12}},
        {4, {0.08, 96, 97, 100, 4380, 20, 60000, fal::MotorControlType::OnOff,
                fal::MotorControlType::VSD, fal::FlowMode::Percent, 75},
            36, 40, {94072.16, 26038.44, 5442.70}},
        {5, {0.08, 96, 97, 0, 4380, 20, 60000, fal::MotorControlType::OnOff,
                fal::MotorControlType::TwoSpeed, fal::FlowMode::Volume, 40000},
            36, 38, {94072.16, 29829.67, 5139.40}},
        {6, {0.07, 95, 93, 88, 6240, 2, 8000, fal::MotorControlType::VSD,
                fal::MotorControlType::VSD, fal::FlowMode::Volume, 5000},
            0, 0, {14125.64, 5060.58, 634.55}},
        {7, {0.07, 97, 96, 90, 6240, 10, 30000, fal::MotorControlType::TwoSpeed,
                fal::MotorControlType::TwoSpeed, fal::FlowMode::Percent, 55},
            0, 0, {67010.31, 17260.23, 3482.51}},
        {8, {0.07, 95, 93, 100, 8760, 25, 80000, fal::MotorControlType::OnOff,
                fal::MotorControlType::VSD, fal::FlowMode::Percent, 75},
            0, 0, {247877.76, 104573.43, 10031.30}},
        {9, {0.07, 95, 93, 100, 8760, 25, 80000, fal::MotorControlType::OnOff,
                fal::MotorControlType::TwoSpeed, fal::FlowMode::Percent, 75},
            0, 0, {247877.76, 139431.24, 7591.26}},
        {10, {0.07, 95, 93, 100, 8760, 25, 80000, fal::MotorControlType::OnOff,
                fal::MotorControlType::None, fal::FlowMode::Percent, 75},
            36, 32.75, {247877.76, 154447.75, 6540.10}},
        {11, {0.07, 95, 93, 100, 8760, 25, 80000, fal::MotorControlType::OnOff,
                fal::MotorControlType::VSD, fal::FlowMode::Percent, 75},
            36, 40, {247877.76, 68610.63, 12548.70}},
        // Old case #13 repeated #12 through the removed input-object constructor.
        {12, {0.07, 95, 93, 100, 8760, 25, 80000, fal::MotorControlType::OnOff,
                fal::MotorControlType::TwoSpeed, fal::FlowMode::Percent, 75},
            36, 40, {247877.76, 86816.41, 11274.29}}
    };
    for (const auto& scenario : scenarios) {
        CAPTURE(scenario.original_case);
        const auto actual = scenario.current_diameter == 0 ? fal::calculate(scenario.input) :
            fal::changeFanSize(scenario.input, scenario.current_diameter, scenario.new_diameter);
        checkResult(actual, scenario.expected);
    }
}

TEST_CASE("Fan affinity laws normalize delivered baseline power for every control transition", "[fanAffinityLaws]") {
    const fal::MotorControlType controls[] = {fal::MotorControlType::OnOff, fal::MotorControlType::TwoSpeed,
        fal::MotorControlType::VSD, fal::MotorControlType::None};
    for (const auto current : controls) {
        for (const auto modified : controls) {
            auto input = exampleInput();
            input.motor_control_type_current = current;
            input.motor_control_type_new = modified;
            input.flow_percent_baseline = 90;
            input.desired_flow_rate = 90;
            const auto result = fal::calculate(input);
            const double current_power = 10 / (0.97 * 0.96);
            CHECK(result.annual_energy_baseline == Catch::Approx(current_power * input.operating_hours));
            if (current == modified) {
                CHECK(result.annual_energy_new == Catch::Approx(result.annual_energy_baseline));
                CHECK(result.annual_cost_savings == Catch::Approx(0).margin(1e-9));
            }
            checkResult(fal::changeFanSize(input, 36, 36), result);
        }
    }
}

TEST_CASE("Fan affinity laws VSD worked example", "[fanAffinityLaws]") {
    const fal::Input input{0.07, 97, 96, 7040.0 / 30000 * 100, 6240, 11.22, 30000,
        fal::MotorControlType::VSD, fal::MotorControlType::VSD, fal::FlowMode::Volume, 5000};
    const auto result = fal::calculate(input);
    CHECK(result.annual_energy_baseline / input.operating_hours == Catch::Approx(12.0489690722));
    CHECK(result.annual_energy_new / input.operating_hours == Catch::Approx(4.3166011808));
    // The same baseline normalization must also apply when the fan is resized.
    const auto resized = fal::changeFanSize(input, 36, 40);
    CHECK(resized.annual_energy_baseline == Catch::Approx(result.annual_energy_baseline));
    CHECK(resized.annual_energy_new == Catch::Approx(result.annual_energy_new * std::pow(36.0 / 40, 4)));
}

TEST_CASE("Fan affinity laws equivalent flow modes and units", "[fanAffinityLaws]") {
    auto input = exampleInput();
    const auto percent_result = fal::changeFanSize(input, 36, 40);
    input.flow_mode = fal::FlowMode::Volume;
    input.desired_flow_rate = 16500;
    checkResult(fal::changeFanSize(input, 36, 40), percent_result);
    const auto volume_result = fal::calculate(input);
    input.rated_flow *= 0.00047194745;
    input.desired_flow_rate *= 0.00047194745;
    checkResult(fal::calculate(input), volume_result);
    checkResult(fal::changeFanSize(input, 36, 40), percent_result);
}

TEST_CASE("Fan affinity laws two-speed time shares", "[fanAffinityLaws]") {
    struct Scenario {
        double flow;
        fal::TimeFactorResult expected;
    };
    const Scenario scenarios[] = {
        {0, {0, 0, 0, 1}},
        {0.25, {0.0625, 0, 0.5, 0.5}},
        {0.5, {0.125, 0, 1, 0}},
        {0.9, {0.825, 0.8, 0.2, 0}},
        {1, {1, 1, 0, 0}},
        {0.5668, {0.2419, 0.1336, 0.8664, 0}},
        {40000 / (60000 * std::pow(38.0 / 36, 3)),
            {0.24198133838752, 0.133692958157166, 0.866307041842834, 0}}
    };
    for (const auto& scenario : scenarios) {
        CAPTURE(scenario.flow);
        const auto result = fal::get50PercentTimeFactor(scenario.flow);
        CHECK(result.factor == Catch::Approx(scenario.expected.factor).margin(1e-12));
        CHECK(result.time_above_50_percent == Catch::Approx(scenario.expected.time_above_50_percent).margin(1e-12));
        CHECK(result.time_at_50_percent == Catch::Approx(scenario.expected.time_at_50_percent).margin(1e-12));
        CHECK(result.time_at_0_percent == Catch::Approx(scenario.expected.time_at_0_percent).margin(1e-12));
        CHECK(result.time_above_50_percent + result.time_at_50_percent + result.time_at_0_percent == Catch::Approx(1));
        CHECK(result.time_above_50_percent >= 0);
        CHECK(result.time_at_50_percent >= 0);
        CHECK(result.time_at_0_percent >= 0);
    }
}

TEST_CASE("Fan affinity laws leave input validation to the caller", "[fanAffinityLaws]") {
    const auto extrapolated = fal::get50PercentTimeFactor(1.2);
    CHECK(extrapolated.factor == Catch::Approx(1.35));
    CHECK(extrapolated.time_above_50_percent == Catch::Approx(1.4));
    CHECK(extrapolated.time_at_50_percent == Catch::Approx(-0.4));
    CHECK(extrapolated.time_at_0_percent == 0);
    CHECK(std::isnan(fal::get50PercentTimeFactor(std::numeric_limits<double>::quiet_NaN()).factor));

    auto input = exampleInput();
    input.electricity_cost = 0;
    const auto free_energy = fal::calculate(input);
    CHECK(free_energy.annual_energy_baseline > 0);
    CHECK(free_energy.annual_energy_new > 0);
    CHECK(free_energy.annual_cost_savings == 0);
    input.operating_hours = 0;
    checkResult(fal::calculate(input), {0, 0, 0});

    for (const auto control : {fal::MotorControlType::VSD, fal::MotorControlType::TwoSpeed}) {
        input = exampleInput();
        input.motor_control_type_current = control;
        input.flow_percent_baseline = 0;
        CHECK(std::isfinite(fal::calculate(input).annual_energy_baseline));
        CHECK(std::isinf(fal::calculate(input).annual_energy_new));
    }
    input = exampleInput();
    input.motor_efficiency = 0;
    const auto zero_efficiency = fal::calculate(input);
    CHECK(std::isinf(zero_efficiency.annual_energy_baseline));
    CHECK(std::isnan(zero_efficiency.annual_cost_savings));
}

TEST_CASE("Fan affinity laws preserve zero modification flow and signed savings", "[fanAffinityLaws]") {
    auto input = exampleInput();
    input.desired_flow_rate = 0;
    CHECK(fal::calculate(input).annual_energy_new == 0);
    input.motor_control_type_new = fal::MotorControlType::VSD;
    CHECK(fal::calculate(input).annual_energy_new == 0);
    input.flow_mode = fal::FlowMode::Volume;
    input.desired_flow_rate = 36000;
    CHECK(fal::calculate(input).annual_cost_savings < 0);
    input.motor_control_type_new = fal::MotorControlType::TwoSpeed;
    CHECK(fal::calculate(input).annual_cost_savings < 0);
    input.desired_flow_rate = 30000;
    const auto resized = fal::changeFanSize(input, 36, 32);
    CHECK(std::isfinite(resized.annual_energy_new));
    CHECK(resized.annual_cost_savings < 0);
}
