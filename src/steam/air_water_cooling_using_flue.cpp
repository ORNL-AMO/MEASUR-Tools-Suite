#include "steam/air_water_cooling_using_flue.h"
#include <cmath>
#include "processHeat/losses/gas_flue_gas_material.h"

namespace air_water_cooling_using_flue {

/**
 * @brief Calculates heat recovery using flue gas and condensing heat exchanger.
 * @details Uses gas composition and process parameters to estimate heat recovery, available heat, and latent heat effects.
 *
 * Steps:
 * 1. Calculate flue gas properties
 * 2. Estimate fraction condensed and latent heat effect
 * 3. Calculate flue gas flow and sensible heat recovery
 * 4. Return results struct
 */
AirWaterCoolingUsingFlueResults airWaterCoolingUsingFlue(
    const gas_composition::GasComposition& gas_compositions,
    double heat_input,
    double temp_flue_gas_in,
    double temp_flue_gas_out,
    double temp_comb_air,
    double fuel_temp,
    double perc_o2,
    double ambient_air_temp,
    double moist_comb_air
) {
    AirWaterCoolingUsingFlueResults results;

    // --- Step 1: Calculate flue gas properties ---
    gas_flue_gas_material::ProcessHeatProperties res = gas_flue_gas_material::processHeatProperties(
        gas_compositions, temp_flue_gas_in, perc_o2, temp_comb_air, fuel_temp, ambient_air_temp, moist_comb_air);
    results.excess_air = res.excess_air;
    results.specific_heat = res.specific_heat;

    // --- Step 2: Estimate fraction condensed and latent heat effect ---
    // Empirical fit for fraction condensed
    results.fraction_condensed = 1.0 - (0.0000009 * std::pow(temp_flue_gas_out, 3.0136)) / (2.8082 - 0.1168 * perc_o2 * 100.0);
    // Latent heat effect
    results.latent_heat_fraction = (results.fraction_condensed * 0.00935 * 1087.0) / 100.0;

    // --- Step 3: Calculate flue gas flow and sensible heat recovery ---
    results.flow_flue_gas = heat_input * (0.0763 * (0.6 + (res.stoich_air * (1.0 + res.excess_air)))) * 1'000'000.0 / res.heat_value_fuel;
    results.sensible_heat_recovery = res.specific_heat * (temp_flue_gas_in - temp_flue_gas_out) * results.flow_flue_gas / 1'000'000.0;

    // --- Step 4: Calculate available heat and total heat recovery ---
    results.available_heat_fraction = res.available_heat;
    results.total_available_heat_fraction = res.available_heat + results.latent_heat_fraction;
    results.latent_heat_recovery = heat_input * results.latent_heat_fraction;

    return results;
}

} // namespace air_water_cooling_using_flue
