import { assert } from 'chai';

describe('Process Heat ExhaustGasEAF', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate totalHeatExhaust correctly', function () {
        var offGasTemp = 2800;
        var CO = 12;
        var H2 = 10;
        var combustibleGases = 3;
        var vfr = 8000;
        var dustLoading = 0.001;

        var totalHeatLoss = moduleInstance.exhaustGasEAFTotalHeatLoss(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
        assert.equal(totalHeatLoss, 12553119.018404908);
    });
});