import { assert } from 'chai';

describe('Process Heat LiquidLoadChargeMaterial', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate totalHeat correctly', function () {
        var inp = {
            thermicReactionType: 0, specificHeatLiquid: 0.48, vaporizingTemperature: 240, latentHeat: 250,
            specificHeatVapor: 0.25, chargeFeedRate: 1000, initialTemperature: 70, dischargeTemperature: 320,
            percentVaporized: 100, percentReacted: 25, reactionHeat: 50, additionalHeat: 0
        };
        var liquidLoadChargeMaterial = new moduleInstance.LiquidLoadChargeMaterial(moduleInstance.ThermicReactionType.ENDOTHERMIC, inp.specificHeatLiquid, inp.vaporizingTemperature, inp.latentHeat, inp.specificHeatVapor, inp.chargeFeedRate, inp.initialTemperature, inp.dischargeTemperature, inp.percentVaporized, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        var totalHeat = liquidLoadChargeMaterial.getTotalHeat()
        assert.equal(totalHeat, 364100.0);
        liquidLoadChargeMaterial.delete();
    });
});