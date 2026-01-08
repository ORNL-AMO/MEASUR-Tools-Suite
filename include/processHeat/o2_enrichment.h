#pragma once
/**
 * @ingroup process_heat
 * @namespace o2_enrichment
 * @brief O2 enrichment calculations for fuel-fired furnaces.
 */
namespace o2_enrichment {

/**
 * @ingroup process_heat
 * @struct O2EnrichmentResults
 * @brief Results of the O2 enrichment calculation.
 * @details Contains all output values from the O2 enrichment calculation.
 */
struct O2EnrichmentResults {
    double excess_air = 0;                  ///< Excess air (fraction)
    double excess_air_enriched = 0;         ///< Excess air with O2 enrichment (fraction)
    double heat_input = 0;                  ///< Heat input @unitb{\degreeFahrenheit}
    double heat_input_enriched = 0;         ///< Heat input with O2 enrichment @unitb{\degreeFahrenheit}
    double air_specific_heat = 0;           ///< Air specific heat @unitb{Btu/(lb\cdot\degreeFahrenheit)}
    double enriched_air_specific_heat = 0;  ///< Enriched air specific heat @unitb{Btu/(lb\cdot\degreeFahrenheit)}
    double air_correction = 0;              ///< Air correction @unitb{Btu}
    double enriched_air_correction = 0;     ///< Enriched air correction @unitb{Btu}
    double combustion_air_correction = 0;   ///< Combustion air correction @unitb{Btu}
    double combustion_air_correction_enriched = 0; ///< Combustion air correction with O2 enrichment @unitb{Btu}
    double std_available_heat = 0;          ///< Standard available heat (fraction)
    double std_available_heat_enriched = 0; ///< Standard available heat with O2 enrichment (fraction)
    double available_heat = 0;              ///< Available heat (fraction)
    double available_heat_enriched = 0;     ///< Available heat with O2 enrichment (fraction)
    double fuel_consumption_enriched = 0;   ///< Fuel consumption with O2 enrichment @unitb{MMBtu/hr}
    double fuel_savings_enriched = 0;       ///< Fuel savings with O2 enrichment (percent)
};

/**
 * @brief Calculates the O2 enrichment results for a fuel-fired furnace.
 * @details Uses process and enrichment parameters to estimate available heat, fuel consumption, and fuel savings.
 *
 * @param[in] o2_comb_air O2 in combustion air (percent)
 * @param[in] o2_comb_air_enriched O2 in enriched combustion air (percent)
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] flue_gas_temp_enriched Flue gas temperature with O2 enrichment @unitb{\degreeFahrenheit}
 * @param[in] o2_flue_gas O2 in flue gas (percent)
 * @param[in] o2_flue_gas_enriched O2 in flue gas with O2 enrichment (percent)
 * @param[in] comb_air_temp Combustion air preheat temperature @unitb{\degreeFahrenheit}
 * @param[in] comb_air_temp_enriched Combustion air preheat temperature with O2 enrichment @unitb{\degreeFahrenheit}
 * @param[in] fuel_consumption Fuel consumption @unitb{MMBtu/hr}
 * @return O2EnrichmentResults struct with all calculated outputs.
 */
O2EnrichmentResults calculateO2Enrichment(
    double o2_comb_air,
    double o2_comb_air_enriched,
    double flue_gas_temp,
    double flue_gas_temp_enriched,
    double o2_flue_gas,
    double o2_flue_gas_enriched,
    double comb_air_temp,
    double comb_air_temp_enriched,
    double fuel_consumption
);

/**
 * @brief Calculates excess air from O2 in flue gas.
 * @param[in] o2_flue_gas O2 in flue gas (fraction)
 * @return Excess air (fraction)
 */
double calculateExcessAir(double o2_flue_gas);

/**
 * @brief Calculates heat input from flue gas temperature.
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}
 * @return Heat input @unitb{\degreeFahrenheit}
 */
double calculateHeatInput(double flue_gas_temp);

/**
 * @brief Calculates air specific heat from combustion air temperature.
 * @param[in] comb_air_temp Combustion air preheat temperature @unitb{\degreeFahrenheit}
 * @return Air specific heat @unitb{Btu/(lb\cdot\degreeFahrenheit)}
 */
double calculateAirSpecificHeat(double comb_air_temp);

/**
 * @brief Calculates air correction.
 * @param[in] air_specific_heat Air specific heat @unitb{Btu/(lb\cdot\degreeFahrenheit)}
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] excess_air Excess air (fraction)
 * @return Air correction @unitb{Btu}
 */
double calculateAirCorrection(double air_specific_heat, double flue_gas_temp, double excess_air);

/**
 * @brief Calculates combustion air correction.
 * @param[in] air_specific_heat Air specific heat @unitb{Btu/(lb\cdot\degreeFahrenheit)}
 * @param[in] comb_air_temp Combustion air preheat temperature @unitb{\degreeFahrenheit}
 * @param[in] excess_air Excess air (fraction)
 * @return Combustion air correction @unitb{Btu}
 */
double calculateCombustionAirCorrection(double air_specific_heat, double comb_air_temp, double excess_air);

/**
 * @brief Calculates standard available heat.
 * @param[in] heat_input Heat input @unitb{\degreeFahrenheit}
 * @param[in] air_correction Air correction @unitb{Btu}
 * @param[in] combustion_air_correction Combustion air correction @unitb{Btu}
 * @return Standard available heat (fraction)
 */
double calculateStdAvailableHeat(double heat_input, double air_correction, double combustion_air_correction);

/**
 * @brief Calculates available heat.
 * @param[in] o2_comb_air O2 in combustion air (fraction)
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}
 * @param[in] available_heat Standard available heat (fraction)
 * @return Available heat (fraction)
 */
double calculateAvailableHeat(double o2_comb_air, double flue_gas_temp, double available_heat);

} // namespace o2_enrichment

