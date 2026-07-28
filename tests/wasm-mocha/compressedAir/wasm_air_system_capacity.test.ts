import { assert } from 'chai';
import createModule, {
    type AirSystemCapacityOutput,
    type DoubleVector,
    type MeasurToolsSuite,
    type PipeData,
} from 'measur-tools-suite';

describe('Compressed Air Air System Capacity', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function getReceiverCapacities(receiverCapacitiesGal: number[]): DoubleVector {
        const receiverCapacities: DoubleVector = new moduleInstance.DoubleVector();
        for (const capacity of receiverCapacitiesGal) {
            receiverCapacities.push_back(capacity);
        }

        return receiverCapacities;
    }

    it('should calculate total pipe volume, receiver volume, and system capacity', function () {
        const receiverCapacitiesGal = [400, 500, 660, 1060];
        const receiverCapacities: DoubleVector = getReceiverCapacities(receiverCapacitiesGal);

        const pipeLengths = {
            oneHalf: 3000,
            threeFourths: 2000,
            one: 1000,
            oneAndOneFourth: 200,
            oneAndOneHalf: 100,
            two: 500,
            twoAndOneHalf: 500,
            three: 300,
            threeAndOneHalf: 0,
            four: 1000,
            five: 0,
            six: 0,
            eight: 0,
            ten: 0,
            twelve: 0,
            fourteen: 0,
            sixteen: 0,
            eighteen: 0,
            twenty: 0,
            twentyFour: 0
        };

        const pipeData: PipeData = new moduleInstance.PipeData(
            pipeLengths.oneHalf, pipeLengths.threeFourths, pipeLengths.one,
            pipeLengths.oneAndOneFourth, pipeLengths.oneAndOneHalf, pipeLengths.two,
            pipeLengths.twoAndOneHalf, pipeLengths.three, pipeLengths.threeAndOneHalf,
            pipeLengths.four, pipeLengths.five, pipeLengths.six,
            pipeLengths.eight, pipeLengths.ten, pipeLengths.twelve,
            pipeLengths.fourteen, pipeLengths.sixteen, pipeLengths.eighteen,
            pipeLengths.twenty, pipeLengths.twentyFour
        );

        let result: AirSystemCapacityOutput | undefined;

        try {
            result = moduleInstance.calculateAirSystemCapacity({
                pipeLengths: pipeData,
                receivers: receiverCapacities
            });
            assert.approximately(result.totalPipeVolume, 155.28, 0.01);
            assert.approximately(result.totalReceiverVolume, 350.243236, 0.01);
            assert.approximately(result.totalCapacityOfCompressedAirSystem, 505.523236, 0.01);
        } finally {
            result?.receiverCapacities.delete();
            result?.pipeLengths.delete();
            receiverCapacities.delete();
            pipeData.delete();
        }
    });

    it('should calculate converted pipe volumes for each nominal pipe size', function () {
        const receiverCapacitiesGal = [400, 500, 660, 1060];
        const receiverCapacities: DoubleVector = getReceiverCapacities(receiverCapacitiesGal);

        const pipeData: PipeData = new moduleInstance.PipeData(
            3000, 2000, 1000, 200, 100, 500,
            500, 300, 0, 1000, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
        );

        let result: AirSystemCapacityOutput | undefined;

        try {
            result = moduleInstance.calculateAirSystemCapacity({
                pipeLengths: pipeData,
                receivers: receiverCapacities
            });
            assert.approximately(result.pipeLengths.oneHalf, 6.3, 0.01);
            assert.approximately(result.pipeLengths.threeFourths, 7.4, 0.01);
            assert.approximately(result.pipeLengths.one, 6, 0.01);
            assert.approximately(result.pipeLengths.oneAndOneFourth, 2.08, 0.01);
            assert.approximately(result.pipeLengths.oneAndOneHalf, 1.41, 0.01);
            assert.approximately(result.pipeLengths.two, 11.65, 0.01);
            assert.approximately(result.pipeLengths.twoAndOneHalf, 16.65, 0.01);
            assert.approximately(result.pipeLengths.three, 15.39, 0.01);
            assert.approximately(result.pipeLengths.threeAndOneHalf, 0, 0.01);
            assert.approximately(result.pipeLengths.four, 88.4, 0.01);
            assert.approximately(result.pipeLengths.five, 0, 0.01);
            assert.approximately(result.pipeLengths.six, 0, 0.01);
        } finally {
            result?.receiverCapacities.delete();
            result?.pipeLengths.delete();
            receiverCapacities.delete();
            pipeData.delete();
        }
    });

    it('should calculate converted receiver capacities in cubic feet', function () {
        const receiverCapacitiesGal = [400, 500, 660, 1060];
        const receiverCapacities: DoubleVector = getReceiverCapacities(receiverCapacitiesGal);

        const pipeData: PipeData = new moduleInstance.PipeData(
            3000, 2000, 1000, 200, 100, 500,
            500, 300, 0, 1000, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
        );

        let result: AirSystemCapacityOutput | undefined;

        try {
            result = moduleInstance.calculateAirSystemCapacity({
                pipeLengths: pipeData,
                receivers: receiverCapacities
            });
            const resultReceiverCapacities: number[] = [];
            for (let i = 0; i < result.receiverCapacities.size(); i++) {
                resultReceiverCapacities.push(result.receiverCapacities.get(i));
            }

            assert.approximately(resultReceiverCapacities[0], 53.475936, 0.01);
            assert.approximately(resultReceiverCapacities[1], 66.84492, 0.01);
            assert.approximately(resultReceiverCapacities[2], 88.235294, 0.01);
            assert.approximately(resultReceiverCapacities[3], 141.71123, 0.01);
        } finally {
            result?.receiverCapacities.delete();
            result?.pipeLengths.delete();
            receiverCapacities.delete();
            pipeData.delete();
        }
    });
});
