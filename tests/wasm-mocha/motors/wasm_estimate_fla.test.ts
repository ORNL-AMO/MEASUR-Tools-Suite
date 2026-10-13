import { assert } from 'chai';
import createModule, { type EstimateFLAInput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('EstimateFLA WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function makeInput(overrides: Partial<EstimateFLAInput> = {}): EstimateFLAInput {
        return {
            motorRatedPower: 50,
            motorRpm: 1800,
            lineFrequency: moduleInstance.LineFrequency.FREQ60,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD,
            specifiedEfficiency: 0,
            ratedVoltage: 100,
            ...overrides
        };
    }

    it('returns plain value objects with six ordered partial-load anchors', function () {
        const input = makeInput();
        const output = moduleInstance.calculateEstimateFLA(input);

        assert.closeTo(output.estimatedFLA, 277.7547835326, 1e-9);
        const expectedPartialLoadCurrents = [
            18.8775576,
            23.6212730421,
            34.0613092325,
            46.5048449789,
            60.381474681,
            75.5372248259
        ];
        output.partialLoadCurrents.forEach((current, index) => {
            assert.closeTo(current, expectedPartialLoadCurrents[index], 1e-9);
        });
        assert.notProperty(input, 'delete');
        assert.notProperty(output, 'delete');
    });

    it('preserves energy-efficient and specified-efficiency full-load goldens', function () {
        const energyEfficient = moduleInstance.calculateEstimateFLA(
            makeInput({
                motorRatedPower: 200,
                motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ50,
                efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
                ratedVoltage: 460
            })
        );
        const specified = moduleInstance.calculateEstimateFLA(
            makeInput({
                motorRatedPower: 200,
                motorRpm: 1780,
                efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED,
                specifiedEfficiency: .95,
                ratedVoltage: 460
            })
        );

        assert.closeTo(energyEfficient.estimatedFLA, 225.800612262395, 1e-9);
        assert.closeTo(specified.estimatedFLA, 227.288340026, 1e-8);
    });

    it('removes the legacy EstimateFLA runtime constructor', function () {
        assert.notProperty(moduleInstance, 'EstimateFLA');
    });
});
