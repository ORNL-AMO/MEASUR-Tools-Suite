

#include "processHeat/losses/solid_liquid_flue_gas_material.h"

#include <cmath>
#include <iostream>

#include "physics/gas_constants.h"
namespace solid_liquid_flue_gas_material {

/**
 * @brief Calculates excess air percentage given flue gas O2 levels using iterative algorithm.
 *
 * The algorithm normalizes fuel composition, estimates initial excess air, and iteratively refines it
 * based on the difference between calculated and measured flue gas O2 until convergence.
 *
 * Constants are used for stoichiometric coefficients and convergence criteria.
 */
double calculateExcessAirFromFlueGasO2(double flue_gas_o2, double carbon, double hydrogen, double sulphur,
                                       double inert_ash, double o2, double moisture, double nitrogen,
                                       double moisture_in_air_combustion) {
    // --- Normalize fuel composition ---
    const double percent_total_fuel = carbon + hydrogen + sulphur + inert_ash + o2 + moisture + nitrogen;
    const double carbon_frac        = carbon / percent_total_fuel;
    const double hydrogen_frac      = hydrogen / percent_total_fuel;
    const double sulphur_frac       = sulphur / percent_total_fuel;
    const double o2_frac            = o2 / percent_total_fuel;
    const double moisture_frac      = moisture / percent_total_fuel;

    // --- Initial estimate for excess air ---
    double excess_air = (8.52381 * flue_gas_o2) / (2.0 - (9.52381 * flue_gas_o2));
    if (excess_air == 0.0) {
        return 0.0;
    }

    // --- Iterative refinement ---

    for (int i = 0; i < 100; ++i) {
        // Use the calculateFlueGasO2 function for O2 calculation in flue gas
        double o2_calc = calculateFlueGasO2(excess_air, carbon, hydrogen, sulphur, inert_ash, o2, moisture, nitrogen,
                                            moisture_in_air_combustion);
        const double error = std::fabs((flue_gas_o2 - o2_calc) / flue_gas_o2);
        if (error < 0.02) {
            break;
        }
        // Adjust excess air based on error direction
        if (o2_calc > flue_gas_o2) {
            excess_air -= (excess_air * 0.01);
        }
        else {
            excess_air += (excess_air * 0.01);
        }
    }

    return excess_air;
}

/**
 * @brief Calculates flue gas O2 fraction given excess air and fuel composition.
 *
 * The algorithm normalizes fuel composition, computes stoichiometric air, and calculates the O2 fraction
 * in the flue gas based on combustion chemistry.
 *
 * Constants are used for stoichiometric coefficients.
 */
double calculateFlueGasO2(double excess_air, double carbon, double hydrogen, double sulphur, double inert_ash,
                          double o2, double moisture, double nitrogen, double moisture_in_air_combustion) {
    // --- Constants for stoichiometry ---
    using namespace gas_constants;

    // --- Normalize fuel composition ---
    const double percent_total_fuel = carbon + hydrogen + sulphur + inert_ash + o2 + moisture + nitrogen;
    const double carbon_frac        = carbon / percent_total_fuel;
    const double hydrogen_frac      = hydrogen / percent_total_fuel;
    const double sulphur_frac       = sulphur / percent_total_fuel;
    const double o2_frac            = o2 / percent_total_fuel;
    const double moisture_frac      = moisture / percent_total_fuel;

    // --- Stoichiometric air and combustion calculations ---
    const double o2s_air          = carbon_frac * kCToO2 + hydrogen_frac * kHToO2 + sulphur_frac * kSToO2 - o2_frac;
    const double n2s_air          = o2s_air * kN2O2Ratio;
    const double ms_air           = o2s_air + n2s_air;
    const double m_combustion_air = ms_air * (1.0 + excess_air);

    // Step 4 & 5: Calculate flue gas components
    const double m_co2 = carbon_frac * kCToCO2;
    const double m_h2o =
        hydrogen_frac * kHToH2O + moisture_frac + (moisture_in_air_combustion / 100.0) * m_combustion_air;
    const double m_so2 = sulphur_frac * kSToSO2;
    const double m_o2  = o2s_air * excess_air;
    const double m_n2  = n2s_air * (1.0 + excess_air);

    // --- Calculate O2 fraction in flue gas ---
    return m_o2 / (m_h2o + m_co2 + m_n2 + m_o2 + m_so2);
}

double calculateHeatingValueFuel(double carbon, double hydrogen, double sulphur, double inert_ash, double o2,
                                 double moisture, double nitrogen) {

    constexpr double kHvC = 14100.0; // Btu/lb for carbon
    constexpr double kHvH = 61100.0; // Btu/lb for hydrogen
    constexpr double kHvS = 3980.0;  // Btu/lb for sulphur

    const double percent_total_fuel = carbon  + hydrogen + sulphur + inert_ash + o2 + moisture + nitrogen;
    const double carbon_frac        = carbon / percent_total_fuel;
    const double hydrogen_frac      = hydrogen / percent_total_fuel;
    const double sulphur_frac       = sulphur / percent_total_fuel;

    double heating_value_fuel = carbon_frac * kHvC + hydrogen_frac * kHvH + sulphur_frac * kHvS;
    return heating_value_fuel;
}

double totalHeatLoss(const double flue_gas_temperature, const double excess_air,
                     const double combustion_air_temperature, const double fuel_temperature,
                     const double moisture_in_air_combustion, const double ash_discharge_temperature,
                     const double unburned_carbon_in_ash, const double carbon, const double hydrogen,
                     const double sulphur, const double inert_ash, const double o2, const double moisture,
                     const double nitrogen, const double ambient_air_temp_f) {
    using namespace gas_constants;

    // --- Constants ---
    constexpr double kHfuel = 0.24;
    constexpr double kHvC   = 14100.0;
    constexpr double kHvH   = 61100.0;
    constexpr double kHvS   = 3980.0;

    // --- Normalize fuel composition ---
    // values in as percents
    const double percent_total_fuel   = (carbon + hydrogen + sulphur + inert_ash + o2 + moisture + nitrogen) / 100;
    const double carbon_frac          = (carbon / 100) / percent_total_fuel;
    const double hydrogen_frac        = (hydrogen / 100) / percent_total_fuel;
    const double sulphur_frac         = (sulphur / 100) / percent_total_fuel;
    const double o2_frac              = (o2 / 100) / percent_total_fuel;
    const double moisture_frac        = (moisture / 100) / percent_total_fuel;
    const double excess_air_frac      = excess_air / 100.0;
    const double unburned_carbon_frac = unburned_carbon_in_ash / 100.0;
    const double inert_ash_frac       = inert_ash / 100.0;

    // --- Step 2 & 3: Fuel and combustion air enthalpy ---
    const double h_fuel            = kHfuel * (1.0 - moisture_frac) * (fuel_temperature - ambient_air_temp_f);
    const double cp_combustion_air = 0.01788166862315 + 0.0000016704748 * combustion_air_temperature;
    const double o2s_air           = carbon_frac * (32.0 / 12.0) + hydrogen_frac * 8.0 + sulphur_frac - o2_frac;
    const double n2s_air           = o2s_air * (76.85 / 23.15);
    const double ms_air            = o2s_air + n2s_air;
    const double m_combustion_air  = ms_air * (1.0 + excess_air_frac);
    const double h_combustion_air =
        m_combustion_air * cp_combustion_air * (combustion_air_temperature - ambient_air_temp_f) / 0.075;

    // --- Step 4 & 5: Flue gas components and heating value ---
    const double heating_value_fuel = carbon_frac * kHvC + hydrogen_frac * kHvH + sulphur_frac * kHvS;
    const double m_co2              = carbon_frac * kCToCO2;
    const double m_h2o =
        hydrogen_frac * kHToH2O + moisture_frac + (moisture_in_air_combustion / 100.0) * m_combustion_air;
    const double m_so2 = sulphur_frac * kSToSO2;
    const double m_o2  = o2s_air * excess_air_frac;
    const double m_n2  = n2s_air * (1.0 + excess_air_frac);

    // --- Step 5: Partial pressure of H2O and enthalpy of saturated steam ---
    const double p_h2o = (m_h2o / 0.047636) /
                         (m_co2 / 0.116367 + m_h2o / 0.047636 + m_n2 / 0.074077 + m_o2 / 0.084611 + m_so2 / 0.169381);
    const double h_sat = 1096.7 * std::pow(p_h2o * 29.926, 0.013);

    // --- Step 6: Sensible heat of flue gas components (expanded for clarity) ---
    const double absolute_flue_gas_temp = flue_gas_temperature + 460.0; // Rankine

    // CO2 sensible heat
    const double cp_co2         = specificHeatCO2(absolute_flue_gas_temp); // Btu/lb-mol-R
    const double delta_t_co2    = flue_gas_temperature - ambient_air_temp_f;
    const double moles_co2      = carbon_frac * kCToCO2;
    const double h_sensible_co2 = moles_co2 * (cp_co2 / kCO2Mw) * delta_t_co2;

    // H2O sensible heat (from fuel and moisture)
    const double cp_h2o              = specificHeatH2O(absolute_flue_gas_temp); // Btu/lb-mol-R
    const double delta_t_h2o         = flue_gas_temperature - ambient_air_temp_f;
    const double moles_h2o_fuel      = hydrogen_frac * kHToH2O + moisture_frac;
    const double moles_h2o_air       = (moisture_in_air_combustion / 100.0) * m_combustion_air;
    const double h_sensible_h2o_fuel = moles_h2o_fuel * (h_sat + (cp_h2o / kH2OMw) * delta_t_h2o);
    const double h_sensible_h2o_air  = moles_h2o_air * (cp_h2o / kH2OMw) * delta_t_h2o;
    const double h_sensible_h2o      = h_sensible_h2o_fuel + h_sensible_h2o_air;

    // SO2 sensible heat
    const double cp_so2         = kSO2Cp; // Btu/lb-mol-R
    const double delta_t_so2    = flue_gas_temperature - ambient_air_temp_f;
    const double moles_so2      = sulphur_frac * kSToSO2;
    const double h_sensible_so2 = moles_so2 * (cp_so2 / kSO2Mw) * delta_t_so2;

    // O2 sensible heat
    const double cp_o2         = specificHeatO2(absolute_flue_gas_temp); // Btu/lb-mol-R
    const double delta_t_o2    = flue_gas_temperature - ambient_air_temp_f;
    const double h_sensible_o2 = m_o2 * (cp_o2 / kO2Mw) * delta_t_o2;

    // N2 sensible heat
    const double cp_n2         = specificHeatN2(absolute_flue_gas_temp); // Btu/lb-mol-R
    const double delta_t_n2    = flue_gas_temperature - ambient_air_temp_f;
    const double h_sensible_n2 = m_n2 * (cp_n2 / kN2Mw) * delta_t_n2;

    // Total sensible heat of flue gas
    const double h_fg = h_sensible_h2o + h_sensible_co2 + h_sensible_n2 + h_sensible_o2 + h_sensible_so2;

    // --- Step 7, 8, 9: Other losses ---
    const double h_moisture = moisture * (flue_gas_temperature - ambient_air_temp_f);
    const double h_carbon   = 14093.0 * unburned_carbon_frac * (inert_ash_frac / percent_total_fuel);
    const double h_ash =
        (inert_ash_frac / percent_total_fuel) * 0.25 * (1.8 * ash_discharge_temperature + 32.0 - ambient_air_temp_f);
    const double h_in = h_fuel + h_combustion_air + heating_value_fuel + h_moisture;

    // --- Final available heat percent ---
    const double available_heat_percent = (h_in - h_fg - h_ash - h_carbon) / heating_value_fuel;
    return available_heat_percent;
}

} // namespace solid_liquid_flue_gas_material