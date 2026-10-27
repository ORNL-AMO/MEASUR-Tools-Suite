import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OptimalPumpShaftPowerModule,
    type OptimalPumpShaftPowerInput,
    type OptimalFanShaftPowerInput,
} from 'measur-tools-suite';

describe('OptimalPumpShaftPower stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts typed plain inputs and returns hp without runtime constructors', function () {
        const calculator: OptimalPumpShaftPowerModule = moduleInstance;
        const pump: OptimalPumpShaftPowerInput = {
            flowRate: 1840, head: 174.85, specificGravity: 1, pumpEfficiency: 0.8,
        };
        const fan: OptimalFanShaftPowerInput = {
            flowRate: 2000, inletPressure: 20, outletPressure: 25,
            compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 1,
        };
        const pumpBefore = { ...pump };
        const fanBefore = { ...fan };
        const pumpPower: number = calculator.calculateOptimalPumpShaftPower(pump);
        const fanPower: number = calculator.calculateOptimalFanShaftPower(fan);
        assert.isFunction(calculator.calculateOptimalPumpShaftPower);
        assert.isFunction(calculator.calculateOptimalFanShaftPower);
        assert.isNumber(pumpPower);
        assert.isNumber(fanPower);
        assert.approximately(pumpPower, 101.51891512553706, 1e-10);
        assert.approximately(fanPower, 2.347270250445352, 1e-14);
        assert.deepEqual(pump, pumpBefore);
        assert.deepEqual(fan, fanBefore);
        for (const name of ['OptimalPumpShaftPower', 'OptimalPumpShaftPowerInput', 'OptimalFanShaftPowerInput']) {
            assert.notProperty(moduleInstance, name);
        }
        assert.notProperty(pump, 'delete');
        assert.notProperty(fan, 'delete');
        calculator.calculateOptimalPumpShaftPower({ ...pump, pumpEfficiency: 0.5 });
        calculator.calculateOptimalFanShaftPower({ ...fan, velocityPressure: 6 });
        assert.strictEqual(calculator.calculateOptimalPumpShaftPower(pump), pumpPower);
        assert.strictEqual(calculator.calculateOptimalFanShaftPower(fan), fanPower);
    });

    it('preserves captured pump and fan duties including supplied efficiency scaling', function () {
        // Captured from unchanged OptimalPumpShaftPower at 8d34462, compiled with -O3 before removal.
        const pumps: { input: OptimalPumpShaftPowerInput; expected: number }[] = [
            { input: { flowRate: 1840, head: 174.85, specificGravity: 1, pumpEfficiency: 0.8 }, expected: 101.51891512553706 },
            { input: { flowRate: 1000, head: 125, specificGravity: 1.5, pumpEfficiency: 0.75 }, expected: 63.109320489324432 },
            { input: { flowRate: 1000, head: 125, specificGravity: 1.5, pumpEfficiency: 0.5 }, expected: 94.663980733986648 },
            { input: { flowRate: 1000, head: 125, specificGravity: 1.5, pumpEfficiency: 1 }, expected: 47.331990366993324 },
            { input: { flowRate: 1000, head: 125, specificGravity: 1.5, pumpEfficiency: 1.5 }, expected: 31.554660244662216 },
            { input: { flowRate: 1000, head: 125, specificGravity: 1.5, pumpEfficiency: -0.75 }, expected: -63.109320489324432 },
            { input: { flowRate: 1000, head: 125, specificGravity: 0.5, pumpEfficiency: 0.75 }, expected: 21.036440163108143 },
            { input: { flowRate: 0, head: 125, specificGravity: 1.5, pumpEfficiency: 0.75 }, expected: 0 },
            { input: { flowRate: 1000, head: 0, specificGravity: 1.5, pumpEfficiency: 0.75 }, expected: 0 },
            { input: { flowRate: 1000, head: 125, specificGravity: 0, pumpEfficiency: 0.75 }, expected: 0 },
            { input: { flowRate: -1000, head: 125, specificGravity: 1.5, pumpEfficiency: 0.75 }, expected: -63.109320489324432 },
            { input: { flowRate: 1000, head: -125, specificGravity: 1.5, pumpEfficiency: 0.75 }, expected: -63.109320489324432 },
            { input: { flowRate: 1000, head: 125, specificGravity: -1.5, pumpEfficiency: 0.75 }, expected: -63.109320489324432 },
            { input: { flowRate: 1e-150, head: 1e-150, specificGravity: 1, pumpEfficiency: 0.75 }, expected: 3.3658304260973025e-304 },
            { input: { flowRate: 1e+150, head: 1e+150, specificGravity: 1, pumpEfficiency: 0.75 }, expected: 3.3658304260973029e+296 },
        ];
        for (const { input, expected } of pumps) {
            const actual = moduleInstance.calculateOptimalPumpShaftPower(input);
            if (expected === 0) {
                assert.isTrue(Object.is(actual, expected));
            } else {
                assert.approximately(actual, expected, Math.max(Number.MIN_VALUE, Math.abs(expected) * 1e-12));
            }
        }
        const fans: { input: OptimalFanShaftPowerInput; expected: number }[] = [
            { input: { flowRate: 129691, inletPressure: -16.36, outletPressure: 1.1, compressibilityFactor: 0.988, fanEfficiency: 0.595398315, velocityPressure: 0 }, expected: 590.62218629848621 },
            { input: { flowRate: 129691, inletPressure: -16.36, outletPressure: 1.1, compressibilityFactor: 0.988, fanEfficiency: 0.595398315, velocityPressure: 1 }, expected: 556.79502786214664 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 1 }, expected: 2.347270250445352 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.5, velocityPressure: 1 }, expected: 3.5209053756680282 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 1, velocityPressure: 1 }, expected: 1.7604526878340141 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 1.5, velocityPressure: 1 }, expected: 1.173635125222676 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: -0.75, velocityPressure: 1 }, expected: -2.347270250445352 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 0 }, expected: 2.9340878130566908 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 5 }, expected: 0 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 6 }, expected: -0.586817562611338 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 0, fanEfficiency: 0.75, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 0, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 2000, inletPressure: -20, outletPressure: -15, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 1 }, expected: 2.347270250445352 },
            { input: { flowRate: -2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.75, velocityPressure: 1 }, expected: -2.347270250445352 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: -1.4, fanEfficiency: 0.75, velocityPressure: 1 }, expected: -2.347270250445352 },
        ];
        for (const { input, expected } of fans) {
            const actual = moduleInstance.calculateOptimalFanShaftPower(input);
            if (expected === 0) {
                assert.isTrue(Object.is(actual, expected));
            } else {
                assert.approximately(actual, expected, Math.max(Number.MIN_VALUE, Math.abs(expected) * 1e-12));
            }
        }
    });

    it('retains zero efficiency, signed zeros, infinities and NaN', function () {
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: 1, pumpEfficiency: 0 }), Infinity));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: 1, pumpEfficiency: -0 }), -Infinity));
        assert.isNaN(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 0, head: 100, specificGravity: 1, pumpEfficiency: 0 }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: -0, head: 100, specificGravity: 1, pumpEfficiency: 0.8 }), -0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 0, head: 100, specificGravity: 1, pumpEfficiency: -0.8 }), -0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: Infinity, head: 100, specificGravity: 1, pumpEfficiency: 0.8 }), Infinity));
        assert.isNaN(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: Infinity, head: 0, specificGravity: 1, pumpEfficiency: 0.8 }));
        assert.isNaN(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: NaN, pumpEfficiency: 0.8 }));
        assert.isNaN(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: 1, pumpEfficiency: NaN }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: 1, pumpEfficiency: Infinity }), 0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: 1000, head: 100, specificGravity: 1, pumpEfficiency: -Infinity }), -0));
        assert.isNaN(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: Infinity, head: 100, specificGravity: 1, pumpEfficiency: Infinity }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: Number.MAX_VALUE, head: Number.MAX_VALUE, specificGravity: 1, pumpEfficiency: 1 }), Infinity));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalPumpShaftPower({ flowRate: Number.MIN_VALUE, head: 1, specificGravity: 1, pumpEfficiency: Number.MAX_VALUE }), 0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0, velocityPressure: 1 }), Infinity));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: -0, velocityPressure: 1 }), -Infinity));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0, velocityPressure: 6 }), -Infinity));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 0, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0, velocityPressure: 1 }));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0, velocityPressure: 5 }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: -0, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.8, velocityPressure: 1 }), -0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 0, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: -0.8, velocityPressure: 1 }), -0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: Infinity, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.8, velocityPressure: 1 }), Infinity));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: Infinity, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: 0.8, velocityPressure: 5 }));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: Infinity, outletPressure: Infinity, compressibilityFactor: 1.4, fanEfficiency: 0.8, velocityPressure: 1 }));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: NaN, fanEfficiency: 0.8, velocityPressure: 1 }));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: NaN, velocityPressure: 1 }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: Infinity, velocityPressure: 1 }), 0));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: -Infinity, velocityPressure: 1 }), -0));
        assert.isNaN(moduleInstance.calculateOptimalFanShaftPower({ flowRate: Infinity, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, fanEfficiency: Infinity, velocityPressure: 1 }));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: Number.MAX_VALUE, inletPressure: 0, outletPressure: Number.MAX_VALUE, compressibilityFactor: 1, fanEfficiency: 1, velocityPressure: 0 }), Infinity));
        assert.isTrue(Object.is(moduleInstance.calculateOptimalFanShaftPower({ flowRate: Number.MIN_VALUE, inletPressure: 0, outletPressure: 1, compressibilityFactor: 1, fanEfficiency: Number.MAX_VALUE, velocityPressure: 0 }), 0));
    });
});
