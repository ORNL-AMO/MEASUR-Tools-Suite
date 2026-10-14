#include "motorDriven/motor/motor_power.h"

#include "catch.hpp"

using Catch::Approx;

TEST_CASE("Motor electrical input power preserves legacy native goldens", "[motor_power]") {
    // Captured by compiling the unchanged MotorPower.cpp at base 4c573f3.
    struct Golden {
        double voltage;
        double current;
        double power_factor;
        double power;
    };
    const Golden goldens[] = {
        {460, 100, 0.85, 67.723186575943089},
        {230, 25, 0.75, 7.4694691076407835},
        {400, 113.8, 0.9, 70.958657484481762},
        {2300, 557.9, 0.92, 2044.7143839683038},
        {460, 100, 1, 79.674337148168362},
        {0, 100, 0.85, 0},
        {460, 0, 0.85, 0},
        {460, 100, 0, 0},
        {-460, 100, 0.85, -67.723186575943089},
        {460, -100, 0.85, -67.723186575943089},
        {460, 100, -0.85, -67.723186575943089},
        {460, 100, 1.2, 95.609204577802032},
    };
    for (const auto& golden : goldens) {
        CAPTURE(golden.voltage, golden.current, golden.power_factor);
        CHECK(motor_power::calculate(golden.voltage, golden.current, golden.power_factor) ==
              Approx(golden.power).epsilon(1e-12).margin(1e-12));
    }
}
