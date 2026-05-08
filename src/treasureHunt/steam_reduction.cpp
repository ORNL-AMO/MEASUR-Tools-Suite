/**
 * @file steam_reduction.cpp
 * @brief Implementation of Steam Reduction Calculations.
 */

#include "treasureHunt/steam_reduction.h"

#include "steamModeler/SteamProperties.h"

namespace steam_reduction {

double calculateChangeEnthalpy(double pressure,
                                SteamProperties::ThermodynamicQuantity steam_variable_option,
                                double steam_variable, double feed_water_temperature) {
    double steam_enthalpy =
        SteamProperties(pressure, steam_variable_option, steam_variable).calculate().specificEnthalpy;
    // Feedwater enthalpy at atmospheric pressure (0.101325 MPaa) and given temperature.
    double feed_enthalpy =
        SteamProperties(0.101325, SteamProperties::ThermodynamicQuantity::TEMPERATURE, feed_water_temperature)
            .calculate()
            .specificEnthalpy;
    return steam_enthalpy - feed_enthalpy;
}

SteamReductionOutput flowMeterReduction(const FlowMeterMethodData& data, int hours_per_year,
                                        double system_efficiency, int units, double boiler_efficiency,
                                        double change_enthalpy) {
    double steam_use =
        data.flow_rate * static_cast<double>(hours_per_year) * (static_cast<double>(units) / system_efficiency);
    double energy_use = change_enthalpy * steam_use * (1.0 / boiler_efficiency);
    return SteamReductionOutput {steam_use, energy_use, 0.0};
}

SteamReductionOutput airMassFlowReduction(const MassFlowMethodData& data, int hours_per_year,
                                          double system_efficiency, int units, double boiler_efficiency,
                                          double change_enthalpy) {
    double air_flow_rate = 0.0;
    if (data.is_nameplate) {
        air_flow_rate = data.mass_flow_nameplate_data.flow_rate;
    }
    else {
        air_flow_rate = data.mass_flow_measured_data.air_velocity * data.mass_flow_measured_data.area_of_duct;
    }

    // Air Cp constant: 0.072381 kJ·min/(m³·hr·K), derived from 1.08 Btu·hr/(scf·hr·R).
    constexpr double kAirCpCoeff = 0.072381;
    double heat_flow_rate = kAirCpCoeff * air_flow_rate * (data.outlet_temperature - data.inlet_temperature);

    double energy_use = (static_cast<double>(units) * heat_flow_rate * static_cast<double>(hours_per_year)) /
                        (system_efficiency * boiler_efficiency);
    double steam_use = (energy_use / change_enthalpy) * boiler_efficiency;
    return SteamReductionOutput {steam_use, energy_use, 0.0};
}

SteamReductionOutput waterMassFlowReduction(const MassFlowMethodData& data, int hours_per_year,
                                            double system_efficiency, int units, double boiler_efficiency,
                                            double change_enthalpy) {
    double water_flow_rate = data.mass_flow_nameplate_data.flow_rate;

    // Water heat capacity constant: 251045 (kJ/(m³·K))·(min/hr), derived from 8.34 lb/gal × 1 Btu/(lb·°F) × 60 min/hr.
    constexpr double kWaterHeatCapacityCoeff = 251045.0;
    double heat_flow_rate =
        kWaterHeatCapacityCoeff * water_flow_rate * (data.outlet_temperature - data.inlet_temperature);

    double energy_use = (static_cast<double>(units) * heat_flow_rate * static_cast<double>(hours_per_year)) /
                        (system_efficiency * boiler_efficiency);
    double steam_use = (energy_use / change_enthalpy) * boiler_efficiency;
    return SteamReductionOutput {steam_use, energy_use, 0.0};
}

SteamReductionOutput offsheetReduction(const OffsheetMethodData& data, double boiler_efficiency,
                                       double change_enthalpy) {
    double energy_use = data.consumption;
    double steam_use  = (energy_use / change_enthalpy) * boiler_efficiency;
    return SteamReductionOutput {steam_use, energy_use, 0.0};
}

SteamReductionOutput steamReduction(const std::vector<SteamReductionInput>& input_vec) {
    double steam_use = 0.0, energy_use = 0.0, energy_cost = 0.0;

    for (const auto& input : input_vec) {
        double change_enthalpy = calculateChangeEnthalpy(input.pressure, input.steam_variable_option,
                                                          input.steam_variable, input.feed_water_temperature);

        SteamReductionOutput tmp_output;
        switch (input.measurement_method) {
            case SteamMeasurementMethod::kFlowMeter: {
                tmp_output = flowMeterReduction(input.flow_meter_method_data, input.hours_per_year,
                                                input.system_efficiency, input.units, input.boiler_efficiency,
                                                change_enthalpy);
                break;
            }
            case SteamMeasurementMethod::kAirMassFlow: {
                tmp_output = airMassFlowReduction(input.air_mass_flow_method_data, input.hours_per_year,
                                                  input.system_efficiency, input.units, input.boiler_efficiency,
                                                  change_enthalpy);
                break;
            }
            case SteamMeasurementMethod::kWaterMassFlow: {
                tmp_output = waterMassFlowReduction(input.water_mass_flow_method_data, input.hours_per_year,
                                                    input.system_efficiency, input.units, input.boiler_efficiency,
                                                    change_enthalpy);
                break;
            }
            case SteamMeasurementMethod::kOffsheet:
            default: {
                tmp_output = offsheetReduction(input.offsheet_method_data, input.boiler_efficiency, change_enthalpy);
                break;
            }
        }

        double tmp_energy_cost = 0.0;
        if (input.utility_type == UtilityType::kSteam) {
            tmp_energy_cost = tmp_output.steam_use * input.utility_cost;
        }
        else {
            // Natural gas or other utility: cost based on energy use.
            tmp_energy_cost = tmp_output.energy_use * input.utility_cost;
        }

        steam_use  += tmp_output.steam_use;
        energy_use += tmp_output.energy_use;
        energy_cost += tmp_energy_cost;
    }

    return SteamReductionOutput {steam_use, energy_use, energy_cost};
}

} // namespace steam_reduction
