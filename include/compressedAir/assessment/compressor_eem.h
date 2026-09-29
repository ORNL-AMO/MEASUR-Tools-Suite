#pragma once

/**
 * @ingroup compressor_eem_assessment
 * @file compressor_eem.h
 * @brief Compressor energy efficiency measure calculation declarations.
 */

namespace compressed_air::assessment::compressor_eem {

struct ReduceAirLeaksResult {
    double reducedLeakAirflowAcfm = 0.0; ///< Reduced leak airflow @unitb{\acfm}.
    double adjustedUseAirflowAcfm = 0.0; ///< Adjusted use airflow after leak reduction @unitb{\acfm}.
    double adjustedUseFraction    = 0.0; ///< Adjusted use airflow fraction @unitb{\unitless}.
};

struct ImproveEndUseEfficiencyResult {
    double reducedAirflowAcfm = 0.0; ///< Reduced airflow @unitb{\acfm}.
    double reducedAirflowFraction = 0.0; ///< Reduced airflow fraction @unitb{\unitless}.
};

struct ReduceSystemAirPressureResult {
    double adjustedFullLoadPressurePsig = 0.0; ///< Adjusted full-load pressure @unitb{\psig}.
    double adjustedFullLoadPowerKw      = 0.0; ///< Adjusted full-load power @unitb{\kilo\watt}.
    double adjustedUseAirflowAcfm       = 0.0; ///< Adjusted use airflow @unitb{\acfm}.
    double adjustedUseFraction          = 0.0; ///< Adjusted use airflow fraction @unitb{\unitless}.
};

struct AdjustCascadingSetPointResult {
    double adjustedFullLoadPowerKw = 0.0; ///< Adjusted full-load power @unitb{\kilo\watt}.
    double adjustedUseAirflowAcfm  = 0.0; ///< Adjusted use airflow @unitb{\acfm}.
    double adjustedUseFraction     = 0.0; ///< Adjusted use airflow fraction @unitb{\unitless}.
};

struct PressureReductionSavingResult {
    double powerSavingsKw = 0.0; ///< Demand savings @unitb{\kilo\watt}.
    double energySavingsKwh = 0.0; ///< Annual energy savings @unitb{\kilo\watt\hour}.
    double costSavings = 0.0; ///< Annual cost savings @unitb{\dollar}.
};

ReduceAirLeaksResult reduceAirLeaks(double full_load_airflow, double use_airflow, double leak_airflow,
                                    double leak_reduction_fraction);

ImproveEndUseEfficiencyResult improveEndUseEfficiency(double full_load_airflow, double use_airflow,
                                                      double reduced_average_airflow);

ReduceSystemAirPressureResult reduceSystemAirPressure(double full_load_airflow, double use_airflow,
                                                      double full_load_pressure, double full_load_power,
                                                      double pressure_reduction, double altitude_pressure = 14.69,
                                                      double atmospheric_pressure = 14.69);

AdjustCascadingSetPointResult adjustCascadingSetPoint(double full_load_airflow, double use_airflow,
                                                      double full_load_pressure, double full_load_power,
                                                      double adjusted_full_load_pressure,
                                                      double altitude_pressure = 14.69,
                                                      double atmospheric_pressure = 14.69);

PressureReductionSavingResult pressureReductionSaving(double operating_hours, double cost_per_kwh,
                                                      double rated_full_load_power,
                                                      double rated_full_load_pressure,
                                                      double baseline_discharge_pressure,
                                                      double modified_discharge_pressure,
                                                      double altitude_pressure = 14.69,
                                                      double atmospheric_pressure = 14.69);

double adjustedPower(double rated_full_load_power, double rated_full_load_pressure, double discharge_pressure,
                     double altitude_pressure = 14.69, double atmospheric_pressure = 14.69);

} // namespace compressed_air::assessment::compressor_eem
