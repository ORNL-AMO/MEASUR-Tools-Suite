#include "compressedAir/assessment/compressor_eem.h"

#include <cmath>

namespace compressed_air::assessment::compressor_eem {

ReduceAirLeaksResult reduceAirLeaks(double full_load_airflow, double use_airflow, double leak_airflow,
                                    double leak_reduction_fraction) {
    const double reduced_leak_airflow = leak_reduction_fraction * leak_airflow;
    const double adjusted_use_airflow = use_airflow - reduced_leak_airflow;

    return {reduced_leak_airflow, adjusted_use_airflow, adjusted_use_airflow / full_load_airflow};
}

ImproveEndUseEfficiencyResult improveEndUseEfficiency(double full_load_airflow, double use_airflow,
                                                      double reduced_average_airflow) {
    const double reduced_airflow = use_airflow - reduced_average_airflow;
    return {reduced_airflow, reduced_airflow / full_load_airflow};
}

ReduceSystemAirPressureResult reduceSystemAirPressure(double full_load_airflow, double use_airflow,
                                                      double full_load_pressure, double full_load_power,
                                                      double pressure_reduction, double altitude_pressure,
                                                      double atmospheric_pressure) {
    const double adjusted_full_load_pressure = full_load_pressure - pressure_reduction;
    const double adjusted_full_load_power =
        full_load_power *
        ((std::pow((adjusted_full_load_pressure + altitude_pressure) / altitude_pressure, 0.283) - 1.0) /
         (std::pow((full_load_pressure + atmospheric_pressure) / atmospheric_pressure, 0.283) - 1.0));
    const double adjusted_use_airflow =
        use_airflow -
        (use_airflow - (use_airflow * ((adjusted_full_load_pressure + altitude_pressure) /
                                       (full_load_pressure + atmospheric_pressure)))) *
            0.6;

    return {adjusted_full_load_pressure, adjusted_full_load_power, adjusted_use_airflow,
            adjusted_use_airflow / full_load_airflow};
}

AdjustCascadingSetPointResult adjustCascadingSetPoint(double full_load_airflow, double use_airflow,
                                                      double full_load_pressure, double full_load_power,
                                                      double adjusted_full_load_pressure,
                                                      double altitude_pressure,
                                                      double atmospheric_pressure) {
    const double adjusted_full_load_power =
        full_load_power *
        ((std::pow((adjusted_full_load_pressure + altitude_pressure) / altitude_pressure, 0.283) - 1.0) /
         (std::pow((full_load_pressure + atmospheric_pressure) / atmospheric_pressure, 0.283) - 1.0));
    const double adjusted_use_airflow =
        use_airflow -
        (use_airflow - (use_airflow * ((adjusted_full_load_pressure + altitude_pressure) /
                                       (full_load_pressure + atmospheric_pressure)))) *
            0.6;

    return {adjusted_full_load_power, adjusted_use_airflow, adjusted_use_airflow / full_load_airflow};
}

PressureReductionSavingResult pressureReductionSaving(double operating_hours, double cost_per_kwh,
                                                      double rated_full_load_power,
                                                      double rated_full_load_pressure,
                                                      double baseline_discharge_pressure,
                                                      double modified_discharge_pressure,
                                                      double altitude_pressure,
                                                      double atmospheric_pressure) {
    const double power_savings =
        adjustedPower(rated_full_load_power, rated_full_load_pressure, baseline_discharge_pressure,
                      altitude_pressure, atmospheric_pressure) -
        adjustedPower(rated_full_load_power, rated_full_load_pressure, modified_discharge_pressure,
                      altitude_pressure, atmospheric_pressure);
    const double energy_savings = power_savings * operating_hours;
    return {power_savings, energy_savings, energy_savings * cost_per_kwh};
}

double adjustedPower(double rated_full_load_power, double rated_full_load_pressure, double discharge_pressure,
                     double altitude_pressure, double atmospheric_pressure) {
    return rated_full_load_power *
           ((std::pow((discharge_pressure + altitude_pressure) / altitude_pressure, 0.283) - 1.0) /
            (std::pow((rated_full_load_pressure + atmospheric_pressure) / atmospheric_pressure, 0.283) - 1.0));
}

double pressureReducedAirflow(double use_airflow, double adjusted_full_load_pressure,
                              double altitude_pressure, double original_full_load_pressure,
                              double atmospheric_pressure) {
    if (adjusted_full_load_pressure == original_full_load_pressure) {
        return use_airflow;
    }

    const double pressure_ratio =
        (adjusted_full_load_pressure + altitude_pressure) /
        (original_full_load_pressure + atmospheric_pressure);
    return use_airflow - (use_airflow - use_airflow * pressure_ratio) * 0.6;
}

ReceiverVolumeResult addReceiverVolume(double current_receiver_volume, double added_receiver_volume) {
    return {added_receiver_volume, current_receiver_volume + added_receiver_volume};
}

AutomaticSequencerSetPointResult automaticSequencerSetPoints(double target_pressure, double variance) {
    return {target_pressure - variance, target_pressure + variance};
}

} // namespace compressed_air::assessment::compressor_eem
