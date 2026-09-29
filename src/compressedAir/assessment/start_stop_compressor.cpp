#include "compressedAir/assessment/start_stop_compressor.h"

namespace compressed_air::assessment {

StartStopCompressor::StartStopCompressor(double full_load_power, double full_load_airflow,
                                         double max_power_fraction, double full_load_power_fraction)
    : CompressorModelBase(full_load_power, full_load_airflow), max_power_fraction_(max_power_fraction),
      full_load_power_fraction_(full_load_power_fraction) {
    max_power_ = max_power_fraction * full_load_power;
}

CompressorPerformanceResult StartStopCompressor::calculateFromPowerFraction(double power_fraction) {
    if (power_fraction == 0.0) {
        return {};
    }

    const double airflow =
        full_load_airflow_ * power_fraction / ((full_load_power_fraction_ + max_power_ / full_load_power_) / 2.0);
    return {power_fraction * full_load_power_, airflow, power_fraction, airflow / full_load_airflow_};
}

CompressorPerformanceResult StartStopCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    if (airflow_fraction > 1.0) {
        return {full_load_power_, full_load_airflow_ * airflow_fraction, 1.0, airflow_fraction};
    }

    const double power =
        ((full_load_power_fraction_ + max_power_ / full_load_power_) / 2.0) * airflow_fraction * full_load_power_;
    return {power, full_load_airflow_ * airflow_fraction, power / full_load_power_, airflow_fraction};
}

CompressorPerformanceResult StartStopCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult StartStopCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult StartStopCompressor::calculateFromElectrical(double voltage, double current,
                                                                         double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

void StartStopCompressor::applyPressureInletCorrection(double capacity, double full_load_bhp, double poly_exponent,
                                                       double rated_discharge_pressure,
                                                       double rated_inlet_pressure, double efficiency,
                                                       double full_load_pressure, double max_pressure,
                                                       double inlet_pressure, bool pressure_adjustment,
                                                       double atmospheric_pressure) {
    CompressorModelBase::applyPressureInletCorrection(CompressorType::Screw, capacity, full_load_bhp, poly_exponent,
                                                      rated_discharge_pressure, rated_inlet_pressure, efficiency,
                                                      full_load_pressure, max_pressure, inlet_pressure,
                                                      pressure_adjustment, atmospheric_pressure);

    max_power_ = max_power_fraction_ * full_load_power_;
}

} // namespace compressed_air::assessment
