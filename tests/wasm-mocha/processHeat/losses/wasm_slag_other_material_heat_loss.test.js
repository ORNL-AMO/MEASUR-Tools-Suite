import { assert } from 'chai';
describe('Process Heat SlagOtherMaterialLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });


    it('should calculate heatLoss correctly 1', function () {
        var inp = {
            weight: 3, inletTemperature: 500, outletTemperature: 550, specificHeat: 0.2479, correctionFactor: 1.0
        };
        var heatLoss =  moduleInstance.slagOtherMaterialTotalHeatLoss(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        assert.equal(heatLoss, 37.185);
    });

    it('should calculate heatLoss correctly 2', function () {
        var inp = {
            weight: 10, inletTemperature: 725, outletTemperature: 850, specificHeat: 0.033, correctionFactor: 0.8
        };
        var heatLoss =  moduleInstance.slagOtherMaterialTotalHeatLoss(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        assert.equal(heatLoss, 33.0);
    });
});