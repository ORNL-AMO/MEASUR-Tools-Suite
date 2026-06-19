import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpResults } from 'measur-tools-suite';

describe('Pump Results Existing', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate Pump results calculateExisting correctly', function () {
        const pumpStyle = moduleInstance.PumpStyle.END_SUCTION_STOCK;
        const pumpEfficiency = 90 / 100;
        const rpm = 1780;
        const drive = moduleInstance.Drive.SPECIFIED;
        const kviscosity = 1.0;
        const specificGravity = 1.0;
        const stageCount = 1;
        const speed = moduleInstance.SpecificSpeed.FIXED_SPEED;
        const specifiedEfficiency = 95 / 100;
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
        const motorRatedPower = 300;
        const motorRpm = 1780;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.STANDARD;
        const specifiedMotorEfficiency = 0.95;
        const motorRatedVoltage = 460;
        const fullLoadAmps = 337.3;
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
        const head = 277.0;
        const loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        const motorPower = 150;
        const motorAmps = 80.5;
        const voltage = 460;
        const fieldData = new moduleInstance.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
        const pumpResult = new moduleInstance.PumpResult(pumpInput, motor, fieldData, 8760, 0.06);
        let calculatedResults: PumpResults | undefined;

        try {
            calculatedResults = pumpResult.calculateExisting();

            assert.approximately(calculatedResults.pump_efficiency * 100, 71.5541741283, 0.001, "pump_efficiency");
            assert.approximately(calculatedResults.motor_shaft_power, 189.2746748003, 0.001, "motor_shaft_power");
            assert.approximately(calculatedResults.mover_shaft_power, 179.8109410603, 0.001, "mover_shaft_power");
            assert.approximately(calculatedResults.motor_efficiency * 100, 94.132604934, 0.001, "motor_efficiency");
        } finally {
            calculatedResults?.delete();
            pumpResult.delete();
            fieldData.delete();
            motor.delete();
            pumpInput.delete();
        }
    });
});
