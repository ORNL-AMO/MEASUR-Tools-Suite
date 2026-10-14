import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type MotorPowerFactorInput,
    type MotorPowerFactorModule,
} from 'measur-tools-suite';

describe('Motor Power Factor', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function input(): MotorPowerFactorInput {
        return {
            lineFrequency: moduleInstance.LineFrequency.FREQ60,
            motorRpm: 1780,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
            specifiedEfficiency: 0,
            motorRatedPower: 100,
            loadFactor: 0.75,
            motorCurrent: 100,
            motorEfficiency: 0.9,
            ratedVoltage: 460,
        };
    }

    it('exposes the typed scalar function and removes the legacy constructor', function () {
        const calculator: MotorPowerFactorModule = moduleInstance;
        const result: number = calculator.calculateMotorPowerFactor(input());
        assert.isFunction(calculator.calculateMotorPowerFactor);
        assert.approximately(result, 0.7802596029265596, 1e-12);
        assert.notProperty(moduleInstance, 'MotorPowerFactor');
        assert.notProperty(moduleInstance, 'MotorPowerFactorInput');
    });

    // Captured from fully initialized native MotorPowerFactor inputs at base 2714873.
    // Frequency index, rpm, class index, specified efficiency, hp, load, A, efficiency, V, PF.
    const goldens: ReadonlyArray<readonly [number, number, number, number, number,
        number, number, number, number, number]> = [
        [0, 1780, 1, 0, 100, 0.75, 100, 0.9, 460, 0.7802596029265596],
        [0, 1780, 1, 0, 200, 0.25, 81.528659, 0.9303933838910918, 460, 0.6171822968233854],
        [1, 1450, 0, 0, 100, 0.5, 100, 0.9, 400, 0.5981990289103623],
        [0, 1780, 1, 0, 100, 1, 100, 0.95, 230, 1.9711821547618342],
        [0, 1780, 1, 0, 100, 1.5, 150, 0.95, 2300, 0.19711821547618347],
        [0, 1780, 1, 0, 100, 0, 30, 0, 460, 0.05316004605572918],
        [0, 1780, 1, 0, 100, 0.000999, 30, 0.9, 230, 0.05316004605572918],
        [0, 1780, 1, 0, 100, -0.000999, 30, 0.9, 400, 0.05316004605572918],
        [0, 1780, 1, 0, 100, 0.001, 30, 0.9, 460, 0.0034678204574513758],
        [0, 1780, 1, 0, 100, -0.001, 30, 0.9, 460, -0.0034678204574513758],
        [0, 1780, 1, 0, 100, 0.001001, 30, 0.9, 460, 0.0034712882779088265],
        [0, 1780, 1, 0, 100, -0.001001, 30, 0.9, 460, -0.0034712882779088265],
        [0, 1780, 0, 0, 100, 0, 30, 0, 460, 0.09068480088410688],
        [0, 1780, 2, 0, 100, 0, 30, 0, 460, 0.05031025820280281],
        [0, 1780, 3, 0.95, 100, 0, 30, 0, 460, 0.05274198840502102],
        [1, 1450, 1, 0, 100, 0, 30, 0, 400, 0.05316004605572918],
        [1, 1450, 3, 0.95, 150, 0, 50, 0, 230, 0.04711383388030136],
        [0, 1780, 1, 0, 100, 0, 30, 0.8, 0, 0.05316004605572918],
        [0, 1780, 1, 0, 100, 0, -30, 0, 460, -0.05316004605572918],
        [0, 1780, 1, 0, 100, 0.75, -100, 0.9, 460, -0.7802596029265596],
        [0, 1780, 1, 0, 100, -0.75, 100, 0.9, 460, -0.7802596029265596],
        [0, 1780, 1, 0, 100, 0.75, 100, -0.9, 460, -0.7802596029265596],
        [0, 1780, 1, 0, 100, 0.75, 100, 0.9, -460, -0.7802596029265596],
        [0, 1780, 1, 0, -100, 0.75, 100, 0.9, 460, -0.7802596029265596],
        [0, 1780, 1, 0, 100, 0.75, 20, 0.9, 460, 3.9012980146327974],
        [0, 1780, 1, 0, 0, 0.75, 100, 0.9, 460, 0],
        [0, 1780, 1, 0, 100, 0.75, 0, 0.9, 460, Infinity],
        [0, 1780, 1, 0, 100, 0.75, 100, 0, 460, Infinity],
        [0, 1780, 1, 0, 100, 0.75, 100, 0.9, 0, Infinity],
        [0, 1780, 1, 0, 100, 0, 0, 0, 460, Infinity],
        [0, 1780, 1, 0, 0, 0.75, 0, 0.9, 460, NaN],
    ];

    it('preserves native goldens including boundaries, signs, unclamped and nonfinite results', function () {
        const frequencies = [moduleInstance.LineFrequency.FREQ60, moduleInstance.LineFrequency.FREQ50];
        const classes = [moduleInstance.MotorEfficiencyClass.STANDARD,
            moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
            moduleInstance.MotorEfficiencyClass.PREMIUM, moduleInstance.MotorEfficiencyClass.SPECIFIED];
        for (const [frequency, rpm, efficiencyClass, specified, hp, load, current, efficiency, voltage, expected] of goldens) {
            const data: MotorPowerFactorInput = {
                lineFrequency: frequencies[frequency], motorRpm: rpm, efficiencyClass: classes[efficiencyClass],
                specifiedEfficiency: specified, motorRatedPower: hp, loadFactor: load,
                motorCurrent: current, motorEfficiency: efficiency, ratedVoltage: voltage,
            };
            const actual = moduleInstance.calculateMotorPowerFactor(data);
            const message = `load=${load}, current=${current}, voltage=${voltage}, class=${efficiencyClass}`;
            if (Number.isNaN(expected)) assert.isNaN(actual, message);
            else if (!Number.isFinite(expected)) assert.strictEqual(actual, expected, message);
            else assert.approximately(actual, expected, 1e-10, message);
        }
    });

    it('does not mutate inputs or retain state between loaded and near-zero calls', function () {
        const data: MotorPowerFactorInput = Object.freeze(input());
        const before = { ...data };
        const first = moduleInstance.calculateMotorPowerFactor(data);
        const nearZero: MotorPowerFactorInput = { ...data, loadFactor: 0, motorCurrent: 30 };
        assert.approximately(moduleInstance.calculateMotorPowerFactor(nearZero), 0.053160046055729181, 1e-12);
        assert.strictEqual(moduleInstance.calculateMotorPowerFactor(data), first);
        assert.deepEqual(data, before);
        assert.strictEqual(nearZero.loadFactor, 0);
        assert.strictEqual(nearZero.motorCurrent, 30);
        assert.notProperty(data, 'delete');
    });

    it('ignores supplied voltage and operating efficiency only in the near-zero branch', function () {
        const nearZero: MotorPowerFactorInput = { ...input(), loadFactor: 0, motorCurrent: 30 };
        const expected = moduleInstance.calculateMotorPowerFactor(nearZero);
        assert.strictEqual(moduleInstance.calculateMotorPowerFactor({ ...nearZero,
            ratedVoltage: 2300, motorEfficiency: NaN }), expected);
        const loaded = input();
        assert.approximately(moduleInstance.calculateMotorPowerFactor({ ...loaded, ratedVoltage: 230 }),
            moduleInstance.calculateMotorPowerFactor(loaded) * 2, 1e-12);
    });

    it('uses complete nameplate data for MotorPerformance at zero load', function () {
        const instance = new moduleInstance.MotorPerformance(moduleInstance.LineFrequency.FREQ60, 1780,
            moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, 200, 0, 0, 460, 225.8);
        const output = instance.calculate();
        try {
            assert.approximately(output.current, 27.570269143886257, 1e-10);
            assert.strictEqual(output.efficiency, 0);
            assert.approximately(output.powerFactor, 4.5008995882102676, 1e-10);
        } finally {
            output.delete();
            instance.delete();
        }
    });
});
