
#include "processHeat/process_heat_efficiency_improvement.h"


namespace process_heat_efficiency_improvement {

// Helper functions for each step of the calculation
double calculateExcessAir(double flue_gas_oxygen, double stoich_air_multiplier, double excess_air_denominator_base, double excess_air_o2_multiplier) {
    return (100.0 * stoich_air_multiplier * (flue_gas_oxygen / 100.0)) /
           (excess_air_denominator_base - excess_air_o2_multiplier * (flue_gas_oxygen / 100.0));
}

double calculateHeatInput(double flue_gas_temp, double heat_input_base, double heat_input_temp_coeff) {
    return heat_input_base + heat_input_temp_coeff * flue_gas_temp;
}

double calculateAirSpecificHeat(double combustion_air_temp, double air_specific_heat_base, double air_specific_heat_coeff) {
    return air_specific_heat_base + air_specific_heat_coeff * combustion_air_temp;
}

double calculateAirCorrection(double air_correction_base, double air_specific_heat, double flue_gas_temp, double excess_air) {
    return -(air_correction_base + air_specific_heat * flue_gas_temp) * (excess_air / 100.0);
}

double calculateCombustionAirCorrection(double combustion_air_correction_base, double air_specific_heat, double combustion_air_temp, double excess_air) {
    return (combustion_air_correction_base + air_specific_heat * combustion_air_temp) * (1.0 + (excess_air / 100.0));
}

double calculateAvailableHeat(double heat_input, double air_correction, double combustion_air_correction) {
    return heat_input + air_correction + combustion_air_correction;
}

double calculateFuelSavings(double new_available_heat, double current_available_heat) {
    return ((new_available_heat - current_available_heat) / new_available_heat) * 100.0;
}

double calculateNewEnergyInput(double current_energy_input, double new_fuel_savings) {
    return current_energy_input * (1.0 - new_fuel_savings / 100.0);
}

ProcessHeatEfficiencyImprovementResults processHeatEfficiencyImprovement(
    double current_flue_gas_oxygen,
    double new_flue_gas_oxygen,
    double current_flue_gas_temp,
    double new_flue_gas_temp,
    double current_combustion_air_temp,
    double new_combustion_air_temp,
    double current_energy_input
) {
    // Constants for the calculation
    const double stoich_air_multiplier = 8.52381;
    const double excess_air_o2_multiplier = 9.52381;
    const double excess_air_denominator_base = 2.0;
    const double heat_input_base = 95.0;
    const double heat_input_temp_coeff = -0.025;
    const double air_specific_heat_base = 0.017828518;
    const double air_specific_heat_coeff = 0.000002556;
    const double air_correction_base = -1.07891327;
    const double combustion_air_correction_base = -1.078913827;

    ProcessHeatEfficiencyImprovementResults results;

    // Step 1: Calculate current and new excess air (%)
    results.current_excess_air = calculateExcessAir(current_flue_gas_oxygen, stoich_air_multiplier, excess_air_denominator_base, excess_air_o2_multiplier);
    results.new_excess_air = calculateExcessAir(new_flue_gas_oxygen, stoich_air_multiplier, excess_air_denominator_base, excess_air_o2_multiplier);

    // Step 2: Calculate current and new heat input (%)
    results.current_heat_input = calculateHeatInput(current_flue_gas_temp, heat_input_base, heat_input_temp_coeff);
    results.new_heat_input = calculateHeatInput(new_flue_gas_temp, heat_input_base, heat_input_temp_coeff);

    // Step 3: Calculate current and new air specific heat (Btu/(lb*°F))
    results.current_air_specific_heat = calculateAirSpecificHeat(current_combustion_air_temp, air_specific_heat_base, air_specific_heat_coeff);
    results.new_air_specific_heat = calculateAirSpecificHeat(new_combustion_air_temp, air_specific_heat_base, air_specific_heat_coeff);

    // Step 4: Calculate current and new air correction (% of HHV)
    results.current_air_correction = calculateAirCorrection(air_correction_base, results.current_air_specific_heat, current_flue_gas_temp, results.current_excess_air);
    results.new_air_correction = calculateAirCorrection(air_correction_base, results.new_air_specific_heat, new_flue_gas_temp, results.new_excess_air);

    // Step 5: Calculate current and new combustion air correction (% of HHV)
    results.current_combustion_air_correction = calculateCombustionAirCorrection(combustion_air_correction_base, results.current_air_specific_heat, current_combustion_air_temp, results.current_excess_air);
    results.new_combustion_air_correction = calculateCombustionAirCorrection(combustion_air_correction_base, results.new_air_specific_heat, new_combustion_air_temp, results.new_excess_air);

    // Step 6: Calculate current and new available heat (% of HHV)
    results.current_available_heat = calculateAvailableHeat(results.current_heat_input, results.current_air_correction, results.current_combustion_air_correction);
    results.new_available_heat = calculateAvailableHeat(results.new_heat_input, results.new_air_correction, results.new_combustion_air_correction);

    // Step 7: Calculate new fuel savings (%)
    results.new_fuel_savings = calculateFuelSavings(results.new_available_heat, results.current_available_heat);

    // Step 8: Calculate new energy input (MM Btu/hr)
    results.new_energy_input = calculateNewEnergyInput(current_energy_input, results.new_fuel_savings);

    return results;
}

} // namespace process_heat_efficiency_improvement