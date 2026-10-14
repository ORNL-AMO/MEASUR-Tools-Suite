import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type MotorPowerModule } from 'measur-tools-suite';

describe('Motor Power', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    // Captured from the unchanged native MotorPower class at base 4c573f3.
    const goldens: ReadonlyArray<readonly [number, number, number, number]> = [
        [460, 100, 0.85, 67.723186575943089],
        [230, 25, 0.75, 7.4694691076407835],
        [400, 113.8, 0.9, 70.958657484481762],
        [2300, 557.9, 0.92, 2044.7143839683038],
        [460, 100, 1, 79.674337148168362],
        [0, 100, 0.85, 0],
        [460, 0, 0.85, 0],
        [460, 100, 0, 0],
        [-460, 100, 0.85, -67.723186575943089],
        [460, -100, 0.85, -67.723186575943089],
        [460, 100, -0.85, -67.723186575943089],
        [460, 100, 1.2, 95.609204577802032],
    ];

    it('exposes a typed scalar function without runtime allocation', function () {
        const powerModule: MotorPowerModule = moduleInstance;
        const result: number = powerModule.calculateMotorPower(460, 100, 0.85);
        assert.isFunction(powerModule.calculateMotorPower);
        assert.isNumber(result);
        assert.approximately(result, 67.723186575943089, 1e-10);
        assert.notProperty(moduleInstance, 'MotorPower');
    });

    it('preserves native goldens including zero, signed, and unclamped inputs', function () {
        for (const [voltage, current, powerFactor, expected] of goldens) {
            assert.approximately(
                moduleInstance.calculateMotorPower(voltage, current, powerFactor),
                expected,
                1e-10,
                `voltage=${voltage}, current=${current}, powerFactor=${powerFactor}`
            );
        }
    });
});
