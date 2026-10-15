#include "motorDriven/motor/motor_shaft_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_shaft_power) {
    value_object<motor_shaft_power::Input>("MotorShaftPowerInput")
        .field("motorRatedPower", &motor_shaft_power::Input::motor_rated_power)
        .field("motorMeasuredPower", &motor_shaft_power::Input::motor_measured_power)
        .field("motorRpm", &motor_shaft_power::Input::motor_rpm)
        .field("lineFrequency", &motor_shaft_power::Input::line_frequency)
        .field("efficiencyClass", &motor_shaft_power::Input::efficiency_class)
        .field("specifiedEfficiency", &motor_shaft_power::Input::specified_efficiency)
        .field("ratedVoltage", &motor_shaft_power::Input::rated_voltage)
        .field("fullLoadAmps", &motor_shaft_power::Input::full_load_amps)
        .field("fieldVoltage", &motor_shaft_power::Input::field_voltage)
        .field("loadEstimationMethod", &motor_shaft_power::Input::load_estimation_method)
        .field("fieldCurrent", &motor_shaft_power::Input::field_current);

    value_object<motor_shaft_power::Result>("MotorShaftPowerResult")
        .field("shaftPower", &motor_shaft_power::Result::shaft_power)
        .field("current", &motor_shaft_power::Result::current)
        .field("powerFactor", &motor_shaft_power::Result::power_factor)
        .field("efficiency", &motor_shaft_power::Result::efficiency)
        .field("power", &motor_shaft_power::Result::power)
        .field("estimatedFLA", &motor_shaft_power::Result::estimated_fla)
        .field("loadFactor", &motor_shaft_power::Result::load_factor);

    function("calculateMotorShaftPower", &motor_shaft_power::calculate);
}
