
#include "processHeat/water_heating_using_exhaust.h"
#include "physics/constants.h"

namespace water_heating_using_exhaust {

WaterHeatingUsingExhaustResults waterHeatingUsingExhaust(
    double available_heat,
    double heat_input,
    double hx_efficiency,
    double chiller_in_temperature,
    double chiller_out_temperature,
    double cop_chiller,
    double chiller_efficiency,
    double cop_compressor
) {
    WaterHeatingUsingExhaustResults results;
    // Calculate recovered heat from exhaust gas
    results.recovered_heat = (1 - available_heat) * heat_input * hx_efficiency;

    // Calculate hot water flow rate based on temperature difference and water density
    results.hot_water_flow = results.recovered_heat / ((chiller_in_temperature - chiller_out_temperature) * physics::us::kWaterDensity);

    // Convert recovered heat to tons of refrigeration using COP and conversion factor
    results.tons_refrigeration = results.recovered_heat * cop_chiller / physics::conversions::kBtuPerTonRefrigeration;

    // Calculate chiller capacity in tons
    results.capacity_chiller = results.tons_refrigeration * chiller_efficiency;

    // Calculate equivalent electrical energy required for compressor
    results.electrical_energy = results.recovered_heat * cop_chiller * chiller_efficiency / (cop_compressor);

    return results;
}

} // namespace water_heating_using_exhaust
