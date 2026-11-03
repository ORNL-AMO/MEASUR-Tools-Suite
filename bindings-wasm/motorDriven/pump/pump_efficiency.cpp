#include "motorDriven/pump/pump_efficiency.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(pump_efficiency) {
    emscripten::value_object<pump_efficiency::Input>("PumpEfficiencyInput")
        .field("style", &pump_efficiency::Input::style)
        .field("rpm", &pump_efficiency::Input::rpm)
        .field("kinematicViscosity", &pump_efficiency::Input::kinematic_viscosity)
        .field("stageCount", &pump_efficiency::Input::stage_count)
        .field("flowRate", &pump_efficiency::Input::flow_rate)
        .field("head", &pump_efficiency::Input::head);
    emscripten::value_object<pump_efficiency::Result>("PumpEfficiencyResult")
        .field("average", &pump_efficiency::Result::average)
        .field("max", &pump_efficiency::Result::max);
    emscripten::function("calculatePumpEfficiency", &pump_efficiency::calculate);
}
