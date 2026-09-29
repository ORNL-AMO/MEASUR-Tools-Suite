import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat OpeningLosses', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly (circular)', function () {
        const inp = {
            emissivity: 0.95, diameter: 12, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 100, viewFactor: 0.70
        };
        const heatLoss = moduleInstance.openingTotalHeatLossCircular(inp.emissivity, inp.diameter, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        assert.equal(heatLoss, 16042.398918636909);
    });

    it('should calculate heatLoss correctly (quad)', function () {
        const inp = {
            emissivity: 0.95, length: 48, width: 15, ambientTemperature: 75,
            insideTemperature: 1600, percentTimeOpen: 20, viewFactor: 0.64
        };
        const heatLoss = moduleInstance.openingTotalHeatLossQuad(inp.emissivity, inp.length, inp.width, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
        assert.equal(heatLoss, 18675.03240742869);
    });

    it('should calculate viewFactor correctly (circular)', function () {
        const inp = {
            thickness: 3,
            diameter: 5
        };
        const viewFactor = moduleInstance.calculateViewFactorCircular(inp.thickness, inp.diameter);
        assert.equal(viewFactor, 0.6245198902586311);
    });

    it('should calculate viewFactor correctly (quad)', function () {
        const inp = {
            thickness: 2,
            length: 10,
            width: 5
        };
        const viewFactor = moduleInstance.calculateViewFactorQuad(inp.thickness, inp.length, inp.width);
        assert.equal(viewFactor, 0.7869335937489633);
    });
});