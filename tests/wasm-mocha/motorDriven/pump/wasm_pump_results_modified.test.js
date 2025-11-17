import { assert } from 'chai';

describe('Pump Results Modified', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate Pump results calculateModified correctly', function () {
        //pump input
        let pumpStyle = moduleInstance.PumpStyle.END_SUCTION_ANSI_API;
        let pumpEfficiency = 80 / 100;
        let rpm = 1780;
        let drive = moduleInstance.Drive.DIRECT_DRIVE;
        let kviscosity = 1.0;
        let specificGravity = 1.0;
        let stageCount = 2;
        let speed = moduleInstance.SpecificSpeed.NOT_FIXED_SPEED;
        let specifiedEfficiency = 80;
        let pumpInput = new moduleInstance.PumpResultInput(pumpStyle, pumpEfficiency, rpm, drive, kviscosity, specificGravity, stageCount, speed, specifiedEfficiency);
        //motor
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        let motorRatedPower = 100;
        let motorRpm = 1780;
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.SPECIFIED;
        let specifiedMotorEfficiency = .95;
        let motorRatedVoltage = 460;
        let fullLoadAmps = 225;
        let sizeMargin = 0;
        let motor = new moduleInstance.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedMotorEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
        //field data
        let flowRate = 1840;
        let head = 174.85;
        let loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        let motorPower = 80;
        let motorAmps = 125.857;
        let voltage = 480;
        let fieldData = new moduleInstance.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
        let pumpResult = new moduleInstance.PumpResult(pumpInput, motor, fieldData, 8760, 0.05);
        let calculatedResults = pumpResult.calculateModified();
        pumpResult.delete();
        fieldData.delete();
        motor.delete();
        pumpInput.delete();

        assert.approximately(calculatedResults.pump_efficiency * 100, 80, .001, "pump_efficiency");
        assert.approximately(calculatedResults.motor_rated_power, 100, .001, "motor_rated_power");
        assert.approximately(calculatedResults.motor_shaft_power, 101.51891512553706, .001, "motor_shaft_power");
        assert.approximately(calculatedResults.mover_shaft_power, 101.51891512553706, .001, "mover_shaft_power");
        assert.approximately(calculatedResults.motor_efficiency * 100, 94.973283, .001, "motor_efficiency");
        assert.approximately(calculatedResults.motor_power_factor * 100, 86.926875, .001, "motor_power_factor");
        assert.approximately(calculatedResults.motor_current, 110.338892, .001, "motor_current");
        assert.approximately(calculatedResults.motor_power, 79.741528, .001, "motor_power");
        assert.approximately(calculatedResults.annual_energy, 698.535785, .001, "annual_energy");
        assert.approximately(calculatedResults.annual_cost * 1000, 34926.789251, .001, "annual_cost");
    });
})