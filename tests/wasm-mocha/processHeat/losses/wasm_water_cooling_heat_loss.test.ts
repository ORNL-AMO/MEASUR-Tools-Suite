import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat WaterCoolingHeatLoss', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly', function () {
        const inp = {
            flowRate: 100, initialTemperature: 80, outletTemperature: 120, correctionFactor: 1
        };
        const heatLoss = moduleInstance.waterCoolingTotalHeatLoss(inp.flowRate, inp.initialTemperature, inp.outletTemperature, inp.correctionFactor);
        assert.equal(heatLoss, 1989032.7936134234);
    });
});