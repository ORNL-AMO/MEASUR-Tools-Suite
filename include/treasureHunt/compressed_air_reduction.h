#pragma once

#include <vector>

#include "compressedAir/compressed_air_utils.h"

/**
 * @ingroup compressed_air_reduction_calculator
 * @file compressed_air_reduction.h
 * @brief Declares structs, enums, and functions for the Compressed Air Reduction Calculator.
 * @copybrief compressed_air_reduction_calculator
 */

/**
 * @ingroup compressed_air_reduction_calculator
 * @namespace compressed_air_reduction
 * @brief Compressed air reduction calculations for treasure hunt measures.
 * @details Provides a function-based API for estimating annual compressed air consumption,
 * energy use, and cost savings for compressed air reduction measures identified during an
 * energy treasure hunt or efficiency assessment. Supports four measurement methods:
 * flow meter, bag method, orifice/pressure method, and other. Two utility types are supported:
 * compressed air (cost per unit volume) and electricity (cost per kilowatt-hour, derived via
 * compressor specific power).
 * @see compressed_air_reduction_calculator
 */
namespace compressed_air_reduction {

using compressed_air_utils::CompressorElectricityData;

/**
 * @ingroup compressed_air_reduction_calculator
 * @enum MeasurementMethod
 * @brief Selects the measurement method used to determine compressed air consumption for a single measure.
 * @see compressed_air_reduction_calculator
 */
enum class MeasurementMethod {
    FlowMeter = 0, ///< Flow meter method — reads flow rate directly from an installed flow meter
    Bag       = 1, ///< Bag method — estimates flow rate by timing how long it takes to fill a known-volume bag
    Pressure  = 2, ///< Orifice/pressure method — calculates flow rate from nozzle type and supply pressure
    Other     = 3  ///< Other method — uses a directly supplied annual consumption value
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @enum UtilityType
 * @brief Selects the utility type used to compute annual energy cost.
 * @details For compressed air utility, cost is calculated directly from consumption and a cost
 * per unit volume. For electricity, consumption is first converted to electrical energy use via
 * the compressor specific power, then multiplied by the electricity cost rate.
 * @see compressed_air_reduction_calculator
 */
enum class UtilityType {
    CompressedAir = 0, ///< Compressed air utility — cost based on air consumption @unitb{\dollar\per\cubic\foot}
    Electricity   = 1  ///< Electricity utility — cost based on compressor electricity draw @unitb{\dollar\per\kilo\watt\hour}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct FlowMeterMethodData
 * @brief Input data for the flow meter measurement method.
 * @details Used when compressed air flow is measured directly by an installed flow meter.
 * The meter reading is the instantaneous flow rate; annual consumption is derived by multiplying
 * by annual operating time and the units multiplier.
 * @see compressed_air_reduction_flow_meter_formula
 */
struct FlowMeterMethodData {
    double meter_reading = 0.0; ///< Instantaneous flow rate from the installed meter @unitb{\cubic\foot\per\minute}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct BagMethodData
 * @brief Input data for the bag measurement method.
 * @details The bag method estimates compressed air flow rate by measuring how long it takes to
 * fill a known-volume bag. The bag volume divided by the fill time (converted to minutes) gives
 * the flow rate in scfm.
 * @see compressed_air_reduction_bag_formula
 */
struct BagMethodData {
    double bag_fill_time  = 0.0; ///< Time to fill the bag with compressed air @unitb{\second}
    double bag_volume     = 0.0; ///< Internal volume of the bag @unitb{\cubic\foot}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct PressureMethodData
 * @brief Input data for the orifice/pressure measurement method.
 * @details Used when compressed air flow rate is estimated from the nozzle type and supply
 * pressure using a quadratic equation with pre-calibrated nozzle coefficients. Thirteen nozzle
 * types are supported (indices 0–12), each with a distinct set of coefficients fitted to
 * empirical flow-versus-pressure data. The units multiplier from the outer input is not applied
 * in this method.
 * @see compressed_air_reduction_pressure_formula
 */
struct PressureMethodData {
    int    nozzle_type       = 0;   ///< Nozzle type index (0–12) used to select lookup table coefficients
    int    number_of_nozzles = 1;   ///< Number of nozzles in the system
    double supply_pressure   = 0.0; ///< Compressed air supply pressure @unitb{\psi}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct OtherMethodData
 * @brief Input data for the other (direct consumption) measurement method.
 * @details Used when the annual compressed air consumption is already known from utility records,
 * an audit report, or another source, and no flow-rate measurement is available.
 */
struct OtherMethodData {
    double consumption = 0.0; ///< Annual compressed air consumption @unitb{\cubic\foot\per\year}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct CompressedAirReductionInput
 * @brief Input data for a single compressed air reduction measure.
 * @details Aggregates all parameters needed to evaluate one measure. The active measurement
 * method is selected via @ref MeasurementMethod; only the corresponding method data struct is
 * used in the calculation. The @p units field is a quantity multiplier (e.g., number of identical
 * leak points or equipment pieces). Note: @p units is not applied by the pressure method.
 */
struct CompressedAirReductionInput {
    int               hours_per_year             = 0;                            ///< Annual operating hours @unitb{\hour\per\year}
    UtilityType       utility_type               = UtilityType::CompressedAir;   ///< Utility type for cost calculation
    double            utility_cost               = 0.0;                          ///< Utility cost rate @unitb{\dollar\per\unit}
    MeasurementMethod measurement_method         = MeasurementMethod::FlowMeter; ///< Measurement method to apply
    FlowMeterMethodData       flow_meter_method_data;                            ///< Data for the flow meter method
    BagMethodData             bag_method_data;                                   ///< Data for the bag method
    PressureMethodData        pressure_method_data;                              ///< Data for the orifice/pressure method
    OtherMethodData           other_method_data;                                 ///< Data for the other method
    CompressorElectricityData compressor_electricity_data;                       ///< Data for the electricity utility calculation
    int               units                      = 1;                            ///< Quantity multiplier (not applied to pressure method)
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @struct CompressedAirReductionOutput
 * @brief Output data for a compressed air reduction calculation.
 * @details Contains the accumulated annual energy use, annual energy cost, total flow rate,
 * per-nozzle flow rate (pressure method only), and total consumption across all measures
 * passed to @ref compressedAirReduction.
 */
struct CompressedAirReductionOutput {
    double energy_use              = 0.0; ///< Annual electrical energy use @unitb{\kilo\watt\hour\per\year}
    double energy_cost             = 0.0; ///< Annual energy cost @unitb{\dollar\per\year}
    double flow_rate               = 0.0; ///< Total compressed air flow rate @unitb{\cubic\foot\per\minute}
    double single_nozzle_flow_rate = 0.0; ///< Flow rate per individual nozzle (pressure method only) @unitb{\cubic\foot\per\minute}
    double consumption             = 0.0; ///< Annual compressed air consumption @unitb{\cubic\foot\per\year}
};

/**
 * @ingroup compressed_air_reduction_calculator
 * @brief Calculates total annual compressed air consumption, energy use, and cost for a collection of measures.
 * @details Iterates over @p input_vec, dispatches each measure to the appropriate single-method
 * helper (flow meter, bag, pressure, or other), applies the utility-type cost calculation, and
 * accumulates the results.
 * @see compressed_air_reduction_calculator
 *
 * @param[in] input_vec  Vector of @ref CompressedAirReductionInput structs, one per measure.
 * @return @ref CompressedAirReductionOutput with summed annual energy use
 *         @unitb{\kilo\watt\hour\per\year}, annual energy cost @unitb{\dollar\per\year},
 *         total flow rate @unitb{\cubic\foot\per\minute}, single-nozzle flow rate
 *         @unitb{\cubic\foot\per\minute}, and total consumption @unitb{\cubic\foot\per\year}.
 */
CompressedAirReductionOutput compressedAirReduction(const std::vector<CompressedAirReductionInput>& input_vec);

/**
 * @ingroup compressed_air_reduction_calculator
 * @brief Calculates annual compressed air consumption and flow rate using the flow meter method.
 * @details Computes annual consumption as the product of the meter reading, annual operating hours,
 * units multiplier, and a factor of 60 to convert from per-minute to per-hour.
 * Energy use and energy cost are zero; call @ref compressedAirReduction for a full result.
 * @see compressed_air_reduction_flow_meter_formula
 *
 * @param[in] data           @ref FlowMeterMethodData with the flow meter reading @unitb{\cubic\foot\per\minute}.
 * @param[in] hours_per_year Annual operating hours @unitb{\hour\per\year}.
 * @param[in] units          Quantity multiplier (number of identical measures).
 * @return @ref CompressedAirReductionOutput with flow rate and consumption populated;
 *         energy use and energy cost are zero.
 */
CompressedAirReductionOutput flowMeterReduction(const FlowMeterMethodData& data, int hours_per_year, int units);

/**
 * @ingroup compressed_air_reduction_calculator
 * @brief Calculates annual compressed air consumption and flow rate using the bag method.
 * @details Flow rate is derived from the bag volume and fill time. Annual consumption is computed
 * from the flow rate, annual operating hours, and both quantity multipliers (bags and units).
 * Energy use and energy cost are zero; call @ref compressedAirReduction for a full result.
 * @see compressed_air_reduction_bag_formula
 *
 * @param[in] data           @ref BagMethodData with bag geometry, fill time, and number of bags.
 * @param[in] hours_per_year Annual operating hours @unitb{\hour\per\year}.
 * @param[in] units          Outer quantity multiplier (number of identical leak points or equipment pieces).
 * @return @ref CompressedAirReductionOutput with flow rate and consumption populated;
 *         energy use and energy cost are zero.
 */
CompressedAirReductionOutput bagMethodReduction(const BagMethodData& data, int hours_per_year, int units);

/**
 * @ingroup compressed_air_reduction_calculator
 * @brief Calculates annual compressed air consumption and flow rate using the orifice/pressure method.
 * @details Single-nozzle flow rate is computed from a quadratic function of supply pressure using
 * pre-calibrated coefficients for the selected nozzle type. Total flow rate scales with the number
 * of nozzles. The outer units multiplier is not applied in this method.
 * Energy use and energy cost are zero; call @ref compressedAirReduction for a full result.
 * @see compressed_air_reduction_pressure_formula
 *
 * @param[in] data           @ref PressureMethodData with nozzle type, number of nozzles, and
 *                           supply pressure @unitb{\psi}.
 * @param[in] hours_per_year Annual operating hours @unitb{\hour\per\year}.
 * @return @ref CompressedAirReductionOutput with flow rates and consumption populated;
 *         energy use and energy cost are zero.
 */
CompressedAirReductionOutput pressureMethodReduction(const PressureMethodData& data, int hours_per_year);

/**
 * @ingroup compressed_air_reduction_calculator
 * @brief Returns a partial result with consumption set from a directly supplied value.
 * @details No flow-rate or energy calculation is performed. The supplied consumption value is
 * used directly as the annual compressed air consumption.
 * Energy use, energy cost, and flow rate are zero; call @ref compressedAirReduction for a full result.
 *
 * @param[in] data  @ref OtherMethodData with the annual consumption @unitb{\cubic\foot\per\year}.
 * @return @ref CompressedAirReductionOutput with consumption populated; all other fields are zero.
 */
CompressedAirReductionOutput otherMethodReduction(const OtherMethodData& data);

} // namespace compressed_air_reduction
