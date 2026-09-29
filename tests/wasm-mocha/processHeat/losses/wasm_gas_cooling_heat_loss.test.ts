import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat GasCoolingLosses', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heat loss correctly 1', function () {
        const inp = {
            flowRate: 2500, initialTemperature: 80, finalTemperature: 280, specificHeat: 0.02, correctionFactor: 1.0,
            gasDensity: 1
        };
        const heatLoss = moduleInstance.gasCoolingTotalHeatLoss(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
        assert.equal(heatLoss, 600000.0);
    });

    it('should calculate heat loss correctly 2', function () {
        const inp = {
            flowRate: 600, initialTemperature: 80, finalTemperature: 350, specificHeat: 0.02, correctionFactor: 1.0,
            gasDensity: 1
        };
        const heatLoss = moduleInstance.gasCoolingTotalHeatLoss(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
        assert.equal(heatLoss, 194400.0);
    });
});