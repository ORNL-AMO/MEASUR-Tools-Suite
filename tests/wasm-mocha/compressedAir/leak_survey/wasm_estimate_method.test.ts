import { assert } from 'chai';
import createModule, {
    type EstimateMethodInput,
    type EstimateMethodResult,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Estimate Method', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate annual consumption for a small leak rate', function () {
        const inp: EstimateMethodInput = { operatingTime: 1280, leakRateEstimate: 0.1 };
        const result: EstimateMethodResult = moduleInstance.calculateEstimateMethod(inp);
        assert.approximately(result.annualConsumption, 7.68, 0.01);
    });

    it('should calculate annual consumption for a larger leak rate', function () {
        const inp: EstimateMethodInput = { operatingTime: 1280, leakRateEstimate: 1.429 };
        const result: EstimateMethodResult = moduleInstance.calculateEstimateMethod(inp);
        assert.approximately(result.annualConsumption, 109.7472, 0.01);
    });
});
