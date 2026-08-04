import { assert } from 'chai';
import createModule, {
    type DoubleVector,
    type MeasurToolsSuite,
    type StagingPowerConsumptionOutput,
} from 'measur-tools-suite';

describe('Chiller Staging Efficiency', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function createDoubleVector(values: number[]): DoubleVector {
        const vector: DoubleVector = new moduleInstance.DoubleVector();
        values.forEach((value: number) => vector.push_back(value));
        return vector;
    }

    it('accepts and returns registered double vectors', function () {
        const baselineLoads: DoubleVector = createDoubleVector([300, 300, 300]);
        const modificationLoads: DoubleVector = createDoubleVector([450, 450, 0]);
        let output: StagingPowerConsumptionOutput | undefined;
        let baselinePower: DoubleVector | undefined;
        let modificationPower: DoubleVector | undefined;

        try {
            output = moduleInstance.ChillerStagingEfficiency(
                moduleInstance.ChillerType.Centrifugal,
                moduleInstance.CondenserCoolingType.Water,
                moduleInstance.CompressorConfigType.VFD,
                1000,
                0.676,
                1,
                1,
                42,
                82.12,
                baselineLoads,
                modificationLoads
            );

            baselinePower = output.baselinePowerList;
            modificationPower = output.modPowerList;

            assert.equal(baselinePower.size(), 3);
            assert.equal(modificationPower.size(), 3);
            assert.approximately(baselinePower.get(0), 273.5006, 0.001);
            assert.approximately(modificationPower.get(0), 301.9545, 0.001);
            assert.approximately(output.savingsEnergy, 216.5928, 0.001);
        } finally {
            baselinePower?.delete();
            modificationPower?.delete();
            output?.delete();
            baselineLoads.delete();
            modificationLoads.delete();
        }
    });
});
