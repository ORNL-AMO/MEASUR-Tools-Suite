import { assert } from 'chai';

describe('Pump Results Existing', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate Pump results calculateExisting correctly', function () {
        //pump input
        let pumpStyle = moduleInstance.PumpStyle.END_SUCTION_STOCK;
        let pumpEfficiency = 90 / 100;
        let rpm = 1780;
        let drive = moduleInstance.Drive.SPECIFIED;
        let kviscosity = 1.0;
        let specificGravity = 1.0;
        let stageCount = 1;
        let speed = moduleInstance.SpecificSpeed.FIXED_SPEED;
        let specifiedEfficiency = 95 / 100;
        let pumpInput = new moduleInstance.PumpResultInput(pumpStyle, pumpEfficiency, rpm, drive, kviscosity, specificGravity, stageCount, speed, specifiedEfficiency);
        //motor
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        let motorRatedPower = 300;
        let motorRpm = 1780;
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.STANDARD;
        let specifiedMotorEfficiency = .95;
        let motorRatedVoltage = 460;
        let fullLoadAmps = 337.3;
        let sizeMargin = 0;
        let motor = new moduleInstance.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedMotorEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
        //field data
        let flowRate = 1840;
        let head = 277.0;
        let loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        let motorPower = 150;
        let motorAmps = 80.5;
        let voltage = 460;
        let fieldData = new moduleInstance.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
        let pumpResult = new moduleInstance.PumpResult(pumpInput, motor, fieldData, 8760, 0.06);
        let calculatedResults = pumpResult.calculateExisting();
        pumpResult.delete();
        fieldData.delete();
        motor.delete();
        pumpInput.delete();
        assert.approximately(calculatedResults.pump_efficiency * 100, 71.5541741283, .001, "pump_efficiency");
        assert.approximately(calculatedResults.motor_shaft_power, 189.2746748003, .001, "motor_shaft_power");
        assert.approximately(calculatedResults.mover_shaft_power, 179.8109410603, .001, "mover_shaft_power");
        assert.approximately(calculatedResults.motor_efficiency * 100, 94.132604934, .001, "motor_efficiency");
    });
})