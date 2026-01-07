import { assert } from 'chai';

describe('Process Heat Air Heating Using Exhaust', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate airHeatingUsingExhaustWithGasComposition results correctly', function () {
        let gasInstance = new moduleInstance.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
        let results = moduleInstance.airHeatingUsingExhaustWithGasComposition(gasInstance, 400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
        assert.approximately(results.hxColdAir, 197829.27, 0.001);
        assert.approximately(results.hxOutletExhaust, 187, 0.001);
        assert.approximately(results.energySavings, 930.96, 0.001);
        assert.approximately(results.heatCapacityFlue, 928.78, 0.001);
        assert.approximately(results.heatCapacityAir, 4464, 0.001);
        gasInstance.delete();
    });

    it('should calculate airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial results correctly', function () {
        let coalInstance = new moduleInstance.SolidLiquidFlueGasMaterial('Coal', 75.0, 5.0, 1.00, 9.0, 7.0, 0.0, 1.5);
        let results = moduleInstance.airHeatingUsingExhaustWithSolidLiquidFlueGasMaterial(coalInstance, 400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000);
        assert.approximately(results.hxColdAir, 15621.25, 0.001);
        assert.approximately(results.hxOutletExhaust, 187, 0.001);
        assert.approximately(results.energySavings, 73.512, 0.001);
        assert.approximately(results.heatCapacityFlue, 73.339, 0.001);
        assert.approximately(results.heatCapacityAir, 4464, 0.001);
        coalInstance.delete();
    });
});