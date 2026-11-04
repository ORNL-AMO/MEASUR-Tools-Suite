import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpEfficiencyInput, type PumpEfficiencyLimits } from 'measur-tools-suite';
import { reference } from './hi_2020_reference';
import { pumpStyles } from './hi_2020_test_helpers';

describe('HI 2020 pump_efficiency WASM', function () {
    let module: MeasurToolsSuite;
    before(async function () {
        module = await createModule({locateFile: filename => '/base/bin/' + filename});
    });
    it('matches full-duty SciPy reference values without retaining input or result state', function () {
        for (const [style, rpm, kinematicViscosity, stageCount, flowRate, head, average, max] of reference.composite) {
            const input: PumpEfficiencyInput = Object.freeze({style: pumpStyles(module)[style], rpm, kinematicViscosity, stageCount, flowRate, head});
            const before = {...input};
            const result = module.calculatePumpEfficiency(input);
            assert.approximately(result.average, average, 1e-12);
            assert.approximately(result.max, max, 1e-12);
            assert.deepEqual(Object.keys(result).sort(), ['average', 'max']);
            assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
            assert.notProperty(result, 'delete');
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
            const result = module.calculatePumpEfficiency(input);
            assert.isNaN(result.average);
            assert.isNaN(result.max);
        }
    });
    it('exposes limits as plain data with no runtime constructor', function () {
        const ansi: PumpEfficiencyLimits = module.getPumpEfficiencyLimits(module.PumpStyle.END_SUCTION_ANSI_API);
        assert.deepEqual(ansi, {supported: true, minimumFlowRate: 100, maximumFlowRate: 5000,
            minimumSpecificSpeed: 630, maximumSpecificSpeed: 6300});
        assert.notProperty(ansi, 'delete');
        assert.notProperty(module, 'PumpEfficiencyLimits');
        const api = module.getPumpEfficiencyLimits(module.PumpStyle.API_DOUBLE_SUCTION);
        assert.strictEqual(api.maximumFlowRate, 1300);
        const vertical = module.getPumpEfficiencyLimits(module.PumpStyle.VERTICAL_TURBINE);
        assert.strictEqual(vertical.maximumSpecificSpeed, 17172);
        for (const style of [module.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, module.PumpStyle.POSITIVE_DISPLACEMENT]) {
            const limits = module.getPumpEfficiencyLimits(style);
            assert.isFalse(limits.supported);
            assert.isNaN(limits.minimumFlowRate);
            assert.isNaN(limits.maximumFlowRate);
            assert.isNaN(limits.minimumSpecificSpeed);
            assert.isNaN(limits.maximumSpecificSpeed);
        }
        for (const name of ['PumpEfficiency', 'PumpEfficiencyResults', 'OptimalSpecificSpeedCorrection']) {
            assert.notProperty(module, name);
        }
    });
});
