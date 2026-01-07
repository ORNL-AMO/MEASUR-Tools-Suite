#include <string>
#include <emscripten/bind.h>
#include "steam/air_water_cooling_using_flue.h"

using namespace emscripten;
using namespace air_water_cooling_using_flue;

EMSCRIPTEN_BINDINGS(air_water_cooling_using_flue_class) {
    value_object<AirWaterCoolingUsingFlueResults>("AirWaterCoolingUsingFlueOutput")
        .field("excessAir", &AirWaterCoolingUsingFlueResults::excess_air)
        .field("flowFlueGas", &AirWaterCoolingUsingFlueResults::flow_flue_gas)
        .field("specHeat", &AirWaterCoolingUsingFlueResults::specific_heat)
        .field("fracCondensed", &AirWaterCoolingUsingFlueResults::fraction_condensed)
        .field("effThermal", &AirWaterCoolingUsingFlueResults::available_heat_fraction)
        .field("effThermalLH", &AirWaterCoolingUsingFlueResults::total_available_heat_fraction)
        .field("effLH", &AirWaterCoolingUsingFlueResults::latent_heat_fraction)
        .field("heatRecovery", &AirWaterCoolingUsingFlueResults::latent_heat_recovery)
        .field("sensibleHeatRecovery", &AirWaterCoolingUsingFlueResults::sensible_heat_recovery);

    // Parameters for airWaterCoolingUsingFlue:
    //   gas_compositions (Fuel gas composition for flue gas calculations)
    //   heat_input (Heat input, MBtu/hr)
    //   temp_flue_gas_in (Flue gas inlet temperature, °F)
    //   temp_flue_gas_out (Flue gas outlet temperature, °F)
    //   temp_comb_air (Combustion air temperature, °F)
    //   fuel_temp (Fuel temperature, °F)
    //   perc_o2 (Oxygen percentage in flue gas, fraction)
    //   ambient_air_temp (Ambient air temperature, °F; default: 60)
    //   moist_comb_air (Combustion air moisture, fraction; default: 0)
    function("airWaterCoolingUsingFlue", &airWaterCoolingUsingFlue);
}
