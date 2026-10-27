/**
 * @brief Function prototypes for the Fan result fields
 *
 * This contains the prototypes for the Fan results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing, modified and optimal results.
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#include "motorDriven/fans/FanResult.h"

#include "motorDriven/motor/motor_shaft_power.h"
#include "motorDriven/motor/optimal_motor_power.h"
#include "motorDriven/motor/OptimalMotorShaftPower.h"
#include "motorDriven/pumpFan/FanEnergyIndex.h"
#include "motorDriven/pumpFan/mover_efficiency.h"
#include "motorDriven/pumpFan/MoverShaftPower.h"
#include "motorDriven/pumpFan/optimal_pump_shaft_power.h"

FanResult::Output FanResult::calculateExisting(Fan::FieldDataBaseline const fanFieldData) {
    const auto output = motor_shaft_power::calculate({
        motor.motorRatedPower, fanFieldData.measuredPower, motor.motorRpm, motor.lineFrequency,
        motor.efficiencyClass, motor.specifiedEfficiency, motor.motorRatedVoltage, motor.fullLoadAmps,
        fanFieldData.measuredVoltage, fanFieldData.loadEstimationMethod, fanFieldData.measuredAmps});

    MoverShaftPower::Output const moverShaftPower =
        MoverShaftPower(output.shaft_power, fanInput.drive, fanInput.specifiedEfficiency).calculate();
    double const fanShaftPower   = moverShaftPower.moverShaftPower;
    double const driveEfficiency = moverShaftPower.driveEfficiency;
    double const fanEfficiency =
        mover_efficiency::calculateFan({fanFieldData.flowRate, fanShaftPower, fanFieldData.inletPressure,
            fanFieldData.outletPressure, fanFieldData.compressibilityFactor, fanFieldData.velocityPressure});
    double const annualEnergy =
        output.power * operatingHours / 1000; // Annual energy, MWh/year = kWe * operating hours/1000
    double const annualCost =
        annualEnergy * unitCost; // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)

    double const fanEnergyIndex = FanEnergyIndex(fanFieldData.flowRate, fanFieldData.inletPressure,
                                                 fanFieldData.outletPressure, fanInput.airDensity, output.power)
                                      .calculateEnergyIndex();

    return {output,
            fanEfficiency,
            motor.motorRatedPower,
            fanShaftPower,
            annualEnergy,
            annualCost,
            fanEnergyIndex,
            output.load_factor,
            driveEfficiency,
            output.estimated_fla};
}

FanResult::Output FanResult::calculateModified(Fan::FieldDataModified const fanFieldData, double fanEfficiency) {
    double const fanShaftPower =
        optimal_pump_shaft_power::calculateFan({fanFieldData.flowRate, fanFieldData.inletPressure,
            fanFieldData.outletPressure, fanFieldData.compressibilityFactor, fanEfficiency,
            fanFieldData.velocityPressure});

    OptimalMotorShaftPower::Output const optimalMotorShaftPower =
        OptimalMotorShaftPower(fanShaftPower, fanInput.drive, fanInput.specifiedEfficiency).calculate();
    double const motorShaftPower = optimalMotorShaftPower.motorShaftPower;
    double const driveEfficiency = optimalMotorShaftPower.driveEfficiency;

    const auto output = optimal_motor_power::calculate({
        motor.motorRatedPower, motor.motorRpm, motor.lineFrequency, motor.efficiencyClass,
        motor.specifiedEfficiency, motor.motorRatedVoltage, fanFieldData.measuredVoltage, motorShaftPower});

    double const annualEnergy =
        output.power * operatingHours / 1000; // Annual energy, MWh/year = kWe * operating hours/1000
    double const annualCost =
        annualEnergy * unitCost; // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)

    double const fanEnergyIndex = FanEnergyIndex(fanFieldData.flowRate, fanFieldData.inletPressure,
                                                 fanFieldData.outletPressure, fanInput.airDensity, output.power)
                                      .calculateEnergyIndex();

    return {fanEfficiency,       motor.motorRatedPower, motorShaftPower, fanShaftPower, output.efficiency,
            output.power_factor, output.current,       output.power,    annualEnergy,  annualCost,
            fanEnergyIndex,      output.load_factor,   driveEfficiency};
}
