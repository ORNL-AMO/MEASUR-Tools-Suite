import { assert } from 'chai';

describe('Process Heat ExhaustGasEAF', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate totalHeatExhaust correctly', function () {
        var offGasTemp = 2800;
        var CO = 12;
        var H2 = 10;
        var combustibleGases = 3;
        var vfr = 8000;
        var dustLoading = 0.001;

        var exGasEAF = new moduleInstance.ExhaustGasEAF(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
        var totalHeatExhaust = exGasEAF.getTotalHeatExhaust();
        exGasEAF.delete();
        assert.equal(totalHeatExhaust, 12553119.018404908);
    });
});