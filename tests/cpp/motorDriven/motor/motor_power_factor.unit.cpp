#include "motorDriven/motor/motor_power_factor.h"

#include <cmath>
#include <limits>
#include <stdexcept>

#include "catch.hpp"
#include "motorDriven/motor/MotorPerformance.h"

using Catch::Approx;

TEST_CASE("Motor power factor is stateless and does not modify its complete input", "[motor_power_factor]") {
    const motor_power_factor::Input input = {Motor::LineFrequency::FREQ60, 1780,
        Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 100, 0.75, 100, 0.9, 460};
    auto near_zero = input;
    near_zero.load_factor = 0;
    near_zero.motor_current = 30;
    const auto first = motor_power_factor::calculate(input);
    CHECK(motor_power_factor::calculate(near_zero) == Approx(0.053160046055729181));
    CHECK(motor_power_factor::calculate(input) == first);
    CHECK(input.line_frequency == Motor::LineFrequency::FREQ60);
    CHECK(input.motor_rpm == 1780);
    CHECK(input.efficiency_class == Motor::EfficiencyClass::ENERGY_EFFICIENT);
    CHECK(input.specified_efficiency == 0);
    CHECK(input.motor_rated_power == 100);
    CHECK(input.load_factor == 0.75);
    CHECK(input.motor_current == 100);
    CHECK(input.motor_efficiency == 0.9);
    CHECK(input.rated_voltage == 460);

    // These fields do not participate in the loaded branch, even with an invalid model selection.
    auto loaded = input;
    loaded.line_frequency = Motor::LineFrequency::FREQ50;
    loaded.motor_rpm = 1450;
    loaded.efficiency_class = Motor::EfficiencyClass::SPECIFIED;
    loaded.specified_efficiency = -1;
    CHECK(motor_power_factor::calculate(loaded) == first);

    auto ignored = near_zero;
    ignored.rated_voltage = 2300;
    ignored.motor_efficiency = std::numeric_limits<double>::quiet_NaN();
    CHECK(motor_power_factor::calculate(ignored) == motor_power_factor::calculate(near_zero));
    CHECK(near_zero.load_factor == 0);
    CHECK(near_zero.motor_current == 30);
}

TEST_CASE("Motor power factor propagates near-zero efficiency model errors", "[motor_power_factor]") {
    motor_power_factor::Input input = {Motor::LineFrequency::FREQ60, 1780,
        Motor::EfficiencyClass::SPECIFIED, -1, 100, 0, 30, 0, 460};
    CHECK_THROWS_AS(motor_power_factor::calculate(input), std::runtime_error);
    input.load_factor = 0.001;
    input.motor_efficiency = 0.9;
    CHECK(motor_power_factor::calculate(input) == Approx(0.0034678204574513758));
}

TEST_CASE("MotorPerformance retains loaded outputs and resolves zero-load model data", "[motor_power_factor]") {
    MotorPerformance loaded(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
                            200, 0, 0.25, 460, 225.8);
    const auto result = loaded.calculate();
    CHECK(result.current == Approx(36.1065805345533).epsilon(1e-12));
    CHECK(result.efficiency == Approx(93.03933838910918).epsilon(1e-12));
    CHECK(result.powerFactor == Approx(61.718229798145316).epsilon(1e-12));

    MotorPerformance zero(Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
                          200, 0, 0, 460, 225.8);
    const auto zero_result = zero.calculate();
    // Independently evaluated from the unchanged current and zero-load loss models at base 2714873.
    // The legacy MotorPerformance zero-load path used uninitialized nameplate fields.
    CHECK(zero_result.current == Approx(27.570269143886257).epsilon(1e-12));
    CHECK(zero_result.efficiency == 0);
    CHECK(zero_result.powerFactor == Approx(4.5008995882102676).epsilon(1e-12));
    CHECK(zero.calculate().powerFactor == zero_result.powerFactor);
}

TEST_CASE("Motor power factor preserves fully initialized legacy goldens", "[motor_power_factor]") {
    struct Golden {
        motor_power_factor::Input input;
        double expected;
    };
    // Captured from unchanged MotorPowerFactor.cpp and motor_efficiency.cpp at base 2714873.
    // The nine-argument constructor initialized all model fields before either branch ran.
    const Golden goldens[] = {
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 100, 0.9, 460},
         0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 200, 0.25, 81.528659, 0.9303933838910918, 460},
         0.6171822968233854},
        {{Motor::LineFrequency::FREQ50, 1450, Motor::EfficiencyClass::STANDARD,
          0, 100, 0.5, 100, 0.9, 400},
         0.5981990289103623},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 1, 100, 0.95, 230},
         1.9711821547618342},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 1.5, 150, 0.95, 2300},
         0.19711821547618347},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0, 30, 0, 460},
         0.05316004605572918},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.000999, 30, 0.9, 230},
         0.05316004605572918},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, -0.000999, 30, 0.9, 400},
         0.05316004605572918},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.001, 30, 0.9, 460},
         0.0034678204574513758},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, -0.001, 30, 0.9, 460},
         -0.0034678204574513758},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.001001, 30, 0.9, 460},
         0.0034712882779088265},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, -0.001001, 30, 0.9, 460},
         -0.0034712882779088265},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::STANDARD,
          0, 100, 0, 30, 0, 460},
         0.09068480088410688},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::PREMIUM,
          0, 100, 0, 30, 0, 460},
         0.05031025820280281},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::SPECIFIED,
          0.95, 100, 0, 30, 0, 460},
         0.05274198840502102},
        {{Motor::LineFrequency::FREQ50, 1450, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0, 30, 0, 400},
         0.05316004605572918},
        {{Motor::LineFrequency::FREQ50, 1450, Motor::EfficiencyClass::SPECIFIED,
          0.95, 150, 0, 50, 0, 230},
         0.04711383388030136},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0, 30, 0.8, 0},
         0.05316004605572918},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0, -30, 0, 460},
         -0.05316004605572918},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, -100, 0.9, 460},
         -0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, -0.75, 100, 0.9, 460},
         -0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 100, -0.9, 460},
         -0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 100, 0.9, -460},
         -0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, -100, 0.75, 100, 0.9, 460},
         -0.7802596029265596},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 20, 0.9, 460},
         3.9012980146327974},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 0, 0.75, 100, 0.9, 460},
         0},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 0, 0.9, 460},
         std::numeric_limits<double>::infinity()},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 100, 0, 460},
         std::numeric_limits<double>::infinity()},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0.75, 100, 0.9, 0},
         std::numeric_limits<double>::infinity()},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 100, 0, 0, 0, 460},
         std::numeric_limits<double>::infinity()},
        {{Motor::LineFrequency::FREQ60, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT,
          0, 0, 0.75, 0, 0.9, 460},
         std::numeric_limits<double>::quiet_NaN()},
    };
    for (const auto& golden : goldens) {
        CAPTURE(golden.input.load_factor, golden.input.rated_voltage, golden.input.motor_current,
                static_cast<int>(golden.input.efficiency_class));
        const auto result = motor_power_factor::calculate(golden.input);
        if (std::isnan(golden.expected)) {
            CHECK(std::isnan(result));
        }
        else if (std::isinf(golden.expected)) {
            CHECK(result == golden.expected);
        }
        else {
            CHECK(result == Approx(golden.expected).epsilon(1e-12).margin(1e-12));
        }
    }
}
