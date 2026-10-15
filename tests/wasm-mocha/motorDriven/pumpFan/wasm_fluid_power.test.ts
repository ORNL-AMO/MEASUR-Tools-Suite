import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type FluidPowerModule,
    type PumpFluidPowerInput,
    type FanFluidPowerInput,
} from 'measur-tools-suite';

describe('FluidPower stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts typed plain inputs and returns numeric kW without runtime constructors', function () {
        const calculator: FluidPowerModule = moduleInstance;
        const pump: PumpFluidPowerInput = { specificGravity: 1.02, flowRate: 1000, head: 280 };
        const fan: FanFluidPowerInput = {
            flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1,
        };
        const pumpBefore = { ...pump };
        const fanBefore = { ...fan };
        const pumpPower: number = calculator.calculatePumpFluidPower(pump);
        const fanPower: number = calculator.calculateFanFluidPower(fan);
        assert.isNumber(pumpPower);
        assert.isNumber(fanPower);
        assert.approximately(pumpPower, 53.783681444345156, 1e-10);
        assert.approximately(fanPower, 1.3132977051241745, 1e-12);
        assert.deepEqual(pump, pumpBefore);
        assert.deepEqual(fan, fanBefore);
        for (const name of ['FluidPower', 'PumpFluidPowerInput', 'FanFluidPowerInput']) {
            assert.notProperty(moduleInstance, name);
        }
        assert.notProperty(pump, 'delete');
        assert.notProperty(fan, 'delete');
        calculator.calculatePumpFluidPower({ specificGravity: 2.5, flowRate: 125000, head: 5000 });
        calculator.calculateFanFluidPower({ ...fan, velocityPressure: 6 });
        assert.strictEqual(calculator.calculatePumpFluidPower(pump), pumpPower);
        assert.strictEqual(calculator.calculateFanFluidPower(fan), fanPower);
    });

    it('preserves the six original goldens and captured finite boundaries', function () {
        // Captured from unchanged FluidPower.h at 1998e82, compiled with -O3 before removal.
        const pumps: { input: PumpFluidPowerInput; expected: number }[] = [
            { input: { specificGravity: 1.02, flowRate: 1000, head: 280 }, expected: 53.7836814443 },
            { input: { specificGravity: 1.02, flowRate: 1200, head: 280 }, expected: 64.5404177332 },
            { input: { specificGravity: 1, flowRate: 0, head: 100 }, expected: 0 },
            { input: { specificGravity: 1, flowRate: 1000, head: 0 }, expected: 0 },
            { input: { specificGravity: 0, flowRate: 1000, head: 100 }, expected: 0 },
            { input: { specificGravity: 1, flowRate: -1000, head: 100 }, expected: -18.831821234014409 },
            { input: { specificGravity: 1, flowRate: 1000, head: -100 }, expected: -18.831821234014409 },
            { input: { specificGravity: -1, flowRate: 1000, head: 100 }, expected: -18.831821234014409 },
            { input: { specificGravity: 0.85, flowRate: 100, head: 25 }, expected: 0.40017620122280612 },
            { input: { specificGravity: 2.5, flowRate: 125000, head: 5000 }, expected: 294247.20678147511 },
        ];
        const fans: { input: FanFluidPowerInput; expected: number }[] = [
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 0 }, expected: 1.6416221314 },
            { input: { flowRate: 1200, inletPressure: 25, outletPressure: 35, compressibilityFactor: 1.4, velocityPressure: 0 }, expected: 1.9699465577 },
            { input: { flowRate: 129691, inletPressure: -16.36, outletPressure: 1.1, compressibilityFactor: 0.988, velocityPressure: 0 }, expected: 262.3349690747 },
            { input: { flowRate: 151961, inletPressure: -8.92, outletPressure: 2.28, compressibilityFactor: 0.995, velocityPressure: 0 }, expected: 198.5721824055 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 1.3132977051241745 },
            { input: { flowRate: 0, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 0, velocityPressure: 1 }, expected: 0 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 5 }, expected: 0 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 6 }, expected: -0.32832442628104364 },
            { input: { flowRate: -2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: -1.3132977051241745 },
            { input: { flowRate: 2000, inletPressure: 20, outletPressure: 25, compressibilityFactor: -1.4, velocityPressure: 1 }, expected: -1.3132977051241745 },
            { input: { flowRate: 2000, inletPressure: 25, outletPressure: 20, compressibilityFactor: 1.4, velocityPressure: 0 }, expected: -1.6416221314052184 },
            { input: { flowRate: 2000, inletPressure: -20, outletPressure: -15, compressibilityFactor: 1.4, velocityPressure: 1 }, expected: 1.3132977051241745 },
        ];
        for (const { input, expected } of pumps) {
            assert.approximately(moduleInstance.calculatePumpFluidPower(input), expected, Math.max(1, Math.abs(expected)) * 1e-10);
        }
        for (const { input, expected } of fans) {
            assert.approximately(moduleInstance.calculateFanFluidPower(input), expected, Math.max(1, Math.abs(expected)) * 1e-10);
        }
    });

    it('retains signed zero, infinities and NaN from the supplied arithmetic', function () {
        const pump: PumpFluidPowerInput = { specificGravity: 1, flowRate: Infinity, head: 100 };
        const fan: FanFluidPowerInput = {
            flowRate: Infinity, inletPressure: 20, outletPressure: 25, compressibilityFactor: 1, velocityPressure: 1,
        };
        assert.strictEqual(moduleInstance.calculatePumpFluidPower(pump), Infinity);
        assert.strictEqual(moduleInstance.calculatePumpFluidPower({ ...pump, flowRate: -Infinity }), -Infinity);
        assert.isNaN(moduleInstance.calculatePumpFluidPower({ ...pump, head: 0 }));
        assert.isNaN(moduleInstance.calculatePumpFluidPower({ ...pump, flowRate: 1000, specificGravity: NaN }));
        assert.isTrue(Object.is(moduleInstance.calculatePumpFluidPower({ ...pump, flowRate: -0 }), -0));
        assert.strictEqual(moduleInstance.calculateFanFluidPower(fan), Infinity);
        assert.strictEqual(moduleInstance.calculateFanFluidPower({ ...fan, velocityPressure: 6 }), -Infinity);
        assert.isNaN(moduleInstance.calculateFanFluidPower({ ...fan, velocityPressure: 5 }));
        assert.isNaN(moduleInstance.calculateFanFluidPower({ ...fan, flowRate: 2000, inletPressure: Infinity, outletPressure: Infinity }));
        assert.isNaN(moduleInstance.calculateFanFluidPower({ ...fan, flowRate: 2000, compressibilityFactor: NaN }));
        assert.isTrue(Object.is(moduleInstance.calculateFanFluidPower({ ...fan, flowRate: -0 }), -0));
    });
});
