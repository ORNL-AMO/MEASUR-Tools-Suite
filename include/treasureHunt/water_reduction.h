
#include <vector>

/**
 * @ingroup water_reduction_calculator
 * @file water_reduction.h
 * @brief Declares structs, enums, and functions for the Water Reduction Calculator.
 * @copybrief water_reduction_calculator
 */

/**
 * @ingroup water_reduction_calculator
 * @namespace water_reduction
 * @brief Water reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual water use and cost savings
 * for water reduction measures identified during an energy treasure hunt or water efficiency
 * assessment. Supports four measurement methods: metered flow, volume meter, bucket, and other.
 * @see water_reduction_calculator
 */
namespace water_reduction {

/**
 * @ingroup water_reduction_calculator
 * @struct MeteredFlowMethodData
 * @brief Input data for the metered flow measurement method.
 * @details Used when water use is measured with a continuous flow meter. The meter reading
 * is combined with operating hours to calculate annual water use.
 * @see water_reduction_metered_flow_formula
 */
struct MeteredFlowMethodData {
    double meter_reading = 0.0; ///< Instantaneous flow rate from the meter @unitb{\gallon\per\minute}
};

/**
 * @ingroup water_reduction_calculator
 * @struct VolumeMeterMethodData
 * @brief Input data for the volume meter measurement method.
 * @details Used when water use is measured by recording initial and final readings of a totalizing
 * water meter over a timed interval. The change in reading divided by elapsed time gives the average
 * flow rate.
 * @see water_reduction_volume_meter_formula
 */
struct VolumeMeterMethodData {
    double final_meter_reading   = 0.0; ///< Final meter reading at end of measurement interval @unitb{\gallon}
    double initial_meter_reading = 0.0; ///< Initial meter reading at start of measurement interval @unitb{\gallon}
    double elapsed_time          = 0.0; ///< Duration of the measurement interval @unitb{\minute}
};

/**
 * @ingroup water_reduction_calculator
 * @struct BucketMethodData
 * @brief Input data for the bucket measurement method.
 * @details Used when water use is measured by timing how long it takes to fill a container of known
 * volume. The bucket volume divided by the fill time gives the flow rate.
 * @see water_reduction_bucket_formula
 */
struct BucketMethodData {
    double bucket_volume    = 0.0; ///< Volume of the bucket used for the measurement @unitb{\gallon}
    double bucket_fill_time = 0.0; ///< Time required to fill the bucket @unitb{\second}
};

/**
 * @ingroup water_reduction_calculator
 * @struct WaterOtherMethodData
 * @brief Input data for the other (direct consumption) measurement method.
 * @details Used when annual water consumption is known directly from a report, bill, or other source
 * without requiring a flow-rate conversion.
 * @see water_reduction_other_formula
 */
struct WaterOtherMethodData {
    double consumption = 0.0; ///< Annual water consumption @unitb{\gallon\per\year}
};

/**
 * @ingroup water_reduction_calculator
 * @enum WaterReductionMeasurementMethod
 * @brief Selects the measurement method used to determine water use for a single measure.
 * @see water_reduction_calculator
 */
enum class WaterReductionMeasurementMethod {
    Metered = 0, ///< Metered flow method — uses an instantaneous flow meter reading
    Volume  = 1, ///< Volume meter method — uses initial/final totalizing meter readings over a timed interval
    Bucket  = 2, ///< Bucket method — uses the time required to fill a container of known volume
    Other   = 3  ///< Other method — uses a directly supplied annual consumption value
};

/**
 * @ingroup water_reduction_calculator
 * @struct WaterReductionInput
 * @brief Input data for a single water reduction measure.
 * @details Aggregates all parameters needed to evaluate one measure. The active measurement method
 * is selected via @ref WaterReductionMeasurementMethod; only the corresponding method data struct is
 * used in the calculation.
 */
struct WaterReductionInput {
    int    operating_hours     = 0;                                          ///< Annual operating hours @unitb{\hour\per\year}
    double water_cost          = 0.0;                                        ///< Water cost rate @unitb{\dollar\per\gallon}
    WaterReductionMeasurementMethod measurement_method = WaterReductionMeasurementMethod::Metered; ///< Measurement method to apply
    MeteredFlowMethodData metered_flow_method_data;                          ///< Data for the metered flow method
    VolumeMeterMethodData volume_meter_method_data;                          ///< Data for the volume meter method
    BucketMethodData      bucket_method_data;                                ///< Data for the bucket method
    WaterOtherMethodData  other_method_data;                                 ///< Data for the other method
};

/**
 * @ingroup water_reduction_calculator
 * @struct WaterReductionOutput
 * @brief Output data for a water reduction calculation.
 * @details Contains the accumulated annual water use and annual water cost across all measures passed
 * to @ref waterReduction, or the individual result from a single-method helper function.
 */
struct WaterReductionOutput {
    double water_use  = 0.0; ///< Annual water use @unitb{\gallon\per\year}
    double water_cost = 0.0; ///< Annual water cost @unitb{\dollar\per\year}
};

/**
 * @ingroup water_reduction_calculator
 * @brief Calculates total annual water use and cost for a collection of water reduction measures.
 * @details Iterates over @p input_vec, dispatches each measure to the appropriate single-method
 * helper (metered flow, volume meter, bucket, or other), and accumulates the results.
 * @see water_reduction_calculator
 * @see water_reduction_water_cost_formula
 *
 * @param[in] input_vec  Vector of @ref WaterReductionInput structs, one per measure.
 * @return @ref WaterReductionOutput with the summed annual water use @unitb{\gallon\per\year}
 *         and annual water cost @unitb{\dollar\per\year} across all measures.
 */
WaterReductionOutput waterReduction(const std::vector<WaterReductionInput>& input_vec);

/**
 * @ingroup water_reduction_calculator
 * @brief Calculates annual water use and cost using the metered flow method.
 * @details Multiplies the meter reading by 60 (to convert gal/min to gal/hr) and by the annual
 * operating hours to obtain annual water use. Water cost is then derived using
 * @ref water_reduction_water_cost_formula.
 * @see water_reduction_metered_flow_formula
 *
 * @param[in] data            @ref MeteredFlowMethodData with the meter reading @unitb{\gallon\per\minute}.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] water_cost      Water cost rate @unitb{\dollar\per\gallon}.
 * @return @ref WaterReductionOutput with annual water use @unitb{\gallon\per\year}
 *         and annual water cost @unitb{\dollar\per\year}.
 */
WaterReductionOutput meteredFlowReduction(const MeteredFlowMethodData& data, int operating_hours, double water_cost);

/**
 * @ingroup water_reduction_calculator
 * @brief Calculates annual water use and cost using the volume meter method.
 * @details Computes the average flow rate from the change in meter reading over the elapsed time,
 * then scales to annual use by multiplying by the operating hours. Water cost is then derived using
 * @ref water_reduction_water_cost_formula.
 * @see water_reduction_volume_meter_formula
 *
 * @param[in] data            @ref VolumeMeterMethodData with initial/final meter readings @unitb{\gallon}
 *                            and elapsed time @unitb{\minute}.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] water_cost      Water cost rate @unitb{\dollar\per\gallon}.
 * @return @ref WaterReductionOutput with annual water use @unitb{\gallon\per\year}
 *         and annual water cost @unitb{\dollar\per\year}.
 */
WaterReductionOutput volumeMeterReduction(const VolumeMeterMethodData& data, int operating_hours, double water_cost);

/**
 * @ingroup water_reduction_calculator
 * @brief Calculates annual water use and cost using the bucket measurement method.
 * @details Computes the flow rate by dividing the bucket volume by the fill time (converted to hours),
 * then scales to annual use by multiplying by the operating hours. Water cost is then derived using
 * @ref water_reduction_water_cost_formula.
 * @see water_reduction_bucket_formula
 *
 * @param[in] data            @ref BucketMethodData with bucket volume @unitb{\gallon}
 *                            and fill time @unitb{\second}.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year}.
 * @param[in] water_cost      Water cost rate @unitb{\dollar\per\gallon}.
 * @return @ref WaterReductionOutput with annual water use @unitb{\gallon\per\year}
 *         and annual water cost @unitb{\dollar\per\year}.
 */
WaterReductionOutput bucketReduction(const BucketMethodData& data, int operating_hours, double water_cost);

/**
 * @ingroup water_reduction_calculator
 * @brief Calculates annual water use and cost using a directly supplied consumption value.
 * @details Uses the consumption field directly as the annual water use without any flow-rate
 * conversion. Water cost is then derived using @ref water_reduction_water_cost_formula.
 * @see water_reduction_other_formula
 *
 * @param[in] data            @ref WaterOtherMethodData with the annual water consumption @unitb{\gallon\per\year}.
 * @param[in] operating_hours Annual operating hours @unitb{\hour\per\year} (not used in the water-use
 *                            calculation for this method, retained for API consistency).
 * @param[in] water_cost      Water cost rate @unitb{\dollar\per\gallon}.
 * @return @ref WaterReductionOutput with annual water use @unitb{\gallon\per\year}
 *         and annual water cost @unitb{\dollar\per\year}.
 */
WaterReductionOutput otherReduction(const WaterOtherMethodData& data, int operating_hours, double water_cost);

} // namespace water_reduction

