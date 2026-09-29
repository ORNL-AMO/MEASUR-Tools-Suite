import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
describe('Process Heat Leakage Heat Loss', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate total heat loss for correctly', function () {
        const inp = {
            draftPressure: 0.1, openingArea: 3, leakageGasTemperature: 1600, ambientTemperature: 80,
            coefficientDischarge: 0.8052, specificGravity: 1.02, correctionFactor: 1.0
        };
        const leakageTotalHeatLoss = moduleInstance.leakageTotalHeatLoss(inp.draftPressure, inp.openingArea, inp.leakageGasTemperature, inp.ambientTemperature, inp.coefficientDischarge, inp.specificGravity, inp.correctionFactor);
        assert.equal(leakageTotalHeatLoss, 2850767.216228273);
    });
});