#pragma once

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @file process_heat_efficiency_improvement.h
 * 
 * @copybrief process_heat_efficiency_improvement
 */

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @namespace process_heat_efficiency_improvement
 * @brief Efficiency improvement calculations for process heating systems.
 */
namespace process_heat_efficiency_improvement {

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @struct ProcessHeatEfficiencyImprovementResults
 * @brief Results of the process heat efficiency improvement calculation.
 * @details Contains all output values from the efficiency improvement calculation.
 */
struct ProcessHeatEfficiencyImprovementResults {
    double current_excess_air                = 0.0; ///< Current excess air as %
    double new_excess_air                    = 0.0; ///< New excess air as %
    double current_heat_input                = 0.0; ///< Current heat input as %
    double new_heat_input                    = 0.0; ///< New heat input as %
    double current_air_specific_heat         = 0.0; ///< Current specific heat of air in Btu/(lb*°F)
    double new_air_specific_heat             = 0.0; ///< New specific heat of air in Btu/(lb*°F)
    double current_air_correction            = 0.0; ///< Current air correction as % of HHV
    double new_air_correction                = 0.0; ///< New air correction as % of HHV
    double current_combustion_air_correction = 0.0; ///< Current combustion air correction as % of HHV
    double new_combustion_air_correction     = 0.0; ///< New combustion air correction as % of HHV
    double current_available_heat            = 0.0; ///< Current available heat as % of HHV
    double new_available_heat                = 0.0; ///< New available heat as % of HHV
    double new_fuel_savings                  = 0.0; ///< New fuel savings as %
    double new_energy_input                  = 0.0; ///< New energy input in MM Btu/hr
};

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates the efficiency improvement for a fuel fired furnace.
 * @details Uses process parameters to estimate the benefit of efficiency improvements.
 * @param[in] current_flue_gas_oxygen Current % dry of flue gas oxygen.
 * @param[in] new_flue_gas_oxygen New % dry of flue gas oxygen.
 * @param[in] current_flue_gas_temp Current temperature of flue gas @unitb{\degreeFahrenheit}.
 * @param[in] new_flue_gas_temp New temperature of flue gas @unitb{\degreeFahrenheit}.
 * @param[in] current_combustion_air_temp Current temperature of combustion air @unitb{\degreeFahrenheit}.
 * @param[in] new_combustion_air_temp New temperature of combustion air @unitb{\degreeFahrenheit}.
 * @param[in] current_energy_input Current energy input @unitb{\mega\btu\per\hour}.
 * @return ProcessHeatEfficiencyImprovementResults struct with all calculated outputs.
 */
ProcessHeatEfficiencyImprovementResults processHeatEfficiencyImprovement(
    double current_flue_gas_oxygen, double new_flue_gas_oxygen, double current_flue_gas_temp, double new_flue_gas_temp,
    double current_combustion_air_temp, double new_combustion_air_temp, double current_energy_input);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates excess air percentage.
 * @param[in] flue_gas_oxygen Flue gas oxygen percentage (dry basis) @unitb{\percent}.
 * @param[in] stoich_air_multiplier Stoichiometric air multiplier.
 * @param[in] excess_air_denominator_base Base value in denominator.
 * @param[in] excess_air_o2_multiplier O2 multiplier in denominator.
 * @return Excess air @unitb{\percent}.
 */
double calculateExcessAir(double flue_gas_oxygen, double stoich_air_multiplier, double excess_air_denominator_base,
                          double excess_air_o2_multiplier);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates heat input.
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}.
 * @param[in] heat_input_base Base value for heat input @unitb{\percent}.
 * @param[in] heat_input_temp_coeff Temperature coefficient for heat input @unitb{\percent\per\degreeFahrenheit}.
 * @return Heat input @unitb{\percent}.
 */
double calculateHeatInput(double flue_gas_temp, double heat_input_base, double heat_input_temp_coeff);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates air specific heat.
 * @param[in] combustion_air_temp Combustion air temperature @unitb{\degreeFahrenheit}.
 * @param[in] air_specific_heat_base Base specific heat of air @unitb{\btu\per\pound\per\degreeFahrenheit}.
 * @param[in] air_specific_heat_coeff Temperature coefficient for specific heat of air @unitb{\btu\per\pound\per\degreeFahrenheit}.
 * @return Air specific heat @unitb{\btu\per\pound\per\degreeFahrenheit}.
 */
double calculateAirSpecificHeat(double combustion_air_temp, double air_specific_heat_base,
                                double air_specific_heat_coeff);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates air correction.
 * @param[in] air_correction_base Base for air correction @unitb{\percent}.
 * @param[in] air_specific_heat Air specific heat @unitb{\btu\per\pound\per\degreeFahrenheit}.
 * @param[in] flue_gas_temp Flue gas temperature @unitb{\degreeFahrenheit}.
 * @param[in] excess_air Excess air @unitb{\percent}.
 * @return Air correction @unitb{\percent} of HHV.
 */
double calculateAirCorrection(double air_correction_base, double air_specific_heat, double flue_gas_temp,
                              double excess_air);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates combustion air correction.
 * @param[in] combustion_air_correction_base Base for combustion air correction @unitb{\percent}.
 * @param[in] air_specific_heat Air specific heat @unitb{\btu\per\pound\per\degreeFahrenheit}.
 * @param[in] combustion_air_temp Combustion air temperature @unitb{\degreeFahrenheit}.
 * @param[in] excess_air Excess air @unitb{\percent}.
 * @return Combustion air correction @unitb{\percent} of HHV.
 */
double calculateCombustionAirCorrection(double combustion_air_correction_base, double air_specific_heat,
                                        double combustion_air_temp, double excess_air);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates available heat.
 * @param[in] heat_input Heat input @unitb{\percent}.
 * @param[in] air_correction Air correction @unitb{\percent} of HHV.
 * @param[in] combustion_air_correction Combustion air correction @unitb{\percent} of HHV.
 * @return Available heat @unitb{\percent} of HHV.
 */
double calculateAvailableHeat(double heat_input, double air_correction, double combustion_air_correction);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates new fuel savings.
 * @param[in] new_available_heat New available heat @unitb{\percent} of HHV.
 * @param[in] current_available_heat Current available heat @unitb{\percent} of HHV.
 * @return New fuel savings @unitb{\percent}.
 */
double calculateFuelSavings(double new_available_heat, double current_available_heat);

/**
 * @ingroup process_heat_efficiency_improvement_calculator
 * @brief Calculates new energy input.
 * @param[in] current_energy_input Current energy input @unitb{\mega\btu\per\hour}.
 * @param[in] new_fuel_savings New fuel savings @unitb{\percent}.
 * @return New energy input @unitb{\mega\btu\per\hour}.
 */
double calculateNewEnergyInput(double current_energy_input, double new_fuel_savings);

} // namespace process_heat_efficiency_improvement
