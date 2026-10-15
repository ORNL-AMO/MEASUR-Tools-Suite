#include "motorDriven/motor/optimal_motor_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(optimal_motor_power) {
    value_object<optimal_motor_power::Input>("OptimalMotorPowerInput")
        .field("motorRatedPower", &optimal_motor_power::Input::motor_rated_power)
        .field("motorRpm", &optimal_motor_power::Input::motor_rpm)
        .field("lineFrequency", &optimal_motor_power::Input::line_frequency)
        .field("efficiencyClass", &optimal_motor_power::Input::efficiency_class)
        .field("specifiedEfficiency", &optimal_motor_power::Input::specified_efficiency)
        .field("ratedVoltage", &optimal_motor_power::Input::rated_voltage)
        .field("fieldVoltage", &optimal_motor_power::Input::field_voltage)
        .field("optimalMotorShaftPower", &optimal_motor_power::Input::optimal_motor_shaft_power);

    value_object<optimal_motor_power::Result>("OptimalMotorPowerResult")
        .field("power", &optimal_motor_power::Result::power)
        .field("efficiency", &optimal_motor_power::Result::efficiency)
        .field("current", &optimal_motor_power::Result::current)
        .field("powerFactor", &optimal_motor_power::Result::power_factor)
        .field("loadFactor", &optimal_motor_power::Result::load_factor);

    function("calculateOptimalMotorPower", &optimal_motor_power::calculate);
}
