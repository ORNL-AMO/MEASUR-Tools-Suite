import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpEfficiencyInput, type PumpEfficiencyLimits } from 'measur-tools-suite';
import { reference } from './hi_2020_reference';
import { pumpStyles } from './hi_2020_test_helpers';

describe('HI 2020 optimal_pump_efficiency WASM', function () {
    let module: MeasurToolsSuite;
    before(async function () {
        module = await createModule({locateFile: filename => '/base/bin/' + filename});
    });
    it('matches full-duty SciPy reference values without retaining input or result state', function () {
        for (const [style, rpm, kinematicViscosity, stageCount, flowRate, head, average, max] of reference.composite) {
            const input: PumpEfficiencyInput = Object.freeze({style: pumpStyles(module)[style], rpm, kinematicViscosity, stageCount, flowRate, head});
            const before = {...input};
            const result = module.calculateOptimalPumpEfficiency(input);
            assert.approximately(result, average, 1e-12);
            assert.deepEqual(input, before);
        }
    });
    it('rejects invalid inputs and unsupported styles', function () {
        const valid: PumpEfficiencyInput = {style: module.PumpStyle.END_SUCTION_ANSI_API,
            rpm: 2000, kinematicViscosity: 1.107, stageCount: 1, flowRate: 2000, head: 137};
        const invalid: PumpEfficiencyInput[] = [
            {...valid, flowRate: 50}, {...valid, flowRate: 6000}, {...valid, rpm: 1e10},
            {...valid, stageCount: 0}, {...valid, head: 0}, {...valid, rpm: 0},
            {...valid, kinematicViscosity: -1},
            {...valid, style: module.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY},
            {...valid, style: module.PumpStyle.POSITIVE_DISPLACEMENT},
        ];
        for (const key of ['rpm', 'kinematicViscosity', 'stageCount', 'flowRate', 'head']) {
            for (const value of [NaN, Infinity, -Infinity]) { invalid.push({...valid, [key]: value}); }
        }
        for (const input of invalid) {
            const result = module.calculateOptimalPumpEfficiency(input);
            assert.isNaN(result);
        }
    });
});
