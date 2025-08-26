const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat GasLoadChargeMaterial', function () {

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

    it('should calculate total heat correctly', function () {
        var inp = {
            thermicReactionType: 0, specificHeatGas: 0.24, feedRate: 1000, percentVapor: 15, initialTemperature: 80,
            dischargeTemperature: 1150, specificHeatVapor: 0.5, percentReacted: 100, reactionHeat: 80, additionalHeat: 5000
        };
        var gasLoadChargeMaterial = new ToolsSuiteModule.GasLoadChargeMaterial(ToolsSuiteModule.ThermicReactionType.ENDOTHERMIC, inp.specificHeatGas, inp.feedRate, inp.percentVapor, inp.initialTemperature, inp.dischargeTemperature, inp.specificHeatVapor, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
        var heatLoss = gasLoadChargeMaterial.getTotalHeat();
        assert.equal(heatLoss, 383530.0);
        gasLoadChargeMaterial.delete();
    });
});