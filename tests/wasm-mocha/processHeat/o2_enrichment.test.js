import { assert } from 'chai';

describe('Process Heat O2 Enrichment', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate calculateO2Enrichment results correctly 1', function () {
        let results = moduleInstance.calculateO2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10);
        assert.approximately(results.availableHeat, 61.97, 0.001);
        assert.approximately(results.availableHeatEnriched, 74.2210855231, 0.001);
        assert.approximately(results.fuelSavingsEnriched, 16.5058213035, 0.001);
        assert.approximately(results.fuelConsumptionEnriched, 8.3494178697, 0.001);
    });

    it('should calculate calculateO2Enrichment results correctly 2', function () {
        let results = moduleInstance.calculateO2Enrichment(21, 100, 2200, 2300, 5, 1, 900, 80, 10);
        assert.approximately(results.availableHeat, 49.7183629149, 0.001);
        assert.approximately(results.availableHeatEnriched, 69.9474376972, 0.001);
        assert.approximately(results.fuelSavingsEnriched, 28.9203942964, 0.001);
        assert.approximately(results.fuelConsumptionEnriched, 7.1079605704, 0.001);
    });

    it('should calculate calculateO2Enrichment results correctly 3', function () {
        let results = moduleInstance.calculateO2Enrichment(21, 100, 2200, 2300, 8, 3, 1100, 110, 10);
        assert.approximately(results.availableHeat, 49.1204784776, 0.001);
        assert.approximately(results.availableHeatEnriched, 66.3723712295, 0.001);
        assert.approximately(results.fuelSavingsEnriched, 25.9925816002, 0.001);
        assert.approximately(results.fuelConsumptionEnriched, 7.40074184, 0.001);
    });

});