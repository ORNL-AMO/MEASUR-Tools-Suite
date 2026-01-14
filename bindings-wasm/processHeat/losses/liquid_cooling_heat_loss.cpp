#include <emscripten/bind.h>
#include "processHeat/losses/liquid_cooling_heat_loss.h"

using namespace emscripten;
using namespace liquid_cooling_heat_loss;

EMSCRIPTEN_BINDINGS(liquid_cooling_heat_loss) {
    // Parameters for liquidCoolingTotalHeatLoss:
    //   flow_rate (gal/min)
    //   density (lb/ft^3)
    //   initial_temperature (°F)
    //   outlet_temperature (°F)
    //   specific_heat (Btu/lb/°F)
    //   correction_factor (unitless)
    function("liquidCoolingTotalHeatLoss", &totalHeatLoss);
}