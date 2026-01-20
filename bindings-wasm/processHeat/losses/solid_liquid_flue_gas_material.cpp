#include "processHeat/losses/solid_liquid_flue_gas_material.h"

#include <emscripten/bind.h>

using namespace emscripten;
using namespace solid_liquid_flue_gas_material;

EMSCRIPTEN_BINDINGS(solid_liquid_flue_gas_material) {
    // Parameters for totalHeatLoss:
    //   flue_gas_temperature (°F)
    //   excess_air (fraction, unitless)
    //   combustion_air_temperature (°F)
    //   fuel_temperature (°F)
    //   moisture_in_air_combustion (%)
    //   ash_discharge_temperature (°F)
    //   unburned_carbon_in_ash (fraction, unitless)
    //   carbon (%)
    //   hydrogen (%)
    //   sulphur (%)
    //   inert_ash (%)
    //   o2 (%)
    //   moisture (%)
    //   nitrogen (%)
    //   ambient_air_temp_f (°F, default: 60)
    function("solidLiquidFlueGasMaterialTotalHeatLoss", &totalHeatLoss);

    // Parameters for calculateExcessAirFromFlueGasO2:
    //   flue_gas_o2 (%)
    //   carbon (%)
    //   hydrogen (%)
    //   sulphur (%)
    //   inert_ash (%)
    //   o2 (%)
    //   moisture (%)
    //   nitrogen (%)
    //   moisture_in_air_combustion (%)
    function("calculateExcessAirFromFlueGasO2", &calculateExcessAirFromFlueGasO2);

    // Parameters for calculateFlueGasO2:
    //   excess_air (fraction, unitless)
    //   carbon (%)
    //   hydrogen (%)
    //   sulphur (%)
    //   inert_ash (%)
    //   o2 (%)
    //   moisture (%)
    //   nitrogen (%)
    //   moisture_in_air_combustion (%)
    function("calculateFlueGasO2", &calculateFlueGasO2);

    // Parameters for calculateHeatingValueFuel:
    //   carbon (%)
    //   hydrogen (%)
    //   sulphur (%)
    //   inert_ash (%)
    //   o2 (%)
    //   moisture (%)
    //   nitrogen (%)
    function("calculateHeatingValueFuel", &calculateHeatingValueFuel);

    // Parameters for calculateStoichiometricAir:
    //   carbon (%)
    //   hydrogen (%)
    //   sulphur (%)
    //   inert_ash (%)
    //   o2 (%)
    //   moisture (%)
    //   nitrogen (%)
    function("calculateStoichiometricAir", &calculateStoichiometricAir);
}
