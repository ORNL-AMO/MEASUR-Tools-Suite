import { assert } from 'chai';
import createModule, { type FanOutput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Fan Assessment Results Existing', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculateExisting of FanResult correctly', function () {
        const fanSpeed = 1180;
        const drive = moduleInstance.Drive.DIRECT_DRIVE;
        const lineFrequency = moduleInstance.LineFrequency.FREQ60;
        const motorRatedPower = 600;
        const motorRpm = 1180;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        const specifiedEfficiency = 100;
        const motorRatedVoltage = 460;
        const fullLoadAmps = 683.2505707137;
        const sizeMargin = 1;
        const measuredPower = 460;
        const measuredVoltage = 460;
        const measuredAmps = 660;
        const flowRate = 129691;
        const inletPressure = -16.36;
        const outletPressure = 1.1;
        const compressibilityFactor = 0.988;
        const loadEstimationMethod = moduleInstance.LoadEstimationMethod.POWER;
        const operatingHours = 8760;
        const unitCost = 0.06;
        const airDensity = 1.02;
        const velocityPressure = 0;
        const specifiedDriveEfficiency = 1;

        const fanInput = new moduleInstance.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
        const motor = new moduleInstance.Motor(
            lineFrequency,
            motorRatedPower,
            motorRpm,
            efficiencyClass,
            specifiedEfficiency,
            motorRatedVoltage,
            fullLoadAmps,
            sizeMargin
        );
        const baselineFieldData = new moduleInstance.FieldDataBaseline(
            measuredPower,
            measuredVoltage,
            measuredAmps,
            flowRate,
            inletPressure,
            outletPressure,
            compressibilityFactor,
            loadEstimationMethod,
            velocityPressure
        );
        const fanResult = new moduleInstance.FanResult(fanInput, motor, operatingHours, unitCost);
        const output: FanOutput = fanResult.calculateExisting(baselineFieldData);

        try {
            output.fanEfficiency *= 100;
            output.motorEfficiency *= 100;
            output.motorPowerFactor *= 100;
            output.driveEfficiency *= 100;

            assert.approximately(output.fanEfficiency, 59.5398315, 0.001, "fanEfficiency");
            assert.approximately(output.motorRatedPower, 600.0, 0.001, "motorRatedPower");
            assert.approximately(output.motorShaftPower, 590.622186263, 0.001, "motorShaftPower");
            assert.approximately(output.fanShaftPower, 590.622186263, 0.001, "fanShaftPower");
            assert.approximately(output.motorEfficiency, 95.78351108, 0.001, "motorEfficiency");
            assert.approximately(output.motorPowerFactor, 85.77466651, 0.001, "motorPowerFactor");
            assert.approximately(output.motorCurrent, 673.1011529439, 0.001, "motorCurrent");
            assert.approximately(output.motorPower, 460.0, 0.001, "motorPower");
            assert.approximately(output.annualEnergy, 4029.6, 0.001, "annualEnergy");
            assert.approximately(output.annualCost, 241.776, 0.001, "annualCost");
            assert.approximately(output.estimatedFLA, 683.2505707137, 0.001, "estimatedFLA");
            assert.approximately(output.fanEnergyIndex, 1.247872, 0.001, "fanEnergyIndex");
        } finally {
            output.delete();
            fanResult.delete();
            baselineFieldData.delete();
            motor.delete();
            fanInput.delete();
        }
    });
});
