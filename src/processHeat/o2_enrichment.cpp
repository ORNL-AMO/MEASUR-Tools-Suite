
#include "processHeat/o2_enrichment.h"
#include "physics/constants.h"
#include "processHeat/process_heat.h"

namespace o2_enrichment {

O2EnrichmentResults calculateO2Enrichment(double o2_comb_air, double o2_comb_air_enriched, double flue_gas_temp,
                                          double flue_gas_temp_enriched, double o2_flue_gas,
                                          double o2_flue_gas_enriched, double comb_air_temp,
                                          double comb_air_temp_enriched, double fuel_consumption) {
    O2EnrichmentResults results;

    //inputs in percents, need fractions for calculations
    double o2_comb_air_frac          = o2_comb_air / 100.0;
    double o2_comb_air_enriched_frac = o2_comb_air_enriched / 100.0;
    double o2_flue_gas_frac          = o2_flue_gas / 100.0;
    double o2_flue_gas_enriched_frac = o2_flue_gas_enriched / 100.0;

    // --- Step 1: Calculate excess air (fraction) ---
    results.excess_air          = process_heat::calculateExcessAir(o2_flue_gas_frac);
    results.excess_air_enriched = process_heat::calculateExcessAir(o2_flue_gas_enriched_frac);

    // --- Step 2: Calculate heat input (°F) ---

    results.heat_input          = calculateHeatInput(flue_gas_temp);
    results.heat_input_enriched = calculateHeatInput(flue_gas_temp_enriched);

    // --- Step 3: Calculate air specific heat [Btu/(lb*°F)] ---

    results.air_specific_heat          = calculateAirSpecificHeat(comb_air_temp);
    results.enriched_air_specific_heat = calculateAirSpecificHeat(comb_air_temp_enriched);

    // --- Step 4: Calculate air correction [Btu] ---

    results.air_correction = calculateAirCorrection(results.air_specific_heat, flue_gas_temp, results.excess_air);
    results.enriched_air_correction =
        calculateAirCorrection(results.enriched_air_specific_heat, flue_gas_temp_enriched, results.excess_air_enriched);

    // --- Step 5: Calculate combustion air correction [Btu] ---

    results.combustion_air_correction =
        calculateCombustionAirCorrection(results.air_specific_heat, comb_air_temp, results.excess_air);
    results.combustion_air_correction_enriched = calculateCombustionAirCorrection(
        results.enriched_air_specific_heat, comb_air_temp_enriched, results.excess_air_enriched);

    // --- Step 6: Calculate standard available heat (fraction) ---

    results.std_available_heat =
        calculateStdAvailableHeat(results.heat_input, results.air_correction, results.combustion_air_correction);
    results.std_available_heat_enriched = calculateStdAvailableHeat(
        results.heat_input_enriched, results.enriched_air_correction, results.combustion_air_correction_enriched);

    // --- Step 7: Calculate available heat (fraction) ---
    results.available_heat = calculateAvailableHeat(o2_comb_air_frac, flue_gas_temp, results.std_available_heat);
    results.available_heat_enriched = calculateAvailableHeat(o2_comb_air_enriched_frac, flue_gas_temp_enriched,
                                                                       results.std_available_heat_enriched);

    // --- Step 8: Calculate fuel consumption with O2 enrichment [MMBtu/hr] ---
    results.fuel_consumption_enriched =
        fuel_consumption * (results.std_available_heat / results.available_heat_enriched);

    // --- Step 9: Calculate fuel savings with O2 enrichment (percent) ---
    results.fuel_savings_enriched = ((fuel_consumption - results.fuel_consumption_enriched) / fuel_consumption) * 100.0;

    return results;
}

// --- Helper Functions for O2 Enrichment Calculation Steps ---

double calculateHeatInput(double flue_gas_temp) {
    constexpr double kHeatInputIntercept = 95.0;
    constexpr double kHeatInputSlope     = -0.025;
    return kHeatInputIntercept + kHeatInputSlope * flue_gas_temp;
}

double calculateAirSpecificHeat(double comb_air_temp) {
    using namespace physics::us;
    return kSpecificHeatAirBase + kSpecificHeatAirCoeff * comb_air_temp;
}

double calculateAirCorrection(double air_specific_heat, double flue_gas_temp, double excess_air) {
    constexpr double kAirCorrectionBase  = -1.07891327;
    double           air_correction_term = kAirCorrectionBase + air_specific_heat * flue_gas_temp;
    return -air_correction_term * excess_air;
}

double calculateCombustionAirCorrection(double air_specific_heat, double comb_air_temp, double excess_air) {
    using namespace physics::us;
    double           combustion_air_correction_term = kAirCorrectionBase + air_specific_heat * comb_air_temp;
    return combustion_air_correction_term * (1.0 + excess_air);
}

double calculateStdAvailableHeat(double heat_input, double air_correction, double combustion_air_correction) {
    return heat_input + air_correction + combustion_air_correction;
}

double calculateAvailableHeat(double o2_comb_air, double flue_gas_temp, double available_heat) {
    constexpr double kAvailableHeatFactor     = 9.38;
    constexpr double kO2AirRef                = 0.21;
    constexpr double kAvailableHeatFraction   = 0.02;
    constexpr double kAvailableHeatTempRef    = 60.0;
    constexpr double kAvailableHeatTempDiv    = 980.0;
    constexpr double kAvailableHeatMultiplier = 100.0;
    double enrichment_term = kAvailableHeatFactor * (o2_comb_air - kO2AirRef) / o2_comb_air * kAvailableHeatFraction *
                             ((flue_gas_temp - kAvailableHeatTempRef) / kAvailableHeatTempDiv);
    return available_heat + kAvailableHeatMultiplier * enrichment_term;
}

} // namespace o2_enrichment
