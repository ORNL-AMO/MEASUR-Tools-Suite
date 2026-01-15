
#include <vector>

/**
 * @ingroup water_reduction
 * @file water_reduction.h
 * @brief Functions to calculate water use and cost savings for water reduction measures.
 * @details Provides a function-based API for water reduction calculations.
 */

/**
 * @ingroup water_reduction
 * @namespace water_reduction
 * @brief Water reduction calculations for treasure hunt measures.
 */
namespace water_reduction {

/**
 * @struct MeteredFlowMethodData
 * @brief Input data for the metered flow method.
 */
struct MeteredFlowMethodData {
    double meter_reading = 0.0; ///< Meter reading value
};

/**
 * @struct VolumeMeterMethodData
 * @brief Input data for the volume meter method.
 */
struct VolumeMeterMethodData {
    double final_meter_reading = 0.0;
    double initial_meter_reading = 0.0;
    double elapsed_time = 0.0;
};

/**
 * @struct BucketMethodData
 * @brief Input data for the bucket method.
 */
struct BucketMethodData {
    double bucket_volume = 0.0;
    double bucket_fill_time = 0.0;
};

/**
 * @struct WaterOtherMethodData
 * @brief Input data for the "other" method.
 */
struct WaterOtherMethodData {
    double consumption = 0.0;
};

/**
 * @enum WaterReductionMeasurementMethod
 * @brief Measurement method for water reduction input.
 */
enum class WaterReductionMeasurementMethod {
    Metered = 0, ///< Metered flow method
    Volume = 1,  ///< Volume meter method
    Bucket = 2,  ///< Bucket method
    Other = 3    ///< Other method
};

/**
 * @struct WaterReductionInput
 * @brief Input data for a single water reduction measure.
 */
struct WaterReductionInput {
    int operating_hours = 0;
    double water_cost = 0.0;
    WaterReductionMeasurementMethod measurement_method = WaterReductionMeasurementMethod::Metered;
    MeteredFlowMethodData metered_flow_method_data;
    VolumeMeterMethodData volume_meter_method_data;
    BucketMethodData bucket_method_data;
    WaterOtherMethodData other_method_data;
};

/**
 * @struct WaterReductionOutput
 * @brief Output data for water reduction calculation.
 */
struct WaterReductionOutput {
    double water_use = 0.0;
    double water_cost = 0.0;
};

/**
 * @ingroup water_reduction
 * @brief Calculates water use and cost savings for a set of water reduction measures.
 * @param[in] input_vec Vector of WaterReductionInput structs.
 * @return WaterReductionOutput struct with calculated results.
 */
WaterReductionOutput waterReduction(const std::vector<WaterReductionInput>& input_vec);


/**
 * @brief Calculates water use and cost for the metered flow method.
 * @param[in] data MeteredFlowMethodData struct with input values.
 * @param[in] operating_hours Number of operating hours.
 * @param[in] water_cost Cost per unit of water.
 * @return WaterReductionOutput struct with calculated water use and cost.
 */
WaterReductionOutput meteredFlowReduction(const MeteredFlowMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the volume meter method.
 * @param[in] data VolumeMeterMethodData struct with input values.
 * @param[in] operating_hours Number of operating hours.
 * @param[in] water_cost Cost per unit of water.
 * @return WaterReductionOutput struct with calculated water use and cost.
 */
WaterReductionOutput volumeMeterReduction(const VolumeMeterMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the bucket method.
 * @param[in] data BucketMethodData struct with input values.
 * @param[in] operating_hours Number of operating hours.
 * @param[in] water_cost Cost per unit of water.
 * @return WaterReductionOutput struct with calculated water use and cost.
 */
WaterReductionOutput bucketReduction(const BucketMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the "other" method.
 * @param[in] data WaterOtherMethodData struct with input values.
 * @param[in] operating_hours Number of operating hours.
 * @param[in] water_cost Cost per unit of water.
 * @return WaterReductionOutput struct with calculated water use and cost.
 */
WaterReductionOutput otherReduction(const WaterOtherMethodData& data, int operating_hours, double water_cost);

} // namespace water_reduction

