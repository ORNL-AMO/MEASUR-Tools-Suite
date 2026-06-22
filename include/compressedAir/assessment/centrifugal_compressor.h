#pragma once

/**
 * @ingroup centrifugal_compressor_assessment
 * @file centrifugal_compressor.h
 * @brief Centrifugal compressor assessment model declarations.
 */

#include <vector>

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @class CentrifugalBlowOffCompressor
 * @brief Centrifugal compressor model with blow-off control.
 */
class CentrifugalBlowOffCompressor : public CompressorModelBase {
  public:
    CentrifugalBlowOffCompressor(double full_load_power, double full_load_airflow, double blow_off_power,
                                 double blow_off_airflow);

    CompressorBlowOffResult calculateFromPowerFraction(double power_fraction, double blow_off_fraction);
    CompressorBlowOffResult calculateFromCapacityFraction(double airflow_fraction);
    CompressorBlowOffResult calculateFromMeasuredPower(double power, double blow_off_fraction);
    CompressorBlowOffResult calculateFromMeasuredCapacity(double airflow);
    CompressorBlowOffResult calculateFromElectrical(double voltage, double current, double power_factor,
                                                    double blow_off_fraction);

    void adjustDischargePressure(const std::vector<double>& capacity, const std::vector<double>& discharge_pressure,
                                 double full_load_pressure, double max_pressure = 0.0);

  private:
    double blow_off_airflow_          = 1.0;
    double blow_off_airflow_fraction_ = 1.0;
    double blow_off_power_fraction_   = 0.0;
};

/**
 * @class CentrifugalLoadUnloadCompressor
 * @brief Centrifugal compressor model with load/unload control.
 */
class CentrifugalLoadUnloadCompressor : public CompressorModelBase {
  public:
    CentrifugalLoadUnloadCompressor(double full_load_power, double full_load_airflow, double no_load_power);

    CompressorPerformanceResult calculateFromPowerFraction(double power_fraction);
    CompressorPerformanceResult calculateFromCapacityFraction(double airflow_fraction);
    CompressorPerformanceResult calculateFromMeasuredPower(double power);
    CompressorPerformanceResult calculateFromMeasuredCapacity(double airflow);
    CompressorPerformanceResult calculateFromElectrical(double voltage, double current, double power_factor);

    void adjustDischargePressure(const std::vector<double>& capacity, const std::vector<double>& discharge_pressure,
                                 double full_load_pressure, double max_pressure = 0.0);

  private:
    const double full_load_airflow_fraction_ = 1.0;
    const double no_load_airflow_fraction_   = 0.0;
    double       no_load_power_fraction_     = 0.0;
};

/**
 * @class CentrifugalModulationUnloadCompressor
 * @brief Centrifugal compressor model with modulation and unloading.
 */
class CentrifugalModulationUnloadCompressor : public CompressorModelBase {
  public:
    CentrifugalModulationUnloadCompressor(double full_load_power, double full_load_airflow, double no_load_power,
                                          double max_airflow, double unload_power, double unload_airflow);

    CompressorPerformanceResult calculateFromPowerFraction(double power_fraction);
    CompressorPerformanceResult calculateFromCapacityFraction(double airflow_fraction);
    CompressorPerformanceResult calculateFromMeasuredPower(double power);
    CompressorPerformanceResult calculateFromMeasuredCapacity(double airflow);
    CompressorPerformanceResult calculateFromElectrical(double voltage, double current, double power_factor);

    void adjustDischargePressure(const std::vector<double>& capacity, const std::vector<double>& discharge_pressure,
                                 double full_load_pressure, double max_pressure);

  private:
    double       max_airflow_              = 1.0;
    const double max_power_fraction_       = 1.0;
    const double max_airflow_raw_          = 1.0;
    const double unload_airflow_           = 1.0;
    double       no_load_power_fraction_   = 0.0;
    double       unload_power_fraction_    = 1.0;
    double       max_airflow_fraction_     = 1.0;
    double       unload_airflow_fraction_  = 1.0;
    double       unload_base_fraction_     = 1.0;
    const double no_load_airflow_fraction_ = 0.0;
};

} // namespace compressed_air::assessment
