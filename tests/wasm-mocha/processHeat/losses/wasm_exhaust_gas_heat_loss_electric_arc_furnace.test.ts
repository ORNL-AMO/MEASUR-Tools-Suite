import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat ExhaustGasEAF', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate totalHeatExhaust correctly', function () {
        const offGasTemp = 2800;
        const CO = 12;
        const H2 = 10;
        const combustibleGases = 3;
        const vfr = 8000;
        const dustLoading = 0.001;

        const totalHeatLoss = moduleInstance.exhaustGasEAFTotalHeatLoss(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
        assert.equal(totalHeatLoss, 12553119.018404908);
    });
});