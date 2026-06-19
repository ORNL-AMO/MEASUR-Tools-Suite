import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Fan Compressibility Factor', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate Fan Compressibility Factor correctly (#1)', function () {
        const moverShaftPower = 300;
        const inletPressure = -8.5;
        const outletPressure = 3;
        const barometricPressure = 29;
        const flowRate = 1000;
        const specificHeatRatio = 1.4;

        const compressibilityFactor = new moduleInstance.CompressibilityFactor(
            moverShaftPower,
            inletPressure,
            outletPressure,
            barometricPressure,
            flowRate,
            specificHeatRatio
        );

        try {
            assert.approximately(compressibilityFactor.calculate(), 1.5795535958, 0.001, "compressibilityFactorResult");
        } finally {
            compressibilityFactor.delete();
        }
    });

    it('should calculate Fan Compressibility Factor correctly (#2)', function () {
        const moverShaftPower = 566;
        const inletPressure = -16.36;
        const outletPressure = 1.1;
        const barometricPressure = 29.36;
        const flowRate = 129691;
        const specificHeatRatio = 1.4;

        const compressibilityFactor = new moduleInstance.CompressibilityFactor(
            moverShaftPower,
            inletPressure,
            outletPressure,
            barometricPressure,
            flowRate,
            specificHeatRatio
        );

        try {
            assert.approximately(compressibilityFactor.calculate(), 0.9879934727, 0.001, "compressibilityFactorResult");
        } finally {
            compressibilityFactor.delete();
        }
    });

    it('should calculate Fan Compressibility Factor correctly (#3)', function () {
        const moverShaftPower = 623;
        const inletPressure = -8.92;
        const outletPressure = 2.28;
        const barometricPressure = 29.36;
        const flowRate = 151961;
        const specificHeatRatio = 1.4;

        const compressibilityFactor = new moduleInstance.CompressibilityFactor(
            moverShaftPower,
            inletPressure,
            outletPressure,
            barometricPressure,
            flowRate,
            specificHeatRatio
        );

        try {
            assert.approximately(compressibilityFactor.calculate(), 0.9953146218, 0.001, "compressibilityFactorResult");
        } finally {
            compressibilityFactor.delete();
        }
    });
});
