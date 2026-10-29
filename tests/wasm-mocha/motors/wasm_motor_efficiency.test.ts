import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type MotorEfficiencyInput } from 'measur-tools-suite';

describe('Motor Efficiency', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function makeInput(overrides: Partial<MotorEfficiencyInput> = {}): MotorEfficiencyInput {
        return {
            lineFrequency: moduleInstance.LineFrequency.FREQ60,
            motorRpm: 1200,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
            motorRatedPower: 200,
            loadFactor: 1,
            specifiedEfficiency: 0,
            ...overrides
        };
    }

    it('calculates an energy-efficient motor from a plain input', function () {
        const input = makeInput();
        const efficiency = moduleInstance.calculateMotorEfficiency(input);

        assert.equal(efficiency, 0.9533208465291122);
        assert.notProperty(input, 'delete');
        assert.isNumber(efficiency);
    });

    it('preserves premium and specified-efficiency behavior', function () {
        const premiumEfficiency = moduleInstance.calculateMotorEfficiency(makeInput({
            motorRpm: 1780,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM
        }));
        const specifiedEfficiency = moduleInstance.calculateMotorEfficiency(makeInput({
            motorRpm: 1600,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED,
            motorRatedPower: 150,
            specifiedEfficiency: 0.95
        }));

        assert.approximately(premiumEfficiency, 0.9612112999, 1e-10);
        assert.approximately(specifiedEfficiency, 0.95, 1e-12);
    });

    it('removes the legacy runtime constructor', function () {
        assert.notProperty(moduleInstance, 'MotorEfficiency');
    });
});
