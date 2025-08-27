import { assert } from 'chai';

describe('Process Heat WaterCoolingLosses', function () {
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
        var waterCoolingLosses = new moduleInstance.WaterCoolingLosses(inp.flowRate, inp.initialTemperature, inp.outletTemperature, inp.correctionFactor);
        var heatLoss = waterCoolingLosses.getHeatLoss();
        assert.equal(heatLoss, 1989032.7936134234);
        waterCoolingLosses.delete();
    });
});