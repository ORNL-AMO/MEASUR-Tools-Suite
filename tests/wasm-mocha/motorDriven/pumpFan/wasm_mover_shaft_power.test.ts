import { assert } from 'chai';
import createModule, {
    type Drive,
    type MeasurToolsSuite,
    type MoverShaftPowerInput,
    type MoverShaftPowerResult,
    type MoverShaftPowerModule,
} from 'measur-tools-suite';

function checkNumber(actual: number, expected: number): void {
    if (Number.isNaN(expected)) {
        assert.isNaN(actual);
    } else if (expected === 0 || !Number.isFinite(expected)) {
        assert.isTrue(Object.is(actual, expected), `expected ${actual} to match ${expected}, including sign`);
    } else {
        assert.approximately(actual, expected, Math.abs(expected) * 1e-12);
    }
}

type Fixture = [power: number, drive: Drive, efficiency: number, expectedPower: number, expectedEfficiency: number];

describe('MoverShaftPower stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function checkFixtures(fixtures: Fixture[]): void {
        const calculator: MoverShaftPowerModule = moduleInstance;
        for (const [motorShaftPower, drive, specifiedEfficiency, power, efficiency] of fixtures) {
            const input: MoverShaftPowerInput = { motorShaftPower, drive, specifiedEfficiency };
            const result: MoverShaftPowerResult = calculator.calculateMoverShaftPower(input);
            checkNumber(result.moverShaftPower, power);
            checkNumber(result.driveEfficiency, efficiency);
        }
    }

    // Both fields captured from the unchanged -O3 legacy calculator at base 2a20eed.
    it('preserves captured duties for all five drives', function () {
        const drive = moduleInstance.Drive;
        checkFixtures([
            [50, drive.V_BELT_DRIVE, 0, 47.874006161154519, 0.95748012322309028],
            [100, drive.V_BELT_DRIVE, 0, 95.908679491417715, 0.95908679491417725],
            [150, drive.V_BELT_DRIVE, 0, 143.95256505385677, 0.9596837670257119],
            [200, drive.V_BELT_DRIVE, 0, 191.98113755661001, 0.95990568778304997],
            [250, drive.V_BELT_DRIVE, 0, 239.9970463698356, 0.95998818547934239],
            [0.001, drive.V_BELT_DRIVE, 0, 0.00091561131281008804, 0.91561131281008801],
            [1, drive.V_BELT_DRIVE, 0, 0.92300588014910112, 0.92300588014910112],
            [10, drive.V_BELT_DRIVE, 0, 9.5002386060280521, 0.95002386060280508],
            [600, drive.V_BELT_DRIVE, 0, 576.02217126524181, 0.9600369521087363],
            [-50, drive.V_BELT_DRIVE, 0, 87826.47322736535, -1756.529464547307],
            [50, drive.N_V_BELT_DRIVE, 0, 48.481432972253224, 0.96962865944506449],
            [100, drive.N_V_BELT_DRIVE, 0, 97.077628208155517, 0.9707762820815552],
            [150, drive.N_V_BELT_DRIVE, 0, 145.6804036098977, 0.97120269073265131],
            [200, drive.N_V_BELT_DRIVE, 0, 194.27224111186428, 0.97136120555932148],
            [250, drive.N_V_BELT_DRIVE, 0, 242.85503312131115, 0.97142013248524461],
            [0.001, drive.N_V_BELT_DRIVE, 0, 0.00093972236629291997, 0.93972236629291994],
            [1, drive.N_V_BELT_DRIVE, 0, 0.94500420010650077, 0.94500420010650077],
            [10, drive.N_V_BELT_DRIVE, 0, 9.6430275757343225, 0.9643027575734322],
            [600, drive.N_V_BELT_DRIVE, 0, 582.87297947517266, 0.97145496579195445],
            [-50, drive.N_V_BELT_DRIVE, 0, 62718.909448118109, -1254.3781889623622],
            [50, drive.S_BELT_DRIVE, 0, 49.392573188901288, 0.9878514637780258],
            [100, drive.S_BELT_DRIVE, 0, 98.831051283262212, 0.98831051283262206],
            [150, drive.S_BELT_DRIVE, 0, 148.27216144395908, 0.98848107629306048],
            [200, drive.S_BELT_DRIVE, 0, 197.7088964447457, 0.98854448222372859],
            [250, drive.S_BELT_DRIVE, 0, 247.14201324852445, 0.98856805299409778],
            [0.001, drive.S_BELT_DRIVE, 0, 0.00097588894651716798, 0.97588894651716795],
            [1, drive.S_BELT_DRIVE, 0, 0.97800168004260035, 0.97800168004260035],
            [10, drive.S_BELT_DRIVE, 0, 9.8572110302937297, 0.98572110302937288],
            [600, drive.S_BELT_DRIVE, 0, 593.14919179006904, 0.98858198631678185],
            [-50, drive.S_BELT_DRIVE, 0, 25057.563779247241, -501.15127558494481],
            [50, drive.SPECIFIED, 1, 50, 1],
            [50, drive.SPECIFIED, 0.97999999999999998, 49, 0.97999999999999998],
            [50, drive.SPECIFIED, 0.95999999999999996, 48, 0.95999999999999996],
            [50, drive.SPECIFIED, 0.93999999999999995, 47, 0.93999999999999995],
            [50, drive.SPECIFIED, 0.92000000000000004, 46, 0.92000000000000004],
            [50, drive.SPECIFIED, 0.90000000000000002, 45, 0.90000000000000002],
            [250, drive.SPECIFIED, 1, 250, 1],
            [250, drive.SPECIFIED, 0.97999999999999998, 245, 0.97999999999999998],
            [250, drive.SPECIFIED, 0.95999999999999996, 240, 0.95999999999999996],
            [250, drive.SPECIFIED, 0.93999999999999995, 235, 0.93999999999999995],
            [250, drive.SPECIFIED, 0.92000000000000004, 230, 0.92000000000000004],
            [250, drive.SPECIFIED, 0.90000000000000002, 225, 0.90000000000000002],
            [0, drive.DIRECT_DRIVE, 0.10000000000000001, 0, 1],
            [50, drive.DIRECT_DRIVE, 0.10000000000000001, 50, 1],
            [-50, drive.DIRECT_DRIVE, 0.10000000000000001, -50, 1],
            [50, drive.SPECIFIED, 0, 0, 0],
            [50, drive.SPECIFIED, -0.5, -25, -0.5],
            [50, drive.SPECIFIED, 1.5, 75, 1.5],
        ]);
    });

    it('preserves captured signed and nonfinite arithmetic', function () {
        const drive = moduleInstance.Drive;
        checkFixtures([
            [0, drive.DIRECT_DRIVE, 0.80000000000000004, 0, 1],
            [-0.0, drive.DIRECT_DRIVE, 0.80000000000000004, -0.0, 1],
            [Infinity, drive.DIRECT_DRIVE, 0.80000000000000004, Infinity, 1],
            [-Infinity, drive.DIRECT_DRIVE, 0.80000000000000004, -Infinity, 1],
            [NaN, drive.DIRECT_DRIVE, 0.80000000000000004, NaN, 1],
            [1.7976931348623157e+308, drive.DIRECT_DRIVE, 0.80000000000000004, 1.7976931348623157e+308, 1],
            [-1.7976931348623157e+308, drive.DIRECT_DRIVE, 0.80000000000000004, -1.7976931348623157e+308, 1],
            [4.9406564584124654e-324, drive.DIRECT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 1],
            [-4.9406564584124654e-324, drive.DIRECT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 1],
            [0, drive.V_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [-0.0, drive.V_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [Infinity, drive.V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [-Infinity, drive.V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [NaN, drive.V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [1.7976931348623157e+308, drive.V_BELT_DRIVE, 0.80000000000000004, 1.725851924113813e+308, 0.96003700000000003],
            [-1.7976931348623157e+308, drive.V_BELT_DRIVE, 0.80000000000000004, Infinity, -Infinity],
            [4.9406564584124654e-324, drive.V_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 1],
            [-4.9406564584124654e-324, drive.V_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 1],
            [0, drive.N_V_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [-0.0, drive.N_V_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [Infinity, drive.N_V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [-Infinity, drive.N_V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [NaN, drive.N_V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [1.7976931348623157e+308, drive.N_V_BELT_DRIVE, 0.80000000000000004, 1.7463779843276708e+308, 0.97145499999999996],
            [-1.7976931348623157e+308, drive.N_V_BELT_DRIVE, 0.80000000000000004, Infinity, -Infinity],
            [4.9406564584124654e-324, drive.N_V_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 1],
            [-4.9406564584124654e-324, drive.N_V_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 1],
            [0, drive.S_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [-0.0, drive.S_BELT_DRIVE, 0.80000000000000004, 0, NaN],
            [Infinity, drive.S_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [-Infinity, drive.S_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [NaN, drive.S_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [1.7976931348623157e+308, drive.S_BELT_DRIVE, 0.80000000000000004, 1.7771670746484577e+308, 0.98858199999999996],
            [-1.7976931348623157e+308, drive.S_BELT_DRIVE, 0.80000000000000004, Infinity, -Infinity],
            [4.9406564584124654e-324, drive.S_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 1],
            [-4.9406564584124654e-324, drive.S_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 1],
            [0, drive.SPECIFIED, 0.80000000000000004, 0, 0.80000000000000004],
            [-0.0, drive.SPECIFIED, 0.80000000000000004, -0.0, 0.80000000000000004],
            [Infinity, drive.SPECIFIED, 0.80000000000000004, Infinity, 0.80000000000000004],
            [-Infinity, drive.SPECIFIED, 0.80000000000000004, -Infinity, 0.80000000000000004],
            [NaN, drive.SPECIFIED, 0.80000000000000004, NaN, 0.80000000000000004],
            [1.7976931348623157e+308, drive.SPECIFIED, 0.80000000000000004, 1.4381545078898526e+308, 0.80000000000000004],
            [-1.7976931348623157e+308, drive.SPECIFIED, 0.80000000000000004, -1.4381545078898526e+308, 0.80000000000000004],
            [4.9406564584124654e-324, drive.SPECIFIED, 0.80000000000000004, 4.9406564584124654e-324, 0.80000000000000004],
            [-4.9406564584124654e-324, drive.SPECIFIED, 0.80000000000000004, -4.9406564584124654e-324, 0.80000000000000004],
            [50, drive.SPECIFIED, 0, 0, 0],
            [50, drive.SPECIFIED, -0.0, -0.0, -0.0],
            [50, drive.SPECIFIED, -0.5, -25, -0.5],
            [50, drive.SPECIFIED, 1.5, 75, 1.5],
            [50, drive.SPECIFIED, Infinity, Infinity, Infinity],
            [50, drive.SPECIFIED, -Infinity, -Infinity, -Infinity],
            [50, drive.SPECIFIED, NaN, NaN, NaN],
            [50, drive.SPECIFIED, 4.9406564584124654e-324, 2.4703282292062327e-322, 4.9406564584124654e-324],
        ]);
    });

    it('exposes plain objects, preserves inputs and has no legacy constructors', function () {
        assert.isFunction(moduleInstance.calculateMoverShaftPower);
        for (const name of ['MoverShaftPower', 'MoverShaftPowerOutput', 'MoverShaftPowerInput', 'MoverShaftPowerResult']) {
            assert.notProperty(moduleInstance, name);
        }
        const input: MoverShaftPowerInput = {
            motorShaftPower: 50, drive: moduleInstance.Drive.N_V_BELT_DRIVE, specifiedEfficiency: 0.9
        };
        const before = { ...input };
        const result: MoverShaftPowerResult = moduleInstance.calculateMoverShaftPower(input);
        assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
        assert.sameMembers(Object.keys(result), ['moverShaftPower', 'driveEfficiency']);
        assert.notProperty(input, 'delete');
        assert.notProperty(result, 'delete');
        moduleInstance.calculateMoverShaftPower({ ...input, drive: moduleInstance.Drive.SPECIFIED, specifiedEfficiency: 0.5 });
        assert.deepEqual(moduleInstance.calculateMoverShaftPower(input), result);
        assert.deepEqual(input, before);
        for (const drive of [moduleInstance.Drive.DIRECT_DRIVE, moduleInstance.Drive.V_BELT_DRIVE,
                moduleInstance.Drive.N_V_BELT_DRIVE, moduleInstance.Drive.S_BELT_DRIVE]) {
            const normal = moduleInstance.calculateMoverShaftPower({ ...input, drive });
            const ignored = moduleInstance.calculateMoverShaftPower({ ...input, drive, specifiedEfficiency: NaN });
            assert.deepEqual(ignored, normal);
        }
    });
});
