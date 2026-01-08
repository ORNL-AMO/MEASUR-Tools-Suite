import { assert } from 'chai';

describe('Process Heat Energy Equivalency', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate calculateElectricalEquivalentHeatInput results correctly', function () {
        let results = moduleInstance.calculateElectricalEquivalentHeatInput(10, 60, 90);
        assert.approximately(results, 1953.807, 0.001);
    });

    it('should calculate calculateFuelFiredEquivalentHeatInput results correctly', function () {
        let results = moduleInstance.calculateFuelFiredEquivalentHeatInput(1800, 90, 60);
        assert.approximately(results, 9.21278339, 0.001);
    });
});