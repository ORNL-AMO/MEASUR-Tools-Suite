import { assert } from 'chai';

describe('Process Heat Atmosphere', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate total heat loss correctly', function () {
        var inletTemperature = 100.0
        var outletTemperature = 1400.0;
        var flowRate = 1200.0;
        var correctionFactor = 1.0;
        var specificHeat = 0.02;

        let atmosphere = new moduleInstance.Atmosphere(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
        let heatLoss = atmosphere.getTotalHeat();
        assert.equal(heatLoss, 31200.0);
        atmosphere.delete();
    });
});