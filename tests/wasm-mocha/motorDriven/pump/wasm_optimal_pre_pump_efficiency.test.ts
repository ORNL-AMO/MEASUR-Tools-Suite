import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OptimalPrePumpEfficiencyInput,
    type OptimalPrePumpEfficiencyModule,
    type PumpEfficiencyResult,
    type PumpStyle,
} from 'measur-tools-suite';

const relativePercentTolerance = 1e-14;
const absolutePercentTolerance = 1e-12;
const relativeFractionTolerance = 1e-14;
const absoluteFractionTolerance = 1e-15;

function checkPercent(actual: number, expected: number): void {
    if (Number.isNaN(expected)) {
        assert.isNaN(actual);
    } else if (!Number.isFinite(expected)) {
        assert.strictEqual(actual, expected);
    } else {
        assert.approximately(actual, expected, absolutePercentTolerance + Math.abs(expected) * relativePercentTolerance);
    }
}

describe('OptimalPrePumpEfficiency stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('accepts immutable typed inputs and preserves all styles across the numeric range', function () {
        const calculator: OptimalPrePumpEfficiencyModule = moduleInstance;
        const styles: PumpStyle[] = [
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
        // Immutable captures at 666f224, Apple clang 21 arm64, -O3 -DNDEBUG -std=gnu++20.
        const flows = [0.001, 1, 100, 500, 1000, 2000, 5000, 10000, 100000, 0, -0, -1, -1000, 1e-300, 2.2250738585072014e-308, 4.9406564584124654e-324, 1.7976931348623157e+308, Infinity, -Infinity, NaN];
        const expectedByStyle: number[][] = [
            [
                23.990318897386416, 24.166542914393645, 37.604958139262777, 57.18821716442406, 65.271534555431273,
                72.997867334984136, 79.577936321323904, 83.339755523798303, 85.957483662816884, 23.990141999999992,
                23.990141999999992, 23.812745033010032, -15226.473089786881, 23.990141999999992, 23.990141999999992,
                23.990141999999992, 85.957483999999994, 85.957483999999994, -Infinity, NaN
            ],
            [
                22.400209134352373, 22.634470009438807, 40.581413990584061, 64.987909448342862, 71.87699271025599,
                77.872881242496064, 83.126723112034895, 85.63699468136879, 89.681425194978274, 22.399974,
                22.399974, 22.164197565131261, -12495.729639822215, 22.399974, 22.399974,
                22.399974, 89.704526000000001, 89.704526000000001, -Infinity, NaN
            ],
            [
                52.834059739884374, 52.88170936957691, 57.207475269099447, 68.719154239133118, 75.575287270852812,
                80.59094257557372, 84.536770890235928, 86.726233689948316, 90.121186232840785, 52.834012000000001,
                52.834012000000001, 52.786229462647711, -83.145910557428081, 52.834012000000001, 52.834012000000001,
                52.834012000000001, 90.158463999999995, 90.158463999999995, -Infinity, NaN
            ],
            [
                22.400209134352373, 22.634470009438807, 40.581413990584061, 64.987909448342862, 71.87699271025599,
                77.872881242496064, 83.126723112034895, 85.63699468136879, 89.681425194978274, 22.399974,
                22.399974, 22.164197565131261, -12495.729639822215, 22.399974, 22.399974,
                22.399974, 89.704526000000001, 89.704526000000001, -Infinity, NaN
            ],
            [
                52.834059739884374, 52.88170936957691, 57.207475269099447, 68.719154239133118, 75.575287270852812,
                80.59094257557372, 84.536770890235928, 86.726233689948316, 90.121186232840785, 52.834012000000001,
                52.834012000000001, 52.786229462647711, -83.145910557428081, 52.834012000000001, 52.834012000000001,
                52.834012000000001, 90.158463999999995, 90.158463999999995, -Infinity, NaN
            ],
            [
                39.49864857241014, 39.705372025798091, 55.042345907214809, 74.196725779157518, 79.533102946097571,
                83.026286383998098, 85.77136500528448, 86.893672109662376, 87.129683999999997, 39.498441,
                39.498441, 39.290223047896994, -24809.723424731757, 39.498441, 39.498441,
                39.498441, 87.129683999999997, 87.129683999999997, -Infinity, NaN
            ],
            [
                45.293354756795964, 45.490211310462627, 59.55315850632195, 75.917583906682609, 80.893890555730152,
                83.970844379551124, 86.563517859353837, 87.565777275803356, 87.748473000000004, 45.293157000000008,
                45.293157000000008, 45.094692596657467, -69416.904220929922, 45.293157000000008, 45.293157000000008,
                45.293157000000008, 87.748473000000004, 87.748473000000004, -Infinity, NaN
            ],
            [
                68.669608886435569, 68.712877004526504, 72.344666163754042, 79.449461614546152, 82.49098752707944,
                85.009592728133512, 87.60387559206886, 89.011767712603586, 90.124014639823841, 68.669565500000004,
                68.669565500000004, 68.626103790777663, -413.07652228725851, 68.669565500000004, 68.669565500000004,
                68.669565500000004, 90.124015999999997, 90.124015999999997, -Infinity, NaN
            ],
            [
                74.247056696214159, 74.271299320677613, 76.407288404218136, 81.437568326854944, 84.032600232095177,
                86.145509250195346, 88.718275611425099, 89.954519635493838, 90.99998817272899, 74.247032399999995,
                74.247032399999995, 74.222706782182257, -37.72331497644187, 74.247032399999995, 74.247032399999995,
                74.247032399999995, 91, 91, -Infinity, NaN
            ],
            [
                68.669608886435569, 68.712877004526504, 72.344666163754042, 79.449461614546152, 82.49098752707944,
                85.009592728133512, 87.60387559206886, 89.011767712603586, 90.124014639823841, 68.669565500000004,
                68.669565500000004, 68.626103790777663, -413.07652228725851, 68.669565500000004, 68.669565500000004,
                68.669565500000004, 90.124015999999997, 90.124015999999997, -Infinity, NaN
            ],
            [
                82.560292021695815, 82.56131260644139, 82.661571380762723, 83.049453117618981, 83.497852838537767,
                84.286619547930314, 85.992734267123993, 87.529969773203803, 90.279678492972991, 82.560290999999992,
                82.560290999999992, 82.559269214601571, 81.443238583447624, 82.560290999999992, 82.560290999999992,
                82.560290999999992, 90.379273999999995, 90.379273999999995, -Infinity, NaN
            ],
            [
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0
            ],
            [
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0
            ],
        ];
        for (const [styleIndex, style] of styles.entries()) {
            for (const [flowIndex, flowRate] of flows.entries()) {
                const input: OptimalPrePumpEfficiencyInput = Object.freeze({ style, flowRate });
                const actual: number = calculator.calculateOptimalPrePumpEfficiency(input);
                assert.isNumber(actual);
                checkPercent(actual, expectedByStyle[styleIndex][flowIndex]);
                calculator.calculateOptimalPrePumpEfficiency({ style: moduleInstance.PumpStyle.DOUBLE_SUCTION, flowRate: NaN });
                checkPercent(calculator.calculateOptimalPrePumpEfficiency(input), expectedByStyle[styleIndex][flowIndex]);
                assert.strictEqual(input.style, style);
                assert.isTrue(Object.is(input.flowRate, flowRate));
            }
        }
        for (const name of ['OptimalPrePumpEff', 'OptimalPrePumpEfficiency', 'OptimalPrePumpEfficiencyInput', 'OptimalPrePumpEfficiencyResult']) {
            assert.notProperty(moduleInstance, name);
        }
        // Leave unknown enum handling to embind; no JS validation or alternative fallback is added.
    });

    it('selects the upper interval at equality for every threshold and equivalent style group', function () {
        const fixtures = [
            { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, flows: [8999.9999999999982, 9000, 9000.0000000000018], expected: [89.802851476388838, 89.804162620322515, 89.804162620322515] },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flows: [2549.9999999999995, 2550, 2550.0000000000005], expected: [85.767055860241015, 85.768012551311003, 85.768012551311003] },
            { style: moduleInstance.PumpStyle.AXIAL_FLOW, flows: [2549.9999999999995, 2550, 2550.0000000000005], expected: [85.767055860241015, 85.768012551311003, 85.768012551311003] },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flows: [7219.9999999999991, 7220, 7220.0000000000009], expected: [88.431019933984075, 88.429924607793865, 88.429924607793865] },
            { style: moduleInstance.PumpStyle.AXIAL_FLOW, flows: [7219.9999999999991, 7220, 7220.0000000000009], expected: [88.431019933984075, 88.429924607793865, 88.429924607793865] },
            { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, flows: [1029.9999999999998, 1030, 1030.0000000000002], expected: [81.071829771252183, 81.071493631455823, 81.071493631455823] },
            { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, flows: [889.99999999999989, 890, 890.00000000000011], expected: [78.733213659923905, 78.733425728709335, 78.733425728709335] },
            { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, flows: [4439.9999999999991, 4440, 4440.0000000000009], expected: [84.125657475720729, 84.125701188488691, 84.125701188488691] },
            { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, flows: [4439.9999999999991, 4440, 4440.0000000000009], expected: [84.125657475720729, 84.125701188488691, 84.125701188488691] },
            { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, flows: [2169.9999999999995, 2170, 2170.0000000000005], expected: [78.518747493498751, 78.519292317337801, 78.519292317337801] },
            { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, flows: [2169.9999999999995, 2170, 2170.0000000000005], expected: [78.518747493498751, 78.519292317337801, 78.519292317337801] },
            { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, flows: [1689.9999999999998, 1690, 1690.0000000000002], expected: [71.382670018721427, 71.382430878931473, 71.382430878931473] },
        ];
        for (const { style, flows, expected } of fixtures) {
            for (const [index, flowRate] of flows.entries()) {
                checkPercent(moduleInstance.calculateOptimalPrePumpEfficiency({ style, flowRate }), expected[index]);
            }
        }
    });

    it('preserves the composite fractions through the plain result API', function () {
        const fixtures = [
            { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, flow: 100, average: 0.30716859847864231, maximum: 0.33778841732326587 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, flow: 2000, average: 0.72960709313227678, maximum: 0.75589073588267208 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, flow: 10000, average: 0.82110213196336113, maximum: 0.83842443360912178 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, flow: 100, average: 0.3369133438188715, maximum: 0.37049824020855737 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, flow: 2000, average: 0.77835723220739605, maximum: 0.8063970684646028 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, flow: 10000, average: 0.84407452353906609, maximum: 0.86188146002001753 },
            { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, flow: 100, average: 0.50306328302289338, maximum: 0.55321068308212706 },
            { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, flow: 2000, average: 0.80553784553817265, maximum: 0.83455684652287099 },
            { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, flow: 10000, average: 0.85496691362486132, maximum: 0.873003640358894 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, flow: 100, average: 0.3369133438188715, maximum: 0.37049824020855737 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, flow: 2000, average: 0.77835723220739605, maximum: 0.8063970684646028 },
            { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, flow: 10000, average: 0.84407452353906609, maximum: 0.86188146002001753 },
            { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, flow: 100, average: 0.50306328302289338, maximum: 0.55321068308212706 },
            { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, flow: 2000, average: 0.80553784553817265, maximum: 0.83455684652287099 },
            { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, flow: 10000, average: 0.85496691362486132, maximum: 0.873003640358894 },
            { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, flow: 100, average: 0.48142640187469049, maximum: 0.52941694936370065 },
            { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, flow: 2000, average: 0.82989128362241638, maximum: 0.85978760210083882 },
            { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, flow: 10000, average: 0.85664129782200193, maximum: 0.87471334804017231 },
            { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, flow: 100, average: 0.52650450104366642, maximum: 0.57898861733251594 },
            { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, flow: 2000, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, flow: 10000, average: 0.86336234948341173, maximum: 0.88157618971737128 },
            { style: moduleInstance.PumpStyle.AXIAL_FLOW, flow: 100, average: 0.65433442925140728, maximum: 0.71956115420542743 },
            { style: moduleInstance.PumpStyle.AXIAL_FLOW, flow: 2000, average: 0.84972434706377054, maximum: 0.88033513934466179 },
            { style: moduleInstance.PumpStyle.AXIAL_FLOW, flow: 10000, average: 0.87782225385141399, maximum: 0.89634114605818049 },
            { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, flow: 100, average: 0.69493360827249473, maximum: 0.76420742499638716 },
            { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, flow: 2000, average: 0.86108351228438895, maximum: 0.89210351144308031 },
            { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, flow: 10000, average: 0.8872497730803165, maximum: 0.90596755203392865 },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flow: 100, average: 0.65276583471768901, maximum: 0.71783619577025237 },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flow: 2000, average: 0.83981846558582396, maximum: 0.87007240463386581 },
            { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, flow: 10000, average: 0.89001741255622002, maximum: 0.90879357874813316 },
            { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, flow: 100, average: 0.75743480557413378, maximum: 0.83293899658897552 },
            { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, flow: 2000, average: 0.84249461526173863, maximum: 0.87284496094108999 },
            { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, flow: 10000, average: 0.86300427445741612, maximum: 0.8812105605962508 },
            { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, flow: 100, average: -0.068630660524582845, maximum: -0.075472044711826516 },
            { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, flow: 2000, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, flow: 10000, average: -0.012295423274621822, maximum: -0.012554812481560099 },
            { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, flow: 100, average: -0.068630660524582845, maximum: -0.075472044711826516 },
            { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, flow: 2000, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, flow: 10000, average: -0.012295423274621822, maximum: -0.012554812481560099 },
        ];
        for (const fixture of fixtures) {
            const result: PumpEfficiencyResult = moduleInstance.calculatePumpEfficiency({
                style: fixture.style, rpm: 2000, kinematicViscosity: 1.107,
                stageCount: 1, flowRate: fixture.flow, head: 137,
            });
            assert.approximately(result.average, fixture.average,
                absoluteFractionTolerance + Math.abs(fixture.average) * relativeFractionTolerance);
            assert.approximately(result.max, fixture.maximum,
                absoluteFractionTolerance + Math.abs(fixture.maximum) * relativeFractionTolerance);
            assert.notProperty(result, 'delete');
        }
    });
});
