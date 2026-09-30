import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Compressed Air Assessment - Positive Displacement Compressors', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates modulation without unload and exposes pressure/inlet correction results', function () {
        const compressor = new moduleInstance.ModulationWithoutUnloadCompressor(85.4, 473, 55.3);

        try {
            const baseline = compressor.calculateFromPowerFraction(0.89);
            assert.approximately(baseline.powerKw, 76.006, 0.001);
            assert.approximately(baseline.airflowAcfm, 325.38, 0.01);
            assert.approximately(baseline.powerFraction, 0.89, 0.0001);
            assert.approximately(baseline.airflowFraction, 0.6879, 0.0001);

            compressor.applyPressureInletCorrection(473, 105, 1.4, 100, 14.5, 0.917, 110, 110, 14.7, true, 14.7);
            assert.approximately(compressor.adjustedFullLoadPowerKw, 90.0736, 0.001);
            assert.approximately(compressor.adjustedFullLoadAirflowAcfm, 469.46, 0.01);

            const adjusted = compressor.calculateFromMeasuredPower(75.9);
            assert.approximately(adjusted.powerKw, 75.9, 0.001);
            assert.approximately(adjusted.airflowAcfm, 278.1105, 0.001);
            assert.approximately(adjusted.powerFraction, 0.8426441883, 0.0001);
            assert.approximately(adjusted.airflowFraction, 0.5924, 0.0001);
        } finally {
            compressor.delete();
        }
    });

    it('calculates start/stop compressor performance', function () {
        const compressor = new moduleInstance.StartStopCompressor(89.5, 560, 1.05, 1);

        try {
            const result = compressor.calculateFromCapacityFraction(0.2);
            assert.approximately(result.powerKw, 18.3475, 0.001);
            assert.approximately(result.airflowAcfm, 112, 0.001);
            assert.approximately(result.powerFraction, 0.205, 0.0001);
            assert.approximately(result.airflowFraction, 0.2, 0.0001);
        } finally {
            compressor.delete();
        }
    });

    it('uses compressor type when correcting start/stop performance', function () {
        const screw = new moduleInstance.StartStopCompressor(89.5, 560, 1.05, 1);
        const reciprocating = new moduleInstance.StartStopCompressor(
            89.5, 560, 1.05, 1, moduleInstance.CompressorType.Reciprocating
        );

        try {
            screw.applyPressureInletCorrection(473, 105, 1.4, 100, 14.5, 0.917, 110, 110, 14.7, true, 14.7);
            reciprocating.applyPressureInletCorrection(
                473, 105, 1.4, 100, 14.5, 0.917, 110, 110, 14.7, true, 14.7
            );
            assert.approximately(screw.adjustedFullLoadPowerKw, 90.0736, 0.001);
            assert.approximately(reciprocating.adjustedFullLoadPowerKw, 89.3967, 0.001);
        } finally {
            screw.delete();
            reciprocating.delete();
        }
    });

    it('calculates load/unload compressor performance', function () {
        const compressor = new moduleInstance.LoadUnloadCompressor(
            166.5, 1048, 1048 / 7.481, 175.5, 100, 110, 5, 10.1, 14.7,
            moduleInstance.CompressorType.Screw,
            moduleInstance.CompressorLubricant.Injected,
            moduleInstance.CompressorControl.LoadUnload,
            1, 100
        );

        try {
            const result = compressor.calculateFromPowerFraction(0.94);
            assert.approximately(result.powerKw, 156.51, 0.01);
            assert.approximately(result.powerFraction, 0.94, 0.0001);
        } finally {
            compressor.delete();
        }
    });

    it('uses the short load/unload constructor unloaded load factor', function () {
        const highNoLoad = new moduleInstance.LoadUnloadCompressor(100, 500, 100, 105, 100, 110, 5, 0.6);
        const lowNoLoad = new moduleInstance.LoadUnloadCompressor(100, 500, 100, 105, 100, 110, 5, 0.2);

        try {
            assert.equal(highNoLoad.calculateFromPowerFraction(0.59).powerKw, 0);
            assert.approximately(lowNoLoad.calculateFromPowerFraction(0.59).powerKw, 59, 0.001);
            const electrical = lowNoLoad.calculateFromElectrical(440, 154.74, 0.5);
            assert.approximately(electrical.powerKw, 58.98, 0.02);
        } finally {
            highNoLoad.delete();
            lowNoLoad.delete();
        }
    });

    it('calculates modulation with unload compressor performance', function () {
        const compressor = new moduleInstance.ModulationWithUnloadCompressor(
            166.5, 1048, 1048 / 7.481, 175.5, 107.5, 100, 110, 5
        );

        try {
            const result = compressor.calculateFromCapacityFraction(0.97);
            assert.approximately(result.airflowAcfm, 1016.56, 0.01);
            assert.approximately(result.airflowFraction, 0.97, 0.0001);
        } finally {
            compressor.delete();
        }
    });

    it('calculates variable frequency drive compressor performance', function () {
        const compressor = new moduleInstance.VariableFrequencyDriveCompressor(174.4, 115, 55.8, 11.2, 1009, 605, 202);

        try {
            const result = compressor.calculateFromCapacityFraction(0.31);
            assert.approximately(result.powerKw, 72.0695, 0.001);
            assert.approximately(result.airflowAcfm, 312.79, 0.01);
            assert.approximately(result.powerFraction, 0.4132, 0.001);
            assert.approximately(result.airflowFraction, 0.31, 0.0001);
        } finally {
            compressor.delete();
        }
    });
});
