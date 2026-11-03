#include "motorDriven/pump/optimal_specific_speed_correction.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(optimal_specific_speed_correction) {
    emscripten::value_object<optimal_specific_speed_correction::Input>("OptimalSpecificSpeedCorrectionInput")
        .field("style", &optimal_specific_speed_correction::Input::style)
        .field("specificSpeed", &optimal_specific_speed_correction::Input::specific_speed);
    emscripten::function("calculateOptimalSpecificSpeedCorrection", &optimal_specific_speed_correction::calculate);
}
