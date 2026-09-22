#pragma once

/**
 * @ingroup start_stop_compressor_assessment
 * @file start_stop_compressor.h
 * @brief Start/stop compressor assessment model declarations.
 */

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @class StartStopCompressor
 * @brief Compressor model for start/stop control.
 */
class StartStopCompressor : public CompressorModelBase {
  public:
    /**
     * @brief Construct a start/stop model using the historical screw-compressor pressure correction.
     * @param[in] full_load_power Full-load package input power @unitb{\kilo\watt}.
     * @param[in] full_load_airflow Full-load delivered airflow @unitb{\acfm}.
     * @param[in] max_power_fraction Maximum/full-load power ratio @unitb{\unitless}.
     * @param[in] full_load_power_fraction Lower on-cycle power fraction @unitb{\unitless}.
     */
    StartStopCompressor(double full_load_power, double full_load_airflow, double max_power_fraction,
                        double full_load_power_fraction);
    /**
     * @brief Construct a start/stop model with explicit compressor construction.
     * @param[in] full_load_power Full-load package input power @unitb{\kilo\watt}.
     * @param[in] full_load_airflow Full-load delivered airflow @unitb{\acfm}.
     * @param[in] max_power_fraction Maximum/full-load power ratio @unitb{\unitless}.
     * @param[in] full_load_power_fraction Lower on-cycle power fraction @unitb{\unitless}.
     * @param[in] compressor_type Screw or reciprocating pressure-correction basis.
     */
    StartStopCompressor(double full_load_power, double full_load_airflow, double max_power_fraction,
                        double full_load_power_fraction, CompressorType compressor_type);

    CompressorPerformanceResult calculateFromPowerFraction(double power_fraction);
    CompressorPerformanceResult calculateFromCapacityFraction(double airflow_fraction);
    CompressorPerformanceResult calculateFromMeasuredPower(double power);
    CompressorPerformanceResult calculateFromMeasuredCapacity(double airflow);
    CompressorPerformanceResult calculateFromElectrical(double voltage, double current, double power_factor);

    void applyPressureInletCorrection(double capacity, double full_load_bhp, double poly_exponent,
                                      double rated_discharge_pressure, double rated_inlet_pressure,
                                      double efficiency, double full_load_pressure, double max_pressure,
                                      double inlet_pressure, bool pressure_adjustment,
                                      double atmospheric_pressure = 14.69);

  private:
    const double max_power_fraction_       = 1.0;
    const double full_load_power_fraction_ = 1.0;
    const CompressorType compressor_type_;
    double       max_power_;
};

} // namespace compressed_air::assessment
