import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process heat water heating using exhaust', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate waterHeatingUsingExhaust results correctly', function () {
        const results = moduleInstance.waterHeatingUsingExhaust(0.69, 6000000, 0.7, 190, 170, 0.73, 0.88, 5);
        assert.approximately(results.recoveredHeat, 1302000, 0.001);
        assert.approximately(results.hotWaterFlow, 7810.437912, 0.001);
        assert.approximately(results.tonsRefrigeration, 79.205, 0.001);
        assert.approximately(results.capacityChiller, 69.7004, 0.001);
        assert.approximately(results.electricalEnergy, 167280.96, 0.001);
    });

});