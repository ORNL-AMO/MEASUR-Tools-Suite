import { assert } from 'chai';

describe('Compressed Air Estimate Method', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate annual consumption for a small leak rate', function () {
        const inp = { operatingTime: 1280, leakRateEstimate: 0.1 };
        const result = m.calculateEstimateMethod(inp);
        assert.approximately(result.annualConsumption, 7.68, 0.01);
    });

    it('should calculate annual consumption for a larger leak rate', function () {
        const inp = { operatingTime: 1280, leakRateEstimate: 1.429 };
        const result = m.calculateEstimateMethod(inp);
        assert.approximately(result.annualConsumption, 109.7472, 0.01);
    });
});
