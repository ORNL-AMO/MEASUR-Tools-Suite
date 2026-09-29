#include "compressedAir/assessment/load_unload_compressor.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "compressedAir/assessment/modulation_without_unload_compressor.h"
#include "util/CurveFitVal.h"

namespace compressed_air::assessment {

LoadUnloadCompressor::LoadUnloadCompressor(double full_load_power, double full_load_airflow, double storage_volume,
                                           double max_power, double full_load_pressure, double max_pressure,
                                           double modulating_pressure, double unloaded_load_factor,
                                           double atmospheric_pressure, CompressorType compressor_type,
                                           CompressorLubricant lubricant, CompressorControl control,
                                           double no_load_power, double unload_capacity_percent,
                                           double blowdown_time, double unload_sump_pressure,
                                           double no_load_power_fraction_for_modulation, double unload_power,
                                           double unload_pressure, double unload_airflow)
    : CompressorModelBase(full_load_power, full_load_airflow), max_power_(max_power),
      atmospheric_pressure_(atmospheric_pressure), full_load_pressure_(full_load_pressure),
      max_pressure_(max_pressure), modulating_pressure_(modulating_pressure), compressor_type_(compressor_type),
      lubricant_(lubricant), control_(control), no_load_fraction_(no_load_power / full_load_power),
      storage_volume_(storage_volume), no_load_power_(no_load_power), unload_capacity_percent_(unload_capacity_percent),
      blowdown_time_(blowdown_time), unload_sump_pressure_(unload_sump_pressure),
      no_load_power_fraction_for_modulation_(no_load_power_fraction_for_modulation), unload_power_(unload_power),
      unload_pressure_(unload_pressure), unload_airflow_(unload_airflow), modulation_exponent_(1.0) {
    (void)unloaded_load_factor;
    if (compressor_type == CompressorType::Screw && lubricant == CompressorLubricant::None) {
        throw std::invalid_argument("Lubricant needs to be Injected or Free for Screw Compressor Type");
    }

    setNoLoadPowerFraction(no_load_power_fraction_for_modulation, lubricant, control);
    setModulationExponent(control);
    if (compressor_type == CompressorType::Screw) {
        if (lubricant == CompressorLubricant::Injected) {
            shutdown_time_ = 2.0;
            reload_time_   = 3.0;
        }
        else if (lubricant == CompressorLubricant::Free) {
            shutdown_time_ = 0.004;
            reload_time_   = 0.001;
            setBlowdownTime(0.003);
            setUnloadSumpPressure(15.0);
        }
    }
    else if (compressor_type == CompressorType::Reciprocating) {
        shutdown_time_ = 0.004;
        reload_time_   = 0.001;
        setBlowdownTime(0.003);
        setUnloadSumpPressure(15.0);
    }

    if (control != CompressorControl::ModulationUnload) {
        setUnloadCapacity();
        setUnloadPower();
        setUnloadPressure();
    }
}

void LoadUnloadCompressor::setNoLoadPowerFraction(double no_load_power_fraction_for_modulation,
                                                  CompressorLubricant lubricant, CompressorControl control) {
    if (lubricant == CompressorLubricant::Injected && control == CompressorControl::LoadUnload) {
        full_load_power_fraction_ = 0.92;
    }
    else {
        full_load_power_fraction_ = no_load_power_fraction_for_modulation;
    }
}

void LoadUnloadCompressor::setUnloadCapacity() {
    unload_airflow_ = full_load_airflow_ * unload_capacity_percent_ / 100.0;
}

void LoadUnloadCompressor::setUnloadPower() {
    const double max_mod_power = full_load_power_fraction_ * max_power_;
    unload_power_ = (max_power_ - max_mod_power) * std::pow(unload_airflow_ / full_load_airflow_, modulation_exponent_) +
                    max_mod_power;
}

void LoadUnloadCompressor::setUnloadPressure() {
    unload_pressure_ = max_pressure_ + (1.0 - (unload_airflow_ / full_load_airflow_)) * modulating_pressure_;
}

void LoadUnloadCompressor::setModulationExponent(CompressorControl control) {
    modulation_exponent_ = control == CompressorControl::VariableDisplacementUnload ? 2.0 : 1.0;
}

double LoadUnloadCompressor::curveFit(double value, bool capacity_vs_power) const {
    const double max_mod_power = full_load_power_fraction_ * max_power_;
    const double blowdown_decay_time = blowdown_time_ / std::log(1.0 / tolerance_);
    const double shutdown_decay_time = shutdown_time_ / std::log(1.0 / tolerance_);

    std::vector<double> percent_capacity;
    std::vector<double> percent_power;
    const double        capacity_decrement = full_load_airflow_ / 76.0;
    double              curve_airflow      = full_load_airflow_;
    do {
        double modulation_runtime = 0.0;
        double average_modulation_power = 0.0;
        if (unload_airflow_ != full_load_airflow_) {
            if (curve_airflow < unload_airflow_) {
                modulation_runtime =
                    ((modulating_pressure_ * storage_volume_) / (atmospheric_pressure_ * full_load_airflow_)) *
                    std::log((full_load_airflow_ - curve_airflow) / (unload_airflow_ - curve_airflow)) * 60.0;
                if (modulation_runtime == 0.0) {
                    modulation_runtime = 1.0;
                }

                const double average_pressure_1 =
                    max_pressure_ + modulating_pressure_ - curve_airflow * modulating_pressure_ / full_load_airflow_;
                const double average_pressure_2 =
                    ((curve_airflow * modulating_pressure_) / full_load_airflow_) - modulating_pressure_;
                const double average_pressure_3 =
                    modulating_pressure_ * storage_volume_ / atmospheric_pressure_ / full_load_airflow_;
                const double average_pressure_4 =
                    (1.0 - std::exp(-atmospheric_pressure_ * full_load_airflow_ / modulating_pressure_ /
                                    storage_volume_ * modulation_runtime / 60.0)) /
                    modulation_runtime * 60.0;
                const double average_pressure =
                    average_pressure_1 + average_pressure_2 * average_pressure_3 * average_pressure_4;
                average_modulation_power =
                    (max_power_ - max_mod_power) *
                        std::pow((max_pressure_ + modulating_pressure_ - average_pressure) / modulating_pressure_,
                                 modulation_exponent_) +
                    max_mod_power;
            }
            else {
                average_modulation_power =
                    (max_power_ - max_mod_power) * std::pow(curve_airflow / full_load_airflow_, modulation_exponent_) +
                    max_mod_power;
            }
        }

        double curve_power = 0.0;
        if (curve_airflow < unload_airflow_) {
            const double unload_decay_runtime =
                storage_volume_ * 60.0 * (unload_pressure_ - full_load_pressure_) /
                (curve_airflow * atmospheric_pressure_);
            const double blowdown_runtime = std::min(blowdown_time_, unload_decay_runtime);

            const double average_blowdown_power =
                no_load_power_ +
                (((unload_power_ - max_mod_power) * std::exp(-blowdown_runtime / shutdown_decay_time) +
                  max_mod_power) -
                 no_load_power_) *
                    ((1.0 - std::exp(-blowdown_runtime / blowdown_decay_time)) *
                     (blowdown_decay_time / blowdown_runtime));
            const double blowdown_energy = blowdown_runtime * average_blowdown_power;

            const double off_load_runtime = unload_decay_runtime - blowdown_runtime;
            const double off_load_power   = full_load_power_ * no_load_fraction_;
            const double off_load_energy  = off_load_runtime * off_load_power;

            const double sump_pressure_after_blowdown =
                unload_sump_pressure_ + (unload_pressure_ - unload_sump_pressure_) *
                                            std::exp(-blowdown_runtime / blowdown_decay_time);
            const double reload_runtime =
                reload_time_ * ((unload_pressure_ - sump_pressure_after_blowdown) /
                                (unload_pressure_ - (unload_pressure_ - unload_sump_pressure_) * tolerance_));
            double minimum_blowdown_power = 0.0;
            if (blowdown_runtime == blowdown_time_) {
                minimum_blowdown_power = no_load_power_;
            }
            else {
                minimum_blowdown_power =
                    no_load_power_ +
                    ((((unload_power_ - max_mod_power) * std::exp(-blowdown_runtime / shutdown_decay_time) +
                       max_mod_power) -
                      no_load_power_) *
                     std::exp(-blowdown_runtime / blowdown_decay_time));
            }
            const double average_reload_power = (minimum_blowdown_power + full_load_power_) / 2.0;
            const double reload_energy        = reload_runtime * average_reload_power;

            const double reload_pumpup_runtime =
                60.0 * storage_volume_ *
                ((max_pressure_ - full_load_pressure_ +
                  (reload_runtime / 60.0) * atmospheric_pressure_ * (curve_airflow / storage_volume_)) /
                 (atmospheric_pressure_ * (full_load_airflow_ - curve_airflow)));
            const double average_reload_pumpup_power =
                ((1.0 - (atmospheric_pressure_ * curve_airflow * reload_runtime) /
                            (storage_volume_ * 60.0 * 200.0)) *
                     full_load_power_ +
                 max_power_) /
                2.0;
            const double reload_pumpup_energy = reload_pumpup_runtime * average_reload_pumpup_power;

            const double modulation_energy =
                unload_airflow_ != full_load_airflow_ ? modulation_runtime * average_modulation_power : 0.0;

            const double cycle_runtime =
                blowdown_runtime + off_load_runtime + reload_runtime + reload_pumpup_runtime + modulation_runtime;
            curve_power =
                (blowdown_energy + off_load_energy + reload_energy + reload_pumpup_energy + modulation_energy) /
                cycle_runtime;
        }
        else {
            curve_power = average_modulation_power;
        }

        percent_capacity.push_back(curve_airflow / full_load_airflow_);
        percent_power.push_back(curve_airflow != full_load_airflow_ ? curve_power / full_load_power_ : 1.0);

        if (curve_airflow == 0.0001) {
            break;
        }
        curve_airflow -= capacity_decrement;
        if (curve_airflow <= 0.0) {
            curve_airflow = 0.0001;
        }
    } while (curve_airflow >= 0.0);

    if (capacity_vs_power) {
        CurveFitVal curve_fit(percent_capacity, percent_power, 6);
        return curve_fit.calculate(value);
    }
    CurveFitVal curve_fit(percent_power, percent_capacity, 6);
    return curve_fit.calculate(value);
}

CompressorPerformanceResult LoadUnloadCompressor::calculateFromPowerFraction(double power_fraction) {
    if (power_fraction == 1.0) {
        return {full_load_power_, full_load_airflow_, 1.0, 1.0};
    }

    if (power_fraction < no_load_fraction_) {
        return {};
    }

    if (control_ == CompressorControl::ModulationUnload ||
        control_ == CompressorControl::VariableDisplacementUnload) {
        const double average_power = power_fraction * full_load_power_;
        if (average_power >= unload_power_) {
            return ModulationWithoutUnloadCompressor(
                       full_load_power_, full_load_airflow_, no_load_power_,
                       control_ == CompressorControl::VariableDisplacementUnload ? 2.0 : 1.0, false,
                       compressor_type_, full_load_power_fraction_, max_power_)
                .calculateFromPowerFraction(power_fraction);
        }
    }

    const double airflow_fraction = curveFit(power_fraction, false);
    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult LoadUnloadCompressor::calculateFromCapacityFraction(double airflow_fraction) {
    if (airflow_fraction == 1.0 || airflow_fraction > 1.0) {
        return {full_load_power_, full_load_airflow_ * airflow_fraction, 1.0, airflow_fraction};
    }

    if (control_ == CompressorControl::ModulationUnload ||
        control_ == CompressorControl::VariableDisplacementUnload) {
        const double unload_airflow = full_load_airflow_ * unload_capacity_percent_ / 100.0;
        if (full_load_airflow_ * airflow_fraction >= unload_airflow) {
            return ModulationWithoutUnloadCompressor(
                       full_load_power_, full_load_airflow_, no_load_power_,
                       control_ == CompressorControl::VariableDisplacementUnload ? 2.0 : 1.0, false,
                       compressor_type_, full_load_power_fraction_, max_power_)
                .calculateFromCapacityFraction(airflow_fraction);
        }
    }

    double curve_airflow = full_load_airflow_ * airflow_fraction;
    if (curve_airflow == 0.0) {
        curve_airflow = 0.00000000001;
    }

    const double max_mod_power      = full_load_power_fraction_ * max_power_;
    const double blowdown_decay_time = blowdown_time_ / std::log(1.0 / tolerance_);
    const double shutdown_decay_time = shutdown_time_ / std::log(1.0 / tolerance_);

    double modulation_runtime = 0.0;
    double average_modulation_power = 0.0;
    if (unload_airflow_ != full_load_airflow_) {
        if (curve_airflow < unload_airflow_) {
            modulation_runtime =
                ((modulating_pressure_ * storage_volume_) / (atmospheric_pressure_ * full_load_airflow_)) *
                std::log((full_load_airflow_ - curve_airflow) / (unload_airflow_ - curve_airflow)) * 60.0;
            if (modulation_runtime == 0.0) {
                modulation_runtime = 1.0;
            }

            const double average_pressure_1 =
                max_pressure_ + modulating_pressure_ - curve_airflow * modulating_pressure_ / full_load_airflow_;
            const double average_pressure_2 =
                ((curve_airflow * modulating_pressure_) / full_load_airflow_) - modulating_pressure_;
            const double average_pressure_3 =
                modulating_pressure_ * storage_volume_ / atmospheric_pressure_ / full_load_airflow_;
            const double average_pressure_4 =
                (1.0 - std::exp(-atmospheric_pressure_ * full_load_airflow_ / modulating_pressure_ / storage_volume_ *
                                modulation_runtime / 60.0)) /
                modulation_runtime * 60.0;
            const double average_pressure =
                average_pressure_1 + average_pressure_2 * average_pressure_3 * average_pressure_4;
            average_modulation_power =
                (max_power_ - max_mod_power) *
                    std::pow((max_pressure_ + modulating_pressure_ - average_pressure) / modulating_pressure_,
                             modulation_exponent_) +
                max_mod_power;
        }
        else {
            average_modulation_power =
                (max_power_ - max_mod_power) * std::pow(curve_airflow / full_load_airflow_, modulation_exponent_) +
                max_mod_power;
        }
    }

    double curve_power = 0.0;
    if (curve_airflow < unload_airflow_) {
        const double unload_decay_runtime =
            storage_volume_ * 60.0 * (unload_pressure_ - full_load_pressure_) /
            (curve_airflow * atmospheric_pressure_);
        const double blowdown_runtime = std::min(blowdown_time_, unload_decay_runtime);

        const double average_blowdown_power =
            no_load_power_ +
            (((unload_power_ - max_mod_power) * std::exp(-blowdown_runtime / shutdown_decay_time) +
              max_mod_power) -
             no_load_power_) *
                ((1.0 - std::exp(-blowdown_runtime / blowdown_decay_time)) * blowdown_decay_time /
                 blowdown_runtime);

        const double blowdown_energy = blowdown_runtime * average_blowdown_power;

        const double off_load_runtime = unload_decay_runtime - blowdown_runtime;
        const double off_load_power   = full_load_power_ * no_load_fraction_;
        const double off_load_energy  = off_load_runtime * off_load_power;

        const double sump_pressure_after_blowdown =
            unload_sump_pressure_ +
            (unload_pressure_ - unload_sump_pressure_) * std::exp(-blowdown_runtime / blowdown_decay_time);
        const double reload_runtime =
            reload_time_ * ((unload_pressure_ - sump_pressure_after_blowdown) /
                            (unload_pressure_ - (unload_pressure_ - unload_sump_pressure_) * tolerance_));
        double minimum_blowdown_power = 0.0;
        if (blowdown_runtime == blowdown_time_) {
            minimum_blowdown_power = no_load_power_;
        }
        else {
            minimum_blowdown_power =
                no_load_power_ +
                ((((unload_power_ - max_mod_power) * std::exp(-blowdown_runtime / shutdown_decay_time) +
                   max_mod_power) -
                  no_load_power_) *
                 std::exp(-blowdown_runtime / blowdown_decay_time));
        }

        const double average_reload_power = (minimum_blowdown_power + full_load_power_) / 2.0;
        const double reload_energy        = reload_runtime * average_reload_power;

        const double reload_pumpup_runtime =
            60.0 * storage_volume_ *
            ((max_pressure_ - full_load_pressure_ +
              (reload_runtime / 60.0) * atmospheric_pressure_ * (curve_airflow / storage_volume_)) /
             (atmospheric_pressure_ * (full_load_airflow_ - curve_airflow)));
        const double average_reload_pumpup_power =
            ((1.0 - (atmospheric_pressure_ * curve_airflow * reload_runtime) /
                        (storage_volume_ * 60.0 * 200.0)) *
                 full_load_power_ +
             max_power_) /
            2.0;
        const double reload_pumpup_energy = reload_pumpup_runtime * average_reload_pumpup_power;

        const double modulation_energy =
            unload_airflow_ != full_load_airflow_ ? modulation_runtime * average_modulation_power : 0.0;

        const double cycle_runtime =
            blowdown_runtime + off_load_runtime + reload_runtime + reload_pumpup_runtime + modulation_runtime;
        curve_power = (blowdown_energy + off_load_energy + reload_energy + reload_pumpup_energy + modulation_energy) /
                      cycle_runtime;
    }
    else {
        curve_power = average_modulation_power;
    }

    const double power_fraction = curve_power / full_load_power_;
    return {power_fraction * full_load_power_, full_load_airflow_ * airflow_fraction, power_fraction,
            airflow_fraction};
}

CompressorPerformanceResult LoadUnloadCompressor::calculateFromMeasuredPower(double power) {
    return calculateFromPowerFraction(power / full_load_power_);
}

CompressorPerformanceResult LoadUnloadCompressor::calculateFromMeasuredCapacity(double airflow) {
    return calculateFromCapacityFraction(airflow / full_load_airflow_);
}

CompressorPerformanceResult LoadUnloadCompressor::calculateFromElectrical(double voltage, double current,
                                                                          double power_factor) {
    return calculateFromMeasuredPower(voltage * current * power_factor * 1.732 / 1000.0);
}

void LoadUnloadCompressor::applyPressureInletCorrection(double capacity, double full_load_bhp, double poly_exponent,
                                                        double rated_discharge_pressure,
                                                        double rated_inlet_pressure, double efficiency,
                                                        double full_load_pressure, double max_pressure,
                                                        double inlet_pressure, bool pressure_adjustment,
                                                        double atmospheric_pressure) {
    CompressorModelBase::applyPressureInletCorrection(compressor_type_, capacity, full_load_bhp, poly_exponent,
                                                      rated_discharge_pressure, rated_inlet_pressure, efficiency,
                                                      full_load_pressure, max_pressure, inlet_pressure,
                                                      pressure_adjustment, atmospheric_pressure);

    max_power_ = max_power_adjusted_;
    no_load_fraction_ = no_load_power_ / full_load_power_;
    if (control_ != CompressorControl::ModulationUnload) {
        setUnloadCapacity();
        setUnloadPower();
        setUnloadPressure();
    }
}

ModulationWithUnloadCompressor::ModulationWithUnloadCompressor(
    double full_load_power, double full_load_airflow, double storage_volume, double max_power, double no_load_power,
    double full_load_pressure, double max_pressure, double modulating_pressure, double atmospheric_pressure,
    double unload_capacity_percent, CompressorControl control, double blowdown_time, double unload_sump_pressure,
    double no_load_power_fraction_for_modulation, double unload_power, double unload_pressure, double unload_airflow)
    : LoadUnloadCompressor(full_load_power, full_load_airflow, storage_volume, max_power, full_load_pressure,
                           max_pressure, modulating_pressure, 1.0, atmospheric_pressure, CompressorType::Screw,
                           CompressorLubricant::Injected, control, no_load_power, unload_capacity_percent,
                           blowdown_time, unload_sump_pressure, no_load_power_fraction_for_modulation, unload_power,
                           unload_pressure, unload_airflow) {}

} // namespace compressed_air::assessment
