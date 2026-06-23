#pragma once

/**
 * @ingroup modulation_without_unload_compressor_assessment
 * @file modulation_without_unload_compressor.h
 * @brief Modulating compressor assessment model declarations.
 */

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @class ModulationWithoutUnloadCompressor
 * @brief Compressor model for modulation without unloading.
 */
class ModulationWithoutUnloadCompressor : public CompressorModelBase {
  public:
    ModulationWithoutUnloadCompressor(double full_load_power, double full_load_airflow, double no_load_power,
                                      double modulation_exponent = 1.0, bool without_unload = true,
                                      CompressorType compressor_type = CompressorType::Screw,
                                      double no_load_power_fraction_for_modulation = 0.7,
                                      double max_power = 0.0);

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
    const double         no_load_power_      = 1.0;
    const double         modulation_exponent_ = 1.0;
    const bool           without_unload_     = true;
    const CompressorType compressor_type_;
    double               no_load_fraction_   = 0.0;
    double               no_load_power_fraction_for_modulation_;
    double               max_power_;
};

} // namespace compressed_air::assessment
