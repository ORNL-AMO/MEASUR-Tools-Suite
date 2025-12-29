
#include "processHeat/cascade_heat_high_to_low.h"
#include "physics/constants.h"
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
    using namespace physics::conversions;
    // --- Step 1: Calculate flue gas properties for the primary (high-temp) process ---
    gas_flue_gas_material::ProcessHeatProperties pri_flue_props = gas_flue_gas_material::processHeatProperties(
        gas_compositions, pri_exhaust_temp, pri_exhaust_o2, pri_comb_air_temp,
        fuel_temp_f, ambient_air_temp_f, comb_air_moisture_perc);

    const double stoichiometric_air_volume = pri_flue_props.stoich_air; // SCF/MMBtu
    const double primary_excess_air = pri_flue_props.excess_air;        // fraction
    const double primary_available_heat = pri_flue_props.available_heat;// fraction
    const double primary_flue_specific_heat = pri_flue_props.specific_heat; // Btu/lb-°F
    // Convert mass-based total_generated (lb/hr per MMBtu fuel) to flue gas density (lb/SCF)
    const double primary_flue_density = pri_flue_props.total_generated / kLbPerFt3ToKgPerM3; // lb/SCF

    // --- Step 2: Calculate flue gas properties for the secondary (low-temp) process ---
    gas_flue_gas_material::ProcessHeatProperties sec_flue_props = gas_flue_gas_material::processHeatProperties(
        gas_compositions, sec_exhaust_temp, sec_exhaust_o2, sec_comb_air_temp,
        fuel_temp_f, ambient_air_temp_f, comb_air_moisture_perc);

    const double secondary_excess_air = sec_flue_props.excess_air;      // fraction
    const double secondary_available_heat = sec_flue_props.available_heat; // fraction

    // --- Step 3: Calculate primary flue gas volume (SCF/hr) ---
    // Formula: (firing rate * stoich air * (1 + excess air) * 1,000,000 / fuel HV) + (firing rate * 1,000,000 / fuel HV)
    const double primary_flue_volume =
        pri_firing_rate * stoichiometric_air_volume * (1.0 + primary_excess_air) * kMMBtuToBtu / fuel_hv
        + pri_firing_rate * kMMBtuToBtu / fuel_hv;

    // --- Step 4: Calculate heat exchanger energy rate (MMBtu/hr) ---
    // Formula: flue volume * specific heat * density * delta T / 1,000,000
    const double temperature_difference = pri_exhaust_temp - sec_exhaust_temp; // °F
    const double heat_exchanger_energy_rate =
        primary_flue_volume * primary_flue_specific_heat * primary_flue_density * temperature_difference / kMMBtuToBtu;

    // --- Step 5: Calculate equivalent energy supply to secondary process (MMBtu/hr) ---
    // Formula: hx_energy_rate / secondary_available_heat
    const double equivalent_energy_supply = heat_exchanger_energy_rate / secondary_available_heat;

    // --- Step 6: Determine effective operating hours (hr/yr) ---
    // Use the minimum of primary and secondary operating hours
    const double effective_operating_hours = std::min(pri_op_hours, sec_op_hours);

    // --- Step 7: Calculate hourly energy savings (MMBtu/hr) ---
    // Use the minimum of equivalent energy supply and secondary firing rate
    const double hourly_energy_savings = std::min(equivalent_energy_supply, sec_firing_rate);

    // --- Step 8: Calculate total energy savings (MMBtu/yr) ---
    const double total_energy_savings = hourly_energy_savings * effective_operating_hours;

    // --- Step 9: Calculate total cost savings (USD/yr) ---
    const double total_cost_savings = total_energy_savings * fuel_cost;

    // --- Step 10: Populate results struct ---
    CascadeHeatHighToLowResults results;
    results.pri_flue_volume     = primary_flue_volume;
    results.hx_energy_rate      = heat_exchanger_energy_rate;
    results.eq_energy_supply    = equivalent_energy_supply;
    results.eff_op_hours        = effective_operating_hours;
    results.energy_savings      = total_energy_savings;
    results.cost_savings        = total_cost_savings;
    results.hourly_savings      = hourly_energy_savings;
    results.pri_excess_air      = primary_excess_air;
    results.pri_available_heat  = primary_available_heat;
    results.sec_excess_air      = secondary_excess_air;
    results.sec_available_heat  = secondary_available_heat;
    return results;
}

} // namespace cascade_heat_high_to_low