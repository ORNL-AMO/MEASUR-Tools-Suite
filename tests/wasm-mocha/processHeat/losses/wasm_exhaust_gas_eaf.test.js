const assert = require('chai').assert;
const path = require('path');

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat ExhaustGasEAF', function () {
    let ToolsSuiteModule;
    before(async function () {
        // Dynamically import the Emscripten module with locateFile for .wasm
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

    it('should calculate totalHeatExhaust correctly', function () {
        var offGasTemp = 2800;
        var CO = 12;
        var H2 = 10;
        var combustibleGases = 3;
        var vfr = 8000;
        var dustLoading = 0.001;

        var exGasEAF = new ToolsSuiteModule.ExhaustGasEAF(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
        var totalHeatExhaust = exGasEAF.getTotalHeatExhaust();
        exGasEAF.delete();
        assert.equal(totalHeatExhaust, 12553119.018404908);
    });
});