#include <emscripten/bind.h>

#include "motorDriven/motor/motor_power_factor.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_power_factor) {
    value_object<motor_power_factor::Input>("MotorPowerFactorInput")
        .field("lineFrequency", &motor_power_factor::Input::line_frequency)
        .field("motorRpm", &motor_power_factor::Input::motor_rpm)
        .field("efficiencyClass", &motor_power_factor::Input::efficiency_class)
        .field("specifiedEfficiency", &motor_power_factor::Input::specified_efficiency)
        .field("motorRatedPower", &motor_power_factor::Input::motor_rated_power)
        .field("loadFactor", &motor_power_factor::Input::load_factor)
        .field("motorCurrent", &motor_power_factor::Input::motor_current)
        .field("motorEfficiency", &motor_power_factor::Input::motor_efficiency)
        .field("ratedVoltage", &motor_power_factor::Input::rated_voltage);

    function("calculateMotorPowerFactor", &motor_power_factor::calculate);
}
