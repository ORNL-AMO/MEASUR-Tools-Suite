import { assert } from 'chai';

describe('Optimal Fan Efficiency', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate Optimal Fan Efficiency correctly (AirfoilSISW)', function () {
        let fanType = moduleInstance.FanType.AirfoilSISW
        let fanSpeed = 1180;
        let flowRate = 40000;
        let inletPressure = -9;
        let outletPressure = 1;
        let compressibility = 0.995;

        let optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
        let optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate() * 100;
        optimalEfficiencyFactor.delete();
        assert.approximately(optimalEfficiencyFactorResult, 80.56103029, 0.001, "optimalEfficiencyFactorResult");
    });

    it('should calculate Optimal Fan Efficiency correctly (LongShavings)', function () {
        let fanType = moduleInstance.FanType.LongShavings;
        let fanSpeed = 1180;
        let flowRate = 10000;
        let inletPressure = -9;
        let outletPressure = 1;
        let compressibility = 0.995;

        let optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
        let optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate() * 100;
        assert.approximately(optimalEfficiencyFactorResult, 60.6953126, 0.001, "optimalEfficiencyFactorResult");
        optimalEfficiencyFactor.delete();
    });

    it('should calculate Optimal Fan Efficiency correctly (BackwardCurvedDIDW)', function () {
        let fanType = moduleInstance.FanType.BackwardCurvedDIDW;
        let fanSpeed = 1180;
        let flowRate = 500000;
        let inletPressure = -6;
        let outletPressure = 1;
        let compressibility = 0.995;

        let optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
        let optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate() * 100;
        assert.approximately(optimalEfficiencyFactorResult, 29.31237501, 0.001, "optimalEfficiencyFactorResult");

        optimalEfficiencyFactor.delete();
    });
});