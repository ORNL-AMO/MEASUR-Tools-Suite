#pragma once

/**
 * @ingroup load_unload_compressor_assessment
 * @file load_unload_compressor.h
 * @brief Load/unload compressor assessment model declarations.
 */

#include "compressedAir/assessment/compressor.h"

namespace compressed_air::assessment {

/**
 * @class LoadUnloadCompressor
 * @brief Compressor load/unload cycle model for screw and reciprocating compressors.
 */
class LoadUnloadCompressor : public CompressorModelBase {
  public:
    LoadUnloadCompressor(double full_load_power, double full_load_airflow, double storage_volume, double max_power,
                         double full_load_pressure, double max_pressure, double modulating_pressure,
                         double unloaded_load_factor, double atmospheric_pressure = 14.7,
                         CompressorType compressor_type = CompressorType::Reciprocating,
                         CompressorLubricant lubricant = CompressorLubricant::None,
                         CompressorControl control = CompressorControl::LoadUnload, double no_load_power = 1.0,
                         double unload_capacity_percent = 100.0, double blowdown_time = 0.003,
                         double unload_sump_pressure = 15.0, double no_load_power_fraction_for_modulation = 0.7,
                         double unload_power = 0.0, double unload_pressure = 0.0, double unload_airflow = 0.0);

    void setBlowdownTime(double blowdown_time) { blowdown_time_ = blowdown_time; }
    void setUnloadSumpPressure(double sump_pressure) { unload_sump_pressure_ = sump_pressure; }
    void setNoLoadPowerFraction(double no_load_power_fraction_for_modulation, CompressorLubricant lubricant,
                                CompressorControl control);
    void setUnloadCapacity();
    void setUnloadPower();
    void setUnloadPressure();
    void setModulationExponent(CompressorControl control);

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
    double curveFit(double value, bool capacity_vs_power) const;

    double              max_power_;
    const double        atmospheric_pressure_;
    const double        full_load_pressure_;
    const double        max_pressure_;
    const double        modulating_pressure_;
    CompressorType      compressor_type_;
    CompressorLubricant lubricant_;
    CompressorControl   control_;
    const double        no_load_fraction_;
    const double        storage_volume_;
    const double        no_load_power_ = 1.0;

    double unload_capacity_percent_              = 100.0;
    double blowdown_time_                        = 0.003;
    double unload_sump_pressure_                 = 15.0;
    double shutdown_time_                        = 0.004;
    double tolerance_                            = 0.02;
    double reload_time_                          = 0.001;
    double full_load_power_fraction_             = 0.7;
    double no_load_power_fraction_for_modulation_;
    double unload_power_;
    double unload_pressure_;
    double unload_airflow_;
    double modulation_exponent_;
};

/**
 * @class ModulationWithUnloadCompressor
 * @brief Screw compressor model for modulation or variable displacement with unloading.
 */
class ModulationWithUnloadCompressor : public LoadUnloadCompressor {
  public:
    ModulationWithUnloadCompressor(double full_load_power, double full_load_airflow, double storage_volume,
                                   double max_power, double no_load_power, double full_load_pressure,
                                   double max_pressure, double modulating_pressure,
                                   double atmospheric_pressure = 14.7, double unload_capacity_percent = 100.0,
                                   CompressorControl control = CompressorControl::VariableDisplacementUnload,
                                   double blowdown_time = 0.003, double unload_sump_pressure = 15.0,
                                   double no_load_power_fraction_for_modulation = 0.7,
                                   double unload_power = 0.0, double unload_pressure = 0.0,
                                   double unload_airflow = 0.0);
};

} // namespace compressed_air::assessment
