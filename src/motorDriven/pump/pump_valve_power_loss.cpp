#include "motorDriven/pump/pump_valve_power_loss.h"

PumpValvePowerLoss::Output PumpValvePowerLoss::calculate(const double operating_hours, const double pump_efficiency, const double motor_efficiency,
                                     const double specific_gravity, const double flow_rate,
                                     const double upstream_pressure, const double upstream_gauge_elevation,
                                     const double downstream_pressure, const double downstream_gauge_elevation) const {
    // Constants (unit-sensitive)
    constexpr double KHeightToPressureConversion = 2.307249; // feet of fluid height to PSI
    constexpr double kFluidPowerConversion = 1714.231;       // flow rate to power lost
    constexpr double kElectricalPowerConversion = 0.7457;    // horsepower to kW

    const double pressureDrop = (upstream_pressure - downstream_pressure) + specific_gravity *
            (upstream_gauge_elevation - downstream_gauge_elevation) / KHeightToPressureConversion; // [PSI]

    const double headLoss = pressureDrop * KHeightToPressureConversion; // [ft]

    const double powerLossFrictional = pressureDrop * flow_rate / kFluidPowerConversion; // [hp]

    const double powerLossElectrical = (kElectricalPowerConversion   * powerLossFrictional / pump_efficiency) / motor_efficiency; // [kW]

    const double annualEnergyLoss = operating_hours * powerLossElectrical; // [kWh]

    return {pressureDrop, headLoss, powerLossFrictional, powerLossElectrical, annualEnergyLoss};
}