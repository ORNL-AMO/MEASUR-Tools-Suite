#include "treasureHunt/natural_gas_reduction.h"
#include "physics/constants.h"

namespace natural_gas_reduction {

NaturalGasReductionOutput flowMeterMethodReduction(const FlowMeterMethodData& data, int operating_hours,
                                                   double fuel_cost, int units) {
    double total_flow  = data.flow_rate * units;
    double energy_use  = total_flow * operating_hours * 1.03 / 1000.0;
    double energy_cost = energy_use * fuel_cost;
    return NaturalGasReductionOutput{energy_use, energy_cost, 0.0, total_flow};
}

NaturalGasReductionOutput airMassFlowMethodReduction(const AirMassFlowData& data, int operating_hours,
                                                     double fuel_cost, int units) {
    double air_flow_rate;
    if (data.is_nameplate) {
        air_flow_rate = data.nameplate_data.air_flow;
    } else {
        air_flow_rate = data.measured_data.area_of_duct * data.measured_data.air_velocity;
    }
    double heat_flow   = (physics::us::kAirSensibleHeatFactor * air_flow_rate * (data.outlet_temperature - data.inlet_temperature)) / 1000000.0;
    double total_flow  = air_flow_rate * units;
    double energy_use  = (heat_flow * operating_hours * units) / data.system_efficiency;
    double energy_cost = energy_use * fuel_cost;
    return NaturalGasReductionOutput{energy_use, energy_cost, heat_flow, total_flow};
}

NaturalGasReductionOutput waterMassFlowMethodReduction(const WaterMassFlowData& data, int operating_hours,
                                                       double fuel_cost, int units) {
    double heat_flow   = (physics::us::kWaterSensibleHeatFactor * data.water_flow * (data.outlet_temperature - data.inlet_temperature)) / 1000000.0;
    double total_flow  = data.water_flow * units;
    double energy_use  = (heat_flow * operating_hours * units) / data.system_efficiency;
    double energy_cost = energy_use * fuel_cost;
    return NaturalGasReductionOutput{energy_use, energy_cost, heat_flow, total_flow};
}

NaturalGasReductionOutput otherMethodReduction(const NaturalGasOtherMethodData& data, double fuel_cost) {
    double energy_cost = data.consumption * fuel_cost;
    return NaturalGasReductionOutput{data.consumption, energy_cost, 0.0, 0.0};
}

NaturalGasReductionOutput naturalGasReduction(const std::vector<NaturalGasReductionInput>& input_vec) {
    double energy_use = 0.0, energy_cost = 0.0, heat_flow = 0.0, total_flow = 0.0;
    for (const auto& input : input_vec) {
        NaturalGasReductionOutput tmp;
        switch (input.measurement_method) {
            case NaturalGasMeasurementMethod::FlowMeter:
                tmp = flowMeterMethodReduction(input.flow_meter_method_data, input.operating_hours, input.fuel_cost,
                                               input.units);
                break;
            case NaturalGasMeasurementMethod::AirMassFlow:
                tmp = airMassFlowMethodReduction(input.air_mass_flow_data, input.operating_hours, input.fuel_cost,
                                                 input.units);
                break;
            case NaturalGasMeasurementMethod::WaterMassFlow:
                tmp = waterMassFlowMethodReduction(input.water_mass_flow_data, input.operating_hours, input.fuel_cost,
                                                   input.units);
                break;
            case NaturalGasMeasurementMethod::Other:
            default:
                tmp = otherMethodReduction(input.other_method_data, input.fuel_cost);
                break;
        }
        energy_use  += tmp.energy_use;
        energy_cost += tmp.energy_cost;
        heat_flow   += tmp.heat_flow;
        total_flow  += tmp.total_flow;
    }
    return NaturalGasReductionOutput{energy_use, energy_cost, heat_flow, total_flow};
}

} // namespace natural_gas_reduction
