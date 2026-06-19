import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat LiquidLoadChargeMaterial', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate totalHeat correctly', function () {
        const inp = {
            thermicReactionType: 0, specificHeatLiquid: 0.48, vaporizingTemperature: 240, latentHeat: 250,
            specificHeatVapor: 0.25, chargeFeedRate: 1000, initialTemperature: 70, dischargeTemperature: 320,
            percentVaporized: 100, percentReacted: 25, reactionHeat: 50, additionalHeat: 0
        };
        const totalHeat = moduleInstance.liquidLoadChargeMaterialTotalHeatRequired(moduleInstance.ThermicReactionType.ENDOTHERMIC, inp.specificHeatLiquid, inp.vaporizingTemperature, inp.latentHeat, inp.specificHeatVapor, inp.chargeFeedRate, inp.initialTemperature, inp.dischargeTemperature, inp.percentVaporized, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        assert.equal(totalHeat, 364100.0);
    });
});