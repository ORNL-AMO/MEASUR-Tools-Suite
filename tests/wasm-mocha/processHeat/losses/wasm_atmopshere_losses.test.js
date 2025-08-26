const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat Atmosphere', function () {

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

    it('should calculate total heat loss correctly', function () {
        var inletTemperature = 100.0
        var outletTemperature = 1400.0;
        var flowRate = 1200.0;
        var correctionFactor = 1.0;
        var specificHeat = 0.02;

        let atmosphere = new ToolsSuiteModule.Atmosphere(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
        let heatLoss = atmosphere.getTotalHeat();
        assert.equal(heatLoss, 31200.0);
        atmosphere.delete();
    });
});