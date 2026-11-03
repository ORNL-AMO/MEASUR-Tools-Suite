#include "motorDriven/pump/optimal_pre_pump_efficiency.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(optimal_pre_pump_efficiency) {
    emscripten::value_object<optimal_pre_pump_efficiency::Input>("OptimalPrePumpEfficiencyInput")
        .field("style", &optimal_pre_pump_efficiency::Input::style)
        .field("flowRate", &optimal_pre_pump_efficiency::Input::flow_rate);
    emscripten::function("calculateOptimalPrePumpEfficiency", &optimal_pre_pump_efficiency::calculate);
}
