#pragma once

/**
 * @ingroup compressor_performance_points_assessment
 * @file compressor_performance_points.h
 * @brief Compressor assessment performance-point generation declarations.
 */

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @struct CompressorPerformancePoint
 * @brief One compressor performance point used by assessment profile calculations.
 */
struct CompressorPerformancePoint {
    double dischargePressurePsig = 0.0; ///< Discharge pressure @unitb{\psig}.
    bool   isDefaultPressure     = true; ///< True when pressure should be calculated from defaults.
    double airflowAcfm           = 0.0; ///< Airflow @unitb{\acfm}.
    bool   isDefaultAirflow      = true; ///< True when airflow should be calculated from defaults.
    double powerKw               = 0.0; ///< Package power @unitb{\kilo\watt}.
    bool   isDefaultPower        = true; ///< True when power should be calculated from defaults.
};

/**
 * @struct CompressorPerformancePoints
 * @brief Set of compressor performance points used by the assessment workflow.
 */
struct CompressorPerformancePoints {
    CompressorPerformancePoint fullLoad;    ///< Full-load point.
    CompressorPerformancePoint maxFullFlow; ///< Maximum full-flow point.
    CompressorPerformancePoint midTurndown; ///< VFD mid-turndown point.
    CompressorPerformancePoint turndown;    ///< VFD turndown point.
    CompressorPerformancePoint unloadPoint; ///< Unload point.
    CompressorPerformancePoint noLoad;      ///< No-load point.
    CompressorPerformancePoint blowoff;     ///< Blow-off point.
};

/**
 * @struct CompressorNameplateData
 * @brief Nameplate and rated compressor data needed to generate assessment performance points.
 */
struct CompressorNameplateData {
    CompressorType      compressorType                 = CompressorType::Screw; ///< Compressor type.
    CompressorStage     stage                          = CompressorStage::Single; ///< Compressor stage.
    CompressorLubricant lubricant                      = CompressorLubricant::Injected; ///< Lubricant type.
    double              motorPowerHp                   = 0.0; ///< Motor size @unitb{\hp}.
    double              fullLoadOperatingPressurePsig  = 0.0; ///< Rated full-load pressure @unitb{\psig}.
    double              fullLoadRatedCapacityAcfm      = 0.0; ///< Rated full-load capacity @unitb{\acfm}.
    double              ratedLoadPowerKw               = 0.0; ///< Rated load power @unitb{\kilo\watt}.
    double              polytropicCompressorExponent   = 1.4; ///< Polytropic compressor exponent @unitb{\unitless}.
    double              fullLoadAmps                   = 0.0; ///< Full-load current @unitb{\ampere}.
    double              totalPackageInputPowerKw       = 0.0; ///< Full-load package input power @unitb{\kilo\watt}.
};

/**
 * @struct CompressorControlsData
 * @brief Compressor control settings needed to generate assessment performance points.
 */
struct CompressorControlsData {
    CompressorControl control                = CompressorControl::LoadUnload; ///< Compressor control strategy.
    double            unloadPointCapacityPct = 100.0; ///< Unload/turndown capacity @unitb{\percent}.
    int               numberOfUnloadSteps    = 0; ///< Number of unload steps @unitb{\unitless}.
    bool              automaticShutdown      = false; ///< True when automatic shutdown is enabled.
    double            unloadSumpPressurePsig = 15.0; ///< Unload sump pressure @unitb{\psig}.
};

/**
 * @struct CompressorDesignDetails
 * @brief Design inputs needed to generate assessment performance points.
 */
struct CompressorDesignDetails {
    double blowdownTimeSec          = 0.003; ///< Blowdown time @unitb{\second}.
    double modulatingPressurePsig   = 0.0; ///< Modulating pressure range @unitb{\psig}.
    double inputPressurePsia        = 14.5; ///< Compressor inlet pressure @unitb{\psia}.
    double designEfficiencyPct      = 100.0; ///< Design efficiency @unitb{\percent}.
    double serviceFactor            = 1.0; ///< Service factor @unitb{\unitless}.
    double noLoadPowerFMPercent     = 0.0; ///< Full-modulation no-load power @unitb{\percent}.
    double noLoadPowerULPercent     = 0.0; ///< Unload no-load power @unitb{\percent}.
    double maxFullFlowPressurePsig  = 0.0; ///< Maximum full-flow pressure @unitb{\psig}.
};

/**
 * @struct CentrifugalSpecifics
 * @brief Centrifugal compressor curve endpoints used for performance-point interpolation.
 */
struct CentrifugalSpecifics {
    double surgeAirflowAcfm        = 0.0; ///< Surge airflow @unitb{\acfm}.
    double maxFullLoadPressurePsig = 0.0; ///< Maximum full-load pressure @unitb{\psig}.
    double maxFullLoadCapacityAcfm = 0.0; ///< Capacity at maximum full-load pressure @unitb{\acfm}.
    double minFullLoadPressurePsig = 0.0; ///< Minimum full-load pressure @unitb{\psig}.
    double minFullLoadCapacityAcfm = 0.0; ///< Capacity at minimum full-load pressure @unitb{\acfm}.
};

/**
 * @struct CompressorPerformancePointInput
 * @brief Input bundle for default performance-point generation.
 */
struct CompressorPerformancePointInput {
    CompressorNameplateData    nameplate; ///< Nameplate and rated data.
    CompressorControlsData     controls; ///< Control settings.
    CompressorDesignDetails    design; ///< Design details.
    CentrifugalSpecifics       centrifugal; ///< Centrifugal curve data.
    CompressorPerformancePoints points; ///< Existing points and default flags.
    double                     atmosphericPressurePsia = 14.7; ///< Atmospheric pressure @unitb{\psia}.
};

/**
 * @struct SequencerSetPointInput
 * @brief Input bundle for automatic sequencer set-point adjustment.
 */
struct SequencerSetPointInput {
    CompressorPerformancePointInput compressor; ///< Compressor performance-point input.
    double targetPressurePsig = 0.0; ///< Sequencer target pressure @unitb{\psig}.
    double variancePsig       = 0.0; ///< Sequencer pressure variance @unitb{\psig}.
};

/**
 * @struct PressureReductionPointInput
 * @brief Input bundle for system pressure reduction performance-point adjustment.
 */
struct PressureReductionPointInput {
    CompressorPerformancePointInput compressor; ///< Compressor performance-point input.
    double pressureReductionPsig = 0.0; ///< Average system pressure reduction @unitb{\psig}.
};

/**
 * @struct CascadingSetPointInput
 * @brief Input bundle for cascading set-point performance-point adjustment.
 */
struct CascadingSetPointInput {
    CompressorPerformancePointInput compressor; ///< Compressor performance-point input.
    double fullLoadPressurePsig    = 0.0; ///< Adjusted full-load pressure @unitb{\psig}.
    double maxFullFlowPressurePsig = 0.0; ///< Adjusted maximum full-flow pressure @unitb{\psig}.
};

CompressorPerformancePoints generatePerformancePoints(CompressorPerformancePointInput input);
CompressorPerformancePoints adjustPerformancePointsForSequencer(SequencerSetPointInput input);
CompressorPerformancePoints reduceSystemPressurePerformancePoints(PressureReductionPointInput input);
CompressorPerformancePoints adjustCascadingSetPointPerformancePoints(CascadingSetPointInput input);

double calculatePressureAdjustedAirflow(double capacity_acfm, double point_pressure_psig,
                                        double rated_pressure_psig, double atmospheric_pressure_psia = 14.7);
double calculatePressureAdjustedPower(CompressorType compressor_type, double inlet_pressure_psia,
                                      double point_pressure_psig, double rated_full_load_pressure_psig,
                                      double package_power_kw, double atmospheric_pressure_psia = 14.7);
double calculateNoLoadPower(double no_load_power_ul_percent, double package_power_kw,
                            double design_efficiency_percent);
double calculateNoLoadPowerWithoutUnloading(double no_load_power_fm_percent, double full_load_power_kw);
double calculateUnloadPointPower(double no_load_power_fm_percent, double unload_point_capacity_percent,
                                 double exponent, double max_full_flow_power_kw);
double calculateUnloadPointAirflow(double full_load_airflow_acfm, double unload_point_capacity_percent);
double calculateUnloadPointDischargePressure(double max_full_flow_pressure_psig,
                                             double modulating_pressure_range_psig,
                                             double full_load_airflow_acfm,
                                             double unload_point_airflow_acfm);
double calculateCentrifugalUnloadPointAirflow(const CentrifugalSpecifics& centrifugal,
                                              double discharge_pressure_psig);
double calculateRatedSpecificPower(double total_package_input_power_kw, double full_load_rated_capacity_acfm);
double calculateRatedIsentropicEfficiency(double rated_specific_power,
                                          double full_load_operating_pressure_psig);

} // namespace compressed_air::assessment
