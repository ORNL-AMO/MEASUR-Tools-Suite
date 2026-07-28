import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type WaterHeatingUsingSteamOutput } from 'measur-tools-suite';

describe('Steam water heating using steam', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate waterHeatingUsingSteam results correctly 1', function () {
        const results: WaterHeatingUsingSteamOutput = moduleInstance.waterHeatingUsingSteam(0.1565, 340.2, 285.93, 0.5150, 2.7255, 285.93, 0.2048, 0.72, 0.8, 7000);
        assert.approximately(results.tempWaterOut, 352.304, 0.01, "tempWaterOut");
        assert.approximately(results.bpTempWaterOut, 426.1, 0.01, "bpTempWaterOut");
        assert.approximately(results.enthalpySteamIn, 2695.04, 0.01, "enthalpySteamIn");
        assert.approximately(results.enthalpySteamOut, 472.5, 0.01, "enthalpySteamOut");
        assert.approximately(results.enthalpyMakeUpWater, 53.876, 0.01, "enthalpyMakeUpWater");
        assert.approximately(results.flowByPassSteam, 0, 0.01, "flowByPassSteam");
        assert.approximately(results.energySavedDWH, 7351062329.1926, 0.01, "energySavedDWH");
        assert.approximately(results.energySavedBoiler, 1246124501.2457, 0.01, "energySavedBoiler");
        assert.approximately(results.waterSaved, 2381.4, 0.01, "waterSaved");
        assert.approximately(results.heatGainRate, 756109.2681, 0.01, "heatGainRate");
    });


    it('should calculate waterHeatingUsingSteam results correctly 2', function () {
        const results: WaterHeatingUsingSteamOutput = moduleInstance.waterHeatingUsingSteam(0.1703, 226.79, 285.93, 0.2737, 0.6814, 285.93, 0.2048, 0.7, 0.7, 8000);
        assert.approximately(results.tempWaterOut, 388.75, 0.01, "tempWaterOut");
        assert.approximately(results.bpTempWaterOut, 403.57, 0.01, "bpTempWaterOut");
        assert.approximately(results.enthalpySteamIn, 2698.89, 0.01, "enthalpySteamIn");
        assert.approximately(results.enthalpySteamOut, 483.41, 0.01, "enthalpySteamOut");
        assert.approximately(results.enthalpyMakeUpWater, 53.876, 0.01, "enthalpyMakeUpWater");
        assert.approximately(results.flowByPassSteam, 94.61, 0.01, "flowByPassSteam");
        assert.approximately(results.energySavedDWH, 3346757808.4035, 0.01, "energySavedDWH");
        assert.approximately(results.energySavedBoiler, 648872153.14, 0.01, "energySavedBoiler");
        assert.approximately(results.waterSaved, 1057.44, 0.01, "waterSaved");
        assert.approximately(results.heatGainRate, 292841.3082, 0.01, "heatGainRate");
    });
});
