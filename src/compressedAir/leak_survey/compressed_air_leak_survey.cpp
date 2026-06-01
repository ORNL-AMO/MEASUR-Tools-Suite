#include "compressedAir/leak_survey/compressed_air_leak_survey.h"

namespace compressed_air_leak_survey {

Result calculate(const std::vector<Input>& inputs) {
    Result result;

    for (const auto& input : inputs) {
        double tmp_electricity      = 0.0;
        double tmp_electricity_cost = 0.0;
        double tmp_flow_rate        = 0.0;
        double tmp_annual_flow      = 0.0;

        // Route to the selected measurement method sub-calculator
        if (input.measurement_method == static_cast<int>(MeasurementMethod::kEstimate)) {
            auto est_input          = input.estimate_input;
            est_input.operating_time = input.hours_per_year;
            auto est_result         = estimate_method::calculate(est_input);
            tmp_flow_rate           = est_input.leak_rate_estimate * input.units;
            tmp_annual_flow         = est_result.annual_consumption * 1000.0 * input.units;

        } else if (input.measurement_method == static_cast<int>(MeasurementMethod::kDecibels)) {
            auto deb_result  = decibels_method::calculate(input.decibels_input);
            tmp_flow_rate    = deb_result.leak_rate_estimate * input.units;
            tmp_annual_flow  = input.hours_per_year * tmp_flow_rate * 60.0;

        } else if (input.measurement_method == static_cast<int>(MeasurementMethod::kBag)) {
            auto bag_result = bag_method::calculate(input.bag_input);
            tmp_flow_rate   = bag_result.flow_rate * input.units;
            tmp_annual_flow = bag_result.annual_consumption * input.units;

        } else if (input.measurement_method == static_cast<int>(MeasurementMethod::kOrifice)) {
            auto orf_result = orifice_method::calculate(input.orifice_input);
            tmp_flow_rate   = orf_result.leak_rate_estimate * input.units;
            tmp_annual_flow = input.hours_per_year * tmp_flow_rate * 60.0;
        }

        // Apply the selected utility cost model
        if (input.utility_type == static_cast<int>(UtilityType::kCompressedAir)) {
            tmp_electricity_cost = input.utility_cost * tmp_annual_flow;

        } else if (input.utility_type == static_cast<int>(UtilityType::kElectricity)) {
            const auto& ced  = input.compressor_electricity_data;
            tmp_electricity  = (ced.compressor_specific_power / 60.0) * tmp_annual_flow;
            tmp_electricity_cost = tmp_electricity * input.utility_cost;
        }

        result.annual_total_electricity      += tmp_electricity;
        result.annual_total_electricity_cost += tmp_electricity_cost;
        result.total_flow_rate               += tmp_flow_rate;
        result.annual_total_flow_rate        += tmp_annual_flow;
    }

    return result;
}

} // namespace compressed_air_leak_survey
