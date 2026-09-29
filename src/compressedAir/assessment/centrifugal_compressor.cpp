#include "compressedAir/assessment/centrifugal_compressor.h"

#include "util/CurveFitVal.h"

namespace compressed_air::assessment {

CentrifugalBlowOffCompressor::CentrifugalBlowOffCompressor(double full_load_power, double full_load_airflow,
                                                           double blow_off_power, double blow_off_airflow)
    : CompressorModelBase(full_load_power, full_load_airflow), blow_off_airflow_(blow_off_airflow) {
    blow_off_airflow_fraction_ = blow_off_airflow / full_load_airflow;
    blow_off_power_fraction_   = blow_off_power / full_load_power;
}

CompressorBlowOffResult CentrifugalBlowOffCompressor::calculateFromPowerFraction(double power_fraction,
                                                                                 double blow_off_fraction) {
    double airflow_fraction = 0.0;

    if (roundDouble(power_fraction) <= roundDouble(blow_off_power_fraction_)) {
        airflow_fraction = blow_off_airflow_fraction_ - blow_off_fraction;
    }
    else {
        airflow_fraction = ((1.0 - blow_off_airflow_fraction_) / (1.0 - blow_off_power_fraction_)) *
                           (power_fraction - 1.0 +
                            ((1.0 - blow_off_power_fraction_) / (1.0 - blow_off_airflow_fraction_)));
    }

    const double calculated_blow_off_fraction = blow_off_airflow_fraction_ - airflow_fraction;

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction, calculated_blow_off_fraction * full_load_airflow_, calculated_blow_off_fraction};
}

CompressorBlowOffResult
CentrifugalBlowOffCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    double power_fraction               = 0.0;
    double calculated_blow_off_fraction = 0.0;

    if (airflow_fraction < blow_off_airflow_fraction_) {
        power_fraction                 = blow_off_power_fraction_;
        calculated_blow_off_fraction   = blow_off_airflow_fraction_ - airflow_fraction;
    }
    else {
        power_fraction = ((1.0 - blow_off_power_fraction_) / (1.0 - blow_off_airflow_fraction_)) *
                             airflow_fraction +
                         1.0 -
                         ((1.0 - blow_off_power_fraction_) / (1.0 - blow_off_airflow_fraction_)) * 1.0;
    }

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction, calculated_blow_off_fraction * full_load_airflow_, calculated_blow_off_fraction};
}

CompressorBlowOffResult CentrifugalBlowOffCompressor::calculateFromMeasuredPower(double power,
                                                                                 double blow_off_fraction) {
    return calculateFromPowerFraction(power / full_load_power_, blow_off_fraction);
}

CompressorBlowOffResult CentrifugalBlowOffCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorBlowOffResult CentrifugalBlowOffCompressor::calculateFromElectrical(double voltage, double current,
                                                                              double power_factor,
                                                                              double blow_off_fraction) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0, blow_off_fraction);
}

void CentrifugalBlowOffCompressor::adjustDischargePressure(const std::vector<double>& capacity,
                                                           const std::vector<double>& discharge_pressure,
                                                           double full_load_pressure, double max_pressure) {
    (void)max_pressure;
    if (full_load_pressure > 0.0) {
        CurveFitVal curve_fit(discharge_pressure, capacity, 2);
        full_load_airflow_adjusted_ = full_load_airflow_ = curve_fit.calculate(full_load_pressure);

        blow_off_airflow_fraction_ = blow_off_airflow_ / full_load_airflow_;
    }
}

CentrifugalLoadUnloadCompressor::CentrifugalLoadUnloadCompressor(double full_load_power, double full_load_airflow,
                                                                 double no_load_power)
    : CompressorModelBase(full_load_power, full_load_airflow) {
    no_load_power_fraction_ = no_load_power / full_load_power;
}

CompressorPerformanceResult CentrifugalLoadUnloadCompressor::calculateFromPowerFraction(double power_fraction) {
    const double airflow_fraction = (power_fraction - no_load_power_fraction_) *
                                    ((full_load_airflow_fraction_ - no_load_airflow_fraction_) /
                                     (1.0 - no_load_power_fraction_));

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult
CentrifugalLoadUnloadCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    const double power_fraction = (((1.0 - no_load_power_fraction_) /
                                    (full_load_airflow_fraction_ - no_load_airflow_fraction_)) *
                                       airflow_fraction +
                                   no_load_power_fraction_);

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult CentrifugalLoadUnloadCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult CentrifugalLoadUnloadCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult CentrifugalLoadUnloadCompressor::calculateFromElectrical(double voltage, double current,
                                                                                     double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

void CentrifugalLoadUnloadCompressor::adjustDischargePressure(const std::vector<double>& capacity,
                                                              const std::vector<double>& discharge_pressure,
                                                              double full_load_pressure, double max_pressure) {
    (void)max_pressure;
    if (full_load_pressure > 0.0) {
        CurveFitVal curve_fit(discharge_pressure, capacity, 2);
        full_load_airflow_adjusted_ = full_load_airflow_ = curve_fit.calculate(full_load_pressure);
    }
}

CentrifugalModulationUnloadCompressor::CentrifugalModulationUnloadCompressor(double full_load_power,
                                                                             double full_load_airflow,
                                                                             double no_load_power,
                                                                             double max_airflow,
                                                                             double unload_power,
                                                                             double unload_airflow)
    : CompressorModelBase(full_load_power, full_load_airflow), max_airflow_(max_airflow),
      max_airflow_raw_(max_airflow), unload_airflow_(unload_airflow) {
    max_airflow_adjusted_ = max_airflow;

    no_load_power_fraction_  = no_load_power / full_load_power;
    unload_power_fraction_   = unload_power / full_load_power;
    max_airflow_fraction_    = max_airflow / full_load_airflow;
    unload_airflow_fraction_ = unload_airflow / full_load_airflow;
    unload_base_fraction_    = unload_airflow / max_airflow;
}

CompressorPerformanceResult
CentrifugalModulationUnloadCompressor::calculateFromPowerFraction(double power_fraction) {
    double airflow_fraction = 1.0;
    if (power_fraction <= no_load_power_fraction_) {
        airflow_fraction = no_load_airflow_fraction_;
    }
    else if (power_fraction < unload_power_fraction_) {
        airflow_fraction = (power_fraction - no_load_power_fraction_) *
                           ((unload_airflow_fraction_ - no_load_airflow_fraction_) /
                            (unload_power_fraction_ - no_load_power_fraction_));
    }
    else if (power_fraction >= unload_power_fraction_) {
        airflow_fraction = ((1.0 - unload_base_fraction_) / (max_power_fraction_ - unload_power_fraction_)) *
                               power_fraction +
                           (1.0 - (1.0 - unload_base_fraction_) /
                                      (max_power_fraction_ - unload_power_fraction_));
    }

    return {power_fraction * full_load_power_,
            (airflow_fraction < unload_base_fraction_ ? full_load_airflow_ : max_airflow_) * airflow_fraction,
            power_fraction, airflow_fraction};
}

CompressorPerformanceResult
CentrifugalModulationUnloadCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    double power_fraction = 1.0;
    if (airflow_fraction < unload_power_fraction_) {
        power_fraction = ((unload_power_fraction_ - no_load_power_fraction_) /
                          (unload_airflow_fraction_ - no_load_airflow_fraction_)) *
                             airflow_fraction +
                         no_load_power_fraction_;
    }
    else if (airflow_fraction < max_airflow_fraction_) {
        power_fraction = ((max_power_fraction_ - unload_power_fraction_) /
                          (max_airflow_fraction_ - unload_airflow_fraction_)) *
                             airflow_fraction +
                         max_power_fraction_ -
                         ((max_power_fraction_ - unload_power_fraction_) /
                          (max_airflow_fraction_ - unload_airflow_fraction_)) *
                             max_airflow_fraction_;
    }

    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult CentrifugalModulationUnloadCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult CentrifugalModulationUnloadCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult CentrifugalModulationUnloadCompressor::calculateFromElectrical(double voltage,
                                                                                          double current,
                                                                                          double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

void CentrifugalModulationUnloadCompressor::adjustDischargePressure(const std::vector<double>& capacity,
                                                                    const std::vector<double>& discharge_pressure,
                                                                    double full_load_pressure, double max_pressure) {
    if (full_load_pressure > 0.0 || max_pressure > 0.0) {
        CurveFitVal curve_fit(discharge_pressure, capacity, 2);

        if (full_load_pressure > 0.0) {
            full_load_airflow_adjusted_ = full_load_airflow_ = curve_fit.calculate(full_load_pressure);
        }
        if (max_pressure > 0.0) {
            max_airflow_adjusted_ = max_airflow_ = curve_fit.calculate(max_pressure);
        }

        max_airflow_fraction_    = max_airflow_ / full_load_airflow_;
        unload_airflow_fraction_ = unload_airflow_ / full_load_airflow_;
        unload_base_fraction_    = unload_airflow_ / max_airflow_;
    }
}

} // namespace compressed_air::assessment
