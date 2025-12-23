#include <string>

#include <emscripten/bind.h>
#include "processHeat/cascade_heat_high_to_low.h"


using namespace emscripten;
using namespace cascade_heat_high_to_low;
EMSCRIPTEN_BINDINGS(cascade_heat_high_to_low_class) {
    value_object<CascadeHeatHighToLowResults>("CascadeHeatHighToLowOutput")
        .field("priFlueVolume", &CascadeHeatHighToLowResults::pri_flue_volume)
        .field("hxEnergyRate", &CascadeHeatHighToLowResults::hx_energy_rate)
        .field("eqEnergySupply", &CascadeHeatHighToLowResults::eq_energy_supply)
        .field("effOpHours", &CascadeHeatHighToLowResults::eff_op_hours)
        .field("energySavings", &CascadeHeatHighToLowResults::energy_savings)
        .field("costSavings", &CascadeHeatHighToLowResults::cost_savings)
        .field("hourlySavings", &CascadeHeatHighToLowResults::hourly_savings)
        .field("priExcessAir", &CascadeHeatHighToLowResults::pri_excess_air)
        .field("priAvailableHeat", &CascadeHeatHighToLowResults::pri_available_heat)
        .field("secExcessAir", &CascadeHeatHighToLowResults::sec_excess_air)
        .field("secAvailableHeat", &CascadeHeatHighToLowResults::sec_available_heat);

    // Parameters for calculateCascadeHeatHighToLow:
    //   gas_compositions (GasComposition)
    //   fuel_hv (Btu/SCF)
    //   fuel_cost (USD/MMBtu)
    //   pri_firing_rate (MMBtu/hr)
    //   pri_exhaust_temp (°F)
    //   pri_exhaust_o2 (fraction)
    //   pri_comb_air_temp (°F)
    //   pri_op_hours (hr/yr)
    //   sec_firing_rate (MMBtu/hr)
    //   sec_exhaust_temp (°F)
    //   sec_exhaust_o2 (fraction)
    //   sec_comb_air_temp (°F)
    //   sec_op_hours (hr/yr)
    //   fuel_temp_f (°F)
    //   ambient_air_temp_f (°F)
    //   comb_air_moisture_perc (percent)
    function("calculateCascadeHeatHighToLow", &calculateCascadeHeatHighToLow);
}