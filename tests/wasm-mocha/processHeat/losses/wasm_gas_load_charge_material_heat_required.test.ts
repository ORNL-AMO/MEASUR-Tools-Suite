import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
describe('Process Heat GasLoadChargeMaterial', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate total heat correctly', function () {
        const inp = {
            thermicReactionType: 0, specificHeatGas: 0.24, feedRate: 1000, percentVapor: 15, initialTemperature: 80,
            dischargeTemperature: 1150, specificHeatVapor: 0.5, percentReacted: 100, reactionHeat: 80, additionalHeat: 5000
        };
        const heatLoss = moduleInstance.gasLoadChargeMaterialTotalHeatRequired(moduleInstance.ThermicReactionType.ENDOTHERMIC, inp.specificHeatGas, inp.feedRate, inp.percentVapor, inp.initialTemperature, inp.dischargeTemperature, inp.specificHeatVapor, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        assert.equal(heatLoss, 383530.0);
    });
});