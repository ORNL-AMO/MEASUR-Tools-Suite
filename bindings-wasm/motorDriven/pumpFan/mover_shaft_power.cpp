#include "motorDriven/pumpFan/mover_shaft_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mover_shaft_power) {
    value_object<mover_shaft_power::Input>("MoverShaftPowerInput")
        .field("motorShaftPower", &mover_shaft_power::Input::motor_shaft_power)
        .field("drive", &mover_shaft_power::Input::drive)
        .field("specifiedEfficiency", &mover_shaft_power::Input::specified_efficiency);

    value_object<mover_shaft_power::Result>("MoverShaftPowerResult")
        .field("moverShaftPower", &mover_shaft_power::Result::mover_shaft_power)
        .field("driveEfficiency", &mover_shaft_power::Result::drive_efficiency);

    function("calculateMoverShaftPower", &mover_shaft_power::calculate);
}
