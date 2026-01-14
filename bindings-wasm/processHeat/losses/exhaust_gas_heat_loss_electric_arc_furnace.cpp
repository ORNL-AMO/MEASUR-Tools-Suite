#include <emscripten/bind.h>
#include "processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace.h"

using namespace emscripten;
using namespace exhaust_gas_heat_loss_electric_arc_furnace;

// exhaustGasEAF
EMSCRIPTEN_BINDINGS(exhaust_gas_heat_loss_electric_arc_furnace) {
    // Parameters for exhaustGasEAFTotalHeatLoss:
    //   off_gas_temp (°F),
    //   co_percent (%),
    //   h2_percent (%),
    //   combustible_gases_percent (%),
    //   volume_flow_rate (ft³/min),
    //   dust_loading (lb/ft³)
    function("exhaustGasEAFTotalHeatLoss", &totalHeatLoss);
}
