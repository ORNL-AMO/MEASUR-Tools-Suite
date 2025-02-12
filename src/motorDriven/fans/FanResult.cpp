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
#include "motorDriven/motor/MotorShaftPower.h"
#include "motorDriven/pumpFan/FanEnergyIndex.h"
#include "motorDriven/pumpFan/MoverShaftPower.h"
#include "motorDriven/pumpFan/MoverEfficiency.h"
#include "motorDriven/pumpFan/OptimalPumpShaftPower.h"
#include "motorDriven/motor/OptimalMotorShaftPower.h"
#include "motorDriven/motor/OptimalMotorPower.h"

FanResult::Output FanResult::calculateExisting(Fan::FieldDataBaseline const fanFieldData)
{
    MotorShaftPower motorShaftPower(motor.motorRatedPower, fanFieldData.measuredPower, motor.motorRpm,
                                    motor.lineFrequency, motor.efficiencyClass, motor.specifiedEfficiency,
                                    motor.motorRatedVoltage, motor.fullLoadAmps, fanFieldData.measuredVoltage,
                                    fanFieldData.loadEstimationMethod, fanFieldData.measuredAmps);
    MotorShaftPower::Output const output = motorShaftPower.calculate();

    MoverShaftPower::Output const moverShaftPower = MoverShaftPower(output.shaftPower, fanInput.drive, fanInput.specifiedEfficiency).calculate();
    double const fanShaftPower = moverShaftPower.moverShaftPower;
    double const driveEfficiency = moverShaftPower.driveEfficiency;
    double const fanEfficiency = MoverEfficiency(fanFieldData.flowRate, fanShaftPower, fanFieldData.inletPressure,
                                                 fanFieldData.outletPressure, fanFieldData.compressibilityFactor, fanFieldData.velocityPressure)
            .calculate();
    double const annualEnergy = output.power * operatingHours / 1000; // Annual energy, MWh/year = kWe * operating hours/1000
    double const annualCost = annualEnergy * unitCost; // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)

    double const fanEnergyIndex = FanEnergyIndex(fanFieldData.flowRate, fanFieldData.inletPressure, fanFieldData.outletPressure,
                                                 fanInput.airDensity, output.power)
            .calculateEnergyIndex();

    return {motorShaftPower.calculate(), fanEfficiency, motor.motorRatedPower, fanShaftPower, annualEnergy, annualCost,
            fanEnergyIndex, output.loadFactor, driveEfficiency, output.estimatedFLA};
}

FanResult::Output FanResult::calculateModified(Fan::FieldDataModified const fanFieldData, double fanEfficiency)
{
    double const fanShaftPower = OptimalPumpShaftPower(fanFieldData.flowRate, fanFieldData.inletPressure,
                                                       fanFieldData.outletPressure, fanFieldData.compressibilityFactor,
                                                       fanEfficiency, fanFieldData.velocityPressure)
            .calculate();

    OptimalMotorShaftPower::Output const optimalMotorShaftPower = OptimalMotorShaftPower(fanShaftPower, fanInput.drive, fanInput.specifiedEfficiency).calculate();
    double const motorShaftPower = optimalMotorShaftPower.motorShaftPower;
    double const driveEfficiency = optimalMotorShaftPower.driveEfficiency;

    OptimalMotorPower::Output const output = OptimalMotorPower(motor.motorRatedPower, motor.motorRpm, motor.lineFrequency,
                                                               motor.efficiencyClass, motor.specifiedEfficiency, motor.motorRatedVoltage,
                                                               fanFieldData.measuredVoltage, motorShaftPower)
            .calculate();
    //    fanFieldData.measuredVoltage, motorShaftPower).calculate(isOptimal);

    double const annualEnergy = output.power * operatingHours / 1000; // Annual energy, MWh/year = kWe * operating hours/1000
    double const annualCost = annualEnergy * unitCost; // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)

    double const fanEnergyIndex = FanEnergyIndex(fanFieldData.flowRate, fanFieldData.inletPressure, fanFieldData.outletPressure,
                                                 fanInput.airDensity, output.power)
            .calculateEnergyIndex();

    return {fanEfficiency, motor.motorRatedPower, motorShaftPower, fanShaftPower, output.efficiency, output.powerFactor,
            output.current, output.power, annualEnergy, annualCost, fanEnergyIndex, output.loadFactor, driveEfficiency};
}