const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat GasCoolingLosses', function () {

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

    it('should calculate heat loss correctly 1', function () {
        var inp = {
            flowRate: 2500, initialTemperature: 80, finalTemperature: 280, specificHeat: 0.02, correctionFactor: 1.0,
            gasDensity: 1
        };
        var gasCoolingLosses = new ToolsSuiteModule.GasCoolingLosses(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
        var heatLoss = gasCoolingLosses.getHeatLoss();
        assert.equal(heatLoss, 600000.0);
        gasCoolingLosses.delete();
    });

    it('should calculate heat loss correctly 2', function () {
        var inp = {
            flowRate: 600, initialTemperature: 80, finalTemperature: 350, specificHeat: 0.02, correctionFactor: 1.0,
            gasDensity: 1
        };
        var gasCoolingLosses = new ToolsSuiteModule.GasCoolingLosses(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
        var heatLoss = gasCoolingLosses.getHeatLoss();
        assert.equal(heatLoss, 194400.0);
        gasCoolingLosses.delete();
    });
});