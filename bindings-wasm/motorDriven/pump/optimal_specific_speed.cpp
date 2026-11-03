#include "motorDriven/pump/optimal_specific_speed.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(optimal_specific_speed) {
    emscripten::value_object<optimal_specific_speed::Input>("OptimalSpecificSpeedInput")
        .field("rpm", &optimal_specific_speed::Input::rpm)
        .field("flowRate", &optimal_specific_speed::Input::flow_rate)
        .field("head", &optimal_specific_speed::Input::head)
        .field("stageCount", &optimal_specific_speed::Input::stage_count);
    emscripten::function("calculateOptimalSpecificSpeed", &optimal_specific_speed::calculate);
}
