#include <emscripten/bind.h>
#include "processHeat/losses/slag_other_material_heat_loss.h"

using namespace emscripten;
using namespace slag_other_material_heat_loss;

EMSCRIPTEN_BINDINGS(slag_other_material_heat_loss) {
    // Parameters for slagOtherMaterialTotalHeatLoss:
    //   weight (lb)
    //   inlet_temperature (°F)
    //   outlet_temperature (°F)
    //   specific_heat (Btu/lb/°F)
    //   correction_factor (unitless)
    function("slagOtherMaterialTotalHeatLoss", &totalHeatLoss);
}