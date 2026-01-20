#include "steam/water_heating_using_flue.h"

#include <cmath>

#include "physics/constants.h"
#include "physics/gas_constants.h"
#include "physics/gas_composition.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "steamModeler/SaturatedProperties.h"
#include "steamModeler/SteamProperties.h"

namespace water_heating_using_flue {

WaterHeatingUsingFlueResults
waterHeatingUsingFlue(const gas_composition::GasComposition& gas_compositions, double temp_flue_gas_f,
                               double perc_o2, double temp_comb_air_f, double moist_comb_air, double rating_boiler,
                               double pr_steam, double temp_ambient_air_f, double temp_steam_f, double temp_fw,
                               double perc_blow_down, double eff_hx, double op_hours, double cost_fuel, double hhv_fuel,
                               SteamCondition cond_steam, double fuel_temp_f) {
    WaterHeatingUsingFlueResults results;

    // --- Temperature conversions (Fahrenheit to Kelvin) ---
    const double steam_temp_k      = physics::conversions::fahrenheitToKelvin(temp_steam_f);
    const double feedwater_temp_k  = physics::conversions::fahrenheitToKelvin(temp_fw);
    const double flue_gas_temp_k   = physics::conversions::fahrenheitToKelvin(temp_flue_gas_f);

    // --- Flue gas properties ---
    auto flue_props = gas_flue_gas_material::processHeatProperties(
        gas_compositions, temp_flue_gas_f, perc_o2, temp_comb_air_f, fuel_temp_f, temp_ambient_air_f, moist_comb_air);
    results.boiler_available_heat  = flue_props.available_heat; // Fraction of heat available from boiler
    // Convert specific heat from Btu/(lb·°F) to kJ/(kg·K)
    results.flue_gas_specific_heat = physics::conversions::kBtuPerLbFToKJPerKgK * flue_props.specific_heat;
    // Calculate flue gas mass flow (kg/hr) using conversion from lb/ft³ to kg/m³
    results.flue_gas_mass_flow     = physics::conversions::kLbPerFt3ToKgPerM3 * flue_props.total_generated * rating_boiler * 1'000'000 / hhv_fuel;

    // --- Steam and feedwater enthalpy ---
    if (cond_steam == SteamCondition::Saturated) {
        // Use quality = 1 for saturated steam
        results.steam_specific_enthalpy = SteamProperties(pr_steam, SteamProperties::ThermodynamicQuantity::QUALITY, 1)
                                            .calculate()
                                            .specificEnthalpy;
    } else {
        // Use temperature for superheated steam
        results.steam_specific_enthalpy = SteamProperties(pr_steam, SteamProperties::ThermodynamicQuantity::TEMPERATURE, steam_temp_k)
                                            .calculate()
                                            .specificEnthalpy;
    }
    // Feedwater enthalpy (kJ/kg)
    results.feedwater_specific_enthalpy = SaturatedProperties(pr_steam, feedwater_temp_k).calculate().liquidSpecificEnthalpy;

    // --- Feedwater specific heat (empirical polynomial fit) ---
    // Feedwater specific heat (kJ/kg-K) using shared empirical fit
    results.feedwater_specific_heat = gas_constants::specificHeatFeedwater(feedwater_temp_k);

    // --- Mass flow calculations ---
    // Steam mass flow (kg/hr)
    results.steam_mass_flow = (rating_boiler * 1'000'000 * results.boiler_available_heat * (1 - perc_blow_down)) /
                             (results.steam_specific_enthalpy - results.feedwater_specific_enthalpy);
    // Feedwater mass flow (kg/hr)
    results.feedwater_mass_flow = results.steam_mass_flow * (1 + perc_blow_down);

    // --- Heat capacity calculations ---
    results.flue_gas_heat_capacity    = results.flue_gas_specific_heat * results.flue_gas_mass_flow;      // kJ/hr-K
    results.feedwater_heat_capacity   = results.feedwater_specific_heat * results.feedwater_mass_flow;    // kJ/hr-K

    // Minimum heat capacity (kJ/hr-K)
    if (results.flue_gas_heat_capacity < results.feedwater_heat_capacity) {
        results.min_heat_capacity = results.flue_gas_heat_capacity;
    } else {
        results.min_heat_capacity = results.feedwater_heat_capacity;
    }

    // --- Heat recovery calculations ---
    // Recovered heat (kJ/hr)
    results.recovered_heat = eff_hx * results.min_heat_capacity * (flue_gas_temp_k - feedwater_temp_k);

    // Flue gas and feedwater exit temperatures (K)
    results.flue_gas_exit_temp   = flue_gas_temp_k - results.recovered_heat / results.flue_gas_heat_capacity;
    results.feedwater_exit_temp  = feedwater_temp_k + results.recovered_heat / results.feedwater_heat_capacity;

    // --- Annual energy and cost savings ---
    results.annual_energy_savings = results.recovered_heat / results.boiler_available_heat * op_hours / 1'000'000; // GJ/yr
    results.annual_cost_savings   = results.annual_energy_savings * cost_fuel; // $/yr

    return results;
}

} // namespace water_heating_using_flue
