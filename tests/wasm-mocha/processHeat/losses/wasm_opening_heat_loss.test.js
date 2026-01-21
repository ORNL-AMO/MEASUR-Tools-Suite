import { assert } from 'chai';

describe('Process Heat OpeningLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly (circular)', function () {
        var inp = {
            emissivity: 0.95, diameter: 12, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 100, viewFactor: 0.70
        };
        var heatLoss = moduleInstance.openingTotalHeatLossCircular(inp.emissivity, inp.diameter, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        assert.equal(heatLoss, 16042.398918636909);
    });

    it('should calculate heatLoss correctly (quad)', function () {
        var inp = {
            emissivity: 0.95, length: 48, width: 15, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 20, viewFactor: 0.64
        };
        var heatLoss = moduleInstance.openingTotalHeatLossQuad(inp.emissivity, inp.length, inp.width, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        assert.equal(heatLoss, 18675.03240742869);
    });

    it('should calculate viewFactor correctly (circular)', function () {
        var inp = {
            thickness: 3,
            diameter: 5
        };
        var viewFactor = moduleInstance.calculateViewFactorCircular(inp.thickness, inp.diameter);
        assert.equal(viewFactor, 0.6245198902586311);
    });

    it('should calculate viewFactor correctly (quad)', function () {
        var inp = {
            thickness: 2,
            length: 10,
            width: 5
        };
        var viewFactor = moduleInstance.calculateViewFactorQuad(inp.thickness, inp.length, inp.width);
        assert.equal(viewFactor, 0.7869335937489633);
    });
});