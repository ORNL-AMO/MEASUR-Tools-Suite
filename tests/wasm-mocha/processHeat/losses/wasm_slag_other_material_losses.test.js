const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat SlagOtherMaterialLosses', function () {

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

    it('should calculate heatLoss correctly 1', function () {
        var inp = {
            weight: 3, inletTemperature: 500, outletTemperature: 550, specificHeat: 0.2479, correctionFactor: 1.0
        };
        var slagOtherMaterialLosses = new ToolsSuiteModule.SlagOtherMaterialLosses(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        var heatLoss = slagOtherMaterialLosses.getHeatLoss();
        assert.equal(heatLoss, 37.185);
        slagOtherMaterialLosses.delete();
    });

    it('should calculate heatLoss correctly 2', function () {
        var inp = {
            weight: 10, inletTemperature: 725, outletTemperature: 850, specificHeat: 0.033, correctionFactor: 0.8
        };
        var slagOtherMaterialLosses = new ToolsSuiteModule.SlagOtherMaterialLosses(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        var heatLoss = slagOtherMaterialLosses.getHeatLoss();
        assert.equal(heatLoss, 33.0);
        slagOtherMaterialLosses.delete();
    });
});