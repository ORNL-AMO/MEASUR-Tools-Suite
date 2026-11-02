import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type PumpEfficiencyInput,
    type PumpEfficiencyModule,
    type PumpEfficiencyResult,
} from 'measur-tools-suite';

const relativeFractionTolerance = 1e-14;
const absoluteFractionTolerance = 1e-15;

function checkFraction(actual: number, expected: number): void {
    if (Number.isNaN(expected)) {
        assert.isNaN(actual);
    } else if (!Number.isFinite(expected) || expected === 0) {
        assert.isTrue(Object.is(actual, expected));
    } else {
        assert.isTrue(Number.isFinite(actual));
        assert.approximately(actual, expected,
            absoluteFractionTolerance + Math.abs(expected) * relativeFractionTolerance);
    }
}

describe('PumpEfficiency stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('preserves the existing representative efficiency assertions', function () {
        const input: PumpEfficiencyInput = {
            style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API,
            rpm: 2000, kinematicViscosity: 1.107, stageCount: 1, flowRate: 2000, head: 137,
        };
        const result: PumpEfficiencyResult = moduleInstance.calculatePumpEfficiency(input);
        assert.approximately(result.average, 0.84, 0.001, 'average');
        assert.approximately(result.max, 0.869, 0.001, 'max');
    });

    it('preserves captured styles, boundaries, fractional stages and nonfinite arithmetic', function () {
        const calculator: PumpEfficiencyModule = moduleInstance;
        // Unchanged fixed legacy captures at 23b58b0, Apple clang 21, -O3 -DNDEBUG -std=gnu++20.
        const fixtures: { input: PumpEfficiencyInput; average: number; maximum: number }[] = [
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.30716859847864231, maximum: 0.33778841732326587 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.72960709313227678, maximum: 0.75589073588267208 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.82110213196336113, maximum: 0.83842443360912178 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.71690488464797109, maximum: 0.74273093822045799 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.72586676933729755, maximum: 0.75201566924414953 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.69836468114945904, maximum: 0.72352283539659468 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.3369133438188715, maximum: 0.37049824020855737 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.77835723220739605, maximum: 0.8063970684646028 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.84407452353906609, maximum: 0.86188146002001753 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.76565502372309036, maximum: 0.79323727080238871 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.77461690841241682, maximum: 0.80252200182608024 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.74711482022457831, maximum: 0.7740291679785255 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.50306328302289338, maximum: 0.55321068308212706 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.80553784553817265, maximum: 0.83455684652287099 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.85496691362486132, maximum: 0.873003640358894 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.79283563705386695, maximum: 0.8213970488606569 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.80179752174319341, maximum: 0.83068177988434844 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.77429543355535491, maximum: 0.80218894603679358 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.3369133438188715, maximum: 0.37049824020855737 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.77835723220739605, maximum: 0.8063970684646028 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.84407452353906609, maximum: 0.86188146002001753 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.76565502372309036, maximum: 0.79323727080238871 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.77461690841241682, maximum: 0.80252200182608024 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.74711482022457831, maximum: 0.7740291679785255 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.50306328302289338, maximum: 0.55321068308212706 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.80553784553817265, maximum: 0.83455684652287099 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.85496691362486132, maximum: 0.873003640358894 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.79283563705386695, maximum: 0.8213970488606569 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.80179752174319341, maximum: 0.83068177988434844 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.77429543355535491, maximum: 0.80218894603679358 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.48142640187469049, maximum: 0.52941694936370065 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.82989128362241638, maximum: 0.85978760210083882 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.85664129782200193, maximum: 0.87471334804017231 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.81718907513811068, maximum: 0.84662780443862473 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.82615095982743714, maximum: 0.85591253546231627 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.79864887163959852, maximum: 0.8274197016147613 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.52650450104366642, maximum: 0.57898861733251594 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.86336234948341173, maximum: 0.88157618971737128 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.82663465509364098, maximum: 0.85641365555031335 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.83559653978296744, maximum: 0.86569838657400489 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.80809445159512894, maximum: 0.83720555272645014 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.65433442925140728, maximum: 0.71956115420542743 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.84972434706377054, maximum: 0.88033513934466179 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.87782225385141399, maximum: 0.89634114605818049 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.83702213857946484, maximum: 0.8671753416824477 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.8459840232687913, maximum: 0.87646007270613924 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.81848193508095268, maximum: 0.84796723885858438 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.69493360827249473, maximum: 0.76420742499638716 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.86108351228438895, maximum: 0.89210351144308031 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.8872497730803165, maximum: 0.90596755203392865 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.84838130380008325, maximum: 0.87894371378086622 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.85734318848940971, maximum: 0.88822844480455776 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.8298411003015711, maximum: 0.8597356109570029 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.65276583471768901, maximum: 0.71783619577025237 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83981846558582396, maximum: 0.87007240463386581 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.89001741255622002, maximum: 0.90879357874813316 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.82511621738288488, maximum: 0.85484051706333963 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.84889452653666309, maximum: 0.87947542504803555 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.84639927834312789, maximum: 0.87689028708682981 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: 0.75743480557413378, maximum: 0.83293899658897552 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.84249461526173863, maximum: 0.87284496094108999 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: 0.86300427445741612, maximum: 0.8812105605962508 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: 0.82979240677743293, maximum: 0.8596851632788759 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: 0.83875429146675939, maximum: 0.86896989430256733 },
            { input: { style: moduleInstance.PumpStyle.LARGE_END_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5.0, flowRate: 2000.0, head: 137.0 }, average: 0.81125220327892089, maximum: 0.84047706045501258 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: -0.068630660524582845, maximum: -0.075472044711826516 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: -0.012295423274621822, maximum: -0.012554812481560099 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: -0.01307378870187031, maximum: -0.013544763826521153 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: -0.0041119040125438206, maximum: -0.0042600328028296148 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 100.0, head: 137.0 }, average: -0.068630660524582845, maximum: -0.075472044711826516 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 10000.0, head: 137.0 }, average: -0.012295423274621822, maximum: -0.012554812481560099 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.5, flowRate: 2000.0, head: 137.0 }, average: -0.01307378870187031, maximum: -0.013544763826521153 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.0, flowRate: 2000.0, head: 137.0 }, average: -0.0041119040125438206, maximum: -0.0042600328028296148 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 0.001, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 10.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 100.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.73181046586426868, maximum: 0.75817348374996452 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1000.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.45616347760374515, maximum: 0.4725964837984109 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 10.219605948395726, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 10.219605948395728, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 10.21960594839573, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 8999.999999999998, head: 137.0 }, average: 0.88773805346091894, maximum: 0.90712622783963537 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 9000.0, head: 137.0 }, average: 0.88775116490025574, maximum: 0.90713962563244244 },
            { input: { style: moduleInstance.PumpStyle.DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 9000.000000000002, head: 137.0 }, average: 0.88775116490025563, maximum: 0.90713962563244233 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2549.9999999999995, head: 137.0 }, average: 0.85016360527395485, maximum: 0.87839349205906592 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2550.0, head: 137.0 }, average: 0.85017317218465471, maximum: 0.87840337664133428 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2550.0000000000005, head: 137.0 }, average: 0.85017317218465505, maximum: 0.87840337664133461 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2549.9999999999995, head: 137.0 }, average: 0.85761661521997357, maximum: 0.8860939809911047 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2550.0, head: 137.0 }, average: 0.85762618213067343, maximum: 0.88610386557337306 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2550.0000000000005, head: 137.0 }, average: 0.85762618213067354, maximum: 0.88610386557337317 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7219.999999999999, head: 137.0 }, average: 0.8840864769503809, maximum: 0.90484990425163025 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7220.0, head: 137.0 }, average: 0.88407552368847875, maximum: 0.90483869374424009 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7220.000000000001, head: 137.0 }, average: 0.88407552368847975, maximum: 0.9048386937442412 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7219.999999999999, head: 137.0 }, average: 0.87746072683294096, maximum: 0.8980685434733936 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7220.0, head: 137.0 }, average: 0.87744977357103882, maximum: 0.89805733296600343 },
            { input: { style: moduleInstance.PumpStyle.AXIAL_FLOW, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 7220.000000000001, head: 137.0 }, average: 0.87744977357103904, maximum: 0.89805733296600365 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1029.9999999999998, head: 137.0 }, average: 0.80455405199346175, maximum: 0.8407997054843217 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1030.0, head: 137.0 }, average: 0.80455069059549822, maximum: 0.84079619265331829 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1030.0000000000002, head: 137.0 }, average: 0.80455069059549822, maximum: 0.84079619265331829 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 889.9999999999999, head: 137.0 }, average: 0.77876750787057103, maximum: 0.81562821451987644 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 890.0, head: 137.0 }, average: 0.77876962855842535, maximum: 0.81563043558435422 },
            { input: { style: moduleInstance.PumpStyle.MULTISTAGE_BOILER_FEED, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 890.0000000000001, head: 137.0 }, average: 0.77876962855842535, maximum: 0.81563043558435422 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4439.999999999999, head: 137.0 }, average: 0.83902205355592607, maximum: 0.86217334137968782 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4440.0, head: 137.0 }, average: 0.83902249068360579, maximum: 0.86217379056911092 },
            { input: { style: moduleInstance.PumpStyle.API_DOUBLE_SUCTION, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4440.000000000001, head: 137.0 }, average: 0.83902249068360579, maximum: 0.86217379056911092 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4439.999999999999, head: 137.0 }, average: 0.83902205355592607, maximum: 0.86217334137968782 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4440.0, head: 137.0 }, average: 0.83902249068360579, maximum: 0.86217379056911092 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_STOCK, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 4440.000000000001, head: 137.0 }, average: 0.83902249068360579, maximum: 0.86217379056911092 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2169.9999999999995, head: 137.0 }, average: 0.78497984091060502, maximum: 0.81249429376716886 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2170.0, head: 137.0 }, average: 0.78498528914899546, maximum: 0.8124999329726269 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2170.0000000000005, head: 137.0 }, average: 0.78498528914899546, maximum: 0.8124999329726269 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2169.9999999999995, head: 137.0 }, average: 0.78497984091060502, maximum: 0.81249429376716886 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2170.0, head: 137.0 }, average: 0.78498528914899546, maximum: 0.8124999329726269 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2170.0000000000005, head: 137.0 }, average: 0.78498528914899546, maximum: 0.8124999329726269 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1689.9999999999998, head: 137.0 }, average: 0.71278452503791656, maximum: 0.7399577740762987 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1690.0, head: 137.0 }, average: 0.71278213364001697, maximum: 0.73995529151192674 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_SLURRY, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1690.0000000000002, head: 137.0 }, average: 0.71278213364001697, maximum: 0.73995529151192674 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2265.4054903281612, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83965977582309803, maximum: 0.86990799817091746 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2265.405490328162, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2265.4054903281626, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 4074.1482138312786, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.8500959272813351, maximum: 0.88072010550896884 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 4074.148213831279, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.8500959272813351, maximum: 0.88072010550896884 },
            { input: { style: moduleInstance.PumpStyle.VERTICAL_TURBINE, rpm: 4074.1482138312804, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.8500959272813351, maximum: 0.88072010550896884 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 0.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: -0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: -1.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.6906290940472134, maximum: 0.71550857856954264 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 1e-300, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2.2250738585072014e-308, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 5e-324, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 1.7976931348623157e+308, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: -Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: NaN, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 0.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: -0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: -1.0, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1e-300, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 2.2250738585072014e-308, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 5e-324, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.7976931348623157e+308, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: Infinity, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: -Infinity, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: -0.00037158021756460174, maximum: -0.00038496616430705135 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: NaN, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83933686357794668, maximum: 0.86957345321252744 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 0.0, flowRate: 2000.0, head: 137.0 }, average: 0.69086759379551121, maximum: 0.71575567012326469 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: -0, flowRate: 2000.0, head: 137.0 }, average: 0.69086759379551121, maximum: 0.71575567012326469 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: -1.0, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1e-300, flowRate: 2000.0, head: 137.0 }, average: 0.69086759379551121, maximum: 0.71575567012326469 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 2.2250738585072014e-308, flowRate: 2000.0, head: 137.0 }, average: 0.69086759379551121, maximum: 0.71575567012326469 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 5e-324, flowRate: 2000.0, head: 137.0 }, average: 0.69086759379551121, maximum: 0.71575567012326469 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.7976931348623157e+308, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: Infinity, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: -Infinity, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: NaN, flowRate: 2000.0, head: 137.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 0.0, head: 137.0 }, average: -0.14884085, maximum: -Infinity },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: -0, head: 137.0 }, average: -0.14884085, maximum: -Infinity },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: -1.0, head: 137.0 }, average: 0.45094692596657465, maximum: NaN },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1e-300, head: 137.0 }, average: -0.14884085, maximum: -6.0175763408286807e+103 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2.2250738585072014e-308, head: 137.0 }, average: -0.14884085, maximum: -2.8902269451587434e+106 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 5e-324, head: 137.0 }, average: -0.14884085, maximum: -8.8306749684560674e+111 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 1.7976931348623157e+308, head: 137.0 }, average: 0.87748473000000005, maximum: 0.87843293175088155 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: Infinity, head: 137.0 }, average: 0.87748473000000005, maximum: 0.87843293175088155 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: -Infinity, head: 137.0 }, average: -Infinity, maximum: NaN },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: NaN, head: 137.0 }, average: NaN, maximum: NaN },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 0.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: -0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: -1.0 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 1e-300 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 2.2250738585072014e-308 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 5e-324 }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 1.7976931348623157e+308 }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: Infinity }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: -Infinity }, average: -0.14884085, maximum: -0.15420274925356978 },
            { input: { style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API, rpm: 2000.0, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: NaN }, average: 0.83970844379551124, maximum: 0.86995841937683449 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: -Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
            { input: { style: moduleInstance.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, rpm: NaN, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: -Infinity, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
            { input: { style: moduleInstance.PumpStyle.POSITIVE_DISPLACEMENT, rpm: NaN, kinematicViscosity: 1.107, stageCount: 1.0, flowRate: 2000.0, head: 137.0 }, average: 0, maximum: 0 },
        ];
        for (const fixture of fixtures) {
            const input: PumpEfficiencyInput = Object.freeze(fixture.input);
            const before = { ...input };
            const result: PumpEfficiencyResult = calculator.calculatePumpEfficiency(input);
            checkFraction(result.average, fixture.average);
            checkFraction(result.max, fixture.maximum);
            assert.deepEqual(input, before);
            assert.deepEqual(Object.keys(result).sort(), ['average', 'max']);
            assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
            assert.notProperty(result, 'delete');
            assert.notProperty(input, 'pumpEfficiency');
        }
    });

    it('returns independent plain results without retaining state', function () {
        const input: PumpEfficiencyInput = Object.freeze({
            style: moduleInstance.PumpStyle.END_SUCTION_ANSI_API,
            rpm: 2000, kinematicViscosity: 1.107, stageCount: 1, flowRate: 2000, head: 137,
        });
        const first: PumpEfficiencyResult = moduleInstance.calculatePumpEfficiency(input);
        moduleInstance.calculatePumpEfficiency({ ...input, flowRate: NaN });
        const second: PumpEfficiencyResult = moduleInstance.calculatePumpEfficiency(input);
        assert.notStrictEqual(first, second);
        assert.strictEqual(second.average, first.average);
        assert.strictEqual(second.max, first.max);
        first.average = -1;
        assert.approximately(second.average, 0.83933686357794668, 1e-14);
    });

    it('exposes all six functions and removes the superseded runtime constructors', function () {
        for (const name of [
            'calculateOptimalDeviationFactor', 'calculateOptimalPrePumpEfficiency',
            'calculateOptimalSpecificSpeed', 'calculateOptimalSpecificSpeedCorrection',
            'calculateOptimalPumpEfficiency', 'calculatePumpEfficiency',
        ]) {
            assert.isFunction(Reflect.get(moduleInstance, name));
        }
        for (const name of [
            'OptimalSpecificSpeedCorrection', 'PumpEfficiency', 'PumpEfficiencyResults',
            'PumpEfficiencyInput', 'PumpEfficiencyResult',
        ]) {
            assert.notProperty(moduleInstance, name);
        }
    });
});
