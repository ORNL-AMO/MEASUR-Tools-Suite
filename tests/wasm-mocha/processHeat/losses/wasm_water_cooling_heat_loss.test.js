import { assert } from 'chai';

describe('Process Heat WaterCoolingHeatLoss', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly', function () {
        var inp = {
            flowRate: 100, initialTemperature: 80, outletTemperature: 120, correctionFactor: 1
        };
        var heatLoss = moduleInstance.waterCoolingTotalHeatLoss(inp.flowRate, inp.initialTemperature, inp.outletTemperature, inp.correctionFactor);
        assert.equal(heatLoss, 1989032.7936134234);
    });
});