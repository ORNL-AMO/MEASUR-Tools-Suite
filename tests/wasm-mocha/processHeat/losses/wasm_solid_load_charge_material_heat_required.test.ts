import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat SolidLoadChargeMaterial', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });


    it('should calculate totalHeat correctly', function () {
        const inp = {
            thermicReactionType: 1, specificHeatSolid: 0.15, latentHeat: 60, specificHeatLiquid: 0.481, meltingPoint: 2900,
            chargeFeedRate: 10000, waterContentCharged: 0.1, waterContentDischarged: 0, initialTemperature: 70,
            dischargeTemperature: 2200, waterVaporDischargeTemperature: 500, chargeMelted: 0, chargeReacted: 1,
            reactionHeat: 100, additionalHeat: 0
        };
        const totalHeat = moduleInstance.solidLoadChargeMaterialTotalHeatRequired(moduleInstance.ThermicReactionType.EXOTHERMIC, inp.specificHeatSolid, inp.latentHeat, inp.specificHeatLiquid, inp.meltingPoint, inp.chargeFeedRate, inp.waterContentCharged, inp.waterContentDischarged, inp.initialTemperature, inp.dischargeTemperature, inp.waterVaporDischargeTemperature, inp.chargeMelted, inp.chargeReacted, inp.reactionHeat, inp.additionalHeat);
        assert.equal(totalHeat, 3204310.28);
    });
});