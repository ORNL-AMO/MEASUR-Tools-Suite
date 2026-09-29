import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat Cascade Heat High To Low', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate CascadeHeatHighToLow results correctly', function () {
        const gasInstance = new moduleInstance.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
        try {
            const results = moduleInstance.calculateCascadeHeatHighToLow(gasInstance, 1020, 5.00, 12.0, 1475, 0.07, 80, 8000, 9.50, 225, 17.5, 80, 7000, 60, 60, 0);
            assert.approximately(results.priFlueVolume, 175123.0293326335, 0.001);
            assert.approximately(results.hxEnergyRate, 4.2341865845, 0.001);
            assert.approximately(results.eqEnergySupply, 4.7235204084, 0.001);
            assert.approximately(results.effOpHours, 7000, 0.001);
            assert.approximately(results.energySavings, 33064.6428585547, 0.001);
            assert.approximately(results.costSavings, 165323.2142927737, 0.001);
            assert.approximately(results.hourlySavings, 4.7235204084, 0.001);
            assert.approximately(results.priExcessAir, 0.4519750365, 0.001);
            assert.approximately(results.priAvailableHeat, 0.4724916999, 0.001);
            assert.approximately(results.secExcessAir, -1.05775222, 0.001);
            assert.approximately(results.secAvailableHeat, 0.896487289, 0.001);
        } finally {
            gasInstance.delete();
        }
    });

});
