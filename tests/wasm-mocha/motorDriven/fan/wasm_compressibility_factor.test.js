import { assert } from 'chai';

describe('Fan Compressibility Factor', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate Fan Compressibility Factor correctly (#1)', function () {
        let moverShaftPower = 300;
        let inletPressure = -8.5;
        let outletPressure = 3;
        let barometricPressure = 29;
        let flowRate = 1000;
        let specificHeatRatio = 1.4;

        let compressibilityFactor = new moduleInstance.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
        let compressibilityFactorResult = compressibilityFactor.calculate();
        assert.approximately(compressibilityFactorResult, 1.5795535958, .001, "compressibilityFactorResult");
        compressibilityFactor.delete();
    });

    it('should calculate Fan Compressibility Factor correctly (#2)', function () {
        let moverShaftPower = 566;
        let inletPressure = -16.36;
        let outletPressure = 1.1;
        let barometricPressure = 29.36;
        let flowRate = 129691;
        let specificHeatRatio = 1.4;

        let compressibilityFactor = new moduleInstance.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
        let compressibilityFactorResult = compressibilityFactor.calculate();
        assert.approximately(compressibilityFactorResult, 0.9879934727, .001, "compressibilityFactorResult");
        compressibilityFactor.delete();
    });

    it('should calculate Fan Compressibility Factor correctly (#3)', function () {
        let moverShaftPower = 623;
        let inletPressure = -8.92;
        let outletPressure = 2.28;
        let barometricPressure = 29.36;
        let flowRate = 151961;
        let specificHeatRatio = 1.4;

        let compressibilityFactor = new moduleInstance.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
        let compressibilityFactorResult = compressibilityFactor.calculate();
        assert.approximately(compressibilityFactorResult, 0.9953146218, .001, "compressibilityFactorResult");
        compressibilityFactor.delete();
    });
});