
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
    double meter_reading = 0.0; ///< Meter reading value, gallons per minute (gal/min)
};

/**
 * @struct VolumeMeterMethodData
 * @brief Input data for the volume meter method.
 */
struct VolumeMeterMethodData {
    double final_meter_reading = 0.0; ///< Final meter reading, gallons (gal)
    double initial_meter_reading = 0.0; ///< Initial meter reading, gallons (gal)
    double elapsed_time = 0.0; ///< Elapsed time between readings, minutes (min)
};

/**
 * @struct BucketMethodData
 * @brief Input data for the bucket method.
 */
struct BucketMethodData {
    double bucket_volume = 0.0; ///< Volume of bucket, gallons (gal)
    double bucket_fill_time = 0.0; ///< Time to fill bucket, seconds (s)
};

/**
 * @struct WaterOtherMethodData
 * @brief Input data for the "other" method.
 */
struct WaterOtherMethodData {
    double consumption = 0.0; ///< Annual water consumption, gallons per year (gal/year)
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
    int operating_hours = 0; ///< Annual operating hours, hours per year (hours/year)
    double water_cost = 0.0; ///< Cost of water, dollars per gallon ($/gal)
    WaterReductionMeasurementMethod measurement_method = WaterReductionMeasurementMethod::Metered; ///< Selected measurement method
    MeteredFlowMethodData metered_flow_method_data; ///< Data for metered flow method
    VolumeMeterMethodData volume_meter_method_data; ///< Data for volume meter method
    BucketMethodData bucket_method_data; ///< Data for bucket method
    WaterOtherMethodData other_method_data; ///< Data for other method
};

/**
 * @struct WaterReductionOutput
 * @brief Output data for water reduction calculation.
 */
struct WaterReductionOutput {
    double water_use = 0.0; ///< Annual water use or savings, gallons per year (gal/year)
    double water_cost = 0.0; ///< Annual water cost or savings, dollars per year ($/year)
};

/**
 * @ingroup water_reduction
 * @brief Calculates water use and cost savings for a set of water reduction measures.
 * @param[in] input_vec Vector of WaterReductionInput structs containing measurement data for each water reduction measure.
 * @return WaterReductionOutput struct with calculated annual water use (gal/year) and cost ($/year).
 */
WaterReductionOutput waterReduction(const std::vector<WaterReductionInput>& input_vec);


/**
 * @brief Calculates water use and cost for the metered flow method.
 * @param[in] data MeteredFlowMethodData struct with meter reading in gallons per minute (gal/min).
 * @param[in] operating_hours Annual operating hours, hours per year (hours/year).
 * @param[in] water_cost Cost of water, dollars per gallon ($/gal).
 * @return WaterReductionOutput struct with calculated annual water use (gal/year) and cost ($/year).
 */
WaterReductionOutput meteredFlowReduction(const MeteredFlowMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the volume meter method.
 * @param[in] data VolumeMeterMethodData struct with initial and final meter readings in gallons (gal) and elapsed time in minutes (min).
 * @param[in] operating_hours Annual operating hours, hours per year (hours/year).
 * @param[in] water_cost Cost of water, dollars per gallon ($/gal).
 * @return WaterReductionOutput struct with calculated annual water use (gal/year) and cost ($/year).
 */
WaterReductionOutput volumeMeterReduction(const VolumeMeterMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the bucket method.
 * @param[in] data BucketMethodData struct with bucket volume in gallons (gal) and fill time in seconds (s).
 * @param[in] operating_hours Annual operating hours, hours per year (hours/year).
 * @param[in] water_cost Cost of water, dollars per gallon ($/gal).
 * @return WaterReductionOutput struct with calculated annual water use (gal/year) and cost ($/year).
 */
WaterReductionOutput bucketReduction(const BucketMethodData& data, int operating_hours, double water_cost);

/**
 * @brief Calculates water use and cost for the "other" method.
 * @param[in] data WaterOtherMethodData struct with annual water consumption in gallons per year (gal/year).
 * @param[in] operating_hours Annual operating hours (unitless - not used in this method).
 * @param[in] water_cost Cost of water, dollars per gallon ($/gal).
 * @return WaterReductionOutput struct with calculated annual water use (gal/year) and cost ($/year).
 */
WaterReductionOutput otherReduction(const WaterOtherMethodData& data, int operating_hours, double water_cost);

} // namespace water_reduction

