import { assert } from 'chai';
import createModule, { type AirVelocity, type MeasurToolsSuite, type PipeData } from 'measur-tools-suite';

describe('Compressed Air Air Velocity', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate air velocity for all standard nominal pipe sizes', function () {
        const inp = {
            airFlow: 1800,
            pipePressure: 100,
            atmosphericPressure: 14.7
        };

        const airVelocity: AirVelocity = new moduleInstance.AirVelocity(
            inp.airFlow, inp.pipePressure, inp.atmosphericPressure
        );
        const result: PipeData = airVelocity.calculate();

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
        } finally {
            result.delete();
            airVelocity.delete();
        }
    });
});
