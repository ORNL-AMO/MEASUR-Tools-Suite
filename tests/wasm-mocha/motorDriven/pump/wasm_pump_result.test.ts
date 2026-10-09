import { assert } from 'chai';
import createModule, {
    type ExistingPumpResultInput,
    type MeasurToolsSuite,
    type ModifiedPumpResultInput,
    type PumpResultOutput,
} from 'measur-tools-suite';

describe('Pump Result', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates an existing rotodynamic pump result from measured power', function () {
        const input: ExistingPumpResultInput = {
            system: {
                pumpStyle: moduleInstance.PumpStyle.END_SUCTION_STOCK,
                drive: moduleInstance.Drive.SPECIFIED,
                specifiedDriveEfficiency: 0.95,
                specificGravity: 1,
                flowRate: 1840,
                head: 277,
                differentialPressure: 0,
                motorRatedPower: 300,
                motorRatedSpeed: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60,
                motorEfficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD,
                specifiedMotorEfficiency: 0.95,
                motorRatedVoltage: 460,
                operatingVoltage: 460,
                operatingHours: 8760,
                unitCost: 0.06,
            },
            motorFullLoadAmps: 337.3,
            loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER,
            measuredMotorPower: 150,
            measuredMotorCurrent: 80.5,
        };

        const result: PumpResultOutput = moduleInstance.calculateExistingPumpResult(input);

        assert.notProperty(input, 'delete');
        assert.notProperty(input, 'pumpStyle');
        assert.notProperty(input.system, 'delete');
        assert.notProperty(input.system, 'fieldVoltage');
        assert.approximately(result.pumpEfficiency * 100, 71.5541741283, 0.001, 'pumpEfficiency');
        assert.approximately(result.motorShaftPower, 189.2746748003, 0.001, 'motorShaftPower');
        assert.approximately(result.moverShaftPower, 179.8109410603, 0.001, 'moverShaftPower');
        assert.approximately(result.motorEfficiency * 100, 94.132604934, 0.001, 'motorEfficiency');
        assert.approximately(result.motorPower, 150, 0.001, 'motorPower');
        assert.approximately(result.annualEnergy, 1314, 0.001, 'annualEnergy');
        assert.approximately(result.annualCost, 78.84, 0.001, 'annualCost');
        assert.notProperty(result, 'delete');
    });

    it('calculates an existing positive-displacement pump from differential pressure', function () {
        const input: ExistingPumpResultInput = {
            system: {
                pumpStyle: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT,
                drive: moduleInstance.Drive.DIRECT_DRIVE,
                specifiedDriveEfficiency: 1,
                specificGravity: 1,
                flowRate: 100,
                head: 999,
                differentialPressure: 50,
                motorRatedPower: 200,
                motorRatedSpeed: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60,
                motorEfficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM,
                specifiedMotorEfficiency: 0.95,
                motorRatedVoltage: 460,
                operatingVoltage: 480,
                operatingHours: 8760,
                unitCost: 0.05,
            },
            motorFullLoadAmps: 225,
            loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER,
            measuredMotorPower: 80,
            measuredMotorCurrent: 125.857,
        };

        const result: PumpResultOutput = moduleInstance.calculateExistingPumpResult(input);
        const hydraulicPower = input.system.flowRate * input.system.differentialPressure / 1714.231;

        assert.approximately(result.pumpEfficiency, hydraulicPower / result.moverShaftPower, 0.000001);
        assert.approximately(result.motorPower, input.measuredMotorPower, 0.001);
        assert.approximately(
            result.annualEnergy,
            input.measuredMotorPower * input.system.operatingHours / 1000,
            0.001
        );
        assert.notProperty(result, 'delete');
    });

    it('calculates a modified rotodynamic pump result', function () {
        const input: ModifiedPumpResultInput = {
            system: {
                pumpStyle: moduleInstance.PumpStyle.END_SUCTION_ANSI_API,
                drive: moduleInstance.Drive.DIRECT_DRIVE,
                specifiedDriveEfficiency: 1,
                specificGravity: 1,
                flowRate: 1840,
                head: 174.85,
                differentialPressure: 0,
                motorRatedPower: 100,
                motorRatedSpeed: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60,
                motorEfficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED,
                specifiedMotorEfficiency: 0.95,
                motorRatedVoltage: 460,
                operatingVoltage: 480,
                operatingHours: 8760,
                unitCost: 0.05,
            },
            pumpEfficiency: 0.8,
        };

        const result: PumpResultOutput = moduleInstance.calculateModifiedPumpResult(input);

        assert.notProperty(input, 'delete');
        assert.notProperty(input, 'pumpStyle');
        assert.notProperty(input.system, 'delete');
        assert.approximately(result.pumpEfficiency * 100, 80, 0.001, 'pumpEfficiency');
        assert.approximately(result.motorRatedPower, 100, 0.001, 'motorRatedPower');
        assert.approximately(result.motorShaftPower, 101.51891512553706, 0.001, 'motorShaftPower');
        assert.approximately(result.moverShaftPower, 101.51891512553706, 0.001, 'moverShaftPower');
        assert.approximately(result.motorEfficiency * 100, 94.973283, 0.001, 'motorEfficiency');
        assert.approximately(result.motorPowerFactor * 100, 86.926875, 0.001, 'motorPowerFactor');
        assert.approximately(result.motorCurrent, 110.338892, 0.001, 'motorCurrent');
        assert.approximately(result.motorPower, 79.741528, 0.001, 'motorPower');
        assert.approximately(result.annualEnergy, 698.535785, 0.001, 'annualEnergy');
        assert.approximately(result.annualCost * 1000, 34926.789251, 0.001, 'annualCost');
        assert.notProperty(result, 'delete');
    });

    it('calculates a modified positive-displacement pump and removes the legacy API', function () {
        const input: ModifiedPumpResultInput = {
            system: {
                pumpStyle: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT,
                drive: moduleInstance.Drive.DIRECT_DRIVE,
                specifiedDriveEfficiency: 1,
                specificGravity: 1,
                flowRate: 100,
                head: 999,
                differentialPressure: 50,
                motorRatedPower: 200,
                motorRatedSpeed: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60,
                motorEfficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED,
                specifiedMotorEfficiency: 0.95,
                motorRatedVoltage: 460,
                operatingVoltage: 480,
                operatingHours: 2000,
                unitCost: 0.05,
            },
            pumpEfficiency: 0.8,
        };

        const result: PumpResultOutput = moduleInstance.calculateModifiedPumpResult(input);
        const expectedShaftPower =
            input.system.flowRate * input.system.differentialPressure / (1714.231 * input.pumpEfficiency);

        assert.approximately(result.moverShaftPower, expectedShaftPower, 0.000001);
        assert.approximately(result.motorShaftPower, expectedShaftPower, 0.000001);
        assert.approximately(result.annualEnergy, result.motorPower * input.system.operatingHours / 1000, 0.001);
        assert.approximately(result.annualCost, result.annualEnergy * input.system.unitCost, 0.001);
        assert.notProperty(result, 'delete');
        assert.notProperty(moduleInstance, 'PumpResultInput');
        assert.notProperty(moduleInstance, 'PumpFieldData');
        assert.notProperty(moduleInstance, 'PumpResult');
        assert.notProperty(moduleInstance, 'PumpResults');
    });
});
