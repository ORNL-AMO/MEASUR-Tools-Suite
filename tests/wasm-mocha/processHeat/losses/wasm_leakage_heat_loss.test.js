import { assert } from 'chai';
describe('Process Heat Leakage Heat Loss', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate leakageTotalHeatLoss correctly', function () {
        var inp = {
            draftPressure: 0.1, openingArea: 3, leakageGasTemperature: 1600, ambientTemperature: 80,
            coefficient: 0.8052, specificGravity: 1.02, correctionFactor: 1.0
        };
        var leakageTotalHeatLoss = moduleInstance.leakageTotalHeatLoss(inp.draftPressure, inp.openingArea, inp.leakageGasTemperature, inp.ambientTemperature, inp.coefficient, inp.specificGravity, inp.correctionFactor);
        assert.equal(leakageTotalHeatLoss, 2850767.216228273);
    });
});