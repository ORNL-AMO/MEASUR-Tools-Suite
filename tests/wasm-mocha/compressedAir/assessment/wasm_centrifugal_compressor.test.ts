import { assert } from 'chai';
import createModule, {
    type DoubleVector,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Assessment - Centrifugal Compressors', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function doubleVector(values: number[]): DoubleVector {
        const vector = new moduleInstance.DoubleVector();
        for (const value of values) {
            vector.push_back(value);
        }
        return vector;
    }

    it('calculates blow-off compressor performance from power and capacity fractions', function () {
        const compressor = new moduleInstance.CentrifugalBlowOffCompressor(452.3, 3138, 370.9, 2510);

        try {
            const fromPower = compressor.calculateFromPowerFraction(0.82, 0.6798);
            assert.approximately(fromPower.powerKw, 370.886, 0.001);
            assert.approximately(fromPower.airflowAcfm, 376.788, 0.001);
            assert.approximately(fromPower.powerFraction, 0.82, 0.0001);
            assert.approximately(fromPower.airflowFraction, 0.120073, 0.0001);
            assert.approximately(fromPower.blowOffAirflowAcfm, 2133.21, 0.01);
            assert.approximately(fromPower.blowOffFraction, 0.6798, 0.0001);

            const fromCapacity = compressor.calculateFromCapacityFraction(0.01);
            assert.approximately(fromCapacity.powerKw, 370.9, 0.001);
            assert.approximately(fromCapacity.airflowAcfm, 31.38, 0.001);
            assert.approximately(fromCapacity.powerFraction, 0.820031, 0.0001);
            assert.approximately(fromCapacity.airflowFraction, 0.01, 0.0001);
            assert.approximately(fromCapacity.blowOffAirflowAcfm, 2478.62, 0.01);
            assert.approximately(fromCapacity.blowOffFraction, 0.789873, 0.0001);
        } finally {
            compressor.delete();
        }
    });

    it('adjusts centrifugal load/unload discharge pressure using registered vectors', function () {
        const compressor = new moduleInstance.CentrifugalLoadUnloadCompressor(452.3, 3138, 71.3);
        const capacities = doubleVector([3200, 3138, 2885]);
        const pressures = doubleVector([91, 100, 117]);

        try {
            compressor.adjustDischargePressure(capacities, pressures, 100, 0);
            const result = compressor.calculateFromCapacityFraction(0.24);

            assert.approximately(compressor.adjustedFullLoadAirflowAcfm, 3138, 0.001);
            assert.approximately(result.powerKw, 162.74, 0.01);
            assert.approximately(result.airflowAcfm, 753.12, 0.01);
            assert.approximately(result.powerFraction, 0.3598, 0.005);
            assert.approximately(result.airflowFraction, 0.24, 0.0001);
        } finally {
            capacities.delete();
            pressures.delete();
            compressor.delete();
        }
    });

    it('calculates centrifugal modulation/unload performance', function () {
        const compressor = new moduleInstance.CentrifugalModulationUnloadCompressor(
            452.3, 3138, 71.3, 3005, 411.9, 2731
        );

        try {
            const result = compressor.calculateFromPowerFraction(0.94);
            assert.approximately(result.powerKw, 425.162, 0.001);
            assert.approximately(result.airflowAcfm, 2820.95, 0.01);
            assert.approximately(result.powerFraction, 0.94, 0.0001);
            assert.approximately(result.airflowFraction, 0.93875, 0.005);
        } finally {
            compressor.delete();
        }
    });
});
