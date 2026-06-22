#pragma once

/**
 * @ingroup vfd_compressor_assessment
 * @file vfd_compressor.h
 * @brief Variable frequency drive compressor assessment model declarations.
 */

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @class VariableFrequencyDriveCompressor
 * @brief Compressor model for variable frequency drive control.
 */
class VariableFrequencyDriveCompressor : public CompressorModelBase {
  public:
    VariableFrequencyDriveCompressor(double full_load_power, double mid_turndown_power, double turndown_power,
                                     double no_load_power, double full_load_airflow,
                                     double mid_turndown_airflow, double turndown_airflow);

    CompressorPerformanceResult calculateFromPowerFraction(double power_fraction);
    CompressorPerformanceResult calculateFromCapacityFraction(double airflow_fraction);
    CompressorPerformanceResult calculateFromMeasuredPower(double power);
    CompressorPerformanceResult calculateFromMeasuredCapacity(double airflow);
    CompressorPerformanceResult calculateFromElectrical(double voltage, double current, double power_factor);

  private:
    double turndown_power_fraction_;
    double no_load_power_fraction_;
    double mid_turndown_power_fraction_;
    double turndown_airflow_fraction_;
    double mid_turndown_airflow_fraction_;
    double no_load_power_;
};

} // namespace compressed_air::assessment
