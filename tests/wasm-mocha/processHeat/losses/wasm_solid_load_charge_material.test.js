const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat SolidLoadChargeMaterial', function () {

    let ToolsSuiteModule;

    before(async function () {
        const createModule = (await import(clientPath)).default;
        ToolsSuiteModule = await createModule({
            locateFile: (filename) => {
                if (filename.endsWith('.wasm')) {
                    return wasmPath;
                }
                return filename;
            }
        });
    });

    it('should calculate totalHeat correctly', function () {
        var inp = {
            thermicReactionType: 1, specificHeatSolid: 0.15, latentHeat: 60, specificHeatLiquid: 0.481, meltingPoint: 2900,
            chargeFeedRate: 10000, waterContentCharged: 0.1, waterContentDischarged: 0, initialTemperature: 70,
            dischargeTemperature: 2200, waterVaporDischargeTemperature: 500, chargeMelted: 0, chargeReacted: 1,
            reactionHeat: 100, additionalHeat: 0
        };
        var solidLoadChargeMaterial = new ToolsSuiteModule.SolidLoadChargeMaterial(ToolsSuiteModule.ThermicReactionType.EXOTHERMIC, inp.specificHeatSolid, inp.latentHeat, inp.specificHeatLiquid, inp.meltingPoint, inp.chargeFeedRate, inp.waterContentCharged, inp.waterContentDischarged, inp.initialTemperature, inp.dischargeTemperature, inp.waterVaporDischargeTemperature, inp.chargeMelted, inp.chargeReacted, inp.reactionHeat, inp.additionalHeat);
        var totalHeat = solidLoadChargeMaterial.getTotalHeat()
        assert.equal(totalHeat, 3204310.28);
        solidLoadChargeMaterial.delete();
    });
});