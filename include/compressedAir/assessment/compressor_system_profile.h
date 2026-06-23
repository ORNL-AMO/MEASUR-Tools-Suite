#pragma once

/**
 * @ingroup compressor_system_profile_assessment
 * @file compressor_system_profile.h
 * @brief Compressor assessment system-profile calculation declarations.
 */

#include <string>
#include <vector>

#include "compressedAir/assessment/compressor.h"
#include "compressedAir/assessment/compressor_performance_points.h"

namespace compressed_air::assessment {

/**
 * @enum CompressorSystemControlMode
 * @brief Multi-compressor system allocation strategy.
 */
enum class CompressorSystemControlMode {
    Cascading               = 0, ///< Use existing compressor operating order.
    IsentropicEfficiency    = 1, ///< Use existing order from isentropic efficiency ranking.
    LoadSharing             = 2, ///< Select equal-load compressor combination with least power.
    TargetPressureSequencer = 3, ///< Use sequencer-adjusted existing order.
    BaseTrim                = 4  ///< Select base compressors around a trim compressor.
};

/**
 * @struct CompressorProfileCompressor
 * @brief Compressor definition used by system-profile calculations.
 */
struct CompressorProfileCompressor {
    std::string                 compressorId; ///< Stable compressor identifier.
    CompressorType              compressorType = CompressorType::Screw; ///< Compressor type.
    CompressorControl           control        = CompressorControl::LoadUnload; ///< Control strategy.
    CompressorStage             stage          = CompressorStage::Single; ///< Compressor stage.
    CompressorLubricant         lubricant      = CompressorLubricant::Injected; ///< Lubricant type.
    bool                        automaticShutdown = false; ///< True when automatic shutdown is enabled.
    CompressorPerformancePoints performancePoints; ///< Compressor performance points.
    double                      blowdownTimeSec = 0.003; ///< Blowdown time @unitb{\second}.
    double                      unloadSumpPressurePsig = 15.0; ///< Unload sump pressure @unitb{\psig}.
    double                      noLoadPowerFractionForModulation = 0.7; ///< Modulation floor fraction @unitb{\unitless}.
    double                      modulatingPressurePsig = 0.0; ///< Modulating pressure range @unitb{\psig}.
};

/**
 * @struct CompressorProfileRow
 * @brief One compressor interval row in an assessment system profile.
 */
struct CompressorProfileRow {
    std::string compressorId; ///< Stable compressor identifier.
    std::string dayTypeId; ///< Stable day-type identifier.
    double      timeIntervalHr = 0.0; ///< Interval start time @unitb{\hour}.
    int         operatingOrder = 0; ///< Compressor operating order; zero means off @unitb{\unitless}.
    double      powerKw = 0.0; ///< Compressor package power @unitb{\kilo\watt}.
    double      airflowAcfm = 0.0; ///< Compressor airflow @unitb{\acfm}.
    double      powerFraction = 0.0; ///< Fraction of full-load compressor power @unitb{\unitless}.
    double      airflowFraction = 0.0; ///< Fraction of full-load compressor airflow @unitb{\unitless}.
    double      systemPowerFraction = 0.0; ///< Fraction of total system full-load power @unitb{\unitless}.
    double      systemAirflowFraction = 0.0; ///< Fraction of total system full-load airflow @unitb{\unitless}.
    double      powerFactor = 0.0; ///< Electrical power factor @unitb{\unitless}.
    double      amps = 0.0; ///< Electrical current @unitb{\ampere}.
    double      volts = 0.0; ///< Electrical voltage @unitb{\volt}.
};

/**
 * @struct CompressorProfileTotal
 * @brief Total system demand row used by profile reallocation.
 */
struct CompressorProfileTotal {
    std::string dayTypeId; ///< Stable day-type identifier.
    double      timeIntervalHr = 0.0; ///< Interval start time @unitb{\hour}.
    double      airflowAcfm = 0.0; ///< Total system airflow @unitb{\acfm}.
    double      powerKw = 0.0; ///< Total compressor power @unitb{\kilo\watt}.
    double      totalPowerKw = 0.0; ///< Total power including auxiliary power @unitb{\kilo\watt}.
    double      airflowFraction = 0.0; ///< Fraction of total system full-load airflow @unitb{\unitless}.
    double      powerFraction = 0.0; ///< Fraction of total system full-load power @unitb{\unitless}.
    double      auxiliaryPowerKw = 0.0; ///< Auxiliary equipment power @unitb{\kilo\watt}.
};

/**
 * @struct CompressorRuntimeState
 * @brief Optional reduce-runtime on/off state for one compressor interval.
 */
struct CompressorRuntimeState {
    std::string compressorId; ///< Stable compressor identifier.
    std::string dayTypeId; ///< Stable day-type identifier.
    double      timeIntervalHr = 0.0; ///< Interval start time @unitb{\hour}.
    bool        isCompressorOn = true; ///< True when the compressor is available to run.
    bool        automaticShutdownTimer = false; ///< True when automatic shutdown should be applied.
};

/**
 * @struct CompressorTrimSelection
 * @brief Optional base-trim compressor selection for one day type.
 */
struct CompressorTrimSelection {
    std::string dayTypeId; ///< Stable day-type identifier.
    std::string compressorId; ///< Selected trim compressor identifier.
};

/**
 * @struct CompressorProfileOptions
 * @brief Shared options for profile calculations.
 */
struct CompressorProfileOptions {
    std::string                 dayTypeId; ///< Day type to calculate.
    CompressorInputBasis        inputBasis = CompressorInputBasis::MeasuredCapacity; ///< Profile input basis.
    CompressorSystemControlMode controlMode = CompressorSystemControlMode::Cascading; ///< System allocation mode.
    double                      atmosphericPressurePsia = 14.7; ///< Atmospheric pressure @unitb{\psia}.
    double                      totalAirStorageFt3 = 0.0; ///< Existing air storage @unitb{\cubicFoot}.
    double                      additionalReceiverVolumeFt3 = 0.0; ///< Added receiver volume @unitb{\cubicFoot}.
    bool                        canShutdown = true; ///< True when zero-flow capacity inputs may shut down.
};

/**
 * @struct CompressorProfileSavingsInput
 * @brief Savings input for one day type.
 */
struct CompressorProfileSavingsInput {
    std::string dayTypeId; ///< Stable day-type identifier.
    double      electricityCostPerKwh = 0.0; ///< Electricity cost @unitb{\dollar\per\kilo\watt\hour}.
    double      intervalHours = 1.0; ///< Profile interval duration @unitb{\hour}.
    double      operatingDays = 0.0; ///< Annual operating days @unitb{\day}.
    double      auxiliaryEnergyKwh = 0.0; ///< Added auxiliary energy @unitb{\kilo\watt\hour}.
    double      implementationCost = 0.0; ///< Implementation cost @unitb{\dollar}.
    double      salvageValue = 0.0; ///< Salvage value @unitb{\dollar}.
};

/**
 * @struct CompressorProfileSavingsResult
 * @brief Energy, cost, savings, and payback result for one day type.
 */
struct CompressorProfileSavingsResult {
    double baselineEnergyKwh = 0.0; ///< Baseline annual energy @unitb{\kilo\watt\hour}.
    double baselineCost = 0.0; ///< Baseline annual cost @unitb{\dollar}.
    double adjustedEnergyKwh = 0.0; ///< Adjusted annual energy @unitb{\kilo\watt\hour}.
    double adjustedCost = 0.0; ///< Adjusted annual cost @unitb{\dollar}.
    double energySavingsKwh = 0.0; ///< Annual energy savings @unitb{\kilo\watt\hour}.
    double costSavings = 0.0; ///< Annual cost savings @unitb{\dollar}.
    double percentSavings = 0.0; ///< Cost savings @unitb{\percent}.
    double implementationCost = 0.0; ///< Implementation cost @unitb{\dollar}.
    double salvageValue = 0.0; ///< Salvage value @unitb{\dollar}.
    double paybackMonths = 0.0; ///< Simple payback @unitb{\month}.
};

using CompressorProfileCompressorV = std::vector<CompressorProfileCompressor>;
using CompressorProfileRowV        = std::vector<CompressorProfileRow>;
using CompressorProfileTotalV      = std::vector<CompressorProfileTotal>;
using CompressorRuntimeStateV      = std::vector<CompressorRuntimeState>;
using CompressorTrimSelectionV     = std::vector<CompressorTrimSelection>;

CompressorProfileRowV calculateBaselineProfile(const CompressorProfileCompressorV& compressors,
                                               const CompressorProfileRowV& profile_rows,
                                               const CompressorProfileOptions& options);
CompressorProfileTotalV calculateProfileTotals(const CompressorProfileCompressorV& compressors,
                                               const CompressorProfileRowV& profile_rows,
                                               double interval_hours);
CompressorProfileRowV reallocateProfileFlow(const CompressorProfileCompressorV& compressors,
                                             const CompressorProfileRowV& previous_profile_rows,
                                             const CompressorProfileTotalV& demand_rows,
                                             const CompressorProfileOptions& options,
                                             const CompressorRuntimeStateV& runtime_states = {},
                                             const CompressorTrimSelectionV& trim_selections = {});
CompressorProfileSavingsResult calculateProfileSavings(const CompressorProfileRowV& baseline_rows,
                                                       const CompressorProfileRowV& adjusted_rows,
                                                       const CompressorProfileSavingsInput& input);
CompressorProfileRow calculateCompressorProfileRow(const CompressorProfileCompressor& compressor,
                                                   CompressorInputBasis input_basis, double input_value,
                                                   const CompressorProfileOptions& options,
                                                   double power_factor = 0.0, double amps = 0.0,
                                                   double volts = 0.0);
double calculatePressureReducedAirflow(double use_airflow_acfm, double adjusted_full_load_pressure_psig,
                                       double altitude_pressure_psia,
                                       double original_full_load_pressure_psig);

} // namespace compressed_air::assessment
