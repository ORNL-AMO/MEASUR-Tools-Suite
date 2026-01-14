#include <emscripten/bind.h>
#include "processHeat/losses/gas_cooling_heat_loss.h"

using namespace emscripten;
using namespace gas_cooling_heat_loss;

// gasCoolingLosses
EMSCRIPTEN_BINDINGS(gas_cooling_heat_loss) {
    //Parameters for gasCoolingTotalHeatLoss:
    // double flow_rate (ft³/hr)
    // double initial_temperature (°F)
    // double final_temperature (°F)
    // double specific_heat (Btu/scf°F)
    // double correction_factor (unitless)
    // double gas_density (lb/ft³)
    function("gasCoolingTotalHeatLoss", &totalHeatLoss);
}