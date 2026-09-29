import { assert } from 'chai';
import createModule, {
    type DoubleVector,
    type DoubleVector2D,
    type Fan203Output,
    type Fan203Results,
    type MeasurToolsSuite,
    type TraversePlane
} from 'measur-tools-suite';

type TraversePlaneInput = {
    area: number;
    dryBulbTemp: number;
    barometricPressure: number;
    staticPressure: number;
    pitotTubeCoefficient: number;
    traverseData: number[][];
};

type ExpectedFan203Results = Pick<
    Fan203Results,
    'flow' | 'kpc' | 'power' | 'pressureStatic' | 'pressureTotal' | 'staticPressureRise'
>;

describe('Fan 203', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function createDoubleVector(values: number[]): DoubleVector {
        const doubleVector = new moduleInstance.DoubleVector();
        for (const value of values) {
            doubleVector.push_back(value);
        }
        return doubleVector;
    }

    function createDoubleVector2D(values: number[][]): DoubleVector2D {
        const doubleVector2D = new moduleInstance.DoubleVector2D();
        const rowVectors = values.map((row) => createDoubleVector(row));

        try {
            for (const rowVector of rowVectors) {
                doubleVector2D.push_back(rowVector);
            }
            return doubleVector2D;
        } finally {
            for (const rowVector of rowVectors) {
                rowVector.delete();
            }
        }
    }

    function createTraversePlane(input: TraversePlaneInput): TraversePlane {
        const traverseData = createDoubleVector2D(input.traverseData);

        try {
            return new moduleInstance.TraversePlane(
                input.area,
                input.dryBulbTemp,
                input.barometricPressure,
                input.staticPressure,
                input.pitotTubeCoefficient,
                traverseData
            );
        } finally {
            traverseData.delete();
        }
    }

    function validateFan203Results(
        results: Fan203Results,
        expected: ExpectedFan203Results,
        messagePrefix: string
    ): void {
        assert.approximately(results.flow, expected.flow, 0.0001, `${messagePrefix}Flow`);
        assert.approximately(results.kpc, expected.kpc, 0.0001, `${messagePrefix}KPC`);
        assert.approximately(results.power, expected.power, 0.0001, `${messagePrefix}Power`);
        assert.approximately(results.pressureStatic, expected.pressureStatic, 0.0001, `${messagePrefix}PressureStatic`);
        assert.approximately(results.pressureTotal, expected.pressureTotal, 0.0001, `${messagePrefix}PressureTotal`);
        assert.approximately(
            results.staticPressureRise,
            expected.staticPressureRise,
            0.0001,
            `${messagePrefix}StaticPressureRise`
        );
    }

    it('should calculate Fan 203 Results correctly', function () {
        const area = 143.63 * 32.63 / 144.0;
        const fanRatedInfoInstance = new moduleInstance.FanRatedInfo(1191, 1191, 1170, 0.05, 26.28);

        const flangePlaneInstance = new moduleInstance.FlangePlane(area * 2, 123, 26.57);
        const flangePlaneInstance2 = new moduleInstance.FlangePlane(70 * 78 / 144.0, 132.7, 26.57);
        const traversePlaneInstance = createTraversePlane({
            area,
            dryBulbTemp: 123,
            barometricPressure: 26.57,
            staticPressure: -18.1,
            pitotTubeCoefficient: 0.87292611371180784,
            traverseData: [
                [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
                [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
                [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
            ]
        });
        const additionalTraversePlane = createTraversePlane({
            area,
            dryBulbTemp: 123,
            barometricPressure: 26.57,
            staticPressure: -17.0,
            pitotTubeCoefficient: 0.87292611371180784,
            traverseData: [
                [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
            ]
        });
        const additionalTraversePlanes = new moduleInstance.TraversePlaneVector();
        additionalTraversePlanes.push_back(additionalTraversePlane);
        additionalTraversePlane.delete();

        const mstPlaneInstance = new moduleInstance.MstPlane(area * 2, 123, 26.57, -17.55);
        const mstPlaneInstance2 = new moduleInstance.MstPlane((55.42 * 60.49) / 144.0, 132.7, 26.57, 1.8);
        const planeDataInstance = new moduleInstance.PlaneData(
            flangePlaneInstance,
            flangePlaneInstance2,
            traversePlaneInstance,
            additionalTraversePlanes,
            mstPlaneInstance,
            mstPlaneInstance2,
            0,
            0.627,
            true
        );

        flangePlaneInstance.delete();
        flangePlaneInstance2.delete();
        traversePlaneInstance.delete();
        additionalTraversePlanes.delete();
        mstPlaneInstance.delete();
        mstPlaneInstance2.delete();

        const baseGasDensityInstance = new moduleInstance.BaseGasDensity(
            123,
            -17.6,
            26.57,
            0.0547,
            moduleInstance.GasType.AIR
        );
        const fanShaftPowerInstance = new moduleInstance.FanShaftPower(
            (4200 * 205 * 0.88 * Math.sqrt(3)) / 746.0,
            95,
            100,
            100,
            0
        );
        const fan203Instance = new moduleInstance.Fan203(
            fanRatedInfoInstance,
            planeDataInstance,
            baseGasDensityInstance,
            fanShaftPowerInstance
        );
        const fan203Output: Fan203Output = fan203Instance.calculate();
        const asTested = fan203Output.asTested;
        const converted = fan203Output.converted;

        fanShaftPowerInstance.delete();
        baseGasDensityInstance.delete();
        fan203Instance.delete();

        try {
            assert.approximately(
                fan203Output.fanEfficiencyTotalPressure,
                53.60738684355601,
                0.0001,
                "fanEfficiencyTotalPressure"
            );
            assert.approximately(
                fan203Output.fanEfficiencyStaticPressure,
                49.20691409764023,
                0.0001,
                "fanEfficiencyStaticPressure"
            );
            assert.approximately(
                fan203Output.fanEfficiencyStaticPressureRise,
                50.768875240824116,
                0.0001,
                "fanEfficiencyStaticPressureRise"
            );

            validateFan203Results(asTested, {
                flow: 250332.6394178045,
                kpc: 0.9982905074,
                power: 1671.2107816151,
                pressureStatic: 21.2207447999,
                pressureTotal: 23.1184721997,
                staticPressureRise: 21.8943488943
            }, "fanAsTested");
            validateFan203Results(converted, {
                flow: 245498.3175715673,
                kpc: 0.986542913,
                power: 1445.5400545013,
                pressureStatic: 18.6846696404,
                pressureTotal: 20.355601074,
                staticPressureRise: 19.277771819
            }, "fanConverted");
        } finally {
            converted.delete();
            asTested.delete();
            fan203Output.delete();
            planeDataInstance.delete();
            fanRatedInfoInstance.delete();
        }
    });
});
