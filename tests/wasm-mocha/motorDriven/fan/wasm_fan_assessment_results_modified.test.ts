import { assert } from 'chai';
import createModule, { type FanOutput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Fan Assessment Results Modified', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculateModified of FanResult correctly', function () {
        const fanSpeed = 1180;
        const drive = moduleInstance.Drive.DIRECT_DRIVE;
        const lineFrequency = moduleInstance.LineFrequency.FREQ60;
        const motorRatedPower = 600;
        const motorRpm = 1180;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        const specifiedEfficiency = 100 / 100;
        const motorRatedVoltage = 460;
        const fullLoadAmps = 683.2505707137;
        const sizeMargin = 1;
        const measuredVoltage = 460;
        const measuredAmps = 660;
        const flowRate = 129691;
        const inletPressure = -16.36;
        const outletPressure = 1.1;
        const compressibilityFactor = 0.988;
        const operatingHours = 8760;
        const unitCost = 0.06;
        const airDensity = 1.02;
        const fanEfficiency = 59.5398315 / 100;
        const specifiedDriveEfficiency = 100 / 100;
        const velocityPressure = 0;

        const fanInput = new moduleInstance.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
        const fanFieldData = new moduleInstance.FieldDataModified(
            measuredVoltage,
            measuredAmps,
            flowRate,
            inletPressure,
            outletPressure,
            compressibilityFactor,
            velocityPressure
        );
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
        const fanResult = new moduleInstance.FanResult(fanInput, motor, operatingHours, unitCost);
        const output: FanOutput = fanResult.calculateModified(fanFieldData, fanEfficiency);

        try {
            output.fanEfficiency *= 100;
            output.motorEfficiency *= 100;
            output.motorPowerFactor *= 100;
            output.driveEfficiency *= 100;

            assert.approximately(output.fanEfficiency, 59.5398315, 0.001, "fanEfficiency");
            assert.approximately(output.motorRatedPower, 600.0, 0.001, "motorRatedPower");
            assert.approximately(output.motorShaftPower, 590.622186263, 0.001, "motorShaftPower");
            assert.approximately(output.fanShaftPower, 590.622186263, 0.001, "fanShaftPower");
            assert.approximately(output.motorEfficiency, 95.783511, 0.001, "motorEfficiency");
            assert.approximately(output.motorPowerFactor, 85.774801, 0.001, "motorPowerFactor");
            assert.approximately(output.motorCurrent, 673.100309, 0.001, "motorCurrent");
            assert.approximately(output.motorPower, 460.000144, 0.001, "motorPower");
            assert.approximately(output.annualEnergy, 4029.601262, 0.001, "annualEnergy");
            assert.approximately(output.annualCost, 241.776076, 0.001, "annualCost");
            assert.approximately(output.fanEnergyIndex, 1.247872, 0.001, "fanEnergyIndex");
        } finally {
            output.delete();
            fanResult.delete();
            motor.delete();
            fanFieldData.delete();
            fanInput.delete();
        }
    });
});
