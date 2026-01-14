#include <emscripten/bind.h>
#include "processHeat/losses/auxiliary_power_used.h"

using namespace emscripten;
using namespace auxiliary_power_used;

EMSCRIPTEN_BINDINGS(auxiliary_power_used) {
    // Parameters for auxiliaryCalculatePowerUsed:
    //   number_of_motor_phases (unitless)
    //   supply_voltage (V)
    //   avg_current (A)
    //   power_factor (unitless)
    //   operating_time (percent, 0-100)
    function("auxiliaryCalculatePowerUsed", &calculatePowerUsed);
}
