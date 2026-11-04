import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';
import { reference } from './hi_2020_reference';
import { pumpStyles } from './hi_2020_test_helpers';

describe('HI 2020 optimal_specific_speed_correction WASM', function () {
    let module: MeasurToolsSuite;
    before(async function () {
        module = await createModule({locateFile: filename => '/base/bin/' + filename});
    });
    it('matches independent full-precision SciPy goldens', function () {
        for (const [style, x, expected] of reference.correction) {
            assert.approximately(module.calculateOptimalSpecificSpeedCorrection({style: pumpStyles(module)[style], specificSpeed: x}), expected, 1e-12, `x=${x}`);
        }
    });
    it('returns NaN for unavailable coordinates', function () {
        for (const x of [-1, 0, Infinity, -Infinity, NaN, Number.MAX_VALUE]) {
            const style = 6;
            assert.isNaN(module.calculateOptimalSpecificSpeedCorrection({style: pumpStyles(module)[style], specificSpeed: x}));
        }
    });
});
