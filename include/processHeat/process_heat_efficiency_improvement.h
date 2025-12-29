#pragma once

/**
 * @ingroup process_heat
 * @file process_heat_efficiency_improvement.h
 * @brief Functions to calculate efficiency improvement for fuel fired furnace.
 * @details Provides a function-based API for process heat efficiency improvement calculations.
 * @bug No known bugs.
 */

/**
 * @ingroup process_heat
 * @namespace process_heat_efficiency_improvement
 * @brief Efficiency improvement calculations for process heating systems.
 */
namespace process_heat_efficiency_improvement {

/**
 * @ingroup process_heat
 * @struct ProcessHeatEfficiencyImprovementResults
 * @brief Results of the process heat efficiency improvement calculation.
 * @details Contains all output values from the efficiency improvement calculation.
 */
struct ProcessHeatEfficiencyImprovementResults {
    double current_excess_air                = 0.0; ///< Current excess air as %
    double new_excess_air                    = 0.0; ///< New excess air as %
    double current_heat_input                = 0.0; ///< Current heat input in °F
    double new_heat_input                    = 0.0; ///< New heat input in °F
    double current_air_specific_heat         = 0.0; ///< Current specific heat of air in Btu/(lb*°F)
    double new_air_specific_heat             = 0.0; ///< New specific heat of air in Btu/(lb*°F)
    double current_air_correction            = 0.0; ///< Current air correction in Btu
    double new_air_correction                = 0.0; ///< New air correction in Btu
    double current_combustion_air_correction = 0.0; ///< Current combustion air correction in Btu
    double new_combustion_air_correction     = 0.0; ///< New combustion air correction in Btu
    double current_available_heat            = 0.0; ///< Current available heat as % of HHV
    double new_available_heat                = 0.0; ///< New available heat as % of HHV
    double new_fuel_savings                  = 0.0; ///< New fuel savings as %
    double new_energy_input                  = 0.0; ///< New energy input in MM Btu/hr
};

/**
 * @brief Calculates the efficiency improvement for a fuel fired furnace.
 * @details Uses process parameters to estimate the benefit of efficiency improvements.
 * @param[in] current_flue_gas_oxygen Current % dry of flue gas oxygen
 * @param[in] new_flue_gas_oxygen New % dry of flue gas oxygen
 * @param[in] current_flue_gas_temp Current temperature of flue gas in °F
 * @param[in] new_flue_gas_temp New temperature of flue gas in °F
 * @param[in] current_combustion_air_temp Current temperature of combustion air in °F
 * @param[in] new_combustion_air_temp New temperature of combustion air in °F
 * @param[in] current_energy_input Current energy input in MM Btu/hr
 * @return ProcessHeatEfficiencyImprovementResults struct with all calculated outputs.
 */
ProcessHeatEfficiencyImprovementResults processHeatEfficiencyImprovement(
    double current_flue_gas_oxygen, double new_flue_gas_oxygen, double current_flue_gas_temp, double new_flue_gas_temp,
    double current_combustion_air_temp, double new_combustion_air_temp, double current_energy_input);

/**
 * @brief Calculates excess air percentage.
 * @param flue_gas_oxygen Flue gas oxygen percentage (dry basis)
 * @param stoich_air_multiplier Stoichiometric air multiplier
 * @param excess_air_denominator_base Base value in denominator
 * @param excess_air_o2_multiplier O2 multiplier in denominator
 * @return Excess air as percent
 */
double calculateExcessAir(double flue_gas_oxygen, double stoich_air_multiplier, double excess_air_denominator_base,
                          double excess_air_o2_multiplier);

/**
 * @brief Calculates heat input.
 * @param flue_gas_temp Flue gas temperature (°F)
 * @param heat_input_base Base value for heat input
 * @param heat_input_temp_coeff Temperature coefficient for heat input
 * @return Heat input (°F)
 */
double calculateHeatInput(double flue_gas_temp, double heat_input_base, double heat_input_temp_coeff);

/**
 * @brief Calculates air specific heat.
 * @param combustion_air_temp Combustion air temperature (°F)
 * @param air_specific_heat_base Base specific heat of air
 * @param air_specific_heat_coeff Temperature coefficient for specific heat of air
 * @return Air specific heat (Btu/(lb*°F))
 */
double calculateAirSpecificHeat(double combustion_air_temp, double air_specific_heat_base,
                                double air_specific_heat_coeff);

/**
 * @brief Calculates air correction.
 * @param air_correction_base Base for air correction
 * @param air_specific_heat Air specific heat (Btu/(lb*°F))
 * @param flue_gas_temp Flue gas temperature (°F)
 * @param excess_air Excess air (%)
 * @return Air correction (Btu)
 */
double calculateAirCorrection(double air_correction_base, double air_specific_heat, double flue_gas_temp,
                              double excess_air);

/**
 * @brief Calculates combustion air correction.
 * @param combustion_air_correction_base Base for combustion air correction
 * @param air_specific_heat Air specific heat (Btu/(lb*°F))
 * @param combustion_air_temp Combustion air temperature (°F)
 * @param excess_air Excess air (%)
 * @return Combustion air correction (Btu)
 */
double calculateCombustionAirCorrection(double combustion_air_correction_base, double air_specific_heat,
                                        double combustion_air_temp, double excess_air);

/**
 * @brief Calculates available heat.
 * @param heat_input Heat input (°F)
 * @param air_correction Air correction (Btu)
 * @param combustion_air_correction Combustion air correction (Btu)
 * @return Available heat (% of HHV)
 */
double calculateAvailableHeat(double heat_input, double air_correction, double combustion_air_correction);

/**
 * @brief Calculates new fuel savings.
 * @param new_available_heat New available heat (% of HHV)
 * @param current_available_heat Current available heat (% of HHV)
 * @return New fuel savings (%)
 */
double calculateFuelSavings(double new_available_heat, double current_available_heat);

/**
 * @brief Calculates new energy input.
 * @param current_energy_input Current energy input (MM Btu/hr)
 * @param new_fuel_savings New fuel savings (%)
 * @return New energy input (MM Btu/hr)
 */
double calculateNewEnergyInput(double current_energy_input, double new_fuel_savings);

} // namespace process_heat_efficiency_improvement
