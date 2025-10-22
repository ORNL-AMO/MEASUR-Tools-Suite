import { assert } from 'chai';

describe('Fan Assessment Results Existing', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculateExisting of FanResult correctly', function () {
        let fanSpeed = 1180;
        let drive = moduleInstance.Drive.DIRECT_DRIVE;
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        let motorRatedPower = 600;
        let motorRpm = 1180;
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        let specifiedEfficiency = 100;
        let motorRatedVoltage = 460;
        let fullLoadAmps = 683.2505707137;
        let sizeMargin = 1;
        let measuredPower = 460;
        let measuredVoltage = 460;
        let measuredAmps = 660;
        let flowRate = 129691;
        let inletPressure = -16.36;
        let outletPressure = 1.1;
        let compressibilityFactor = .988;
        let loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        let operatingHours = 8760;
        let unitCost = .06;
        let airDensity = 1.02;
        let velocityPressure = 0;
        //unused
        let specifiedDriveEfficiency = 1;

        let fanInput = new moduleInstance.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
        let motor = new moduleInstance.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
        let baselineFieldData = new moduleInstance.FieldDataBaseline(measuredPower, measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, loadEstimationMethod, velocityPressure);
        let fanResult = new moduleInstance.FanResult(fanInput, motor, operatingHours, unitCost);
        let output = fanResult.calculateExisting(baselineFieldData);
        fanInput.delete();
        motor.delete();
        baselineFieldData.delete();
        fanResult.delete();
        //perform conversions for return object
        output.fanEfficiency = output.fanEfficiency * 100;
        output.motorEfficiency = output.motorEfficiency * 100;
        output.motorPowerFactor = output.motorPowerFactor * 100;
        output.driveEfficiency = output.driveEfficiency * 100;

        assert.approximately(output.fanEfficiency, 59.5398315, .001, "fanEfficiency");
        assert.approximately(output.motorRatedPower, 600.0, .001, "motorRatedPower");
        assert.approximately(output.motorShaftPower, 590.622186263, .001, "motorShaftPower");
        assert.approximately(output.fanShaftPower, 590.622186263, .001, "fanShaftPower");
        assert.approximately(output.motorEfficiency, 95.78351108, .001, "motorEfficiency");
        assert.approximately(output.motorPowerFactor, 85.77466651, .001, "motorPowerFactor");
        assert.approximately(output.motorCurrent, 673.1011529439, .001, "motorCurrent");
        assert.approximately(output.motorPower, 460.0, .001, "motorPower");
        assert.approximately(output.annualEnergy, 4029.6, .001, "annualEnergy");
        assert.approximately(output.annualCost, 241.776, .001, "annualCost");
        assert.approximately(output.estimatedFLA, 683.2505707137, .001, "estimatedFLA");
        assert.approximately(output.fanEnergyIndex, 1.247872, .001, "fanEnergyIndex");
    });
});