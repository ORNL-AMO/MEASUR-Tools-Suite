import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
describe('Process Heat SlagOtherMaterialLosses', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });


    it('should calculate heatLoss correctly 1', function () {
        const inp = {
            weight: 3, inletTemperature: 500, outletTemperature: 550, specificHeat: 0.2479, correctionFactor: 1.0
        };
        const heatLoss =  moduleInstance.slagOtherMaterialTotalHeatLoss(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        assert.equal(heatLoss, 37.185);
    });

    it('should calculate heatLoss correctly 2', function () {
        const inp = {
            weight: 10, inletTemperature: 725, outletTemperature: 850, specificHeat: 0.033, correctionFactor: 0.8
        };
        const heatLoss =  moduleInstance.slagOtherMaterialTotalHeatLoss(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        assert.equal(heatLoss, 33.0);
    });
});