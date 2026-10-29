#include "motorDriven/pumpFan/optimal_pump_shaft_power.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(optimal_pump_shaft_power) {
    value_object<optimal_pump_shaft_power::PumpInput>("OptimalPumpShaftPowerInput")
        .field("flowRate", &optimal_pump_shaft_power::PumpInput::flow_rate)
        .field("head", &optimal_pump_shaft_power::PumpInput::head)
        .field("specificGravity", &optimal_pump_shaft_power::PumpInput::specific_gravity)
        .field("pumpEfficiency", &optimal_pump_shaft_power::PumpInput::pump_efficiency);

    value_object<optimal_pump_shaft_power::FanInput>("OptimalFanShaftPowerInput")
        .field("flowRate", &optimal_pump_shaft_power::FanInput::flow_rate)
        .field("inletPressure", &optimal_pump_shaft_power::FanInput::inlet_pressure)
        .field("outletPressure", &optimal_pump_shaft_power::FanInput::outlet_pressure)
        .field("compressibilityFactor", &optimal_pump_shaft_power::FanInput::compressibility_factor)
        .field("fanEfficiency", &optimal_pump_shaft_power::FanInput::fan_efficiency)
        .field("velocityPressure", &optimal_pump_shaft_power::FanInput::velocity_pressure);

    function("calculateOptimalPumpShaftPower", &optimal_pump_shaft_power::calculatePump);
    function("calculateOptimalFanShaftPower", &optimal_pump_shaft_power::calculateFan);
}
