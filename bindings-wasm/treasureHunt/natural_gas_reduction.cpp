#include <emscripten/bind.h>
#include "treasureHunt/natural_gas_reduction.h"

using namespace emscripten;
using namespace natural_gas_reduction;

EMSCRIPTEN_BINDINGS(natural_gas_reduction_module) {
    value_object<FlowMeterMethodData>("NaturalGasFlowMeterMethodData")
        .field("flowRate", &FlowMeterMethodData::flow_rate);

    value_object<NaturalGasOtherMethodData>("NaturalGasOtherMethodData")
        .field("consumption", &NaturalGasOtherMethodData::consumption);

    value_object<AirMassFlowMeasuredData>("AirMassFlowMeasuredData")
        .field("areaOfDuct", &AirMassFlowMeasuredData::area_of_duct)
        .field("airVelocity", &AirMassFlowMeasuredData::air_velocity);

    value_object<AirMassFlowNameplateData>("AirMassFlowNameplateData")
        .field("airFlow", &AirMassFlowNameplateData::air_flow);

    value_object<AirMassFlowData>("AirMassFlowData")
        .field("isNameplate", &AirMassFlowData::is_nameplate)
        .field("measuredData", &AirMassFlowData::measured_data)
        .field("nameplateData", &AirMassFlowData::nameplate_data)
        .field("inletTemperature", &AirMassFlowData::inlet_temperature)
        .field("outletTemperature", &AirMassFlowData::outlet_temperature)
        .field("systemEfficiency", &AirMassFlowData::system_efficiency);

    value_object<WaterMassFlowData>("WaterMassFlowData")
        .field("waterFlow", &WaterMassFlowData::water_flow)
        .field("inletTemperature", &WaterMassFlowData::inlet_temperature)
        .field("outletTemperature", &WaterMassFlowData::outlet_temperature)
        .field("systemEfficiency", &WaterMassFlowData::system_efficiency);

    enum_<NaturalGasMeasurementMethod>("NaturalGasMeasurementMethod")
        .value("FlowMeter", NaturalGasMeasurementMethod::FlowMeter)
        .value("AirMassFlow", NaturalGasMeasurementMethod::AirMassFlow)
        .value("WaterMassFlow", NaturalGasMeasurementMethod::WaterMassFlow)
        .value("Other", NaturalGasMeasurementMethod::Other);

    value_object<NaturalGasReductionInput>("NaturalGasReductionInput")
        .field("operatingHours", &NaturalGasReductionInput::operating_hours)
        .field("fuelCost", &NaturalGasReductionInput::fuel_cost)
        .field("measurementMethod", &NaturalGasReductionInput::measurement_method)
        .field("flowMeterMethodData", &NaturalGasReductionInput::flow_meter_method_data)
        .field("otherMethodData", &NaturalGasReductionInput::other_method_data)
        .field("airMassFlowData", &NaturalGasReductionInput::air_mass_flow_data)
        .field("waterMassFlowData", &NaturalGasReductionInput::water_mass_flow_data)
        .field("units", &NaturalGasReductionInput::units);

    register_vector<NaturalGasReductionInput>("NaturalGasReductionInputV");

    value_object<NaturalGasReductionOutput>("NaturalGasReductionOutput")
        .field("energyUse", &NaturalGasReductionOutput::energy_use)
        .field("energyCost", &NaturalGasReductionOutput::energy_cost)
        .field("heatFlow", &NaturalGasReductionOutput::heat_flow)
        .field("totalFlow", &NaturalGasReductionOutput::total_flow);

    // naturalGasReduction(input_vec: NaturalGasReductionInputV) -> NaturalGasReductionOutput
    //   input_vec: vector of NaturalGasReductionInput structs, one per measure
    //   returns: NaturalGasReductionOutput with total energy use, energy cost, heat flow, and total flow
    function("naturalGasReduction", &naturalGasReduction);

    // flowMeterMethodReduction(data: FlowMeterMethodData, operating_hours: int, fuel_cost: double, units: int) -> NaturalGasReductionOutput
    //   data: FlowMeterMethodData with measured gas flow rate [ft³/min]
    //   operating_hours: annual operating hours [hr/yr]
    //   fuel_cost: fuel cost rate [$/MMBtu]
    //   units: unit conversion multiplier
    //   returns: NaturalGasReductionOutput
    function("flowMeterMethodReduction", &flowMeterMethodReduction);

    // airMassFlowMethodReduction(data: AirMassFlowData, operating_hours: int, fuel_cost: double, units: int) -> NaturalGasReductionOutput
    //   data: AirMassFlowData with air flow and temperature parameters
    //   operating_hours: annual operating hours [hr/yr]
    //   fuel_cost: fuel cost rate [$/MMBtu]
    //   units: unit conversion multiplier
    //   returns: NaturalGasReductionOutput
    function("airMassFlowMethodReduction", &airMassFlowMethodReduction);

    // waterMassFlowMethodReduction(data: WaterMassFlowData, operating_hours: int, fuel_cost: double, units: int) -> NaturalGasReductionOutput
    //   data: WaterMassFlowData with water flow and temperature parameters
    //   operating_hours: annual operating hours [hr/yr]
    //   fuel_cost: fuel cost rate [$/MMBtu]
    //   units: unit conversion multiplier
    //   returns: NaturalGasReductionOutput
    function("waterMassFlowMethodReduction", &waterMassFlowMethodReduction);

    // naturalGasOtherMethodReduction(data: NaturalGasOtherMethodData, fuel_cost: double) -> NaturalGasReductionOutput
    //   data: NaturalGasOtherMethodData with annual gas consumption [MMBtu/yr]
    //   fuel_cost: fuel cost rate [$/MMBtu]
    //   returns: NaturalGasReductionOutput
    function("naturalGasOtherMethodReduction", &otherMethodReduction);
}
