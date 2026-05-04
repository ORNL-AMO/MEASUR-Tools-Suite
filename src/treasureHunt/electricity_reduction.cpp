#include "treasureHunt/electricity_reduction.h"

#include <cmath>

namespace electricity_reduction {

ElectricityReductionOutput electricityReduction(const std::vector<ElectricityReductionInput>& input_vec) {
    double energy_use = 0.0, energy_cost = 0.0, power = 0.0;
    for (const auto& input : input_vec) {
        ElectricityReductionOutput tmp_output;
        switch (input.measurement_method) {
            case ElectricityReductionMeasurementMethod::Multimeter: {
                tmp_output = multimeterReduction(input.multimeter_data, input.operating_hours,
                                                 input.electricity_cost, input.units);
                break;
            }
            case ElectricityReductionMeasurementMethod::Nameplate: {
                tmp_output = nameplateReduction(input.nameplate_data, input.operating_hours,
                                                input.electricity_cost, input.units);
                break;
            }
            case ElectricityReductionMeasurementMethod::PowerMeter: {
                tmp_output = powerMeterReduction(input.power_meter_data, input.operating_hours,
                                                 input.electricity_cost, input.units);
                break;
            }
            case ElectricityReductionMeasurementMethod::Other:
            default: {
                tmp_output = otherReduction(input.other_method_data, input.electricity_cost);
                break;
            }
        }
        energy_use  += tmp_output.energy_use;
        energy_cost += tmp_output.energy_cost;
        power       += tmp_output.power;
    }
    return ElectricityReductionOutput{energy_use, energy_cost, power};
}

ElectricityReductionOutput multimeterReduction(const MultimeterData& data, int operating_hours,
                                               double electricity_cost, int units) {
    double tmp_power = 0.0;
    if (data.number_of_phases == 1) {
        tmp_power = data.supply_voltage * data.average_current * data.power_factor * 0.001 * units;
    }
    else {
        tmp_power = data.supply_voltage * data.average_current * data.power_factor *
                    (std::sqrt(3.0) / 1000.0) * units;
    }
    double tmp_energy_use  = tmp_power * operating_hours;
    double tmp_energy_cost = tmp_energy_use * electricity_cost;
    return ElectricityReductionOutput{tmp_energy_use, tmp_energy_cost, tmp_power};
}

ElectricityReductionOutput nameplateReduction(const NameplateData& data, int operating_hours,
                                              double electricity_cost, int units) {
    double tmp_power = data.rated_motor_power * data.load_factor *
                       std::pow(data.operational_frequency / data.line_frequency, 2.5) *
                       (1.0 / data.motor_and_drive_efficiency);
    double tmp_energy_use  = tmp_power * operating_hours * units;
    double tmp_energy_cost = tmp_energy_use * electricity_cost;
    return ElectricityReductionOutput{tmp_energy_use, tmp_energy_cost, tmp_power};
}

ElectricityReductionOutput powerMeterReduction(const PowerMeterData& data, int operating_hours,
                                               double electricity_cost, int units) {
    double tmp_power       = data.power * units;
    double tmp_energy_use  = tmp_power * operating_hours;
    double tmp_energy_cost = tmp_energy_use * electricity_cost;
    return ElectricityReductionOutput{tmp_energy_use, tmp_energy_cost, tmp_power};
}

ElectricityReductionOutput otherReduction(const ElectricityOtherMethodData& data, double electricity_cost) {
    double tmp_energy_use  = data.energy;
    double tmp_energy_cost = tmp_energy_use * electricity_cost;
    return ElectricityReductionOutput{tmp_energy_use, tmp_energy_cost, 0.0};
}

} // namespace electricity_reduction
