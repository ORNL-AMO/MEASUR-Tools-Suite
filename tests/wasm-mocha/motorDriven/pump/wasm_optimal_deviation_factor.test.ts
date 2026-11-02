import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OptimalDeviationFactorModule,
    type PumpEfficiencyResults,
} from 'measur-tools-suite';

describe('OptimalDeviationFactor stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts scalar flow and preserves captured multipliers across the numeric range', function () {
        const calculator: OptimalDeviationFactorModule = moduleInstance;
        assert.isFunction(calculator.calculateOptimalDeviationFactor);
        // Native legacy captures at 892065d, -O3, before class removal; allow cross-runtime libm rounding.
        const fixtures: { flowRate: number; expected: number }[] = [
            { flowRate: 0.001, expected: 6.3254019222916433 },
            { flowRate: 1, expected: 1.4871053405999999 },
            { flowRate: 100, expected: 1.0996840790246096 },
            { flowRate: 1000, expected: 1.0455029577240247 },
            { flowRate: 2000, expected: 1.0360243794198285 },
            { flowRate: 10000, expected: 1.0210964032018048 },
            { flowRate: 100000, expected: 1.0101006042969669 },
            { flowRate: 1e-300, expected: 4.042960209397273e104 },
            { flowRate: 2.2250738585072014e-308, expected: 1.9418237299496365e107 },
            { flowRate: Number.MIN_VALUE, expected: 5.9329646185546964e112 },
            { flowRate: Number.MAX_VALUE, expected: 1.0010805906 },
        ];
        for (const { flowRate, expected } of fixtures) {
            const actual: number = calculator.calculateOptimalDeviationFactor(flowRate);
            assert.isNumber(actual);
            assert.approximately(actual, expected, Math.abs(expected) * 1e-12, `flowRate=${flowRate} US gpm`);
        }
        for (const name of ['OptimalDeviationFactor', 'OptimalDeviationFactorInput', 'OptimalDeviationFactorResult']) {
            assert.notProperty(moduleInstance, name);
        }
    });

    it('preserves nonfinite arithmetic and repeated-call independence', function () {
        for (const flowRate of [0, -0]) {
            assert.strictEqual(moduleInstance.calculateOptimalDeviationFactor(flowRate), Infinity);
        }
        for (const flowRate of [-1, -Infinity, NaN]) {
            assert.isNaN(moduleInstance.calculateOptimalDeviationFactor(flowRate));
        }
        assert.strictEqual(moduleInstance.calculateOptimalDeviationFactor(Infinity), 1.0010805906);
        const original: number = moduleInstance.calculateOptimalDeviationFactor(2000);
        moduleInstance.calculateOptimalDeviationFactor(1);
        moduleInstance.calculateOptimalDeviationFactor(NaN);
        assert.strictEqual(moduleInstance.calculateOptimalDeviationFactor(2000), original);
    });

    it('preserves the existing composite calculator and its cleanup contract', function () {
        const fixtures = [
            { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, flowRate: 2000, rpm: 2000,
                viscosity: 1.107, stages: 1, head: 137, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flowRate: 10000, rpm: 1800,
                viscosity: 10, stages: 3, head: 200, average: 0.88589634859567956, maximum: 0.90458557516066063 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, flowRate: 100, rpm: 1200,
                viscosity: 1, stages: 1, head: 75, average: 0.30297122881577326, maximum: 0.33317263673122788 },
            { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, flowRate: 2000, rpm: 2000,
                viscosity: 1.107, stages: 1, head: 137, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, flowRate: 2000, rpm: 2000,
                viscosity: 1.107, stages: 1, head: 137, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
        ];
        for (const fixture of fixtures) {
            const instance = new moduleInstance.PumpEfficiency(fixture.style, 0.90, fixture.rpm,
                fixture.viscosity, fixture.stages, fixture.flowRate, fixture.head);
            let result: PumpEfficiencyResults | undefined;
            try {
                result = instance.calculate();
                assert.approximately(result.average, fixture.average, Math.abs(fixture.average) * 1e-12);
                assert.approximately(result.max, fixture.maximum, Math.abs(fixture.maximum) * 1e-12);
            } finally {
                result?.delete();
                instance.delete();
            }
        }
    });
});
