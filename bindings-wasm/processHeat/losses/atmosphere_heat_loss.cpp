#include <emscripten/bind.h>
#include "processHeat/losses/atmosphere_heat_loss.h"

using namespace emscripten;
using namespace atmosphere_heat_loss;

EMSCRIPTEN_BINDINGS(atmosphere_heat_loss) {
    // Parameters for atmosphereTotalHeatLoss:
    //   flow_rate (SCFH)
    //   specific_heat (Btu/SCF/°F)
    //   inlet_temperature (°F)
    //   outlet_temperature (°F)
    //   correction_factor (unitless)
    function("atmosphereTotalHeatLoss", &totalHeatLoss);
}