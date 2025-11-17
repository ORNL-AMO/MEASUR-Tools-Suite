import { assert } from 'chai';
describe('Process Heat GasLoadChargeMaterial', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate total heat correctly', function () {
        var inp = {
            thermicReactionType: 0, specificHeatGas: 0.24, feedRate: 1000, percentVapor: 15, initialTemperature: 80,
            dischargeTemperature: 1150, specificHeatVapor: 0.5, percentReacted: 100, reactionHeat: 80, additionalHeat: 5000
        };
        var gasLoadChargeMaterial = new moduleInstance.GasLoadChargeMaterial(moduleInstance.ThermicReactionType.ENDOTHERMIC, inp.specificHeatGas, inp.feedRate, inp.percentVapor, inp.initialTemperature, inp.dischargeTemperature, inp.specificHeatVapor, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        var heatLoss = gasLoadChargeMaterial.getTotalHeat();
        assert.equal(heatLoss, 383530.0);
        gasLoadChargeMaterial.delete();
    });
});