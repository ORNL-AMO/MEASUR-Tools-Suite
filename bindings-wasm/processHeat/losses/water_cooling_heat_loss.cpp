#include "processHeat/losses/water_cooling_heat_loss.h"

#include <emscripten/bind.h>

using namespace emscripten;
using namespace water_cooling_heat_loss;

EMSCRIPTEN_BINDINGS(water_cooling_heat_loss) { 
    // Parameters for waterCoolingTotalHeatLoss:
    //   flowRate (gal/min)
    //   initialTemperature (°F)
    //   outletTemperature (°F)
    //   correctionFactor (unitless)
    function("waterCoolingTotalHeatLoss", &totalHeatLoss);
}
