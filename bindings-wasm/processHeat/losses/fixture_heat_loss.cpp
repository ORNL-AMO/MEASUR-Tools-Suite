#include <emscripten/bind.h>
#include "processHeat/losses/fixture_heat_loss.h"

using namespace emscripten;
using namespace fixture_heat_loss;

EMSCRIPTEN_BINDINGS(fixture_heat_loss) {
    // Parameters for fixtureTotalHeatLoss:
    //   specific_heat (Btu/lb/°F)
    //   feed_rate (lb/hr)
    //   initial_temperature (°F)
    //   final_temperature (°F)
    //   correction_factor (unitless)
    function("fixtureTotalHeatLoss", &totalHeatLoss);
}