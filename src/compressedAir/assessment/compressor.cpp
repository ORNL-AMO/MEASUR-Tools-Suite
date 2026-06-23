#include "compressedAir/assessment/compressor.h"

#include <cmath>

namespace compressed_air::assessment {

double CompressorModelBase::roundDouble(double value) { return std::round(value * 10000.0) / 10000.0; }

void CompressorModelBase::applyPressureInletCorrection(CompressorType compressor_type, double capacity,
                                                       double full_load_bhp, double poly_exponent,
                                                       double rated_discharge_pressure,
                                                       double rated_inlet_pressure, double efficiency,
                                                       double full_load_pressure, double max_pressure,
                                                       double inlet_pressure, bool pressure_adjustment,
                                                       double atmospheric_pressure) {
    double power_adjusted    = 0.0;
    double capacity_adjusted = 0.0;

    applyPressureInletCorrection(capacity_adjusted, power_adjusted, compressor_type, capacity, full_load_bhp,
                                 poly_exponent, rated_discharge_pressure, rated_inlet_pressure, efficiency,
                                 full_load_pressure, inlet_pressure, pressure_adjustment, atmospheric_pressure);
    full_load_power_adjusted_ = full_load_power_ = power_adjusted;
    full_load_airflow_adjusted_ = full_load_airflow_ = capacity_adjusted;

    applyPressureInletCorrection(capacity_adjusted, power_adjusted, compressor_type, capacity, full_load_bhp,
                                 poly_exponent, rated_discharge_pressure, rated_inlet_pressure, efficiency,
                                 max_pressure, inlet_pressure, pressure_adjustment, atmospheric_pressure);
    max_power_adjusted_   = power_adjusted;
    max_airflow_adjusted_ = capacity_adjusted;
}

void CompressorModelBase::applyPressureInletCorrection(double& capacity_adjusted, double& power_adjusted,
                                                       CompressorType compressor_type, double capacity,
                                                       double full_load_bhp, double poly_exponent,
                                                       double rated_discharge_pressure,
                                                       double rated_inlet_pressure, double efficiency,
                                                       double discharge_pressure, double inlet_pressure,
                                                       bool pressure_adjustment, double atmospheric_pressure) {
    if (compressor_type == CompressorType::Centrifugal) {
        return;
    }

    double pressure_power = 1.0;
    double pressure_flow  = 1.0;
    if (pressure_adjustment) {
        pressure_power = -0.0000577 * std::pow(atmospheric_pressure, 3) +
                         0.000251 * std::pow(atmospheric_pressure, 2) + 0.0466 * atmospheric_pressure + 0.4442;
        pressure_flow = 0.000258 * std::pow(atmospheric_pressure, 3) -
                        0.0116 * std::pow(atmospheric_pressure, 2) + 0.176 * atmospheric_pressure + 0.09992;
    }

    power_adjusted =
        pressure_power * (atmospheric_pressure / inlet_pressure) * full_load_bhp * 0.746 / efficiency *
        pressureRatioCorrection(poly_exponent, (rated_discharge_pressure + rated_inlet_pressure) / rated_inlet_pressure,
                                discharge_pressure,
                                compressor_type == CompressorType::Screw ? rated_inlet_pressure : atmospheric_pressure);
    capacity_adjusted =
        pressure_flow * capacity * (1.0 - 0.00075 * (discharge_pressure - rated_discharge_pressure));
}

double CompressorModelBase::pressureRatioCorrection(double poly_exponent, double rated_pressure_ratio,
                                                    double operating_pressure, double pressure_ratio_base) {
    const double operating_pressure_ratio = (operating_pressure + pressure_ratio_base) / pressure_ratio_base;
    const double poly_power               = (poly_exponent - 1.0) / poly_exponent;
    return (std::pow(operating_pressure_ratio, poly_power) - 1.0) /
           (std::pow(rated_pressure_ratio, poly_power) - 1.0);
}

} // namespace compressed_air::assessment
