#include "motorDriven/pumpFan/mover_efficiency.h"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mover_efficiency) {
    value_object<mover_efficiency::PumpInput>("PumpMoverEfficiencyInput")
        .field("specificGravity", &mover_efficiency::PumpInput::specific_gravity)
        .field("flowRate", &mover_efficiency::PumpInput::flow_rate)
        .field("head", &mover_efficiency::PumpInput::head)
        .field("moverShaftPower", &mover_efficiency::PumpInput::mover_shaft_power);

    value_object<mover_efficiency::FanInput>("FanMoverEfficiencyInput")
        .field("flowRate", &mover_efficiency::FanInput::flow_rate)
        .field("moverShaftPower", &mover_efficiency::FanInput::mover_shaft_power)
        .field("inletPressure", &mover_efficiency::FanInput::inlet_pressure)
        .field("outletPressure", &mover_efficiency::FanInput::outlet_pressure)
        .field("compressibilityFactor", &mover_efficiency::FanInput::compressibility_factor)
        .field("velocityPressure", &mover_efficiency::FanInput::velocity_pressure);

    function("calculatePumpMoverEfficiency", &mover_efficiency::calculatePump);
    function("calculateFanMoverEfficiency", &mover_efficiency::calculateFan);
}
