#include "motorDriven/pumpFan/fluid_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(fluid_power) {
    value_object<fluid_power::PumpInput>("PumpFluidPowerInput")
        .field("specificGravity", &fluid_power::PumpInput::specific_gravity)
        .field("flowRate", &fluid_power::PumpInput::flow_rate)
        .field("head", &fluid_power::PumpInput::head);

    value_object<fluid_power::FanInput>("FanFluidPowerInput")
        .field("flowRate", &fluid_power::FanInput::flow_rate)
        .field("inletPressure", &fluid_power::FanInput::inlet_pressure)
        .field("outletPressure", &fluid_power::FanInput::outlet_pressure)
        .field("compressibilityFactor", &fluid_power::FanInput::compressibility_factor)
        .field("velocityPressure", &fluid_power::FanInput::velocity_pressure);

    function("calculatePumpFluidPower", &fluid_power::calculatePump);
    function("calculateFanFluidPower", &fluid_power::calculateFan);
}
