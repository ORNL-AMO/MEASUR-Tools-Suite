import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpResults } from 'measur-tools-suite';

describe('Pump Results Modified', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate Pump results calculateModified correctly', function () {
        const pumpStyle = moduleInstance.PumpStyle.END_SUCTION_ANSI_API;
        const pumpEfficiency = 80 / 100;
        const rpm = 1780;
        const drive = moduleInstance.Drive.DIRECT_DRIVE;
        const kviscosity = 1.0;
        const specificGravity = 1.0;
        const stageCount = 2;
        const speed = moduleInstance.SpecificSpeed.NOT_FIXED_SPEED;
        const specifiedEfficiency = 80;
        const pumpInput = new moduleInstance.PumpResultInput(
            pumpStyle,
            pumpEfficiency,
            rpm,
            drive,
            kviscosity,
            specificGravity,
            stageCount,
            speed,
            specifiedEfficiency
        );

        const lineFrequency = moduleInstance.LineFrequency.FREQ60;
        const motorRatedPower = 100;
        const motorRpm = 1780;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.SPECIFIED;
        const specifiedMotorEfficiency = 0.95;
        const motorRatedVoltage = 460;
        const fullLoadAmps = 225;
        const sizeMargin = 0;
        const motor = new moduleInstance.Motor(
            lineFrequency,
            motorRatedPower,
            motorRpm,
            efficiencyClass,
            specifiedMotorEfficiency,
            motorRatedVoltage,
            fullLoadAmps,
            sizeMargin
        );

        const flowRate = 1840;
        const head = 174.85;
        const loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        const motorPower = 80;
        const motorAmps = 125.857;
        const voltage = 480;
        const fieldData = new moduleInstance.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
        const pumpResult = new moduleInstance.PumpResult(pumpInput, motor, fieldData, 8760, 0.05);
        let calculatedResults: PumpResults | undefined;

        try {
            calculatedResults = pumpResult.calculateModified();

            assert.approximately(calculatedResults.pump_efficiency * 100, 80, 0.001, "pump_efficiency");
            assert.approximately(calculatedResults.motor_rated_power, 100, 0.001, "motor_rated_power");
            assert.approximately(calculatedResults.motor_shaft_power, 101.51891512553706, 0.001, "motor_shaft_power");
            assert.approximately(calculatedResults.mover_shaft_power, 101.51891512553706, 0.001, "mover_shaft_power");
            assert.approximately(calculatedResults.motor_efficiency * 100, 94.973283, 0.001, "motor_efficiency");
            assert.approximately(calculatedResults.motor_power_factor * 100, 86.926875, 0.001, "motor_power_factor");
            assert.approximately(calculatedResults.motor_current, 110.338892, 0.001, "motor_current");
            assert.approximately(calculatedResults.motor_power, 79.741528, 0.001, "motor_power");
            assert.approximately(calculatedResults.annual_energy, 698.535785, 0.001, "annual_energy");
            assert.approximately(calculatedResults.annual_cost * 1000, 34926.789251, 0.001, "annual_cost");
        } finally {
            calculatedResults?.delete();
            pumpResult.delete();
            fieldData.delete();
            motor.delete();
            pumpInput.delete();
        }
    });
});
