import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type MotorCurrentInput, type MotorCurrentOutput } from 'measur-tools-suite';

describe('MotorCurrent stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function makeInput(overrides: Partial<MotorCurrentInput> = {}): MotorCurrentInput {
        return {
            motorRatedPower: 100,
            motorRpm: 1500,
            lineFrequency: moduleInstance.LineFrequency.FREQ60,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
            specifiedEfficiency: 0,
            loadFactor: 0.25,
            ratedVoltage: 460,
            ...overrides
        };
    }

    it('returns a plain current/estimated-FLA result and a scalar optimal current', function () {
        const input: MotorCurrentInput = makeInput();
        const output: MotorCurrentOutput = moduleInstance.calculateMotorCurrent(input, 113.8);
        assert.closeTo(output.current, 42.72830823335467, 1e-9);
        assert.closeTo(output.estimatedFLA, 113.83426223054738, 1e-9);
        assert.closeTo(moduleInstance.calculateOptimalMotorCurrent(input), 42.7411726195374, 1e-9);
        assert.deepEqual(Object.keys(output).sort(), ['current', 'estimatedFLA']);
        assert.notProperty(input, 'delete');
        assert.notProperty(output, 'delete');
        assert.notProperty(moduleInstance, 'MotorCurrent');
        assert.notProperty(moduleInstance, 'MotorCurrentInput');
        assert.notProperty(moduleInstance, 'MotorCurrentOutput');
    });

    it('preserves legacy anchors, strict branch boundaries, cap, and negative extrapolation', function () {
        // Captured from freshly built legacy MotorCurrent at base 363c011 before replacing the class.
        const goldens: [load: number, current: number, optimal: number][] = [
            [-0.1, 32.8037658240359, 32.81364218772196],
            [0, 33.32079190019643, 33.33082392703388],
            [0.25, 42.72830823335467, 42.7411726195374],
            [0.250999, 42.789155614647775, 42.80203832039999],
            [0.251, 42.80718085695348, 42.820068989638344],
            [0.251001, 42.807259749150035, 42.82014790558729],
            [0.5, 63.72861191330423, 63.747798946645176],
            [0.75, 87.44208444177028, 87.46841098707905],
            [1, 113.79999999999656, 113.83426223054711],
            [1.25, 142.36380000000074, 142.40666205041475],
            [1.250999, 142.48140607203064, 142.5243035305847],
            [1.251, 142.48248461595944, 142.5253823992349],
            [1.251001, 142.48260331824017, 142.5255011372538],
            [1.5, 173.13348444176913, 173.18561044667257],
            [1.500001, 173.13348444176913, 173.18561044667257],
            [2, 173.13348444176913, 173.18561044667257],
        ];
        for (const [loadFactor, current, optimal] of goldens) {
            const input = makeInput({ loadFactor });
            const output = moduleInstance.calculateMotorCurrent(input, 113.8);
            assert.closeTo(output.current, current, 1e-8, `supplied-FLA load ${loadFactor}`);
            assert.closeTo(output.estimatedFLA, 113.83426223054738, 1e-9);
            assert.closeTo(moduleInstance.calculateOptimalMotorCurrent(input), optimal, 1e-8, `optimal load ${loadFactor}`);
        }
    });

    it('preserves voltage, FLA, frequency, specified-baseline, and premium-pole goldens', function () {
        const goldens: {
            input: MotorCurrentInput;
            fullLoadAmps: number;
            current: number;
            optimal: number;
            estimatedFLA: number;
        }[] = [
            {
                input: makeInput({ ratedVoltage: 230 }),
                fullLoadAmps: 113.8,
                current: 42.72830823335467,
                optimal: 42.7411726195374,
                estimatedFLA: 227.66852446109476
            },
            {
                input: makeInput({  }),
                fullLoadAmps: 227.6,
                current: 85.45661646670933,
                optimal: 42.7411726195374,
                estimatedFLA: 113.83426223054738
            },
            {
                input: makeInput({  }),
                fullLoadAmps: 0,
                current: 0,
                optimal: 42.7411726195374,
                estimatedFLA: 113.83426223054738
            },
            {
                input: makeInput({ motorRatedPower: 500, motorRpm: 1785, ratedVoltage: 2300 }),
                fullLoadAmps: 557.9,
                current: 197.40572260650677,
                optimal: 197.42286478023064,
                estimatedFLA: 111.58968930241159
            },
            {
                input: makeInput({ motorRatedPower: 500, motorRpm: 1785, loadFactor: 0.5, ratedVoltage: 2300 }),
                fullLoadAmps: 557.9,
                current: 304.66521432545727,
                optimal: 304.6916706204591,
                estimatedFLA: 111.58968930241159
            },
            {
                input: makeInput({ motorRatedPower: 500, motorRpm: 1785, loadFactor: 0.75, ratedVoltage: 2300 }),
                fullLoadAmps: 557.9,
                current: 426.5420335857156,
                optimal: 426.57907333078305,
                estimatedFLA: 111.58968930241159
            },
            {
                input: makeInput({ motorRatedPower: 50, loadFactor: 0.83, ratedVoltage: 400, lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD }),
                fullLoadAmps: 70,
                current: 58.89825153021016,
                optimal: 50.80518976466062,
                estimatedFLA: 69.43869588315538
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 1780, loadFactor: 0.83, ratedVoltage: 2300, lineFrequency: moduleInstance.LineFrequency.FREQ50 }),
                fullLoadAmps: 250,
                current: 209.68742444056252,
                optimal: 189.39019528960176,
                estimatedFLA: 45.160122452478994
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 1780, specifiedEfficiency: 0.95, loadFactor: 0.83, ratedVoltage: 230, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED }),
                fullLoadAmps: 450,
                current: 377.4373639930088,
                optimal: 189.39019528960176,
                estimatedFLA: 454.5766800452733
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 1780, specifiedEfficiency: 0.8, loadFactor: 0.83, ratedVoltage: 230, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED }),
                fullLoadAmps: 450,
                current: 377.4373639930088,
                optimal: 191.7152954476481,
                estimatedFLA: 536.7170257100602
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 3600, loadFactor: 0.83, ratedVoltage: 230, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM }),
                fullLoadAmps: 450,
                current: 376.3832047200176,
                optimal: 182.1248801179472,
                estimatedFLA: 435.493374971657
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 1780, loadFactor: 0.83, ratedVoltage: 230, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM }),
                fullLoadAmps: 450,
                current: 377.437363993001,
                optimal: 187.91191229626423,
                estimatedFLA: 448.0762563554074
            },
            {
                input: makeInput({ motorRatedPower: 200, motorRpm: 1200, loadFactor: 0.83, ratedVoltage: 230, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM }),
                fullLoadAmps: 450,
                current: 378.20946540586624,
                optimal: 196.41191817410171,
                estimatedFLA: 467.38842500147217
            },
        ];
        for (const golden of goldens) {
            const output = moduleInstance.calculateMotorCurrent(golden.input, golden.fullLoadAmps);
            assert.closeTo(output.current, golden.current, 1e-8);
            assert.closeTo(output.estimatedFLA, golden.estimatedFLA, 1e-9);
            assert.closeTo(moduleInstance.calculateOptimalMotorCurrent(golden.input), golden.optimal, 1e-8);
        }
    });

    it('has no retained load or FLA state and does not modify input', function () {
        const input = Object.freeze(makeInput({ loadFactor: 2 }));
        const before = { ...input };
        const first = moduleInstance.calculateMotorCurrent(input, 113.8);
        const optimal = moduleInstance.calculateOptimalMotorCurrent(input);
        const capped = makeInput({ loadFactor: 1.5 });
        assert.strictEqual(first.current, moduleInstance.calculateMotorCurrent(capped, 113.8).current);
        assert.strictEqual(optimal, moduleInstance.calculateOptimalMotorCurrent(capped));
        const doubled = moduleInstance.calculateMotorCurrent(input, 227.6);
        assert.closeTo(doubled.current, first.current * 2, 1e-9);
        assert.strictEqual(doubled.estimatedFLA, first.estimatedFLA);
        assert.strictEqual(moduleInstance.calculateMotorCurrent(input, 0).current, 0);
        assert.deepEqual(moduleInstance.calculateMotorCurrent(input, 113.8), first);
        assert.strictEqual(moduleInstance.calculateOptimalMotorCurrent(input), optimal);
        assert.deepEqual(input, before);
    });
});
