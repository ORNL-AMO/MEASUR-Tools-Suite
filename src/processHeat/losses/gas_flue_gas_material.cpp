#include "processHeat/losses/gas_flue_gas_material.h"

#include "physics/gas_composition.h"
using namespace gas_composition;

namespace gas_flue_gas_material {


/**
 * @brief Calculates process heat properties for a given gas composition and operating conditions.
 * @details This function computes available heat, specific heat, and other process heat properties
 *          using constituent gas properties and thermodynamic relationships.
 *
 * Algorithm steps:
 * 1. Determine excess air and flue gas O2.
 * 2. Convert input temperatures to absolute (Rankine).
 * 3. Calculate temperature difference between flue gas and ambient air.
 * 4. Calculate average specific heat (Cp) for major flue gas constituents (O2, N2, H2O, CO2).
 * 5. Compute mean Cp for combustion air at initial and final temperatures.
 * 6. Calculate linear Cp coefficients for combustion air.
 * 7. Aggregate fuel and product properties from gas composition.
 * 8. Convert generated weights to volumes and adjust units.
 * 9. Calculate stoichiometric air required.
 * 10. Apply combustion air moisture correction.
 * 11. Calculate generated volumes for O2 and N2.
 * 12. Convert generated volumes to weights.
 * 13. Calculate partial pressure of water vapor in flue gas.
 * 14. Calculate enthalpy and heat content for each constituent.
 * 15. Compute heat in preheated combustion air and air moisture.
 * 16. Calculate total generated products and weighted average specific heat.
 * 17. Compute sensible heat of fuel.
 * 18. Calculate available heat fraction.
 *
 * Each step is documented inline for clarity and traceability.
 *
 * @param[in] compositions           GasComposition object describing fuel/air mixture.
 * @param[in] flue_gas_temp_f        Flue gas temperature [°F].
 * @param[in] flue_gas_o2            Flue gas O2 [% by vol].
 * @param[in] comb_air_temperature_f Combustion air temperature [°F].
 * @param[in] fuel_temp_f            Fuel temperature [°F].
 * @param[in] ambient_air_temp_f     Ambient air temperature [°F].
 * @param[in] comb_air_moisture_perc Combustion air moisture [% by vol].
 * @param[in] excess_air             Excess air percentage [%].
 * @return ProcessHeatProperties struct with all calculated properties.
 */
ProcessHeatProperties processHeatProperties(GasComposition compositions, const double flue_gas_temp_f,
                                              const double flue_gas_o2, const double comb_air_temperature_f,
                                              const double fuel_temp_f, const double ambient_air_temp_f,
                                              const double comb_air_moisture_perc, const double excess_air) {
    ProcessHeatProperties results;

    // Step 1: Determine excess air and flue gas O2
    if (excess_air != 0) {
        results.excess_air  = excess_air;
        results.flue_gas_o2 = compositions.o2PercentageFromExcessAir(excess_air);
        results.flue_gas_o2 = compositions.adjustedFlueGasO2ForCalcError(excess_air, results.flue_gas_o2);
    }
    else {
        results.excess_air  = compositions.excessAirFromO2(flue_gas_o2);
        results.flue_gas_o2 = flue_gas_o2;
    }

    // Step 2: Convert input temperatures to absolute (Rankine)
    const double initial_temp = 460.0 + comb_air_temperature_f;
    const double final_temp   = 460.0 + flue_gas_temp_f;

    // Step 3: Calculate temperature difference between flue gas and ambient air
    const double delta_temp_flue_ambient = flue_gas_temp_f - ambient_air_temp_f;

    // Step 4: Calculate average specific heat (Cp) for major flue gas constituents
    // Oxygen
    const double initial_cp_o2     = 11.515 - 172.0 / std::sqrt(initial_temp) + 1530.0 / initial_temp;
    const double final_cp_o2       = 11.515 - 172.0 / std::sqrt(final_temp) + 1530.0 / final_temp;
    const double initial_cp_scf_o2 = initial_cp_o2 / 378.2;
    const double final_cp_scf_o2   = final_cp_o2 / 378.2;
    const double avg_cp_o2         = (initial_cp_o2 + final_cp_o2) / 2.0 / 32.0;

    // Nitrogen
    const double initial_cp_n2     = 9.47 - 3470.0 / initial_temp + 1.07e6 / (initial_temp * initial_temp);
    const double final_cp_n2       = 9.47 - 3470.0 / final_temp + 1.07e6 / (final_temp * final_temp);
    const double initial_cp_scf_n2 = initial_cp_n2 / 378.2;
    const double final_cp_scf_n2   = final_cp_n2 / 378.2;
    const double avg_cp_n2         = (initial_cp_n2 + final_cp_n2) / 2.0 / 28.0;

    // Water vapor
    const double initial_cp_h2o     = 19.86 - 597.0 / std::sqrt(initial_temp) + 7500.0 / initial_temp;
    const double final_cp_h2o       = 19.86 - 597.0 / std::sqrt(final_temp) + 7500.0 / final_temp;
    const double initial_cp_scf_h2o = initial_cp_h2o / 378.2;
    const double final_cp_scf_h2o   = final_cp_h2o / 378.2;
    const double avg_cp_h2o         = (initial_cp_h2o + final_cp_h2o) / 2.0 / 18.0;

    // Carbon dioxide
    const double initial_cp_co2 = (16.2 - 6530.0 / initial_temp + 1.41e6 / (initial_temp * initial_temp)) / 44.0;
    const double final_cp_co2   = (16.2 - 6530.0 / final_temp + 1.41e6 / (final_temp * final_temp)) / 44.0;
    const double avg_cp_co2     = (initial_cp_co2 + final_cp_co2) / 2.0;

    // Step 5: Standard dry air volume fractions
    constexpr double k_std_o2_vol  = 20.7;
    constexpr double k_std_n2_vol  = 78.3;
    constexpr double k_std_h2o_vol = 1.0;

    // Step 6: Mean Cp for combustion air at initial and final temperatures
    const double initial_mean_cp =
        (k_std_o2_vol * initial_cp_scf_o2 + k_std_n2_vol * initial_cp_scf_n2 + k_std_h2o_vol * initial_cp_scf_h2o) /
        100.0;
    const double final_mean_cp =
        (k_std_o2_vol * final_cp_scf_o2 + k_std_n2_vol * final_cp_scf_n2 + k_std_h2o_vol * final_cp_scf_h2o) / 100.0;

    // Step 7: Linear Cp coefficients for combustion air
    const double cp_b = (final_mean_cp - initial_mean_cp) / delta_temp_flue_ambient;
    const double cp_a = final_mean_cp - cp_b / flue_gas_temp_f;

    // Step 8: Aggregate fuel and product properties
    results.heat_value_fuel = 0.0;
    double co2_generated_wt = 0.0;
    double h2o_generated_wt = 0.0;
    double o2_generated_wt  = 0.0;

    for (auto* compound : compositions.getConstituents()) {
        results.heat_value_fuel += compound->composition_by_volume * compound->heating_value_volume;
        co2_generated_wt += compound->composition_by_volume * compound->co2_generated;
        h2o_generated_wt += compound->composition_by_volume * compound->h2o_generated;
        o2_generated_wt += compound->composition_by_volume * compound->o2_generated;
    }

    // Step 9: Convert generated weights to volumes (ft^3/lb)
    const double co2_generated_vol = co2_generated_wt * 0.022722;
    const double h2o_generated_vol = h2o_generated_wt * 0.055506;

    // Step 10: Convert weights to lb/MMBtu
    co2_generated_wt *= 0.0026365;
    o2_generated_wt /= 32.0;

    // Step 11: Calculate stoichiometric air required
    constexpr double k_dry_air_o2_vol_frac = 0.209;
    results.stoich_air = o2_generated_wt * (1.0 + (1.0 - k_dry_air_o2_vol_frac) / k_dry_air_o2_vol_frac);

    // Step 12: Combustion air moisture correction
    double comb_air_moisture = 0.0;
    if (comb_air_moisture_perc > 0.009) {
        comb_air_moisture =
            (comb_air_moisture_perc - 0.009) * (results.stoich_air * (1.0 + results.excess_air)) * 0.0763;
    }

    h2o_generated_wt *= 0.0026365;
    h2o_generated_wt += comb_air_moisture;

    // Step 13: Calculate generated volumes for O2 and N2
    const double o2_generated_vol = results.excess_air * o2_generated_wt;
    const double n2_generated_vol =
        (1.0 + results.excess_air) * o2_generated_wt * (1.0 - k_dry_air_o2_vol_frac) / k_dry_air_o2_vol_frac;

    // Step 14: Convert generated volumes to weights
    const double n2_generated_wt = n2_generated_vol * 0.0744;
    o2_generated_wt              = o2_generated_vol * 0.0846;

    // Step 15: Calculate partial pressure of water vapor in flue gas
    const double partial_pressure_h2o =
        h2o_generated_vol / (co2_generated_vol + h2o_generated_vol + o2_generated_vol + n2_generated_vol);

    // Step 16: Calculate enthalpy and heat content for each constituent
    const double enthalpy_at_saturation = compositions.calculateEnthalpyAtSaturation(partial_pressure_h2o);
    const double saturation_temp        = compositions.calculateSaturationTemperature(partial_pressure_h2o);

    const double h2o_heat_content =
        (enthalpy_at_saturation + avg_cp_h2o * (flue_gas_temp_f - saturation_temp)) * 100.0 * h2o_generated_wt;
    const double co2_heat_content = avg_cp_co2 * delta_temp_flue_ambient * 100.0 * co2_generated_wt;
    const double n2_heat_content  = avg_cp_n2 * delta_temp_flue_ambient * 100.0 * n2_generated_wt;
    const double o2_heat_content  = avg_cp_o2 * delta_temp_flue_ambient * 100.0 * o2_generated_wt;

    // Step 17: Heat in preheated combustion air
    const double preheated_air_effect = results.stoich_air * (1.0 + results.excess_air) *
                                        (((comb_air_temperature_f + ambient_air_temp_f) / 2.0) * cp_b + cp_a) *
                                        (comb_air_temperature_f - ambient_air_temp_f);

    // Step 18: Heat content of air moisture
    const double preheated_air_moisture_effect =
        comb_air_moisture * avg_cp_h2o * (flue_gas_temp_f - comb_air_temperature_f);

    // Step 19: Total generated products (lb/MMBtu)
    results.total_generated = co2_generated_wt + h2o_generated_wt + o2_generated_wt + n2_generated_wt;

    // Step 20: Weighted average specific heat of flue gas
    results.specific_heat = (co2_generated_wt * avg_cp_co2 + h2o_generated_wt * avg_cp_h2o +
                             o2_generated_wt * avg_cp_o2 + n2_generated_wt * avg_cp_n2) /
                            results.total_generated;

    // Step 21: Sensible heat of fuel
    const double delta_temp_fuel_ambient = fuel_temp_f - ambient_air_temp_f;
    const double sensible_heat           = results.specific_heat * delta_temp_fuel_ambient;

    // Step 22: Calculate available heat fraction
    results.available_heat =
        (100.0 * (sensible_heat + results.heat_value_fuel + preheated_air_effect + preheated_air_moisture_effect) -
         (h2o_heat_content + co2_heat_content + n2_heat_content + o2_heat_content)) /
        (100.0 * results.heat_value_fuel);

    return results;
}

double totalHeatLoss(double flue_gas_temperature, double excess_air_percentage, double combustion_air_temperature,
                     GasComposition& compositions, double fuel_temperature) {
    double                combustion_air_moisture = 60;
    double                excess_air              = 0;
    ProcessHeatProperties process_heat_properties_results =
        processHeatProperties(compositions, flue_gas_temperature, excess_air_percentage / 100,
                                combustion_air_temperature, fuel_temperature, combustion_air_moisture, excess_air);
    return process_heat_properties_results.available_heat;
}

} // namespace gas_flue_gas_material
