#include "treasureHunt/compressed_air_pressure_reduction.h"

#include <cmath>

#include "physics/constants.h"

namespace compressed_air_pressure_reduction {

CompressedAirPressureReductionOutput compressedAirPressureReduction(
    const std::vector<CompressedAirPressureReductionInput>& input_vec) {
    CompressedAirPressureReductionOutput output;

    for (const auto& input : input_vec) {
        CompressedAirPressureReductionOutput tmp_output;
        if (input.is_baseline) {
            tmp_output = baselineReduction(input.hours_per_year, input.electricity_cost, input.compressor_power);
        }
        else {
            tmp_output = modificationReduction(input.hours_per_year, input.electricity_cost, input.compressor_power,
                                              input.proposed_pressure, input.atmospheric_pressure,
                                              input.pressure_rated);
        }

        output.energy_use += tmp_output.energy_use;
        output.energy_cost += tmp_output.energy_cost;
    }

    return output;
}

CompressedAirPressureReductionOutput baselineReduction(int hours_per_year, double electricity_cost,
                                                       double compressor_power) {
    double energy_use = static_cast<double>(hours_per_year) * compressor_power;
    double energy_cost = energy_use * electricity_cost;

    return CompressedAirPressureReductionOutput {energy_use, energy_cost};
}

CompressedAirPressureReductionOutput modificationReduction(int hours_per_year, double electricity_cost,
                                                           double compressor_power, double proposed_pressure,
                                                           double atmospheric_pressure, double pressure_rated) {
    // Empirical compressed-air power ratio constants from the existing treasure hunt model.
    constexpr double kPressureRatioExponentNumerator = 0.395;
    constexpr double kPressureRatioExponentDenominator = 1.395;

    const double r = (pressure_rated + physics::us::kAtmosphericPressurePsi) / physics::us::kAtmosphericPressurePsi;
    const double x = (proposed_pressure + atmospheric_pressure) / atmospheric_pressure;
    const double c = (kPressureRatioExponentNumerator / kPressureRatioExponentDenominator);

    const double energy_use = static_cast<double>(hours_per_year) *
                              (compressor_power * ((std::pow(x, c) - 1.0) / (std::pow(r, c) - 1.0)));
    const double energy_cost = energy_use * electricity_cost;

    return CompressedAirPressureReductionOutput {energy_use, energy_cost};
}

} // namespace compressed_air_pressure_reduction
