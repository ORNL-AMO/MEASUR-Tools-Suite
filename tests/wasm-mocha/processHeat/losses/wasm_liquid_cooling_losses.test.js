import { assert } from 'chai';

describe('Process Heat LiquidCoolingLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly', function () {
        var inp = {
            flowRate: 100, density: 9.35, initialTemperature: 80, outletTemperature: 210,
            specificHeat: 0.52, correctionFactor: 1.0
        };
        var liquidCoolingLosses = new moduleInstance.LiquidCoolingLosses(inp.flowRate, inp.density, inp.initialTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
        var heatLoss = liquidCoolingLosses.getHeatLoss()
        assert.equal(heatLoss, 3792360.0);
        liquidCoolingLosses.delete();
    });
});