import { assert } from 'chai';

describe('Steam Leak Survey', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function validateSteamLeakResults(results, expected) {
        assert.approximately(results.leakRate, expected.leakRate, .01, "leakRate");
        assert.approximately(results.steamLoss, expected.steamLoss, .01, "steamLoss");
        assert.approximately(results.energyLoss, expected.energyLoss, .01, "energyLoss");
        assert.approximately(results.leakCost, expected.leakCost, .01, "leakCost");
    }

    it('calculates Steam Leaks', function () {
        assert.approximately(moduleInstance.QuantifySteamLeakByPlumeLength.Estimate(300, 8, 80), 447.426, .01, "Quantify Steam Leak from Plume Length");

        let steamLeakElectric = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75);
        assert.approximately(steamLeakElectric.costOfSteam(), 0.059492, .01, "costOfSteam");
        assert.approximately(steamLeakElectric.costOfSteam(90), 0.058548, .01, "costOfSteam");
        steamLeakElectric.delete();

        let steamLeakNaturalGas = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, moduleInstance.UtilityType.natural_gas, 15.50, 1.038, 0);
        assert.approximately(steamLeakNaturalGas.costOfSteam(), 0.03266, .01, "costOfSteam");
        steamLeakNaturalGas.delete();

        let steamLeak = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, 15.50, 1.038);
        validateSteamLeakResults(steamLeak.estimateMethodPRVCalc(500),
            {leakRate: 500, steamLoss: 4380, energyLoss: 5291.35, leakCost: 137405.72});

        validateSteamLeakResults(steamLeak.estimateMethodTurbineCalc(90, 500),
            {leakRate: 500, steamLoss: 4380, energyLoss: 5291.35, leakCost: 133436.27});

        validateSteamLeakResults(steamLeak.orificeMethodCalc(90, 0.25, 0.8748, 14.70),
            {leakRate: 482.71, steamLoss: 4228.58, energyLoss: 5108.42, leakCost: 128823.25});

        validateSteamLeakResults(steamLeak.plumeMethodCalc(90, 8, 80),
            {leakRate: 447.426, steamLoss: 3919.45, energyLoss: 4734.97, leakCost: 119405.69});

        steamLeak.delete();
    });
});