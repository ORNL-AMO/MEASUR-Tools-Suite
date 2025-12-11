#include "physics/gas_composition.h"

#include <cmath>
#include <iostream>
#include <string>

#include "physics/gas_constants.h"
namespace gas_composition {

void GasComposition::set_total_composition_weight() {
    total_composition_weight = 0.0;
    for (auto* g : get_constituents()) {
        total_composition_weight += g->composition_weight;
    }
    for (auto* g : get_constituents()) {
        g->setCompositionWeightFraction(total_composition_weight);
    }
};

void GasComposition::set_heating_value() {
    heating_value = 0.0;
    for (auto* g : get_constituents()) {
        heating_value += g->heating_value * g->composition_weight_fraction;
    }
};

void GasComposition::set_heating_value_volume() {
    heating_value_volume = 0.0;
    for (auto* g : get_constituents()) {
        heating_value_volume += g->heating_value_volume * g->composition_by_volume;
    }
};

void GasComposition::set_specific_gravity() {
    double molecular_weight_mixture = 0.0;
    for (auto* g : get_constituents()) {
        molecular_weight_mixture += g->molecular_weight * g->composition_by_volume;
    }
    specific_gravity = molecular_weight_mixture / (22.4 * 1.205);
};

void GasComposition::set_stoichometric_air() {
    double o2_required = 0.0;
    for (auto* g : get_constituents()) {
        o2_required += g->o2_generated * g->composition_by_volume;
    }
    double kDryAirO2VolumeFraction = 0.209; // Volume fraction of O2 in dry air
    stoichometric_air              = o2_required * (1 + (1 - kDryAirO2VolumeFraction) / kDryAirO2VolumeFraction);
}

double GasComposition::excess_air_from_o2(double flue_gas_o2_percentage) {
    double excess_air = estimate_excess_air_from_o2(flue_gas_o2_percentage);
    if (excess_air == 0)
        return 0;

    for (auto i = 0; i < 100; i++) {
        auto       components = get_mass_flue_gas_components(excess_air);
        auto const calculated_flue_gas_o2_fraction =
            components.mO2 / (components.mH2O + components.mCO2 + components.mN2 + components.mO2 + components.mSO2);
        auto const error =
            std::fabs((flue_gas_o2_percentage - calculated_flue_gas_o2_fraction) / flue_gas_o2_percentage);
        if (error < 0.02)
            break;
        if (calculated_flue_gas_o2_fraction > flue_gas_o2_percentage) {
            excess_air -= (excess_air * 0.01);
        }
        else {
            excess_air += (excess_air * 0.01);
        }
    }
    return excess_air;
}

double GasComposition::o2_percentage_from_excess_air(double excess_air) {
    auto components = get_mass_flue_gas_components(excess_air);
    return components.mO2 / (components.mH2O + components.mCO2 + components.mN2 + components.mO2 + components.mSO2);
}

// TODO: address magic numbers?
double GasComposition::estimate_excess_air_from_o2(double flue_gas_o2_percentage) {
    return (8.52381 * flue_gas_o2_percentage) / (2 - (9.52381 * flue_gas_o2_percentage));
}

double GasComposition::calculate_enthalpy_at_saturation(double partial_pressure_water_vapor) {
    return 1096.7 * pow(partial_pressure_water_vapor * 29.926, 0.013);
}

double GasComposition::calculate_saturation_temperature(double partial_pressure_water_vapor) {
    return 36.009 * log(partial_pressure_water_vapor * 29.926) + 81.054;
}

double GasComposition::adjusted_flue_gas_o2_for_calc_error(double excess_air, double calculated_flue_gas_o2_percent) {
    double adjusted_flue_gas_o2_for_calc_error = calculated_flue_gas_o2_percent;
    if (adjusted_flue_gas_o2_for_calc_error > 0) {
        for (auto i = 0; i < 100; i++) {
            adjusted_flue_gas_o2_for_calc_error = std::round(adjusted_flue_gas_o2_for_calc_error * 1000) / 1000.0;
            double excess_air_new               = excess_air_from_o2(adjusted_flue_gas_o2_for_calc_error);
            if (fabs(1 - excess_air_new / excess_air) < 0.02)
                break;
            if (excess_air_new > excess_air) {
                adjusted_flue_gas_o2_for_calc_error *= 0.99;
            }
            else {
                adjusted_flue_gas_o2_for_calc_error *= 1.01;
            }
        }
    }
    return adjusted_flue_gas_o2_for_calc_error;
}

GasFlueGasComponents GasComposition::get_mass_flue_gas_components(double excess_air) {
    GasFlueGasComponents components;
    components.mH2O = 0;
    components.mCO2 = 0;
    components.mO2  = 0;
    components.mN2  = 0;
    components.mSO2 = 0;

    for (auto* c : get_constituents()) {
        components.mH2O += (c->h2o_generated * c->composition_weight_fraction) / c->molecular_weight;
        components.mCO2 += (c->co2_generated * c->composition_weight_fraction) / c->molecular_weight;
        components.mO2 += (c->o2_generated * c->composition_weight_fraction) / c->molecular_weight;
    }
    components.mO2 *= excess_air;

    auto const& N2 = n2;
    for (auto* c : get_constituents()) {
        components.mN2 += ((c->o2_generated * c->composition_weight_fraction) / c->molecular_weight);
    }

    components.mN2 =
        ((1 - 0.231) / 0.231) * components.mN2 + components.mO2 * (1 - 0.231) / 0.231 + n2.composition_weight_fraction;

    // from previous code, so2 generated is always zero... this calculation would always be zero than.
    //  for (auto* c : constituents) {
    //      components.mSO2 += c->so2_generated * c->composition_weight_fraction / c->molecular_weight;
    //  }

    return components;
}

ProcessHeatProperties GasComposition::process_heat_properties(const double flue_gas_temp_f, const double flue_gas_o2,
                                                              const double comb_air_temperature_f,
                                                              const double fuel_temp_f, const double ambient_air_temp_f,
                                                              const double comb_air_moisture_perc,
                                                              const double excess_air) {
    /**
     * @brief Calculates process heat properties for a given gas composition and operating conditions.
     * @details This function computes available heat, specific heat, and other process heat properties
     *          using constituent gas properties and thermodynamic relationships. All variables use snake_case.
     */
    ProcessHeatProperties results;
    // Determine excess air and flue gas O2
    if (excess_air != 0) {
        results.excess_air  = excess_air;
        results.flue_gas_o2 = o2_percentage_from_excess_air(excess_air);
        results.flue_gas_o2 = adjusted_flue_gas_o2_for_calc_error(excess_air, results.flue_gas_o2);
    }
    else {
        results.excess_air  = excess_air_from_o2(flue_gas_o2);
        results.flue_gas_o2 = flue_gas_o2;
    }

    // Convert input temperatures to absolute (Rankine)
    const double initial_temp = 460.0 + comb_air_temperature_f;
    const double final_temp   = 460.0 + flue_gas_temp_f;

    // Calculate temperature difference between flue gas and ambient air
    const double delta_temp_flue_ambient = flue_gas_temp_f - ambient_air_temp_f;

    // Calculate average specific heat (Cp) for major flue gas constituents across temperature range
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

    // Standard dry air volume fractions
    constexpr double k_std_o2_vol  = 20.7;
    constexpr double k_std_n2_vol  = 78.3;
    constexpr double k_std_h2o_vol = 1.0;

    // Mean Cp for combustion air at initial and final temperatures
    const double initial_mean_cp =
        (k_std_o2_vol * initial_cp_scf_o2 + k_std_n2_vol * initial_cp_scf_n2 + k_std_h2o_vol * initial_cp_scf_h2o) /
        100.0;
    const double final_mean_cp =
        (k_std_o2_vol * final_cp_scf_o2 + k_std_n2_vol * final_cp_scf_n2 + k_std_h2o_vol * final_cp_scf_h2o) / 100.0;

    // Linear Cp coefficients for combustion air
    const double cp_b = (final_mean_cp - initial_mean_cp) / delta_temp_flue_ambient;
    const double cp_a = final_mean_cp - cp_b / flue_gas_temp_f;

    // Aggregate fuel and product properties
    results.heat_value_fuel = 0.0;
    double co2_generated_wt = 0.0;
    double h2o_generated_wt = 0.0;
    double o2_generated_wt  = 0.0;

    for (auto* compound : get_constituents()) {
        results.heat_value_fuel += compound->composition_by_volume * compound->heating_value_volume;
        co2_generated_wt += compound->composition_by_volume * compound->co2_generated;
        h2o_generated_wt += compound->composition_by_volume * compound->h2o_generated;
        o2_generated_wt += compound->composition_by_volume * compound->o2_generated;
    }

    // Convert generated weights to volumes (ft^3/lb)
    const double co2_generated_vol = co2_generated_wt * 0.022722;
    const double h2o_generated_vol = h2o_generated_wt * 0.055506;

    // Convert weights to lb/MMBtu
    co2_generated_wt *= 0.0026365;
    o2_generated_wt /= 32.0;

    // Calculate stoichiometric air required
    constexpr double k_dry_air_o2_vol_frac = 0.209;
    results.stoich_air = o2_generated_wt * (1.0 + (1.0 - k_dry_air_o2_vol_frac) / k_dry_air_o2_vol_frac);

    // Combustion air moisture correction
    double comb_air_moisture = 0.0;
    if (comb_air_moisture_perc > 0.009) {
        comb_air_moisture = (comb_air_moisture_perc - 0.009) * (results.stoich_air * (1.0 + results.excess_air)) * 0.0763;
    }

    h2o_generated_wt *= 0.0026365;
    h2o_generated_wt += comb_air_moisture;

    // Calculate generated volumes for O2 and N2
    const double o2_generated_vol = results.excess_air * o2_generated_wt;
    const double n2_generated_vol =
        (1.0 + results.excess_air) * o2_generated_wt * (1.0 - k_dry_air_o2_vol_frac) / k_dry_air_o2_vol_frac;

    // Convert generated volumes to weights
    const double n2_generated_wt = n2_generated_vol * 0.0744;
    o2_generated_wt              = o2_generated_vol * 0.0846;

    // Calculate partial pressure of water vapor in flue gas
    const double partial_pressure_h2o =
        h2o_generated_vol / (co2_generated_vol + h2o_generated_vol + o2_generated_vol + n2_generated_vol);

    // Calculate enthalpy and heat content for each constituent
    const double enthalpy_at_saturation = calculate_enthalpy_at_saturation(partial_pressure_h2o);
    const double saturation_temp        = calculate_saturation_temperature(partial_pressure_h2o);

    const double h2o_heat_content =
        (enthalpy_at_saturation + avg_cp_h2o * (flue_gas_temp_f - saturation_temp)) * 100.0 * h2o_generated_wt;
    const double co2_heat_content = avg_cp_co2 * delta_temp_flue_ambient * 100.0 * co2_generated_wt;
    const double n2_heat_content  = avg_cp_n2 * delta_temp_flue_ambient * 100.0 * n2_generated_wt;
    const double o2_heat_content  = avg_cp_o2 * delta_temp_flue_ambient * 100.0 * o2_generated_wt;

    // Heat in preheated combustion air
    const double preheated_air_effect = results.stoich_air * (1.0 + results.excess_air) *
                                        (((comb_air_temperature_f + ambient_air_temp_f) / 2.0) * cp_b + cp_a) *
                                        (comb_air_temperature_f - ambient_air_temp_f);

    // Heat content of air moisture
    const double preheated_air_moisture_effect =
        comb_air_moisture * avg_cp_h2o * (flue_gas_temp_f - comb_air_temperature_f);

    // Total generated products (lb/MMBtu)
    results.total_generated = co2_generated_wt + h2o_generated_wt + o2_generated_wt + n2_generated_wt;

    // Weighted average specific heat of flue gas
    results.specific_heat = (co2_generated_wt * avg_cp_co2 + h2o_generated_wt * avg_cp_h2o +
                             o2_generated_wt * avg_cp_o2 + n2_generated_wt * avg_cp_n2) /
                            results.total_generated;

    // Sensible heat of fuel
    const double delta_temp_fuel_ambient = fuel_temp_f - ambient_air_temp_f;
    const double sensible_heat           = results.specific_heat * delta_temp_fuel_ambient;

    // Calculate available heat fraction
    results.available_heat =
        (100.0 * (sensible_heat + results.heat_value_fuel + preheated_air_effect + preheated_air_moisture_effect) -
         (h2o_heat_content + co2_heat_content + n2_heat_content + o2_heat_content)) /
        (100.0 * results.heat_value_fuel);

    return results;
};

}; // namespace gas_composition