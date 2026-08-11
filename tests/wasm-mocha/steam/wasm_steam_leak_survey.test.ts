import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type SteamLeakSurveyResults } from 'measur-tools-suite';

type ExpectedSteamLeakResults = Pick<SteamLeakSurveyResults, 'leakRate' | 'steamLoss' | 'energyLoss' | 'leakCost'>;

describe('Steam Leak Survey', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function validateSteamLeakResults(results: SteamLeakSurveyResults, expected: ExpectedSteamLeakResults): void {
        try {
            assert.approximately(results.leakRate, expected.leakRate, .01, "leakRate");
            assert.approximately(results.steamLoss, expected.steamLoss, .01, "steamLoss");
            assert.approximately(results.energyLoss, expected.energyLoss, .01, "energyLoss");
            assert.approximately(results.leakCost, expected.leakCost, .01, "leakCost");
        } finally {
            results.delete();
        }
    }

    it('calculates Steam Leaks', function () {
        assert.approximately(moduleInstance.QuantifySteamLeakByPlumeLength.estimate(300, 8, 80), 447.426, .01, "Quantify Steam Leak from Plume Length");

        const steamLeakElectric = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75);
        try {
            assert.approximately(steamLeakElectric.costOfSteam(), 0.059492, .01, "costOfSteam");
            assert.approximately(steamLeakElectric.costOfSteam(90), 0.058548, .01, "costOfSteam");
        } finally {
            steamLeakElectric.delete();
        }

        const steamLeakNaturalGas = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, moduleInstance.UtilityType.natural_gas, 15.50, 1.038, 0);
        try {
            assert.approximately(steamLeakNaturalGas.costOfSteam(), 0.03266, .01, "costOfSteam");
        } finally {
            steamLeakNaturalGas.delete();
        }

        const steamLeak = new moduleInstance.SteamLeakSurvey(8760, 500, 300, 0.1, 200, 400, 70, 80, 75, 15.50, 1.038);
        try {
            validateSteamLeakResults(steamLeak.estimateMethodPRVCalc(500),
                {leakRate: 500, steamLoss: 4380, energyLoss: 5291.35, leakCost: 137405.72});

            validateSteamLeakResults(steamLeak.estimateMethodTurbineCalc(90, 500),
                {leakRate: 500, steamLoss: 4380, energyLoss: 5291.35, leakCost: 133436.27});

            validateSteamLeakResults(steamLeak.orificeMethodCalc(90, 0.25, 0.8748, 14.70),
                {leakRate: 497.93, steamLoss: 4361.83, energyLoss: 5269.39, leakCost: 132882.69});

            validateSteamLeakResults(steamLeak.plumeMethodCalc(90, 8, 80),
                {leakRate: 447.426, steamLoss: 3919.45, energyLoss: 4734.97, leakCost: 119405.69});
        } finally {
            steamLeak.delete();
        }
    });
});
