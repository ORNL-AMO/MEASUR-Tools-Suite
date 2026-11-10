import { assert } from 'chai';
import createModule, {
    type FanAffinityLawsInput,
    type FanAffinityLawsResult,
    type FanAffinityLawsTimeFactorResult,
    type MeasurToolsSuite
} from 'measur-tools-suite';

describe('Fan affinity laws namespace functions', () => {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function exampleInput(overrides: Partial<FanAffinityLawsInput> = {}): FanAffinityLawsInput {
        return {
            electricityCost: 0.07, driveEfficiency: 97, motorEfficiency: 96,
            flowPercentBaseline: 90, operatingHours: 6240, motorPower: 10, ratedFlow: 30000,
            motorControlTypeCurrent: moduleInstance.MotorControlType.TwoSpeed,
            motorControlTypeNew: moduleInstance.MotorControlType.TwoSpeed,
            flowMode: moduleInstance.FlowMode.Percent, desiredFlowRate: 55,
            ...overrides
        };
    }

    function validateOutput(actual: FanAffinityLawsResult, expected: FanAffinityLawsResult): void {
        assert.approximately(actual.annualEnergyBaseline, expected.annualEnergyBaseline, 0.01, 'annualEnergyBaseline');
        assert.approximately(actual.annualEnergyNew, expected.annualEnergyNew, 0.01, 'annualEnergyNew');
        assert.approximately(actual.annualCostSavings, expected.annualCostSavings, 0.01, 'annualCostSavings');
        assert.strictEqual(Object.getPrototypeOf(actual), Object.prototype);
        assert.doesNotHaveAnyKeys(actual, ['delete']);
    }

    it('matches all distinct original regression scenarios after S1 and S2', () => {
        const controls = moduleInstance.MotorControlType;
        const modes = moduleInstance.FlowMode;
        const scenarios: {
            originalCase: number;
            input: FanAffinityLawsInput;
            diameters?: [number, number];
            expected: FanAffinityLawsResult;
        }[] = [
            {
                originalCase: 1,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 0,
                    operatingHours: 6240,
                    motorPower: 2,
                    ratedFlow: 8000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.VSD,
                    flowMode: modes.Volume,
                    desiredFlowRate: 5000
                },
                expected: { annualEnergyBaseline: 14125.64, annualEnergyNew: 3448.64, annualCostSavings: 747.39 }
            },
            {
                originalCase: 2,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 97,
                    motorEfficiency: 96,
                    flowPercentBaseline: 100,
                    operatingHours: 6240,
                    motorPower: 10,
                    ratedFlow: 30000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.TwoSpeed,
                    flowMode: modes.Percent,
                    desiredFlowRate: 55
                },
                expected: { annualEnergyBaseline: 67010.31, annualEnergyNew: 14239.69, annualCostSavings: 3693.94 }
            },
            {
                originalCase: 3,
                input: {
                    electricityCost: 0.05,
                    driveEfficiency: 90,
                    motorEfficiency: 92,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 5,
                    ratedFlow: 15000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.None,
                    flowMode: modes.Volume,
                    desiredFlowRate: 0
                },
                diameters: [20, 18],
                expected: { annualEnergyBaseline: 52898.55, annualEnergyNew: 31236.07, annualCostSavings: 1083.12 }
            },
            {
                originalCase: 4,
                input: {
                    electricityCost: 0.08,
                    driveEfficiency: 96,
                    motorEfficiency: 97,
                    flowPercentBaseline: 100,
                    operatingHours: 4380,
                    motorPower: 20,
                    ratedFlow: 60000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.VSD,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                diameters: [36, 40],
                expected: { annualEnergyBaseline: 94072.16, annualEnergyNew: 26038.44, annualCostSavings: 5442.7 }
            },
            {
                originalCase: 5,
                input: {
                    electricityCost: 0.08,
                    driveEfficiency: 96,
                    motorEfficiency: 97,
                    flowPercentBaseline: 0,
                    operatingHours: 4380,
                    motorPower: 20,
                    ratedFlow: 60000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.TwoSpeed,
                    flowMode: modes.Volume,
                    desiredFlowRate: 40000
                },
                diameters: [36, 38],
                expected: { annualEnergyBaseline: 94072.16, annualEnergyNew: 29829.67, annualCostSavings: 5139.4 }
            },
            {
                originalCase: 6,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 88,
                    operatingHours: 6240,
                    motorPower: 2,
                    ratedFlow: 8000,
                    motorControlTypeCurrent: controls.VSD,
                    motorControlTypeNew: controls.VSD,
                    flowMode: modes.Volume,
                    desiredFlowRate: 5000
                },
                expected: { annualEnergyBaseline: 14125.64, annualEnergyNew: 5060.58, annualCostSavings: 634.55 }
            },
            {
                originalCase: 7,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 97,
                    motorEfficiency: 96,
                    flowPercentBaseline: 90,
                    operatingHours: 6240,
                    motorPower: 10,
                    ratedFlow: 30000,
                    motorControlTypeCurrent: controls.TwoSpeed,
                    motorControlTypeNew: controls.TwoSpeed,
                    flowMode: modes.Percent,
                    desiredFlowRate: 55
                },
                expected: { annualEnergyBaseline: 67010.31, annualEnergyNew: 17260.23, annualCostSavings: 3482.51 }
            },
            {
                originalCase: 8,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 25,
                    ratedFlow: 80000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.VSD,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                expected: { annualEnergyBaseline: 247877.76, annualEnergyNew: 104573.43, annualCostSavings: 10031.3 }
            },
            {
                originalCase: 9,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 25,
                    ratedFlow: 80000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.TwoSpeed,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                expected: { annualEnergyBaseline: 247877.76, annualEnergyNew: 139431.24, annualCostSavings: 7591.26 }
            },
            {
                originalCase: 10,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 25,
                    ratedFlow: 80000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.None,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                diameters: [36, 32.75],
                expected: { annualEnergyBaseline: 247877.76, annualEnergyNew: 154447.75, annualCostSavings: 6540.1 }
            },
            {
                originalCase: 11,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 25,
                    ratedFlow: 80000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.VSD,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                diameters: [36, 40],
                expected: { annualEnergyBaseline: 247877.76, annualEnergyNew: 68610.63, annualCostSavings: 12548.7 }
            },
            {
                originalCase: 12,
                input: {
                    electricityCost: 0.07,
                    driveEfficiency: 95,
                    motorEfficiency: 93,
                    flowPercentBaseline: 100,
                    operatingHours: 8760,
                    motorPower: 25,
                    ratedFlow: 80000,
                    motorControlTypeCurrent: controls.OnOff,
                    motorControlTypeNew: controls.TwoSpeed,
                    flowMode: modes.Percent,
                    desiredFlowRate: 75
                },
                diameters: [36, 40],
                expected: { annualEnergyBaseline: 247877.76, annualEnergyNew: 86816.41, annualCostSavings: 11274.29 }
            }
        ];
        // Old #13 was #12 with the removed input-object constructor, so it is consolidated here.
        for (const scenario of scenarios) {
            const actual: FanAffinityLawsResult = scenario.diameters
                ? moduleInstance.calculateFanAffinityLawsWithFanSize(scenario.input, ...scenario.diameters)
                : moduleInstance.calculateFanAffinityLaws(scenario.input);
            validateOutput(actual, scenario.expected);
        }
    });

    it('exports functions and enums without legacy constructors or runtime value-object properties', () => {
        assert.isFunction(moduleInstance.calculateFanAffinityLaws);
        assert.isFunction(moduleInstance.calculateFanAffinityLawsWithFanSize);
        assert.isFunction(moduleInstance.get50PercentTimeFactor);
        for (const name of ['FanAffinityLaws', 'FanAffinityLawsOutput', 'FanAffinityLawsInput',
            'FanAffinityLawsResult', 'FanAffinityLawsTimeFactorResult']) {
            assert.notProperty(moduleInstance, name);
        }
    });

    it('preserves baseline power, unchanged operating points, and equal-diameter results for every control', () => {
        const controls = moduleInstance.MotorControlType;
        for (const current of [controls.OnOff, controls.TwoSpeed, controls.VSD, controls.None]) {
            for (const modified of [controls.OnOff, controls.TwoSpeed, controls.VSD, controls.None]) {
                const input = exampleInput({motorControlTypeCurrent: current, motorControlTypeNew: modified, desiredFlowRate: 90});
                const result: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(input);
                assert.approximately(result.annualEnergyBaseline, 10 / (0.97 * 0.96) * 6240, 1e-8);
                if (current === modified) {
                    assert.approximately(result.annualEnergyNew, result.annualEnergyBaseline, 1e-8);
                    assert.approximately(result.annualCostSavings, 0, 1e-8);
                }
                validateOutput(moduleInstance.calculateFanAffinityLawsWithFanSize(input, 36, 36), result);
            }
        }
    });

    it('matches the delivered-power VSD example with and without resizing', () => {
        const input = exampleInput({
            motorControlTypeCurrent: moduleInstance.MotorControlType.VSD,
            motorControlTypeNew: moduleInstance.MotorControlType.VSD,
            motorPower: 11.22, flowPercentBaseline: 7040 / 30000 * 100,
            flowMode: moduleInstance.FlowMode.Volume, desiredFlowRate: 5000
        });
        const result: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(input);
        assert.approximately(result.annualEnergyBaseline / 6240, 12.0489690722, 1e-8);
        assert.approximately(result.annualEnergyNew / 6240, 4.3166011808, 1e-8);
        const resized: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLawsWithFanSize(input, 36, 40);
        assert.approximately(resized.annualEnergyBaseline, result.annualEnergyBaseline, 1e-8);
        assert.approximately(resized.annualEnergyNew, result.annualEnergyNew * Math.pow(36 / 40, 4), 1e-8);
    });

    it('agrees across flow modes and equivalent volume units', () => {
        const input = exampleInput();
        const percent: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLawsWithFanSize(input, 36, 40);
        input.flowMode = moduleInstance.FlowMode.Volume;
        input.desiredFlowRate = 16500;
        validateOutput(moduleInstance.calculateFanAffinityLawsWithFanSize(input, 36, 40), percent);
        const volume: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(input);
        input.ratedFlow *= 0.00047194745;
        input.desiredFlowRate *= 0.00047194745;
        validateOutput(moduleInstance.calculateFanAffinityLaws(input), volume);
        validateOutput(moduleInstance.calculateFanAffinityLawsWithFanSize(input, 36, 40), percent);
    });

    it('returns plain time shares at boundaries and both rounded and exact resized flow fractions', () => {
        const scenarios: {flow: number; expected: FanAffinityLawsTimeFactorResult}[] = [
            {flow: 0, expected: {factor: 0, timeAbove50Percent: 0, timeAt50Percent: 0, timeAt0Percent: 1}},
            {flow: 0.25, expected: {factor: 0.0625, timeAbove50Percent: 0, timeAt50Percent: 0.5, timeAt0Percent: 0.5}},
            {flow: 0.5, expected: {factor: 0.125, timeAbove50Percent: 0, timeAt50Percent: 1, timeAt0Percent: 0}},
            {flow: 0.9, expected: {factor: 0.825, timeAbove50Percent: 0.8, timeAt50Percent: 0.2, timeAt0Percent: 0}},
            {flow: 1, expected: {factor: 1, timeAbove50Percent: 1, timeAt50Percent: 0, timeAt0Percent: 0}},
            {flow: 0.5668, expected: {factor: 0.2419, timeAbove50Percent: 0.1336, timeAt50Percent: 0.8664, timeAt0Percent: 0}},
            {flow: 40000 / (60000 * Math.pow(38 / 36, 3)), expected: {
                factor: 0.24198133838752, timeAbove50Percent: 0.133692958157166,
                timeAt50Percent: 0.866307041842834, timeAt0Percent: 0
            }}
        ];
        for (const {flow, expected} of scenarios) {
            const result: FanAffinityLawsTimeFactorResult = moduleInstance.get50PercentTimeFactor(flow);
            assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
            assert.notProperty(result, 'delete');
            for (const key of ['factor', 'timeAbove50Percent', 'timeAt50Percent', 'timeAt0Percent'] as const) {
                assert.approximately(result[key], expected[key], 1e-12, key);
                assert.isAtLeast(result[key], 0);
                assert.isAtMost(result[key], 1);
            }
            assert.approximately(result.timeAbove50Percent + result.timeAt50Percent + result.timeAt0Percent, 1, 1e-12);
        }
    });

    it('leaves input validation to the caller and returns raw arithmetic', () => {
        const extrapolated: FanAffinityLawsTimeFactorResult = moduleInstance.get50PercentTimeFactor(1.2);
        assert.approximately(extrapolated.factor, 1.35, 1e-12);
        assert.approximately(extrapolated.timeAbove50Percent, 1.4, 1e-12);
        assert.approximately(extrapolated.timeAt50Percent, -0.4, 1e-12);
        assert.strictEqual(extrapolated.timeAt0Percent, 0);
        assert.isNaN(moduleInstance.get50PercentTimeFactor(NaN).factor);

        const input = exampleInput({electricityCost: 0});
        const freeEnergy: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(input);
        assert.isAbove(freeEnergy.annualEnergyBaseline, 0);
        assert.isAbove(freeEnergy.annualEnergyNew, 0);
        assert.strictEqual(freeEnergy.annualCostSavings, 0);
        input.operatingHours = 0;
        validateOutput(moduleInstance.calculateFanAffinityLaws(input), {
            annualEnergyBaseline: 0, annualEnergyNew: 0, annualCostSavings: 0
        });
        for (const control of [moduleInstance.MotorControlType.VSD, moduleInstance.MotorControlType.TwoSpeed]) {
            const zeroFlow = exampleInput({motorControlTypeCurrent: control, flowPercentBaseline: 0});
            const result: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(zeroFlow);
            assert.isFinite(result.annualEnergyBaseline);
            assert.strictEqual(result.annualEnergyNew, Infinity);
        }
        const zeroEfficiency: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLaws(
            exampleInput({motorEfficiency: 0})
        );
        assert.strictEqual(zeroEfficiency.annualEnergyBaseline, Infinity);
        assert.isNaN(zeroEfficiency.annualCostSavings);
    });

    it('preserves zero modification flow and signed savings without enforcing flow limits', () => {
        for (const control of [moduleInstance.MotorControlType.VSD, moduleInstance.MotorControlType.TwoSpeed]) {
            assert.strictEqual(moduleInstance.calculateFanAffinityLaws(
                exampleInput({motorControlTypeNew: control, desiredFlowRate: 0})
            ).annualEnergyNew, 0);
        }
        const overcapacity = exampleInput({
            motorControlTypeNew: moduleInstance.MotorControlType.VSD,
            flowMode: moduleInstance.FlowMode.Volume, desiredFlowRate: 36000
        });
        assert.isBelow(moduleInstance.calculateFanAffinityLaws(overcapacity).annualCostSavings, 0);
        overcapacity.motorControlTypeNew = moduleInstance.MotorControlType.TwoSpeed;
        assert.isBelow(moduleInstance.calculateFanAffinityLaws(overcapacity).annualCostSavings, 0);
        overcapacity.desiredFlowRate = 30000;
        const resized: FanAffinityLawsResult = moduleInstance.calculateFanAffinityLawsWithFanSize(overcapacity, 36, 32);
        assert.isFinite(resized.annualEnergyNew);
        assert.isBelow(resized.annualCostSavings, 0);
    });
});
