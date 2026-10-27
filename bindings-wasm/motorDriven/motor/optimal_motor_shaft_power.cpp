#include "motorDriven/motor/optimal_motor_shaft_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(optimal_motor_shaft_power) {
    value_object<optimal_motor_shaft_power::Input>("OptimalMotorShaftPowerInput")
        .field("moverShaftPower", &optimal_motor_shaft_power::Input::mover_shaft_power)
        .field("drive", &optimal_motor_shaft_power::Input::drive)
        .field("specifiedEfficiency", &optimal_motor_shaft_power::Input::specified_efficiency);

    value_object<optimal_motor_shaft_power::Result>("OptimalMotorShaftPowerResult")
        .field("motorShaftPower", &optimal_motor_shaft_power::Result::motor_shaft_power)
        .field("driveEfficiency", &optimal_motor_shaft_power::Result::drive_efficiency);

    function("calculateOptimalMotorShaftPower", &optimal_motor_shaft_power::calculate);
}
