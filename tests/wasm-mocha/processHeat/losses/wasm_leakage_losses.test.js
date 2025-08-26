const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat LeakageLosses', function () {

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

    it('should calculate exfiltratedGasesHeatContent correctly', function () {
        var inp = {
            draftPressure: 0.1, openingArea: 3, leakageGasTemperature: 1600, ambientTemperature: 80,
            coefficient: 0.8052, specificGravity: 1.02, correctionFactor: 1.0
        };
        var leakingLosses = new ToolsSuiteModule.LeakageLosses(inp.draftPressure, inp.openingArea, inp.leakageGasTemperature, inp.ambientTemperature, inp.coefficient, inp.specificGravity, inp.correctionFactor);
        var exfiltratedGasesHeatContent = leakingLosses.getExfiltratedGasesHeatContent()
        assert.equal(exfiltratedGasesHeatContent, 2850767.216228273);
        leakingLosses.delete();
    });
});