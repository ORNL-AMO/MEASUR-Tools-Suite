#include <emscripten/bind.h>

#include "treasureHunt/compressed_air_reduction.h"

using namespace emscripten;
using namespace compressed_air_reduction;

EMSCRIPTEN_BINDINGS(compressedAirReduction_module) {
    // Bind measurement method data structs
    value_object<FlowMeterMethodData>("FlowMeterMethodData")
        .field("meterReading", &FlowMeterMethodData::meter_reading);

    value_object<BagMethodData>("BagMethodData")
        .field("bagFillTime",  &BagMethodData::bag_fill_time)
        .field("bagVolume",    &BagMethodData::bag_volume)
        .field("numberOfBags", &BagMethodData::number_of_bags);

    value_object<PressureMethodData>("PressureMethodData")
        .field("nozzleType",      &PressureMethodData::nozzle_type)
        .field("numberOfNozzles", &PressureMethodData::number_of_nozzles)
        .field("supplyPressure",  &PressureMethodData::supply_pressure);

    value_object<OtherMethodData>("OtherMethodData")
        .field("consumption", &OtherMethodData::consumption);

    value_object<CompressorElectricityData>("CompressorElectricityData")
        .field("compressorControlAdjustment", &CompressorElectricityData::compressor_control_adjustment)
        .field("compressorSpecificPower",     &CompressorElectricityData::compressor_specific_power);

    enum_<MeasurementMethod>("CompressedAirMeasurementMethod")
        .value("FlowMeter", MeasurementMethod::FlowMeter)
        .value("Bag",       MeasurementMethod::Bag)
        .value("Pressure",  MeasurementMethod::Pressure)
        .value("Other",     MeasurementMethod::Other);

    enum_<UtilityType>("CompressedAirUtilityType")
        .value("CompressedAir", UtilityType::CompressedAir)
        .value("Electricity",   UtilityType::Electricity);

    value_object<CompressedAirReductionInput>("CompressedAirReductionInput")
        .field("hoursPerYear",             &CompressedAirReductionInput::hours_per_year)
        .field("utilityType",              &CompressedAirReductionInput::utility_type)
        .field("utilityCost",              &CompressedAirReductionInput::utility_cost)
        .field("measurementMethod",        &CompressedAirReductionInput::measurement_method)
        .field("flowMeterMethodData",      &CompressedAirReductionInput::flow_meter_method_data)
        .field("bagMethodData",            &CompressedAirReductionInput::bag_method_data)
        .field("pressureMethodData",       &CompressedAirReductionInput::pressure_method_data)
        .field("otherMethodData",          &CompressedAirReductionInput::other_method_data)
        .field("compressorElectricityData",&CompressedAirReductionInput::compressor_electricity_data)
        .field("units",                    &CompressedAirReductionInput::units);

    register_vector<CompressedAirReductionInput>("CompressedAirReductionInputV");

    value_object<CompressedAirReductionOutput>("CompressedAirReductionOutput")
        .field("energyUse",            &CompressedAirReductionOutput::energy_use)
        .field("energyCost",           &CompressedAirReductionOutput::energy_cost)
        .field("flowRate",             &CompressedAirReductionOutput::flow_rate)
        .field("singleNozzleFlowRate", &CompressedAirReductionOutput::single_nozzle_flow_rate)
        .field("consumption",          &CompressedAirReductionOutput::consumption);

    // compressedAirReduction(input_vec: CompressedAirReductionInputV) -> CompressedAirReductionOutput
    //   input_vec: vector of CompressedAirReductionInput structs, one per measure
    //   returns: CompressedAirReductionOutput with total consumption, flow rates, energy use, and cost
    function("compressedAirReduction", &compressedAirReduction);

    // flowMeterReduction(data: FlowMeterMethodData, hours_per_year: int, units: int) -> CompressedAirReductionOutput
    //   data: FlowMeterMethodData with meter reading in scfm
    //   hours_per_year: annual operating hours
    //   units: quantity multiplier
    //   returns: CompressedAirReductionOutput with flow rate and consumption (energy fields are zero)
    function("flowMeterReduction", &flowMeterReduction);

    // bagMethodReduction(data: BagMethodData, hours_per_year: int, units: int) -> CompressedAirReductionOutput
    //   data: BagMethodData with bag geometry and fill time
    //   hours_per_year: annual operating hours
    //   units: outer quantity multiplier
    //   returns: CompressedAirReductionOutput with flow rate and consumption (energy fields are zero)
    function("bagMethodReduction", &bagMethodReduction);

    // pressureMethodReduction(data: PressureMethodData, hours_per_year: int) -> CompressedAirReductionOutput
    //   data: PressureMethodData with nozzle type, count, and supply pressure
    //   hours_per_year: annual operating hours
    //   returns: CompressedAirReductionOutput with flow rates and consumption (energy fields are zero)
    function("pressureMethodReduction", &pressureMethodReduction);

    // otherMethodReduction(data: OtherMethodData) -> CompressedAirReductionOutput
    //   data: OtherMethodData with direct annual consumption value
    //   returns: CompressedAirReductionOutput with consumption set (all other fields are zero)
    function("otherMethodReduction", &otherMethodReduction);
}
