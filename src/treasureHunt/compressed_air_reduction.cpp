#include "treasureHunt/compressed_air_reduction.h"

#include <cmath>

namespace compressed_air_reduction {

// Nozzle coefficients [a, b, c] for Q_nozzle = a*P^2 + b*P + c (Q in scfm, P in psig).
// Rows 0–12 correspond to the 13 supported nozzle types.
static const double NOZZLE_COEFFICIENTS[13][3] = {
    {-2.2e-07, 0.018893, 0.268476}, {-2.8e-05, 0.038377, 1.061905}, {-7.6e-05, 1.537424, 14.3},
    {-2.2e-05, 0.345931, 5.780952}, {0.000682, 0.643182, 13.83333}, {5.41e-06, 0.228851, 2.968095},
    {-2.1e-06, 0.075463, 1.089857}, {-2.8e-05, 0.14871,  1.841905}, {0.002652, 2.250152, 46.56667},
    {0.000747, 0.842056, 15.95714}, {0.000411, 0.560649, 10.1619},  {0.000935, 0.130792, 4.429524},
    {0.000935, 0.130792, 4.429524}};

CompressedAirReductionOutput compressedAirReduction(const std::vector<CompressedAirReductionInput>& input_vec) {
    double total_energy_use              = 0.0;
    double total_energy_cost             = 0.0;
    double total_flow_rate               = 0.0;
    double total_single_nozzle_flow_rate = 0.0;
    double total_consumption             = 0.0;

    for (const auto& input : input_vec) {
        CompressedAirReductionOutput method_output;

        switch (input.measurement_method) {
            case MeasurementMethod::FlowMeter:
                method_output = flowMeterReduction(input.flow_meter_method_data, input.hours_per_year, input.units);
                break;
            case MeasurementMethod::Bag:
                method_output = bagMethodReduction(input.bag_method_data, input.hours_per_year, input.units);
                break;
            case MeasurementMethod::Pressure:
                method_output = pressureMethodReduction(input.pressure_method_data, input.hours_per_year);
                break;
            case MeasurementMethod::Other:
            default:
                method_output = otherMethodReduction(input.other_method_data);
                break;
        }

        double energy_use  = 0.0;
        double energy_cost = 0.0;

        if (input.utility_type == UtilityType::CompressedAir) {
            energy_cost = input.utility_cost * method_output.consumption;
        } else {
            energy_use  = ((input.compressor_electricity_data.compressor_specific_power * (input.compressor_electricity_data.compressor_control_adjustment / 100)) / 60.0) *
                          method_output.consumption;
            energy_cost = energy_use * input.utility_cost;
        }

        total_energy_use              += energy_use;
        total_energy_cost             += energy_cost;
        total_flow_rate               += method_output.flow_rate;
        total_single_nozzle_flow_rate += method_output.single_nozzle_flow_rate;
        total_consumption             += method_output.consumption;
    }

    return CompressedAirReductionOutput{
        total_energy_use,
        total_energy_cost,
        total_flow_rate,
        total_single_nozzle_flow_rate,
        total_consumption};
}

CompressedAirReductionOutput flowMeterReduction(const FlowMeterMethodData& data, int hours_per_year, int units) {
    double flow_rate   = data.meter_reading;
    double consumption = flow_rate * 60.0 * hours_per_year * units;
    return CompressedAirReductionOutput{0.0, 0.0, flow_rate, 0.0, consumption};
}

CompressedAirReductionOutput bagMethodReduction(const BagMethodData& data, int hours_per_year, int units) {
    double flow_rate   = data.bag_volume / (data.bag_fill_time / 60.0);
    double consumption = flow_rate * hours_per_year * data.number_of_bags * 60.0 * units;
    return CompressedAirReductionOutput{0.0, 0.0, flow_rate, 0.0, consumption};
}

CompressedAirReductionOutput pressureMethodReduction(const PressureMethodData& data, int hours_per_year) {
    const double a                 = NOZZLE_COEFFICIENTS[data.nozzle_type][0];
    const double b                 = NOZZLE_COEFFICIENTS[data.nozzle_type][1];
    const double c                 = NOZZLE_COEFFICIENTS[data.nozzle_type][2];
    double single_nozzle_flow_rate = (a * std::pow(data.supply_pressure, 2.0)) + (b * data.supply_pressure) + c;
    double flow_rate               = single_nozzle_flow_rate * data.number_of_nozzles;
    double consumption             = flow_rate * 60.0 * hours_per_year;
    return CompressedAirReductionOutput{0.0, 0.0, flow_rate, single_nozzle_flow_rate, consumption};
}

CompressedAirReductionOutput otherMethodReduction(const OtherMethodData& data) {
    return CompressedAirReductionOutput{0.0, 0.0, 0.0, 0.0, data.consumption};
}

} // namespace compressed_air_reduction
