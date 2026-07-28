import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat LiquidCoolingLosses', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly', function () {
        const inp = {
            flowRate: 100, density: 9.35, initialTemperature: 80, outletTemperature: 210,
            specificHeat: 0.52, correctionFactor: 1.0
        };
        const heatLoss = moduleInstance.liquidCoolingTotalHeatLoss(inp.flowRate, inp.density, inp.initialTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        assert.equal(heatLoss, 3792360.0);
    });
});