import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OptimalSpecificSpeedInput,
    type OptimalSpecificSpeedModule,
} from 'measur-tools-suite';

describe('OptimalSpecificSpeed stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts required plain inputs and preserves captured duties', function () {
        const calculator: OptimalSpecificSpeedModule = moduleInstance;
        assert.isFunction(calculator.calculateOptimalSpecificSpeed);
        // Immutable native legacy captures at 23b58b0, Apple clang 21, -O3; permit libm rounding.
        const fixtures: { input: OptimalSpecificSpeedInput; expected: number }[] = [
            { input: { rpm: 2000, flowRate: 2000, head: 137, stageCount: 1 }, expected: 2233.5957167946208 },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: 1 }, expected: 1800 },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: 3 }, expected: 4103.1127025185997 },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: 1.5 }, expected: 2439.7254097465811 },
            { input: { rpm: 1750.5, flowRate: 750.25, head: 122.5, stageCount: 2.25 }, expected: 2392.2135126507915 },
            { input: { rpm: 1200, flowRate: 0.001, head: 75, stageCount: 1 }, expected: 1.4889677745633594 },
            { input: { rpm: 3600, flowRate: 100000, head: 1000, stageCount: 6 }, expected: 24542.338315697987 },
            { input: { rpm: 900, flowRate: 100, head: 0.001, stageCount: 1 }, expected: 1600451.4690350306 },
            { input: { rpm: -1800, flowRate: 1000, head: 100, stageCount: 1 }, expected: -1800 },
            { input: { rpm: 1800, flowRate: 1000, head: -100, stageCount: -2 }, expected: 3027.2270949133722 },
        ];
        for (const { input, expected } of fixtures) {
            const unchanged = { ...input };
            const actual: number = calculator.calculateOptimalSpecificSpeed(Object.freeze(input));
            assert.approximately(actual, expected, 1e-12 + Math.abs(expected) * 1e-14);
            assert.deepEqual(input, unchanged);
        }
        for (const name of ['OptimalSpecificSpeed', 'OptimalSpecificSpeedInput', 'OptimalSpecificSpeedResult']) {
            assert.notProperty(moduleInstance, name);
        }
    });

    it('preserves signed-zero and nonfinite arithmetic without validation', function () {
        const fixtures: { input: OptimalSpecificSpeedInput; expected: number }[] = [
            { input: { rpm: 1800, flowRate: 0, head: 100, stageCount: 1 }, expected: 0 },
            { input: { rpm: 1800, flowRate: -0, head: 100, stageCount: 1 }, expected: -0 },
            { input: { rpm: 0, flowRate: 1000, head: 100, stageCount: 1 }, expected: 0 },
            { input: { rpm: -0, flowRate: 1000, head: 100, stageCount: 1 }, expected: -0 },
            { input: { rpm: 1800, flowRate: 1000, head: 0, stageCount: 1 }, expected: Infinity },
            { input: { rpm: 1800, flowRate: 1000, head: -0, stageCount: 1 }, expected: Infinity },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: 0 }, expected: 0 },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: -0 }, expected: 0 },
            { input: { rpm: 1800, flowRate: -1, head: 100, stageCount: 1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: 1000, head: -100, stageCount: 1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: -1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: 1000, head: 0, stageCount: 0 }, expected: NaN },
            { input: { rpm: Infinity, flowRate: 1000, head: 100, stageCount: 1 }, expected: Infinity },
            { input: { rpm: 1800, flowRate: Infinity, head: 100, stageCount: 1 }, expected: Infinity },
            { input: { rpm: 1800, flowRate: 1000, head: Infinity, stageCount: 1 }, expected: 0 },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: Infinity }, expected: Infinity },
            { input: { rpm: NaN, flowRate: 1000, head: 100, stageCount: 1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: NaN, head: 100, stageCount: 1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: 1000, head: NaN, stageCount: 1 }, expected: NaN },
            { input: { rpm: 1800, flowRate: 1000, head: 100, stageCount: NaN }, expected: NaN },
            { input: { rpm: Number.MAX_VALUE, flowRate: Number.MAX_VALUE, head: 100, stageCount: 1 }, expected: Infinity },
            { input: { rpm: 2.2250738585072014e-308, flowRate: Number.MIN_VALUE, head: 100, stageCount: 1 }, expected: 0 },
        ];
        for (const { input, expected } of fixtures) {
            const actual = moduleInstance.calculateOptimalSpecificSpeed(input);
            assert.isTrue(Object.is(actual, expected), JSON.stringify(input));
        }
    });

    it('has no retained state between independent calls', function () {
        const input: OptimalSpecificSpeedInput = Object.freeze({ rpm: 1800, flowRate: 1000, head: 100, stageCount: 1.5 });
        const original = moduleInstance.calculateOptimalSpecificSpeed(input);
        moduleInstance.calculateOptimalSpecificSpeed({ rpm: 900, flowRate: 100, head: 10, stageCount: 3 });
        moduleInstance.calculateOptimalSpecificSpeed({ rpm: 1800, flowRate: -1, head: 100, stageCount: 1 });
        assert.strictEqual(moduleInstance.calculateOptimalSpecificSpeed(input), original);
    });
});
