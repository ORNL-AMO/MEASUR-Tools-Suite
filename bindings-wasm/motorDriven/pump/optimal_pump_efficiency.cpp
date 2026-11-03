#include "motorDriven/pump/optimal_pump_efficiency.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(optimal_pump_efficiency) {
    emscripten::value_object<optimal_pump_efficiency::Input>("OptimalPumpEfficiencyInput")
        .field("style", &optimal_pump_efficiency::Input::style)
        .field("rpm", &optimal_pump_efficiency::Input::rpm)
        .field("kinematicViscosity", &optimal_pump_efficiency::Input::kinematic_viscosity)
        .field("stageCount", &optimal_pump_efficiency::Input::stage_count)
        .field("flowRate", &optimal_pump_efficiency::Input::flow_rate)
        .field("head", &optimal_pump_efficiency::Input::head);
    emscripten::function("calculateOptimalPumpEfficiency", &optimal_pump_efficiency::calculate);
}
