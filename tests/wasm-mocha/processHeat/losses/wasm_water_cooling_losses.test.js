const path = require('path');
const assert = require('chai').assert;

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat WaterCoolingLosses', function () {

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

    it('should calculate heatLoss correctly', function () {
        var inp = {
            flowRate: 100, initialTemperature: 80, outletTemperature: 120, correctionFactor: 1
        };
        var waterCoolingLosses = new ToolsSuiteModule.WaterCoolingLosses(inp.flowRate, inp.initialTemperature, inp.outletTemperature, inp.correctionFactor);
        var heatLoss = waterCoolingLosses.getHeatLoss();
        assert.equal(heatLoss, 1989032.7936134234);
        waterCoolingLosses.delete();
    });
});