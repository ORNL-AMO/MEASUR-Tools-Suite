#include "motorDriven/pump/optimal_deviation_factor.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(optimal_deviation_factor) {
    emscripten::function("calculateOptimalDeviationFactor", &optimal_deviation_factor::calculate);
}
