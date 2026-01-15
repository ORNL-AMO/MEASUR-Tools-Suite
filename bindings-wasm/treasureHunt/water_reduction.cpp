#include <emscripten/bind.h>
#include "treasureHunt/water_reduction.h"

using namespace emscripten;
using namespace water_reduction;

EMSCRIPTEN_BINDINGS(waterReduction_module) {
    // Bind input/output structs
    value_object<MeteredFlowMethodData>("MeteredFlowMethodData")
        .field("meterReading", &MeteredFlowMethodData::meter_reading);

    value_object<VolumeMeterMethodData>("VolumeMeterMethodData")
        .field("finalMeterReading", &VolumeMeterMethodData::final_meter_reading)
        .field("initialMeterReading", &VolumeMeterMethodData::initial_meter_reading)
        .field("elapsedTime", &VolumeMeterMethodData::elapsed_time);

    value_object<BucketMethodData>("BucketMethodData")
        .field("bucketVolume", &BucketMethodData::bucket_volume)
        .field("bucketFillTime", &BucketMethodData::bucket_fill_time);

    value_object<WaterOtherMethodData>("WaterOtherMethodData")
        .field("consumption", &WaterOtherMethodData::consumption);

    enum_<WaterReductionMeasurementMethod>("WaterReductionMeasurementMethod")
        .value("Metered", WaterReductionMeasurementMethod::Metered)
        .value("Volume", WaterReductionMeasurementMethod::Volume)
        .value("Bucket", WaterReductionMeasurementMethod::Bucket)
        .value("Other", WaterReductionMeasurementMethod::Other);

    value_object<WaterReductionInput>("WaterReductionInput")
        .field("hoursPerYear", &WaterReductionInput::operating_hours)
        .field("waterCost", &WaterReductionInput::water_cost)
        .field("measurementMethod", &WaterReductionInput::measurement_method)
        .field("meteredFlowMethodData", &WaterReductionInput::metered_flow_method_data)
        .field("volumeMeterMethodData", &WaterReductionInput::volume_meter_method_data)
        .field("bucketMethodData", &WaterReductionInput::bucket_method_data)
        .field("otherMethodData", &WaterReductionInput::other_method_data);

    register_vector<WaterReductionInput>("WaterReductionInputV");

    value_object<WaterReductionOutput>("WaterReductionOutput")
        .field("waterUse", &WaterReductionOutput::water_use)
        .field("waterCost", &WaterReductionOutput::water_cost);

    // Bind calculation functions
    // waterReduction(input_vec: WaterReductionInputV) -> WaterReductionOutput
    //   input_vec: vector of WaterReductionInput structs
    //   returns: WaterReductionOutput struct with total water use and cost
    function("waterReduction", &waterReduction);

    // meteredFlowReduction(data: MeteredFlowMethodData, operating_hours: int, water_cost: double) -> WaterReductionOutput
    //   data: MeteredFlowMethodData struct
    //   operating_hours: number of operating hours
    //   water_cost: cost per unit of water
    //   returns: WaterReductionOutput struct
    function("meteredFlowReduction", &meteredFlowReduction);

    // volumeMeterReduction(data: VolumeMeterMethodData, operating_hours: int, water_cost: double) -> WaterReductionOutput
    //   data: VolumeMeterMethodData struct
    //   operating_hours: number of operating hours
    //   water_cost: cost per unit of water
    //   returns: WaterReductionOutput struct
    function("volumeMeterReduction", &volumeMeterReduction);

    // bucketReduction(data: BucketMethodData, operating_hours: int, water_cost: double) -> WaterReductionOutput
    //   data: BucketMethodData struct
    //   operating_hours: number of operating hours
    //   water_cost: cost per unit of water
    //   returns: WaterReductionOutput struct
    function("bucketReduction", &bucketReduction);

    // otherReduction(data: WaterOtherMethodData, operating_hours: int, water_cost: double) -> WaterReductionOutput
    //   data: WaterOtherMethodData struct
    //   operating_hours: number of operating hours
    //   water_cost: cost per unit of water
    //   returns: WaterReductionOutput struct
    function("otherReduction", &otherReduction);
}
