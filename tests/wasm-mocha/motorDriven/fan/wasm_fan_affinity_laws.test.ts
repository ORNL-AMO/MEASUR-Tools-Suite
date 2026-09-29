import { assert } from 'chai';
import createModule, {
    type FanAffinityLaws,
    type FanAffinityLawsInput,
    type FanAffinityLawsOutput,
    type MeasurToolsSuite
} from 'measur-tools-suite';

type ExpectedFanAffinityLawsOutput = Pick<
    FanAffinityLawsOutput,
    'annualEnergyBaseline' | 'annualEnergyNew' | 'annualCostSavings'
>;

describe('Fan affinity laws', () => {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function validateFALOutput(results: FanAffinityLawsOutput, expected: ExpectedFanAffinityLawsOutput): void {
        try {
            assert.approximately(results.annualEnergyBaseline, expected.annualEnergyBaseline, 0.01, 'annualEnergyBaseline');
            assert.approximately(results.annualEnergyNew, expected.annualEnergyNew, 0.01, 'annualEnergyNew');
            assert.approximately(results.annualCostSavings, expected.annualCostSavings, 0.01, 'annualCostSavings');
        } finally {
            results.delete();
        }
    }

    function validateFanAffinityLaws(
        fal: FanAffinityLaws,
        calculate: (fal: FanAffinityLaws) => FanAffinityLawsOutput,
        expected: ExpectedFanAffinityLawsOutput
    ): void {
        try {
            validateFALOutput(calculate(fal), expected);
        } finally {
            fal.delete();
        }
    }

    it('Compute annual energy and cost savings', () => {
        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 0, 6240, 2, 8000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.VSD,
                moduleInstance.FlowMode.Volume, 5000
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 14125.64, annualEnergyNew: 3448.64, annualCostSavings: 747.39 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 97, 96, 100, 6240, 10, 30000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.TwoSpeed,
                moduleInstance.FlowMode.Percent, 55
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 67010.3, annualEnergyNew: 14239.7, annualCostSavings: 3693.94 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.05, 90, 92, 100, 8760, 5, 15000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.None,
                moduleInstance.FlowMode.Volume, 0
            ),
            (fal) => fal.changeFanSize(20, 18),
            { annualEnergyBaseline: 52898.55, annualEnergyNew: 31236.06, annualCostSavings: 1083.12 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.08, 96, 97, 91, 4380, 20, 60000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.VSD,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.changeFanSize(36, 40),
            { annualEnergyBaseline: 94072.16, annualEnergyNew: 26038.44, annualCostSavings: 5442.7 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.08, 96, 97, 0, 4380, 20, 60000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.TwoSpeed,
                moduleInstance.FlowMode.Volume, 40000
            ),
            (fal) => fal.changeFanSize(36, 38),
            { annualEnergyBaseline: 94072.16, annualEnergyNew: 51363.6, annualCostSavings: 3416.69 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 88, 6240, 2, 8000,
                moduleInstance.MotorControlType.VSD, moduleInstance.MotorControlType.VSD,
                moduleInstance.FlowMode.Volume, 5000
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 9626.23, annualEnergyNew: 3448.64, annualCostSavings: 432.431 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 97, 96, 90, 6240, 10, 30000,
                moduleInstance.MotorControlType.TwoSpeed, moduleInstance.MotorControlType.TwoSpeed,
                moduleInstance.FlowMode.Percent, 55
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 55283.5, annualEnergyNew: 14239.7, annualCostSavings: 2873.07 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 100, 8760, 25, 80000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.VSD,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 104573.43, annualCostSavings: 10031.3 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 100, 8760, 25, 80000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.TwoSpeed,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.calculate(),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 139431.24, annualCostSavings: 7591.26 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 100, 8760, 25, 80000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.None,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.changeFanSize(36, 32.75),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 154447.75, annualCostSavings: 6540.1 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 100, 8760, 25, 80000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.VSD,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.changeFanSize(36, 40),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 68610.63, annualCostSavings: 12548.7 }
        );

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(
                0.07, 95, 93, 100, 8760, 25, 80000,
                moduleInstance.MotorControlType.OnOff, moduleInstance.MotorControlType.TwoSpeed,
                moduleInstance.FlowMode.Percent, 75
            ),
            (fal) => fal.changeFanSize(36, 40),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 236128.03, annualCostSavings: 822.481 }
        );

        const input: FanAffinityLawsInput = {
            electricityCost: 0.07,
            driveEfficiency: 95,
            motorEfficiency: 93,
            flowPercentBaseline: 100,
            operatingHours: 8760,
            motorPower: 25,
            ratedFlow: 80000,
            motorControlTypeCurrent: moduleInstance.MotorControlType.OnOff,
            motorControlTypeNew: moduleInstance.MotorControlType.TwoSpeed,
            flowMode: moduleInstance.FlowMode.Percent,
            desiredFlowRate: 75
        };

        validateFanAffinityLaws(
            new moduleInstance.FanAffinityLaws(input),
            (fal) => fal.changeFanSize(36, 40),
            { annualEnergyBaseline: 247877.76, annualEnergyNew: 236128.03, annualCostSavings: 822.481 }
        );
    });
});
