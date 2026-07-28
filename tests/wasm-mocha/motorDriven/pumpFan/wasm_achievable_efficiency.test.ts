import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('PumpFan OptimalSpecificSpeedCorrection', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate OptimalSpecificSpeedCorrection correctly', function () {
        const pumpStyle = moduleInstance.PumpStyle.END_SUCTION_SLURRY;
        const specificSpeed = 1170;
        const instance = new moduleInstance.OptimalSpecificSpeedCorrection(pumpStyle, specificSpeed);

        try {
            const achievableEfficiency = instance.calculate() * 100;
            assert.approximately(achievableEfficiency, 1.8942771852074485, 0.001, "achievableEfficiency");
        } finally {
            instance.delete();
        }
    });
});
