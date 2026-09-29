import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat Energy Equivalency', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate calculateElectricalEquivalentHeatInput results correctly', function () {
        const results = moduleInstance.calculateElectricalEquivalentHeatInput(10, 60, 90);
        assert.approximately(results, 1953.807, 0.001);
    });

    it('should calculate calculateFuelFiredEquivalentHeatInput results correctly', function () {
        const results = moduleInstance.calculateFuelFiredEquivalentHeatInput(1800, 90, 60);
        assert.approximately(results, 9.21278339, 0.001);
    });
});