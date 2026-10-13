#include <emscripten/bind.h>

#include "motorDriven/motor/motor_current.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_current) {
    value_object<motor_current::Input>("MotorCurrentInput")
        .field("motorRatedPower", &motor_current::Input::motor_rated_power)
        .field("motorRpm", &motor_current::Input::motor_rpm)
        .field("lineFrequency", &motor_current::Input::line_frequency)
        .field("efficiencyClass", &motor_current::Input::efficiency_class)
        .field("specifiedEfficiency", &motor_current::Input::specified_efficiency)
        .field("loadFactor", &motor_current::Input::load_factor)
        .field("ratedVoltage", &motor_current::Input::rated_voltage);

    value_object<motor_current::Result>("MotorCurrentOutput")
        .field("current", &motor_current::Result::current)
        .field("estimatedFLA", &motor_current::Result::estimated_fla);

    function("calculateMotorCurrent", &motor_current::calculate);
    function("calculateOptimalMotorCurrent", &motor_current::calculateOptimal);
}
