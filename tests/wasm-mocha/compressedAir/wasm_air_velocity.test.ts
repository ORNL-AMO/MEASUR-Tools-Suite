import { assert } from 'chai';
import createModule, { type AirVelocityInput, type MeasurToolsSuite, type PipeData } from 'measur-tools-suite';

describe('Compressed Air Air Velocity', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate air velocity for all standard nominal pipe sizes', function () {
        const input: AirVelocityInput = {
            airFlow: 1800,
            pipePressure: 100,
            atmosphericPressure: 14.7
        };

        const result: PipeData = moduleInstance.calculateAirVelocity(input);

        try {
            assert.approximately(result.oneHalf, 1845.510026, 0.01);
            assert.approximately(result.threeFourths, 1044.628317, 0.01);
            assert.approximately(result.one, 643.782567, 0.01);
            assert.approximately(result.oneAndOneFourth, 369.102005, 0.01);
            assert.approximately(result.oneAndOneHalf, 271.398533, 0.01);
            assert.approximately(result.two, 164.777681, 0.01);
            assert.approximately(result.twoAndOneHalf, 115.585179, 0.01);
            assert.approximately(result.three, 74.919216, 0.01);
            assert.approximately(result.threeAndOneHalf, 55.981093, 0.01);
            assert.approximately(result.four, 43.491988, 0.01);
            assert.approximately(result.five, 27.68265, 0.01);
            assert.approximately(result.six, 19.164175, 0.01);
            assert.approximately(result.eight, 11.068633, 0.01);
            assert.approximately(result.ten, 7.021598, 0.01);
            assert.approximately(result.twelve, 4.947748, 0.01);
            assert.approximately(result.fourteen, 4.09204, 0.01);
            assert.approximately(result.sixteen, 3.133294, 0.01);
            assert.approximately(result.eighteen, 2.471665, 0.01);
            assert.approximately(result.twenty, 1.991558, 0.01);
            assert.approximately(result.twentyFour, 1.376904, 0.01);
        } finally {
            result.delete();
        }
    });
});
