#include "processHeat/flow_calculations_energy_use.h"

#include <cmath>
#include "physics/constants.h"

namespace flow_calculations_energy_use {
FlowCalculationsEnergyUseResults
flowCalculationsEnergyUse(double specific_gravity, double orifice_diameter, double inside_pipe_diameter,
                                   double discharge_coefficient, double gas_heating_value, double gas_temperature,
                                   double gas_pressure, double orifice_pressure_drop, double operating_time) {
    FlowCalculationsEnergyUseResults results;
    using namespace physics::us;
    using namespace physics::conversions;
    // Calculate area
    double area = kOrificeAreaFactor * orifice_diameter * orifice_diameter;
    // Calculate adjusted discharge coefficient
    double adjusted_discharge_coefficient;
    if (orifice_diameter < inside_pipe_diameter) {
        adjusted_discharge_coefficient =
            discharge_coefficient / std::sqrt(1.0 - std::pow(orifice_diameter / inside_pipe_diameter, 4));
    }
    else {
        adjusted_discharge_coefficient = discharge_coefficient;
    }
    // Calculate pressure drop
    double pressure_drop = std::sqrt(orifice_pressure_drop / specific_gravity);
    // Calculate adjusted gas temperature
    double gas_temp_r = fahrenheitToRankine(gas_temperature);
    double adjusted_gas_temperature = std::sqrt(kStandardGasTemperatureR / gas_temp_r);
    // Calculate adjusted gas pressure
    double adjusted_gas_pressure = std::sqrt((gas_pressure + kAtmosphericPressurePsi) / kAtmosphericPressurePsi);
    // Calculate flow
    double flow =
        area * adjusted_discharge_coefficient * pressure_drop * adjusted_gas_temperature * adjusted_gas_pressure;
    results.flow_per_hour = flow;
    // Calculate heat input
    if (gas_heating_value <= 0) {
        results.heat_input = 0;
    }
    else {
        double heat_input_btu = flow * gas_heating_value; // Btu/hr
        results.heat_input = (heat_input_btu * operating_time) / kMMBtuToBtu; // MMBtu
    }
    // Calculate total flow
    results.total_flow = flow * operating_time;
    return results;
}
} // namespace flow_calculations_energy_use