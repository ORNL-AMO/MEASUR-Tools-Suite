import { assert } from 'chai';
import createModule, {
    type DoubleVector,
    type DoubleVector2D,
    type MeasurToolsSuite,
    type PlaneDataNodeBindingData,
    type PlaneDataNodeBindingDataFlange,
    type PlaneDataNodeBindingDataVector,
    type PlaneDataNodeBindingOutput,
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

type ExpectedPlaneResults = Pick<
    PlaneDataNodeBindingData,
    'gasDensity' | 'gasVolumeFlowRate' | 'gasVelocity' | 'gasVelocityPressure' | 'gasTotalPressure'
> & {
    staticPressure?: number;
};

describe('Fan Plane Results', function () {
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

    function validateResults(
        results: PlaneDataNodeBindingData | PlaneDataNodeBindingDataFlange,
        expected: ExpectedPlaneResults,
        planeName: string
    ): void {
        assert.approximately(results.gasDensity, expected.gasDensity, 0.001, "gasDensity_" + planeName);
        assert.approximately(
            results.gasVolumeFlowRate,
            expected.gasVolumeFlowRate,
            0.001,
            "gasVolumeFlowRate_" + planeName
        );
        assert.approximately(results.gasVelocity, expected.gasVelocity, 0.001, "gasVelocity_" + planeName);
        assert.approximately(
            results.gasVelocityPressure,
            expected.gasVelocityPressure,
            0.001,
            "gasVelocityPressure_" + planeName
        );
        assert.approximately(results.gasTotalPressure, expected.gasTotalPressure, 0.001, "gasTotalPressure_" + planeName);

        if (expected.staticPressure !== undefined) {
            assert.approximately(
                (results as PlaneDataNodeBindingDataFlange).staticPressure,
                expected.staticPressure,
                0.001,
                "staticPressure_" + planeName
            );
        }
    }

    function validateAdditionalTraversePlanes(
        addlTravPlanes: PlaneDataNodeBindingDataVector,
        expectedResults: ExpectedPlaneResults[]
    ): void {
        assert.equal(addlTravPlanes.size(), expectedResults.length, "addlTravPlanes size");

        for (let i = 0; i < addlTravPlanes.size(); i++) {
            const addlTravPlane = addlTravPlanes.get(i);
            try {
                validateResults(addlTravPlane, expectedResults[i], "addlTravPlanes_" + (i + 1));
            } finally {
                addlTravPlane.delete();
            }
        }
    }

    it('should calculate Fan Plane Results correctly', function () {
        const area = 143.63 * 32.63 / 144.0;
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
        const traversePlaneInstance2 = createTraversePlane({
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
        const traversePlaneInstance3 = createTraversePlane({
            area,
            dryBulbTemp: 124,
            barometricPressure: 26.57,
            staticPressure: -16.5,
            pitotTubeCoefficient: 0.872,
            traverseData: [
                [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
            ]
        });
        const additionalTraversePlanes = new moduleInstance.TraversePlaneVector();
        additionalTraversePlanes.push_back(traversePlaneInstance2);
        additionalTraversePlanes.push_back(traversePlaneInstance3);
        traversePlaneInstance2.delete();
        traversePlaneInstance3.delete();

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
        const output: PlaneDataNodeBindingOutput = moduleInstance.PlaneDataNodeBindingCalculate(
            planeDataInstance,
            baseGasDensityInstance
        );
        const fanInletFlange = output.fanInletFlange;
        const fanOrEvaseOutletFlange = output.fanOrEvaseOutletFlange;
        const flowTraverse = output.flowTraverse;
        const inletMstPlane = output.inletMstPlane;
        const outletMstPlane = output.outletMstPlane;
        const addlTravPlanes = output.addlTravPlanes;

        baseGasDensityInstance.delete();

        try {
            validateResults(fanInletFlange, {
                gasDensity: 0.054707937910736096,
                gasVolumeFlowRate: 368484.70105160266,
                gasVelocity: 5660.955271820326,
                gasVelocityPressure: 1.4595154074095142,
                gasTotalPressure: -16.090484592590485,
                staticPressure: -17.55
            }, "fanInletFlange");
            validateResults(fanOrEvaseOutletFlange, {
                gasDensity: 0.05781581992717993,
                gasVolumeFlowRate: 348742.34384798247,
                gasVelocity: 9197.600277309428,
                gasVelocityPressure: 4.070924792774011,
                gasTotalPressure: 12.156298668206892,
                staticPressure: 8.085373875432882
            }, "fanOrEvaseOutletFlange");
            validateResults(flowTraverse, {
                gasDensity: 0.0546206208926391,
                gasVolumeFlowRate: 132250.42933608184,
                gasVelocity: 4063.47271956754,
                gasVelocityPressure: 0.75081,
                gasTotalPressure: -17.34919
            }, "flowTraverse");
            validateResults(inletMstPlane, {
                gasDensity: 0.054707937910736096,
                gasVolumeFlowRate: 368484.70105160266,
                gasVelocity: 5660.955271820326,
                gasVelocityPressure: 1.4595154074095142,
                gasTotalPressure: -16.090484592590485
            }, "inletMstPlane");
            validateResults(outletMstPlane, {
                gasDensity: 0.05683429586662124,
                gasVolumeFlowRate: 354698.4763125503,
                gasVelocity: 15236.026136905648,
                gasVelocityPressure: 10.983298668206892,
                gasTotalPressure: 12.783298668206893
            }, "outletMstPlane");
            validateAdditionalTraversePlanes(addlTravPlanes, [
                {
                    gasDensity: 0.054795254928833075,
                    gasVolumeFlowRate: 118104.78734062292,
                    gasVelocity: 3628.839496538495,
                    gasVelocityPressure: 0.6007,
                    gasTotalPressure: -16.3993
                },
                {
                    gasDensity: 0.054780670621748434,
                    gasVolumeFlowRate: 117995.19024728928,
                    gasVelocity: 3625.472060975973,
                    gasVelocityPressure: 0.599426,
                    gasTotalPressure: -15.900574
                }
            ]);
        } finally {
            addlTravPlanes.delete();
            outletMstPlane.delete();
            inletMstPlane.delete();
            flowTraverse.delete();
            fanOrEvaseOutletFlange.delete();
            fanInletFlange.delete();
            output.delete();
            planeDataInstance.delete();
        }
    });
});
