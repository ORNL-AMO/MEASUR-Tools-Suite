import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OptimalSpecificSpeedCorrectionInput,
    type OptimalSpecificSpeedCorrectionModule,
} from 'measur-tools-suite';

describe('OptimalSpecificSpeedCorrection stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('retains the original achievable-efficiency assertion', function () {
        const input: OptimalSpecificSpeedCorrectionInput = {
            style: moduleInstance.PumpStyle.END_SUCTION_SLURRY,
            specificSpeed: 1170,
        };
        const achievableEfficiency = moduleInstance.calculateOptimalSpecificSpeedCorrection(input) * 100;
        assert.approximately(achievableEfficiency, 1.8942771852074485, 0.001, 'achievableEfficiency');
    });

    it('preserves all styles, strict speed intervals and nonfinite outcomes', function () {
        const calculator: OptimalSpecificSpeedCorrectionModule = moduleInstance;
        assert.isFunction(calculator.calculateOptimalSpecificSpeedCorrection);
        // Immutable native legacy matrix at 23b58b0, Apple clang 21, -O3; permit libm rounding.
        const fixtures: { specificSpeed: number; nonvertical: number; vertical: number }[] = [
            { specificSpeed: -10000.0, nonvertical: 0, vertical: 666.04529118999994 },
            { specificSpeed: -1.0, nonvertical: 0.14905439261388748, vertical: 0.14811046581929946 },
            { specificSpeed: -0, nonvertical: 0.14884085, vertical: 0.14788539000000001 },
            { specificSpeed: 0.0, nonvertical: 0.14884085, vertical: 0.14788539000000001 },
            { specificSpeed: 1.0, nonvertical: 0.14862754973011555, vertical: 0.14766065870791836 },
            { specificSpeed: 680.0, nonvertical: 0.050200390373725104, vertical: 0.054497999621451437 },
            { specificSpeed: 1170.0, nonvertical: 0.018942771852074478, vertical: 0.029634927897356143 },
            { specificSpeed: 2000.0, nonvertical: 0.0013573458400000218, vertical: 0.012976983279999915 },
            { specificSpeed: 3000.0, nonvertical: 0.0011049816620000374, vertical: 0.0040988502299998779 },
            { specificSpeed: 5000.0, nonvertical: 0.0123399482500001, vertical: 0.00010315571874998605 },
            { specificSpeed: 10000.0, nonvertical: 0.23778841700000133, vertical: 0.0099952339999999935 },
            { specificSpeed: 20000.0, nonvertical: 154.33890111699998, vertical: 0.050900164000000053 },
            { specificSpeed: 1e+100, nonvertical: 0, vertical: 0 },
            { specificSpeed: 1e+300, nonvertical: 0, vertical: 0 },
            { specificSpeed: Infinity, nonvertical: 0, vertical: 0 },
            { specificSpeed: -Infinity, nonvertical: 0, vertical: Infinity },
            { specificSpeed: NaN, nonvertical: 0, vertical: 0 },
            { specificSpeed: 2529.9999999999995, nonvertical: 4.8667972413260523e-05, vertical: 0.0074387779005637778 },
            { specificSpeed: 2530.0, nonvertical: 0, vertical: 0.0074387779005637197 },
            { specificSpeed: 2530.0000000000005, nonvertical: 0, vertical: 0.0074387779005635549 },
            { specificSpeed: 4549.999999999999, nonvertical: 0.008907112484013548, vertical: 0 },
            { specificSpeed: 4550.0, nonvertical: 0.0089071124840132982, vertical: 0 },
            { specificSpeed: 4550.000000000001, nonvertical: 0.0089071124840130501, vertical: 0 },
        ];
        const styles = [
            moduleInstance.PumpStyle.END_SUCTION_SLURRY,
            moduleInstance.PumpStyle.END_SUCTION_SEWAGE,
            moduleInstance.PumpStyle.END_SUCTION_STOCK,
            moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE,
            moduleInstance.PumpStyle.API_DOUBLE_SUCTION,
            moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED,
            moduleInstance.PumpStyle.END_SUCTION_ANSI_API,
            moduleInstance.PumpStyle.AXIAL_FLOW,
            moduleInstance.PumpStyle.DOUBLE_SUCTION,
            moduleInstance.PumpStyle.VERTICAL_TURBINE,
            moduleInstance.PumpStyle.LARGE_END_SUCTION,
            moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY,
            moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT,
        ];
        for (const style of styles) {
            for (const fixture of fixtures) {
                const input: OptimalSpecificSpeedCorrectionInput = Object.freeze({ style, specificSpeed: fixture.specificSpeed });
                const expected = style === moduleInstance.PumpStyle.VERTICAL_TURBINE ? fixture.vertical : fixture.nonvertical;
                const actual = calculator.calculateOptimalSpecificSpeedCorrection(input);
                if (expected === 0 || !Number.isFinite(expected)) {
                    assert.isTrue(Object.is(actual, expected), String(fixture.specificSpeed));
                } else {
                    assert.approximately(actual, expected, 1e-15 + Math.abs(expected) * 1e-14);
                }
                assert.strictEqual(input.style, style);
                assert.isTrue(Object.is(input.specificSpeed, fixture.specificSpeed));
            }
        }
        for (const name of ['OptimalSpecificSpeedCorrection', 'OptimalSpecificSpeedCorrectionInput']) {
            assert.notProperty(moduleInstance, name);
        }
    });

    it('has no retained state between independent plain-input calls', function () {
        const input: OptimalSpecificSpeedCorrectionInput = Object.freeze({
            style: moduleInstance.PumpStyle.AXIAL_FLOW,
            specificSpeed: 1170,
        });
        const original = moduleInstance.calculateOptimalSpecificSpeedCorrection(input);
        moduleInstance.calculateOptimalSpecificSpeedCorrection({ style: moduleInstance.PumpStyle.VERTICAL_TURBINE, specificSpeed: 5000 });
        moduleInstance.calculateOptimalSpecificSpeedCorrection({ style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, specificSpeed: NaN });
        assert.strictEqual(moduleInstance.calculateOptimalSpecificSpeedCorrection(input), original);
    });
});
