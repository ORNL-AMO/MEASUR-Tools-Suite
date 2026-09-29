#include "compressedAir/assessment/vfd_compressor.h"

#include <cmath>
#include <vector>

#include "util/CurveFitVal.h"

namespace compressed_air::assessment {

VariableFrequencyDriveCompressor::VariableFrequencyDriveCompressor(
    double full_load_power, double mid_turndown_power, double turndown_power, double no_load_power,
    double full_load_airflow, double mid_turndown_airflow, double turndown_airflow)
    : CompressorModelBase(full_load_power, full_load_airflow), no_load_power_(no_load_power) {
    turndown_power_fraction_     = turndown_power / full_load_power;
    no_load_power_fraction_      = no_load_power / full_load_power;
    mid_turndown_power_fraction_ = mid_turndown_power / full_load_power;

    turndown_airflow_fraction_     = turndown_airflow / full_load_airflow;
    mid_turndown_airflow_fraction_ = mid_turndown_airflow / full_load_airflow;
}

CompressorPerformanceResult
VariableFrequencyDriveCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    double power_fraction = 0.0;
    if (airflow_fraction > 1.0) {
        power_fraction = 1.0;
    }
    else if (airflow_fraction < turndown_airflow_fraction_) {
        const double slope =
            (turndown_power_fraction_ - no_load_power_fraction_) / (turndown_airflow_fraction_ - 0.0);
        const double intercept = no_load_power_fraction_ - (slope * 0.0);
        power_fraction         = slope * airflow_fraction + intercept;
    }
    else {
        std::vector<double> percent_capacity{turndown_airflow_fraction_, mid_turndown_airflow_fraction_, 1.0};
        std::vector<double> percent_power{turndown_power_fraction_, mid_turndown_power_fraction_, 1.0};
        CurveFitVal         curve_fit(percent_capacity, percent_power, 2);
        power_fraction = curve_fit.calculate(airflow_fraction);
    }

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult VariableFrequencyDriveCompressor::calculateFromPowerFraction(double power_fraction) {
    if (power_fraction == 1.0) {
        return {full_load_power_, full_load_airflow_, 1.0, 1.0};
    }

    const double power = power_fraction * full_load_power_;
    if (power < no_load_power_) {
        return {};
    }

    double airflow_fraction = 0.0;
    if (power_fraction < turndown_power_fraction_) {
        const double slope =
            (turndown_airflow_fraction_ - 0.0) / (turndown_power_fraction_ - no_load_power_fraction_);
        const double intercept = 0.0 - (slope * no_load_power_fraction_);
        airflow_fraction       = slope * power_fraction + intercept;
    }
    else {
        std::vector<double> percent_power{turndown_power_fraction_, mid_turndown_power_fraction_, 1.0};
        std::vector<double> percent_capacity{turndown_airflow_fraction_, mid_turndown_airflow_fraction_, 1.0};

        CurveFitVal curve_fit(percent_capacity, percent_power, 2);

        const double a = curve_fit.coeff.at(2);
        const double b = curve_fit.coeff.at(1);
        const double c = curve_fit.coeff.at(0);

        airflow_fraction = (-b + std::sqrt(std::pow(b, 2) - (4.0 * a * (c - power_fraction)))) / (2.0 * a);
    }

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult VariableFrequencyDriveCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult VariableFrequencyDriveCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult VariableFrequencyDriveCompressor::calculateFromElectrical(double voltage, double current,
                                                                                     double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

} // namespace compressed_air::assessment
