
#include "treasureHunt/water_reduction.h"

#include <cmath>

namespace water_reduction {
    
WaterReductionOutput waterReduction(const std::vector<WaterReductionInput>& input_vec) {
    double water_use = 0.0, water_cost = 0.0;
    for (const auto& input : input_vec) {
        WaterReductionOutput tmp_output;
        switch (input.measurement_method) {
            case WaterReductionMeasurementMethod::Metered: {
                // Metered flow method: uses meter reading, operating hours, and water cost.
                tmp_output = meteredFlowReduction(input.metered_flow_method_data, input.operating_hours, input.water_cost);
                break;
            }
            case WaterReductionMeasurementMethod::Volume: {
                // Volume meter method: uses initial/final readings, elapsed time, operating hours, and water cost.
                tmp_output = volumeMeterReduction(input.volume_meter_method_data, input.operating_hours, input.water_cost);
                break;
            }
            case WaterReductionMeasurementMethod::Bucket: {
                // Bucket method: uses bucket volume, fill time, operating hours, and water cost.
                tmp_output = bucketReduction(input.bucket_method_data, input.operating_hours, input.water_cost);
                break;
            }
            case WaterReductionMeasurementMethod::Other:
            default: {
                // Other method: uses direct consumption value and water cost.
                tmp_output = otherReduction(input.other_method_data, input.operating_hours, input.water_cost);
                break;
            }
        }
        water_use += tmp_output.water_use;
        water_cost += tmp_output.water_cost;
    }
    return WaterReductionOutput {water_use, water_cost};
}

WaterReductionOutput meteredFlowReduction(const MeteredFlowMethodData& metered_data, int operating_hours,
                                          double water_cost) {
    double tmp_water_use  = metered_data.meter_reading * 60.0 * operating_hours;
    double tmp_water_cost = water_cost * tmp_water_use;
    return WaterReductionOutput {tmp_water_use, tmp_water_cost};
}

WaterReductionOutput volumeMeterReduction(const VolumeMeterMethodData& volume_data, int operating_hours,
                                          double water_cost) {
    if (volume_data.elapsed_time <= 0.0) {
        return WaterReductionOutput {0.0, 0.0};
    }

    double tmp_water_use = ((volume_data.final_meter_reading - volume_data.initial_meter_reading) /
                            (volume_data.elapsed_time * (1.0 / 60.0))) *
                           operating_hours;
    double tmp_water_cost = water_cost * tmp_water_use;
    return WaterReductionOutput {tmp_water_use, tmp_water_cost};
}

WaterReductionOutput bucketReduction(const BucketMethodData& bucket_data, int operating_hours, double water_cost) {
    if (bucket_data.bucket_fill_time <= 0.0) {
        return WaterReductionOutput {0.0, 0.0};
    }

    double tmp_water_use =
        (bucket_data.bucket_volume / (bucket_data.bucket_fill_time * (1.0 / 3600.0))) * operating_hours;
    double tmp_water_cost = water_cost * tmp_water_use;
    return WaterReductionOutput {tmp_water_use, tmp_water_cost};
}

WaterReductionOutput otherReduction(const WaterOtherMethodData& other_data, int, double water_cost) {
    double tmp_water_use  = other_data.consumption;
    double tmp_water_cost = water_cost * tmp_water_use;
    return WaterReductionOutput {tmp_water_use, tmp_water_cost};
}

} // namespace water_reduction