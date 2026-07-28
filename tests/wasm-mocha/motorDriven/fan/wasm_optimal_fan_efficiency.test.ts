import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Optimal Fan Efficiency', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate Optimal Fan Efficiency correctly (AirfoilSISW)', function () {
        const fanType = moduleInstance.FanType.AirfoilSISW;
        const fanSpeed = 1180;
        const flowRate = 40000;
        const inletPressure = -9;
        const outletPressure = 1;
        const compressibility = 0.995;

        const optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(
            fanType,
            fanSpeed,
            flowRate,
            inletPressure,
            outletPressure,
            compressibility
        );

        try {
            assert.approximately(
                optimalEfficiencyFactor.calculate() * 100,
                80.56103029,
                0.001,
                "optimalEfficiencyFactorResult"
            );
        } finally {
            optimalEfficiencyFactor.delete();
        }
    });

    it('should calculate Optimal Fan Efficiency correctly (LongShavings)', function () {
        const fanType = moduleInstance.FanType.LongShavings;
        const fanSpeed = 1180;
        const flowRate = 10000;
        const inletPressure = -9;
        const outletPressure = 1;
        const compressibility = 0.995;

        const optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(
            fanType,
            fanSpeed,
            flowRate,
            inletPressure,
            outletPressure,
            compressibility
        );

        try {
            assert.approximately(
                optimalEfficiencyFactor.calculate() * 100,
                60.6953126,
                0.001,
                "optimalEfficiencyFactorResult"
            );
        } finally {
            optimalEfficiencyFactor.delete();
        }
    });

    it('should calculate Optimal Fan Efficiency correctly (BackwardCurvedDIDW)', function () {
        const fanType = moduleInstance.FanType.BackwardCurvedDIDW;
        const fanSpeed = 1180;
        const flowRate = 500000;
        const inletPressure = -6;
        const outletPressure = 1;
        const compressibility = 0.995;

        const optimalEfficiencyFactor = new moduleInstance.OptimalFanEfficiency(
            fanType,
            fanSpeed,
            flowRate,
            inletPressure,
            outletPressure,
            compressibility
        );

        try {
            assert.approximately(
                optimalEfficiencyFactor.calculate() * 100,
                29.31237501,
                0.001,
                "optimalEfficiencyFactorResult"
            );
        } finally {
            optimalEfficiencyFactor.delete();
        }
    });
});
