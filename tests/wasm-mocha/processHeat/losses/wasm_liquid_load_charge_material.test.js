const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat LiquidLoadChargeMaterial', function () {

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
            thermicReactionType: 0, specificHeatLiquid: 0.48, vaporizingTemperature: 240, latentHeat: 250,
            specificHeatVapor: 0.25, chargeFeedRate: 1000, initialTemperature: 70, dischargeTemperature: 320,
            percentVaporized: 100, percentReacted: 25, reactionHeat: 50, additionalHeat: 0
        };
        var liquidLoadChargeMaterial = new ToolsSuiteModule.LiquidLoadChargeMaterial(ToolsSuiteModule.ThermicReactionType.ENDOTHERMIC, inp.specificHeatLiquid, inp.vaporizingTemperature, inp.latentHeat, inp.specificHeatVapor, inp.chargeFeedRate, inp.initialTemperature, inp.dischargeTemperature, inp.percentVaporized, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        var totalHeat = liquidLoadChargeMaterial.getTotalHeat()
        assert.equal(totalHeat, 364100.0);
        liquidLoadChargeMaterial.delete();
    });
});