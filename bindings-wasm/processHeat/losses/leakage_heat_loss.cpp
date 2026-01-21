#include <emscripten/bind.h>
#include "processHeat/losses/leakage_heat_loss.h"

using namespace emscripten;
using namespace leakage_heat_loss;

EMSCRIPTEN_BINDINGS(leakage_heat_loss) {
    // Parameters for leakageTotalHeatLoss:
    //   draft_pressure (inch H2O)
    //   opening_area (ft^2)
    //   leakage_gas_temperature (°F)
    //   ambient_temperature (°F)
    //   coefficient_discharge (unitless)
    //   specific_gravity (unitless)
    //   correction_factor (unitless)
    function("leakageTotalHeatLoss", &totalHeatLoss);
}