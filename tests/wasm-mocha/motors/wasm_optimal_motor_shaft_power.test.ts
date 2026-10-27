import { assert } from 'chai';
import createModule, {
    type Drive,
    type MeasurToolsSuite,
    type OptimalMotorShaftPowerInput,
    type OptimalMotorShaftPowerResult,
    type OptimalMotorShaftPowerModule,
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

describe('OptimalMotorShaftPower stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function checkFixtures(fixtures: Fixture[]): void {
        const calculator: OptimalMotorShaftPowerModule = moduleInstance;
        for (const [moverShaftPower, drive, specifiedEfficiency, power, efficiency] of fixtures) {
            const input: OptimalMotorShaftPowerInput = { moverShaftPower, drive, specifiedEfficiency };
            const result: OptimalMotorShaftPowerResult = calculator.calculateOptimalMotorShaftPower(input);
            checkNumber(result.motorShaftPower, power);
            checkNumber(result.driveEfficiency, efficiency);
        }
    }

    // Both fields captured from the unchanged -O3 legacy calculator at base 93427c3.
    it('preserves captured duties for all five drives', function () {
        const drive = moduleInstance.Drive;
        checkFixtures([
            [0.001, drive.DIRECT_DRIVE, 0.80000000000000004, 0.001, 1],
            [1, drive.DIRECT_DRIVE, 0.80000000000000004, 1, 1],
            [10, drive.DIRECT_DRIVE, 0.80000000000000004, 10, 1],
            [50, drive.DIRECT_DRIVE, 0.80000000000000004, 50, 1],
            [100, drive.DIRECT_DRIVE, 0.80000000000000004, 100, 1],
            [250, drive.DIRECT_DRIVE, 0.80000000000000004, 250, 1],
            [600, drive.DIRECT_DRIVE, 0.80000000000000004, 600, 1],
            [-50, drive.DIRECT_DRIVE, 0.80000000000000004, -50, 1],
            [0.001, drive.V_BELT_DRIVE, 0.80000000000000004, 0.0010904708209481637, 0.91703508318590365],
            [1, drive.V_BELT_DRIVE, 0.80000000000000004, 1.0819590817354099, 0.92424937031449328],
            [10, drive.V_BELT_DRIVE, 0.80000000000000004, 10.520327017292107, 0.95054079436534111],
            [50, drive.V_BELT_DRIVE, 0.80000000000000004, 52.214537061836324, 0.95758772965441197],
            [100, drive.V_BELT_DRIVE, 0.80000000000000004, 104.25740426439738, 0.95916449009606475],
            [250, drive.V_BELT_DRIVE, 0.80000000000000004, 260.41741132953581, 0.95999725488264875],
            [600, drive.V_BELT_DRIVE, 0.80000000000000004, 624.97626036074303, 0.9600364654709822],
            [-50, drive.V_BELT_DRIVE, 0.80000000000000004, -167416.22527577286, 0.00029865683518809811],
            [0.001, drive.N_V_BELT_DRIVE, 0.80000000000000004, 0.0010646220149629741, 0.93930050848589541],
            [1, drive.N_V_BELT_DRIVE, 0.80000000000000004, 1.0585422012395784, 0.94469544891925505],
            [10, drive.N_V_BELT_DRIVE, 0.80000000000000004, 10.371662155208648, 0.96416561302838033],
            [50, drive.N_V_BELT_DRIVE, 0.80000000000000004, 51.581812187025946, 0.96933391596846985],
            [100, drive.N_V_BELT_DRIVE, 0.80000000000000004, 103.04100304599812, 0.97048744717051516],
            [250, drive.N_V_BELT_DRIVE, 0.80000000000000004, 257.44100809252558, 0.97109625949782163],
            [600, drive.N_V_BELT_DRIVE, 0.80000000000000004, 617.84018597195927, 0.97112491809853074],
            [-50, drive.N_V_BELT_DRIVE, 0.80000000000000004, -119597.30376840918, 0.00041806962552283858],
            [0.001, drive.S_BELT_DRIVE, 0.80000000000000004, 0.0010258488059851896, 0.97480251881721958],
            [1, drive.S_BELT_DRIVE, 0.80000000000000004, 1.0234168804958315, 0.97711892295103997],
            [10, drive.S_BELT_DRIVE, 0.80000000000000004, 10.148664862083459, 0.98535128865680777],
            [50, drive.S_BELT_DRIVE, 0.80000000000000004, 50.632724874810378, 0.98750363768936411],
            [100, drive.S_BELT_DRIVE, 0.80000000000000004, 101.21640121839926, 0.98798217281234324],
            [250, drive.S_BELT_DRIVE, 0.80000000000000004, 252.97640323701023, 0.98823446298182327],
            [600, drive.S_BELT_DRIVE, 0.80000000000000004, 607.13607438878375, 0.98824633440540033],
            [-50, drive.S_BELT_DRIVE, 0.80000000000000004, -47868.921507363673, 0.0010445190412804372],
            [0.001, drive.SPECIFIED, 0.80000000000000004, 0.00125, 0.80000000000000004],
            [1, drive.SPECIFIED, 0.80000000000000004, 1.25, 0.80000000000000004],
            [10, drive.SPECIFIED, 0.80000000000000004, 12.5, 0.80000000000000004],
            [50, drive.SPECIFIED, 0.80000000000000004, 62.5, 0.80000000000000004],
            [100, drive.SPECIFIED, 0.80000000000000004, 125, 0.80000000000000004],
            [250, drive.SPECIFIED, 0.80000000000000004, 312.5, 0.80000000000000004],
            [600, drive.SPECIFIED, 0.80000000000000004, 750, 0.80000000000000004],
            [-50, drive.SPECIFIED, 0.80000000000000004, -62.5, 0.80000000000000004],
        ]);
    });

    it('preserves captured arithmetic boundaries', function () {
        const drive = moduleInstance.Drive;
        checkFixtures([
            [0, drive.DIRECT_DRIVE, 0.80000000000000004, 0, 1],
            [-0, drive.DIRECT_DRIVE, 0.80000000000000004, -0, 1],
            [4.9406564584124654e-324, drive.DIRECT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 1],
            [-4.9406564584124654e-324, drive.DIRECT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 1],
            [1.7976931348623157e+308, drive.DIRECT_DRIVE, 0.80000000000000004, 1.7976931348623157e+308, 1],
            [-1.7976931348623157e+308, drive.DIRECT_DRIVE, 0.80000000000000004, -1.7976931348623157e+308, 1],
            [Infinity, drive.DIRECT_DRIVE, 0.80000000000000004, Infinity, 1],
            [-Infinity, drive.DIRECT_DRIVE, 0.80000000000000004, -Infinity, 1],
            [NaN, drive.DIRECT_DRIVE, 0.80000000000000004, NaN, 1],
            [0, drive.V_BELT_DRIVE, 0.80000000000000004, 0, 0.91702709163232909],
            [-0, drive.V_BELT_DRIVE, 0.80000000000000004, -0, 0.91702709163232909],
            [4.9406564584124654e-324, drive.V_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 0.91702709163232909],
            [-4.9406564584124654e-324, drive.V_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 0.91702709163232909],
            [1.7976931348623157e+308, drive.V_BELT_DRIVE, 0.80000000000000004, Infinity, 0.9600364936752267],
            [-1.7976931348623157e+308, drive.V_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [Infinity, drive.V_BELT_DRIVE, 0.80000000000000004, Infinity, 0.9600364936752267],
            [-Infinity, drive.V_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [NaN, drive.V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [0, drive.N_V_BELT_DRIVE, 0.80000000000000004, 0, 0.93929451966385025],
            [-0, drive.N_V_BELT_DRIVE, 0.80000000000000004, -0, 0.93929451966385025],
            [4.9406564584124654e-324, drive.N_V_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 0.93929451966385025],
            [-4.9406564584124654e-324, drive.N_V_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 0.93929451966385025],
            [1.7976931348623157e+308, drive.N_V_BELT_DRIVE, 0.80000000000000004, Infinity, 0.97112493871247851],
            [-1.7976931348623157e+308, drive.N_V_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [Infinity, drive.N_V_BELT_DRIVE, 0.80000000000000004, Infinity, 0.97112493871247851],
            [-Infinity, drive.N_V_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [NaN, drive.N_V_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [0, drive.S_BELT_DRIVE, 0.80000000000000004, 0, 0.97479993877276017],
            [-0, drive.S_BELT_DRIVE, 0.80000000000000004, -0, 0.97479993877276017],
            [4.9406564584124654e-324, drive.S_BELT_DRIVE, 0.80000000000000004, 4.9406564584124654e-324, 0.97479993877276017],
            [-4.9406564584124654e-324, drive.S_BELT_DRIVE, 0.80000000000000004, -4.9406564584124654e-324, 0.97479993877276017],
            [1.7976931348623157e+308, drive.S_BELT_DRIVE, 0.80000000000000004, Infinity, 0.9882463429442897],
            [-1.7976931348623157e+308, drive.S_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [Infinity, drive.S_BELT_DRIVE, 0.80000000000000004, Infinity, 0.9882463429442897],
            [-Infinity, drive.S_BELT_DRIVE, 0.80000000000000004, -Infinity, 0],
            [NaN, drive.S_BELT_DRIVE, 0.80000000000000004, NaN, NaN],
            [0, drive.SPECIFIED, 0.80000000000000004, 0, 0.80000000000000004],
            [-0, drive.SPECIFIED, 0.80000000000000004, -0, 0.80000000000000004],
            [4.9406564584124654e-324, drive.SPECIFIED, 0.80000000000000004, 4.9406564584124654e-324, 0.80000000000000004],
            [-4.9406564584124654e-324, drive.SPECIFIED, 0.80000000000000004, -4.9406564584124654e-324, 0.80000000000000004],
            [1.7976931348623157e+308, drive.SPECIFIED, 0.80000000000000004, Infinity, 0.80000000000000004],
            [-1.7976931348623157e+308, drive.SPECIFIED, 0.80000000000000004, -Infinity, 0.80000000000000004],
            [Infinity, drive.SPECIFIED, 0.80000000000000004, Infinity, 0.80000000000000004],
            [-Infinity, drive.SPECIFIED, 0.80000000000000004, -Infinity, 0.80000000000000004],
            [NaN, drive.SPECIFIED, 0.80000000000000004, NaN, 0.80000000000000004],
            [50, drive.SPECIFIED, 0, Infinity, 0],
            [0, drive.SPECIFIED, 0, NaN, 0],
            [-0, drive.SPECIFIED, 0, NaN, 0],
            [-50, drive.SPECIFIED, 0, -Infinity, 0],
            [50, drive.SPECIFIED, -0, -Infinity, -0],
            [0, drive.SPECIFIED, -0, NaN, -0],
            [-0, drive.SPECIFIED, -0, NaN, -0],
            [-50, drive.SPECIFIED, -0, Infinity, -0],
            [50, drive.SPECIFIED, -0.5, -100, -0.5],
            [0, drive.SPECIFIED, -0.5, -0, -0.5],
            [-0, drive.SPECIFIED, -0.5, 0, -0.5],
            [-50, drive.SPECIFIED, -0.5, 100, -0.5],
            [50, drive.SPECIFIED, 1, 50, 1],
            [0, drive.SPECIFIED, 1, 0, 1],
            [-0, drive.SPECIFIED, 1, -0, 1],
            [-50, drive.SPECIFIED, 1, -50, 1],
            [50, drive.SPECIFIED, 1.5, 33.333333333333336, 1.5],
            [0, drive.SPECIFIED, 1.5, 0, 1.5],
            [-0, drive.SPECIFIED, 1.5, -0, 1.5],
            [-50, drive.SPECIFIED, 1.5, -33.333333333333336, 1.5],
            [50, drive.SPECIFIED, Infinity, 0, Infinity],
            [0, drive.SPECIFIED, Infinity, 0, Infinity],
            [-0, drive.SPECIFIED, Infinity, -0, Infinity],
            [-50, drive.SPECIFIED, Infinity, -0, Infinity],
            [50, drive.SPECIFIED, -Infinity, -0, -Infinity],
            [0, drive.SPECIFIED, -Infinity, -0, -Infinity],
            [-0, drive.SPECIFIED, -Infinity, 0, -Infinity],
            [-50, drive.SPECIFIED, -Infinity, 0, -Infinity],
            [50, drive.SPECIFIED, NaN, NaN, NaN],
            [0, drive.SPECIFIED, NaN, NaN, NaN],
            [-0, drive.SPECIFIED, NaN, NaN, NaN],
            [-50, drive.SPECIFIED, NaN, NaN, NaN],
            [50, drive.SPECIFIED, 4.9406564584124654e-324, Infinity, 4.9406564584124654e-324],
            [0, drive.SPECIFIED, 4.9406564584124654e-324, 0, 4.9406564584124654e-324],
            [-0, drive.SPECIFIED, 4.9406564584124654e-324, -0, 4.9406564584124654e-324],
            [-50, drive.SPECIFIED, 4.9406564584124654e-324, -Infinity, 4.9406564584124654e-324],
        ]);
    });

    it('exposes plain objects, preserves inputs and keeps interfaces type-only', function () {
        assert.isFunction(moduleInstance.calculateOptimalMotorShaftPower);
        for (const name of ['OptimalMotorShaftPowerInput', 'OptimalMotorShaftPowerResult']) {
            assert.notProperty(moduleInstance, name);
        }
        const input: OptimalMotorShaftPowerInput = {
            moverShaftPower: 50, drive: moduleInstance.Drive.N_V_BELT_DRIVE, specifiedEfficiency: 0.9
        };
        const before = { ...input };
        const result: OptimalMotorShaftPowerResult = moduleInstance.calculateOptimalMotorShaftPower(input);
        assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
        assert.sameMembers(Object.keys(result), ['motorShaftPower', 'driveEfficiency']);
        assert.notProperty(input, 'delete');
        assert.notProperty(result, 'delete');
        moduleInstance.calculateOptimalMotorShaftPower({ ...input, drive: moduleInstance.Drive.SPECIFIED, specifiedEfficiency: 0.5 });
        assert.deepEqual(moduleInstance.calculateOptimalMotorShaftPower(input), result);
        assert.deepEqual(input, before);
        for (const drive of [moduleInstance.Drive.DIRECT_DRIVE, moduleInstance.Drive.V_BELT_DRIVE,
                moduleInstance.Drive.N_V_BELT_DRIVE, moduleInstance.Drive.S_BELT_DRIVE]) {
            const normal = moduleInstance.calculateOptimalMotorShaftPower({ ...input, drive });
            const ignored = moduleInstance.calculateOptimalMotorShaftPower({ ...input, drive, specifiedEfficiency: NaN });
            assert.deepEqual(ignored, normal);
        }
    });
});
