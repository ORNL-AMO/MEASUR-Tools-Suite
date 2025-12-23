#include "processHeat/cascade_heat_high_to_low.h"
#include <algorithm>

namespace cascade_heat_high_to_low {

CascadeHeatHighToLowResults calculateCascadeHeatHighToLow(
    const gas_composition::GasComposition& gas_compositions,
    double fuel_hv,
    double fuel_cost,
    double pri_firing_rate,
    double pri_exhaust_temp,
    double pri_exhaust_o2,
    double pri_comb_air_temp,
    double pri_op_hours,
    double sec_firing_rate,
    double sec_exhaust_temp,
    double sec_exhaust_o2,
    double sec_comb_air_temp,
    double sec_op_hours,
    double fuel_temp_f,
    double ambient_air_temp_f,
    double comb_air_moisture_perc
) {
    // Calculate primary process flue gas properties
    auto pri_props = gas_flue_gas_material::processHeatProperties(
        gas_compositions, pri_exhaust_temp, pri_exhaust_o2, pri_comb_air_temp,
        fuel_temp_f, ambient_air_temp_f, comb_air_moisture_perc);

    double stoich_air_volume  = pri_props.stoich_air;
    double pri_excess_air     = pri_props.excess_air;
    double pri_available_heat = pri_props.available_heat;
    double pri_flue_spec_heat = pri_props.specific_heat;
    // TODO: CHECK DENSITY VS TOTAL GENERATED
    double pri_flue_density   = pri_props.total_generated / 16.018463;

    // Calculate secondary process flue gas properties
    auto sec_props = gas_flue_gas_material::processHeatProperties(
        gas_compositions, sec_exhaust_temp, sec_exhaust_o2, sec_comb_air_temp,
        fuel_temp_f, ambient_air_temp_f, comb_air_moisture_perc);

    double sec_excess_air     = sec_props.excess_air;
    double sec_available_heat = sec_props.available_heat;

    // Main calculation logic
    double pri_flue_volume =
        pri_firing_rate * stoich_air_volume * (1 + pri_excess_air) * 1000000 / fuel_hv
        + pri_firing_rate * 1000000 / fuel_hv;
    double hx_energy_rate =
        pri_flue_volume * pri_flue_spec_heat * pri_flue_density * (pri_exhaust_temp - sec_exhaust_temp) / 1000000;
    double eq_energy_supply = hx_energy_rate / sec_available_heat;
    double eff_op_hours     = std::min(pri_op_hours, sec_op_hours);
    double hourly_savings   = std::min(eq_energy_supply, sec_firing_rate);
    double energy_savings   = hourly_savings * eff_op_hours;
    double cost_savings     = energy_savings * fuel_cost;

    CascadeHeatHighToLowResults results;
    results.pri_flue_volume     = pri_flue_volume;
    results.hx_energy_rate      = hx_energy_rate;
    results.eq_energy_supply    = eq_energy_supply;
    results.eff_op_hours        = eff_op_hours;
    results.energy_savings      = energy_savings;
    results.cost_savings        = cost_savings;
    results.hourly_savings      = hourly_savings;
    results.pri_excess_air      = pri_excess_air;
    results.pri_available_heat  = pri_available_heat;
    results.sec_excess_air      = sec_excess_air;
    results.sec_available_heat  = sec_available_heat;
    return results;
}

} // namespace cascade_heat_high_to_low