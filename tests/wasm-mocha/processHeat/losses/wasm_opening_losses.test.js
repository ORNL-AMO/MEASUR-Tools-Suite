const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat OpeningLosses', function () {

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

    it('should calculate heatLoss correctly (circular)', function () {
        var inp = {
            emissivity: 0.95, diameter: 12, thickness: 9, ratio: 1.33, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 100, viewFactor: 0.70
        };
        var openingLossesCircular = new ToolsSuiteModule.OpeningLosses(inp.emissivity, inp.diameter, inp.thickness, inp.ratio, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        var heatLoss = openingLossesCircular.getHeatLoss();
        assert.equal(heatLoss, 16038.269976979091);
        openingLossesCircular.delete();
    });

    it('should calculate heatLoss correctly (quad)', function () {
        var inp = {
            emissivity: 0.95, length: 48, width: 15, thickness: 9, ratio: 1.67, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 20, viewFactor: 0.64
        };
        var openingLossesQuad = new ToolsSuiteModule.OpeningLosses(inp.emissivity, inp.length, inp.width, inp.thickness, inp.ratio, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        var heatLoss = openingLossesQuad.getHeatLoss();
        assert.equal(heatLoss, 18670.2258869289);
        openingLossesQuad.delete();
    });

    it('should calculate viewFactor correctly (circular)', function () {
        var inp = {
            openingShape: 0, // CIRCULAR
            thickness: 3,
            diameter: 5
        };
        var openingLosses = new ToolsSuiteModule.OpeningLosses();
        var viewFactor = openingLosses.calculateViewFactorCircular(inp.thickness, inp.diameter);
        assert.equal(viewFactor, 0.6245198902586311);
        openingLosses.delete();
    });

    it('should calculate viewFactor correctly (quad)', function () {
        var inp = {
            openingShape: 1, // RECTANGULAR
            thickness: 2,
            length: 10,
            width: 5
        };
        var openingLosses = new ToolsSuiteModule.OpeningLosses();
        var viewFactor = openingLosses.calculateViewFactorQuad(inp.thickness, inp.length, inp.width);
        assert.equal(viewFactor, 0.7869335937489633);
        openingLosses.delete();
    });
});