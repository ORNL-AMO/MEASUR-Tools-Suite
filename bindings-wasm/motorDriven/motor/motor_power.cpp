#include <emscripten/bind.h>

#include "motorDriven/motor/motor_power.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_power) {
    function("calculateMotorPower", &motor_power::calculate);
}
