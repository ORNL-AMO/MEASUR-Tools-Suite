import { assert } from 'chai';

describe('Process Fixture Heat Loss', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    // Test Fixture Total Heat Loss Calculation
    it('should calculate the total heat loss for fixtures', function () {
        // Input parameters
        const inp = {
            specificHeat: 0.122,
            feedRate: 1250.0,
            initialTemperature: 300.0,
            finalTemperature: 1800.0,
            correctionFactor: 1.0
        }

        // Calculate total heat loss
        const totalHeatLoss = moduleInstance.fixtureTotalHeatLoss(
            inp.specificHeat,
            inp.feedRate,
            inp.initialTemperature,
            inp.finalTemperature,
            inp.correctionFactor
        );

        // Assert the result
        assert.equal(totalHeatLoss, 228750.0);
    });
});
