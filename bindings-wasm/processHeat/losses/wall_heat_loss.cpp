#include "processHeat/losses/wall_heat_loss.h"

#include <emscripten/bind.h>

using namespace emscripten;
using namespace wall_heat_loss;

EMSCRIPTEN_BINDINGS(wall_heat_loss) {
    // Parameters for wallTotalHeatLoss:
    //   surface_area (ft²)
    //   ambient_temperature (°F)
    //   surface_temperature (°F)
    //   wind_speed (mph)
    //   surface_emissivity (unitless)
    //   shape_factor (unitless)
    //   correction_factor (unitless)
    function("wallTotalHeatLoss", &totalHeatLoss);

    // Parameters for wallConvectiveHeatLoss:
    //   shape_factor (unitless)
    //   wind_speed (mph)
    //   surface_area (ft²)
    //   surface_temperature (°F)
    //   ambient_temperature (°F)
    function("wallConvectiveHeatLoss", &convectiveHeatLoss);

    // Parameters for wallRadiativeHeatLoss:
    //   surface_emissivity (unitless)
    //   surface_area (ft²)
    //   surface_temperature (°F)
    //   ambient_temperature (°F)
    function("wallRadiativeHeatLoss", &radiativeHeatLoss);
}
