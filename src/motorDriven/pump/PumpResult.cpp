/**
 * @brief Function prototypes for the Pump result fields
 *
 * This contains the prototypes for the Pump results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing, modified and optimal results.
 *
 * @author Omer Aziz
 *
 */

#include "motorDriven/motor/MotorShaftPower.h"
#include "motorDriven/motor/OptimalMotorPower.h"
#include "motorDriven/motor/OptimalMotorShaftPower.h"
#include "motorDriven/pump/PumpResult.h"
#include "motorDriven/pumpFan/MoverEfficiency.h"
#include "motorDriven/pumpFan/OptimalPumpShaftPower.h"
#include "motorDriven/pumpFan/PumpShaftPower.h"

PumpResult::Output PumpResult::calculateExisting()
{
    /**
     * 1a	Calculate motor shaft power from measured power, OR
     * 1b	Calculate motor shaft power from measured current, voltage
     *  This step calculates the following parameters of motor
     *      shaft power,
     *      current,
     *      power factor,
     *      efficiency and
     *      power.
     * 2a	If a belt drive is specified, calculate the pump shaft power
     * 2b	If direct drive, motor shaft power = pump shaft power
     * 3	Calculate fluid power
     * 4	Calculate pump efficiency
     * 5	Calculate annual energy and energy cost
     */
    MotorShaftPower motorShaftPower(motor.motorRatedPower, fieldData.motorPower, motor.motorRpm,
                                    motor.lineFrequency, motor.efficiencyClass, motor.specifiedEfficiency,
                                    motor.motorRatedVoltage, motor.fullLoadAmps, fieldData.voltage,
                                    fieldData.loadEstimationMethod, fieldData.motorAmps);
    auto const output = motorShaftPower.calculate();

    // existing.motorShaftPower = output.shaftPower;
    // existing.motorCurrent = output.current;
    // existing.motorPowerFactor = output.powerFactor;
    // existing.motorEfficiency = output.efficiency;
    // existing.motorPower = output.power;
    // existing.estimatedFLA = output.estimatedFLA;
    // existing.loadFactor = output.loadFactor;

    // existing.motorRatedPower = motor.motorRatedPower;

    //fix this with proper type and attributes, need to store drive efficiency and get it in return object
    PumpShaftPower::Output const pumpShaftPower = PumpShaftPower(output.shaftPower, pumpInput.drive, pumpInput.specifiedEfficiency).calculate();
    // PumpShaftPower::Output const pumpShaftPower = PumpShaftPower(existing.motorShaftPower, pumpInput.drive, pumpInput.specifiedEfficiency).calculate();
    // existing.pumpShaftPower = pumpShaftPower.pumpShaftPower;
    // existing.driveEfficiency = pumpShaftPower.driveEfficiency;

    double pumpEfficiency;
    pumpEfficiency = MoverEfficiency(pumpInput.specificGravity, fieldData.flowRate, fieldData.head,
                                     pumpShaftPower.pumpShaftPower).calculate();
    // existing.pumpEfficiency = MoverEfficiency(pumpInput.specificGravity, fieldData.flowRate, fieldData.head, existing.pumpShaftPower).calculate();

    // Annual energy, MWh/year = kWe * operating hours/1000
    double annualEnergy = output.power * operatingHours / 1000;
    // existing.annualEnergy = existing.motorPower * operatingHours / 1000;

    // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)
    double annualCost = annualEnergy * unitCost;
    // existing.annualCost = existing.annualEnergy * unitCost;

    return Output(pumpEfficiency, motor.motorRatedPower, output.shaftPower, pumpShaftPower.pumpShaftPower, output.efficiency,
                  output.powerFactor, output.current, output.power, annualEnergy, annualCost, output.loadFactor, pumpShaftPower.driveEfficiency, output.estimatedFLA);
    // return existing;
}

PumpResult::Output PumpResult::calculateModified()
{
    /**
         * Steps for calculating the modified values:
     *  1. Calculate fluid power and pump shaft power
     *  2. Calculate Motor shaft power
     *      a. If a belt drive is specified, calculate the motor shaft power
     *      b. If direct drive, motor shaft power = pump shaft power
     *  4. Develop 25% interval motor performance data for specified efficiency rating motor of the selected size
     *  5. Do curve fitting of current from 25% to 1% intervals
     *  6. Do curve fitting of efficiency in 1% intervals
     *  7. Using current and efficiency 1% interval data, calculate balance of motor data in 1% intervals
     *  8. Calculate required power, motor eff., current, pf from shaft power
     *  9. Calculate annual energy and energy cost
     *  10.Calculate annual savings potential and optimization rating

     */

    // modified.pumpEfficiency = pumpInput.pumpEfficiency;
    OptimalPumpShaftPower modifiedPumpShaftPower(fieldData.flowRate, fieldData.head, pumpInput.specificGravity,
                                                 pumpInput.pumpEfficiency);
    double pumpShaftPower = modifiedPumpShaftPower.calculate();
    // modified.pumpShaftPower = modifiedPumpShaftPower.calculate();

    OptimalMotorShaftPower modifiedMotorShaftPower(pumpShaftPower, pumpInput.drive, pumpInput.specifiedEfficiency);
    // OptimalMotorShaftPower modifiedMotorShaftPower(modified.pumpShaftPower, pumpInput.drive, pumpInput.specifiedEfficiency);

    OptimalMotorShaftPower::Output const motorShaftPowerOutput = modifiedMotorShaftPower.calculate();
    // modified.motorShaftPower = motorShaftPowerOutput.motorShaftPower;
    // modified.driveEfficiency = motorShaftPowerOutput.driveEfficiency;

    // modified.motorRatedPower = motor.motorRatedPower;

    OptimalMotorPower modifiedMotorPower(motor.motorRatedPower, motor.motorRpm, motor.lineFrequency,
                                         motor.efficiencyClass, motor.specifiedEfficiency,
                                         motor.motorRatedVoltage, fieldData.voltage, motorShaftPowerOutput.motorShaftPower);

    // OptimalMotorPower modifiedMotorPower(modified.motorRatedPower, motor.motorRpm, motor.lineFrequency,
    //                                      motor.efficiencyClass, motor.specifiedEfficiency,
    //                                      motor.motorRatedVoltage, fieldData.voltage, modified.motorShaftPower);
    OptimalMotorPower::Output output = modifiedMotorPower.calculate();
    // modified.motorCurrent = output.current;
    // modified.motorEfficiency = output.efficiency;
    // modified.motorPower = output.power;
    // modified.motorPowerFactor = output.powerFactor;
    // modified.loadFactor = output.loadFactor;

    // Annual energy, MWh/year = kWe * operating hours/1000
    double annualEnergyCalculation = output.power * operatingHours / 1000;
    // modified.annualEnergy = modified.motorPower * operatingHours;

    // Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)
    double annualCostCalculation = annualEnergyCalculation * unitCost;

    // Annual Savings potential
    //annualSavingsPotential = existing.annualCost - modified.annualCost;
    annualSavingsPotential = 0.0;
    // Optimization Rating
    //optimizationRating = modified.motorPower / existing.motorPower;
    optimizationRating = 0.0;

    return Output(pumpInput.pumpEfficiency, motor.motorRatedPower, motorShaftPowerOutput.motorShaftPower, pumpShaftPower, output.efficiency,
                  output.powerFactor, output.current, output.power, annualEnergyCalculation, annualCostCalculation, output.loadFactor, motorShaftPowerOutput.driveEfficiency);

    // return modified;
}