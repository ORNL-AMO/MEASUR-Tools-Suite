import { assert } from 'chai';

describe('Steam air water cooling using flue', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate airWaterCoolingUsingFlue results correctly', function () {
        let gasInstance = new moduleInstance.GasCompositions('Gas', 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
        let results = moduleInstance.airWaterCoolingUsingFlue(gasInstance, 116, 300, 125, 70, 60, 0.04, 60, 0);
        assert.approximately(results.excessAir, 0.21596, .01, "excessAir");
        assert.approximately(results.flowFlueGas, 107022.7016052115, .01, "flowFlueGas");
        assert.approximately(results.specHeat, 0.2577908474, .01, "specHeat");
        assert.approximately(results.fracCondensed, 0.19816, .01, "fracCondensed");
        assert.approximately(results.effThermal, 0.8443608099, .01, "effThermal");
        assert.approximately(results.effThermalLH, 0.86454, .01, "effThermalLH");
        assert.approximately(results.effLH, 0.02014, .01, "effLH");
        assert.approximately(results.heatRecovery, 2.3362, .01, "heatRecovery");
        assert.approximately(results.sensibleHeatRecovery, 4.83, .01, "sensibleHeatRecovery");
        gasInstance.delete();
    });
});