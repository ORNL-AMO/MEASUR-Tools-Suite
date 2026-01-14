#include "processHeat/losses/gas_flue_gas_material.h"
#include <emscripten/bind.h>

using namespace emscripten;
using namespace gas_flue_gas_material;

EMSCRIPTEN_BINDINGS(gas_flue_gas_material) {
    value_object<ProcessHeatProperties>("ProcessHeatProperties")
        .field("stoichAir", &ProcessHeatProperties::stoich_air)
        .field("excessAir", &ProcessHeatProperties::excess_air)
        .field("availableHeat", &ProcessHeatProperties::available_heat)
        .field("specificHeat", &ProcessHeatProperties::specific_heat)
        .field("density", &ProcessHeatProperties::total_generated)
        .field("flueGasO2", &ProcessHeatProperties::flue_gas_o2);

    // Parameters for gasFlueGasMaterialTotalHeatLoss:
    //   flue_gas_temperature (°F)
    //   excess_air_percentage (percent)
    //   combustion_air_temperature (°F)
    //   compositions (GasComposition)
    //   fuel_temperature (°F)
    function("gasFlueGasMaterialTotalHeatLoss", &totalHeatLoss);

    // Parameters for gasFlueGasMaterialProcessHeatProperties:
    //   compositions (GasComposition)
    //   flue_gas_temp (°F)
    //   flue_gas_o2 (percent)
    //   comb_air_temp (°F)
    //   fuel_temp (°F)
    //   ambient_air_temp (°F, default: 60)
    //   comb_air_moisture (percent, default: 0)
    //   excess_air (percent, default: 0)
    function("gasFlueGasMaterialProcessHeatProperties", &processHeatProperties);
}