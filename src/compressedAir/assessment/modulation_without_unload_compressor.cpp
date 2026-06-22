#include "compressedAir/assessment/modulation_without_unload_compressor.h"

#include <cmath>

namespace compressed_air::assessment {

ModulationWithoutUnloadCompressor::ModulationWithoutUnloadCompressor(
    double full_load_power, double full_load_airflow, double no_load_power, double modulation_exponent,
    bool without_unload, CompressorType compressor_type, double no_load_power_fraction_for_modulation,
    double max_power)
    : CompressorModelBase(full_load_power, full_load_airflow), no_load_power_(no_load_power),
      modulation_exponent_(modulation_exponent), without_unload_(without_unload), compressor_type_(compressor_type),
      no_load_power_fraction_for_modulation_(no_load_power_fraction_for_modulation), max_power_(max_power) {
    no_load_fraction_ = no_load_power / full_load_power;
}

CompressorPerformanceResult
ModulationWithoutUnloadCompressor::calculateFromPowerFraction(double power_fraction) {
    double airflow = 1.0;
    if (power_fraction < no_load_fraction_) {
        return {};
    }
    if (power_fraction >= 1.0) {
        airflow = full_load_airflow_;
    }
    else if (without_unload_) {
        airflow = std::pow((power_fraction * full_load_power_ - no_load_power_) /
                               (full_load_power_ - no_load_power_),
                           1.0 / modulation_exponent_) *
                  full_load_airflow_;
    }
    else {
        if (no_load_power_ == full_load_power_) {
            airflow = full_load_airflow_;
        }
        else {
            const double max_mod_power = max_power_ * no_load_power_fraction_for_modulation_;
            const double numerator     = no_load_power_ - max_mod_power;
            const double denominator   = max_power_ - max_mod_power;
            airflow = std::pow(numerator / denominator, 1.0 / modulation_exponent_) * full_load_airflow_;
        }
    }

    return {power_fraction * full_load_power_, airflow, power_fraction, airflow / full_load_airflow_};
}

CompressorPerformanceResult
ModulationWithoutUnloadCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    if (airflow_fraction > 1.0) {
        return {full_load_power_, full_load_airflow_ * airflow_fraction, 1.0, airflow_fraction};
    }

    double power = 0.0;
    if (without_unload_) {
        power = (full_load_power_ - no_load_power_) * std::pow(airflow_fraction, modulation_exponent_) +
                no_load_power_;
    }
    else {
        const double max_mod_power = no_load_power_ * no_load_power_fraction_for_modulation_;
        power = (no_load_power_ - max_mod_power) * std::pow(airflow_fraction, modulation_exponent_) +
                max_mod_power;
    }

    return {power, full_load_airflow_ * airflow_fraction, power / full_load_power_, airflow_fraction};
}

CompressorPerformanceResult ModulationWithoutUnloadCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult ModulationWithoutUnloadCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult ModulationWithoutUnloadCompressor::calculateFromElectrical(double voltage, double current,
                                                                                      double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

void ModulationWithoutUnloadCompressor::applyPressureInletCorrection(
    double capacity, double full_load_bhp, double poly_exponent, double rated_discharge_pressure,
    double rated_inlet_pressure, double efficiency, double full_load_pressure, double max_pressure,
    double inlet_pressure, bool pressure_adjustment, double atmospheric_pressure) {
    CompressorModelBase::applyPressureInletCorrection(compressor_type_, capacity, full_load_bhp, poly_exponent,
                                                      rated_discharge_pressure, rated_inlet_pressure, efficiency,
                                                      full_load_pressure, max_pressure, inlet_pressure,
                                                      pressure_adjustment, atmospheric_pressure);
}

} // namespace compressed_air::assessment
