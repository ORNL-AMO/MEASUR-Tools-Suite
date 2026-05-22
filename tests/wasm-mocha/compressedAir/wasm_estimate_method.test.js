import { assert } from 'chai';

describe('Compressed Air Leak Estimate Method', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate annual consumption for a small leak rate', function () {
        const inp = { operatingTime: 1280, leakRateEstimate: 0.1 };

        const estimateMethod = new moduleInstance.EstimateMethod(inp.operatingTime, inp.leakRateEstimate);
        const result = estimateMethod.calculate();

        assert.approximately(result.annualConsumption, 7.68, 0.01);

        estimateMethod.delete();
    });

    it('should calculate annual consumption for a larger leak rate', function () {
        const inp = { operatingTime: 1280, leakRateEstimate: 1.429 };

        const estimateMethod = new moduleInstance.EstimateMethod(inp.operatingTime, inp.leakRateEstimate);
        const result = estimateMethod.calculate();

        assert.approximately(result.annualConsumption, 109.7472, 0.01);

        estimateMethod.delete();
    });
});
