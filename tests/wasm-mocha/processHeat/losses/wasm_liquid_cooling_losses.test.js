const path = require('path');
const assert = require('chai').assert;

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat LiquidCoolingLosses', function () {

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
            flowRate: 100, density: 9.35, initialTemperature: 80, outletTemperature: 210,
            specificHeat: 0.52, correctionFactor: 1.0
        };
        var liquidCoolingLosses = new ToolsSuiteModule.LiquidCoolingLosses(inp.flowRate, inp.density, inp.initialTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        var heatLoss = liquidCoolingLosses.getHeatLoss()
        assert.equal(heatLoss, 3792360.0);
        liquidCoolingLosses.delete();
    });
});