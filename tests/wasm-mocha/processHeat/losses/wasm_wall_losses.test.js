import { assert } from 'chai';

describe('Process Heat WallLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate total heat loss correctly', function () {
        var inp = {
            surfaceArea: 500, ambientTemperature: 80, surfaceTemperature: 225, windVelocity: 10,
            surfaceEmissivity: 0.9, conditionFactor: 1.394, correctionFactor: 1
        };
        var wallLosses = new moduleInstance.WallLosses(inp.surfaceArea, inp.ambientTemperature, inp.surfaceTemperature, inp.windVelocity, inp.surfaceEmissivity, inp.conditionFactor, inp.correctionFactor);
        var heatLoss = wallLosses.totalHeatLoss()

        assert.equal(heatLoss, 404487.58875827474);
        wallLosses.delete();
    });
});