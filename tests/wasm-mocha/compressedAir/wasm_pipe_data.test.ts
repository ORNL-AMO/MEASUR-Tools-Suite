import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PipeData } from 'measur-tools-suite';

describe('Compressed Air Pipe Data', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should convert pipe lengths to contained pipe volumes', function () {
        const pipeData: PipeData = new moduleInstance.PipeData(
            3000, 2000, 1000, 200, 100, 500,
            500, 300, 0, 1000, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
        );

        try {
            assert.approximately(pipeData.oneHalf, 6.3, 0.01);
            assert.approximately(pipeData.threeFourths, 7.4, 0.01);
            assert.approximately(pipeData.one, 6, 0.01);
            assert.approximately(pipeData.oneAndOneFourth, 2.08, 0.01);
            assert.approximately(pipeData.oneAndOneHalf, 1.41, 0.01);
            assert.approximately(pipeData.two, 11.65, 0.01);
            assert.approximately(pipeData.twoAndOneHalf, 16.65, 0.01);
            assert.approximately(pipeData.three, 15.39, 0.01);
            assert.approximately(pipeData.threeAndOneHalf, 0, 0.01);
            assert.approximately(pipeData.four, 88.4, 0.01);
            assert.approximately(pipeData.five, 0, 0.01);
            assert.approximately(pipeData.six, 0, 0.01);
        } finally {
            pipeData.delete();
        }
    });
});
