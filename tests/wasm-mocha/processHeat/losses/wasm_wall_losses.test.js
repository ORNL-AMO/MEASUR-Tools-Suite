const path = require('path');
const assert = require('chai').assert;

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat WallLosses', function () {

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
        var inp = {
            surfaceArea: 500, ambientTemperature: 80, surfaceTemperature: 225, windVelocity: 10,
            surfaceEmissivity: 0.9, conditionFactor: 1.394, correctionFactor: 1
        };
        var wallLosses = new ToolsSuiteModule.WallLosses(inp.surfaceArea, inp.ambientTemperature, inp.surfaceTemperature, inp.windVelocity, inp.surfaceEmissivity, inp.conditionFactor, inp.correctionFactor);
        var heatLoss = wallLosses.totalHeatLoss()

        assert.equal(heatLoss, 404487.58875827474);
        wallLosses.delete();
    });
});