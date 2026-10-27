import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type MoverEfficiencyModule,
    type PumpMoverEfficiencyInput,
    type FanMoverEfficiencyInput,
} from 'measur-tools-suite';

describe('MoverEfficiency stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts typed plain inputs and returns fractions without runtime constructors', function () {
        const calculator: MoverEfficiencyModule = moduleInstance;
        const pump: PumpMoverEfficiencyInput = {
            specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 125,
        };
        const fan: FanMoverEfficiencyInput = {
            flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25,
            compressibilityFactor: 1.4, velocityPressure: 1,
        };
        const pumpBefore = { ...pump };
        const fanBefore = { ...fan };
        const pumpEfficiency: number = calculator.calculatePumpMoverEfficiency(pump);
        const fanEfficiency: number = calculator.calculateFanMoverEfficiency(fan);
        assert.isNumber(pumpEfficiency);
        assert.isNumber(fanEfficiency);
        assert.approximately(pumpEfficiency, 0.3786559229, 1e-10);
        assert.approximately(fanEfficiency, 0.35209053756680281, 1e-14);
        assert.deepEqual(pump, pumpBefore);
        assert.deepEqual(fan, fanBefore);
        for (const name of ['MoverEfficiency', 'PumpMoverEfficiencyInput', 'FanMoverEfficiencyInput']) {
            assert.notProperty(moduleInstance, name);
        }
        assert.notProperty(pump, 'delete');
        assert.notProperty(fan, 'delete');
        calculator.calculatePumpMoverEfficiency({ ...pump, moverShaftPower: 25 });
        calculator.calculateFanMoverEfficiency({ ...fan, velocityPressure: 6 });
        assert.strictEqual(calculator.calculatePumpMoverEfficiency(pump), pumpEfficiency);
        assert.strictEqual(calculator.calculateFanMoverEfficiency(fan), fanEfficiency);
    });

    it('preserves all original pump golden rows and captured fan duties', function () {
        // Original pump goldens; the legacy second test case duplicated these 22 rows.
        const pumps: { input: PumpMoverEfficiencyInput; expected: number }[] = [
            { input: { specificGravity: 0.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 0.126218641 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 0.3786559229 },
            { input: { specificGravity: 3.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 0.8835304869 },
            { input: { specificGravity: 9.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 2.3981541786 },
            { input: { specificGravity: 20.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 5.1749642801 },
            { input: { specificGravity: 50.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 12.7480827388 },
            { input: { specificGravity: 1.5, flowRate: 500, head: 125, moverShaftPower: 125 }, expected: 0.1893279615 },
            { input: { specificGravity: 1.5, flowRate: 700, head: 125, moverShaftPower: 125 }, expected: 0.2650591461 },
            { input: { specificGravity: 1.5, flowRate: 1100, head: 125, moverShaftPower: 125 }, expected: 0.4165215152 },
            { input: { specificGravity: 1.5, flowRate: 1800, head: 125, moverShaftPower: 125 }, expected: 0.6815806613 },
            { input: { specificGravity: 1.5, flowRate: 2800, head: 125, moverShaftPower: 125 }, expected: 1.0602365842 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 25, moverShaftPower: 125 }, expected: 0.0757311846 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 75, moverShaftPower: 125 }, expected: 0.2271935538 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 125 }, expected: 0.3786559229 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 195, moverShaftPower: 125 }, expected: 0.5907032398 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 225, moverShaftPower: 125 }, expected: 0.6815806613 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 325, moverShaftPower: 125 }, expected: 0.9845053996 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 25 }, expected: 1.8932796147 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 75 }, expected: 0.6310932049 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 155 }, expected: 0.3053676798 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 255 }, expected: 0.1856156485 },
            { input: { specificGravity: 1.5, flowRate: 1000, head: 125, moverShaftPower: 425 }, expected: 0.1113693891 },
        ];
        // Captured from unchanged MoverEfficiency at 7b5b760, compiled with -O3 before class removal.
        const fans: { input: FanMoverEfficiencyInput; expected: number }[] = [
            { input: { flowRate: 129691, moverShaftPower: 590.622186263, inletPressure: -16.36, outletPressure: 1.1, compressibilityFactor: 0.988, velocityPressure: 0 }, expected: 0.59539831503577312 },
            { input: { flowRate: 129691, moverShaftPower: 590.622186263, inletPressure: -16.36, outletPressure: 1.1, compressibilityFactor: 0.988, velocityPressure: 1 }, expected: 0.56129760970726372 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 0 }, expected: 0.44011317195850364 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 0.35209053756680281 },
            { input: { flowRate: 2000, moverShaftPower: 1, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 1.7604526878340141 },
            { input: { flowRate: 2000, moverShaftPower: -5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: -0.35209053756680281 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 5 }, expected: 0 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 6 }, expected: -0.088022634391700702 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 0, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 0, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: -20, outletPressure: -15, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 0.35209053756680281 },
            { input: { flowRate: -2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: -0.35209053756680281 },
            { input: { flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25, compressibilityFactor: -1.4, velocityPressure: 1 }, expected: -0.35209053756680281 },
        ];
        for (const { input, expected } of pumps) {
            assert.approximately(moduleInstance.calculatePumpMoverEfficiency(input), expected, Math.max(1, Math.abs(expected)) * 1e-10);
        }
        for (const { input, expected } of fans) {
            assert.approximately(moduleInstance.calculateFanMoverEfficiency(input), expected, 1e-14);
        }
    });

    it('retains zero shaft power, signed zeros, infinities and NaN', function () {
        const pump: PumpMoverEfficiencyInput = {
            specificGravity: 1, flowRate: 1000, head: 100, moverShaftPower: 125,
        };
        const fan: FanMoverEfficiencyInput = {
            flowRate: 2000, moverShaftPower: 5, inletPressure: 20, outletPressure: 25,
            compressibilityFactor: 1.4, velocityPressure: 1,
        };
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: 0 }), 0);
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, head: 0 }), 0);
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, specificGravity: 0 }), 0);
        assert.isTrue(Object.is(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: -0 }), -0));
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, moverShaftPower: 0 }), Infinity);
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, moverShaftPower: -0 }), -Infinity);
        assert.isNaN(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: 0, moverShaftPower: 0 }));
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: Infinity }), Infinity);
        assert.isNaN(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: Infinity, head: 0 }));
        assert.isNaN(moduleInstance.calculatePumpMoverEfficiency({ ...pump, specificGravity: NaN }));
        assert.isNaN(moduleInstance.calculatePumpMoverEfficiency({ ...pump, moverShaftPower: NaN }));
        assert.strictEqual(moduleInstance.calculatePumpMoverEfficiency({ ...pump, moverShaftPower: Infinity }), 0);
        assert.isNaN(moduleInstance.calculatePumpMoverEfficiency({ ...pump, flowRate: Infinity, moverShaftPower: Infinity }));
        assert.isTrue(Object.is(moduleInstance.calculateFanMoverEfficiency({ ...fan, flowRate: -0 }), -0));
        assert.strictEqual(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: 0 }), Infinity);
        assert.strictEqual(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: -0 }), -Infinity);
        assert.strictEqual(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: 0, velocityPressure: 6 }), -Infinity);
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: 0, velocityPressure: 5 }));
        assert.strictEqual(moduleInstance.calculateFanMoverEfficiency({ ...fan, flowRate: Infinity }), Infinity);
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, flowRate: Infinity, velocityPressure: 5 }));
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, inletPressure: Infinity, outletPressure: Infinity }));
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, compressibilityFactor: NaN }));
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: NaN }));
        assert.strictEqual(moduleInstance.calculateFanMoverEfficiency({ ...fan, moverShaftPower: Infinity }), 0);
        assert.isNaN(moduleInstance.calculateFanMoverEfficiency({ ...fan, flowRate: Infinity, moverShaftPower: Infinity }));
    });
});
