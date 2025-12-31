import { assert } from 'chai';

describe('Steam water heating using flue', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate waterHeatingUsingFlue results correctly', function () {

        let gasInstance = new moduleInstance.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
        let results = moduleInstance.waterHeatingUsingFlue(gasInstance, 725, 0.05, 80, 0.02, 55.88, 3.45, 60, 500,
            225, 0.04, 0.625, 8000, 5.21, 37706, moduleInstance.SteamConditionType.Superheated, 60);
        gasInstance.delete();

        assert.approximately(results.flowFlueGas, 23658.1596137958, 0.01, "flowFlueGas");
        assert.approximately(results.effBoiler, 0.7193913738, 0.01, "effBoiler");
        assert.approximately(results.enthalpySteam, 2865.339, 0.01, "enthalpySteam");
        assert.approximately(results.enthalpyFW, 452.0478, 0.01, "enthalpyFW");
        assert.approximately(results.flowSteam, 15991.2762656448, 0.01, "flowSteam");
        assert.approximately(results.flowFW, 16630.9273162706, 0.01, "flowFW");
        assert.approximately(results.specheatFG, 1.1319998535, 0.01, "specheatFG");
        assert.approximately(results.heatCapacityFG, 26781.0332157512, 0.01, "heatCapacityFG");
        assert.approximately(results.specheatFW, 4.2285, 0.01, "specheatFW");
        assert.approximately(results.heatCapacityFW, 70323.6515387818, 0.01, "heatCapacityFW");
        assert.approximately(results.heatCapacityMin, 26781.0332157512, 0.01, "heatCapacityMin");
        assert.approximately(results.ratingHeatRecFW, 4649484.9332901333, 0.01, "ratingHeatRecFW");
        assert.approximately(results.tempFlueGasOut, 484.537, 0.01, "tempFlueGasOut");
        assert.approximately(results.tempFWOut, 446.4877442629, 0.01, "tempFWOut");
        assert.approximately(results.energySavingsBoiler, 51704.6503757363, 0.01, "energySavingsBoiler");
        assert.approximately(results.costSavingsBoiler, 269381.2284575859, 0.01, "costSavingsBoiler");
    });

});