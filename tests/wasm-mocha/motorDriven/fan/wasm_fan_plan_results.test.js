import { assert } from 'chai';

describe('Fan Plane Results', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function returnDoubleVector(doublesArray) {
        let doubleVector = new moduleInstance.DoubleVector();

        for (let x of doublesArray) {
            doubleVector.push_back(x);
        }

        return doubleVector;
    }

    function validateResults(results, expected, isStaticPressure, planeName) {
        assert.approximately(results.gasDensity, expected.gasDensity, 0.001, "gasDensity_" + planeName);
        assert.approximately(results.gasVolumeFlowRate, expected.gasVolumeFlowRate, 0.001, "gasVolumeFlowRate_" + planeName);
        assert.approximately(results.gasVelocity, expected.gasVelocity, 0.001, "gasVelocity_" + planeName);
        assert.approximately(results.gasVelocityPressure, expected.gasVelocityPressure, 0.001, "gasVelocityPressure_" + planeName);
        assert.approximately(results.gasTotalPressure, expected.gasTotalPressure, 0.001, "gasTotalPressure_" + planeName);
        if (isStaticPressure) {
            assert.approximately(results.staticPressure, expected.staticPressure, 0.001, "staticPressure_" + planeName);
        }
    }


    it('should calculate Fan Plane Results correctly', function () {
        let area = 143.63 * 32.63 / 144.0;

        //getPlaneData()

        //PlaneData
        let plane5upstreamOfPlane2 = true;
        let totalPressureLossBtwnPlanes1and4 = 0;
        let totalPressureLossBtwnPlanes2and5 = 0.627;

        //let planeDataInstance = new Module.PlaneData(FlangePlane, FlangePlane, TraversePlane, std::vector<TraversePlane>, MstPlane, MstPlane, double, double, bool)

        //FlangePlane
        //FanInletFlange
        let flangePlaneArea = area * 2;
        let flangePlaneLength = 32.63;
        let dryBulbTemp = 123;
        let barometricPressure = 26.57;
        let flangePlaneInstance = new moduleInstance.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);
        //FanEvaseOrOutletFlange
        flangePlaneArea = 70 * 78 / 144.0;
        dryBulbTemp = 132.7;
        barometricPressure = 26.57;
        let flangePlaneInstance2 = new moduleInstance.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);


        //TraversePlane
        //FlowTraverse
        let traverseArea = area;
        let traverseDryBulbTemp = 123;
        let traverseBarometricPressure = 26.57;
        let traverseStaticPressure = -18.1;
        let pitotTubeCoefficient = 0.87292611371180784;
        let traversePlaneTraverseData = new moduleInstance.DoubleVector2D();

        let traversePlaneTraverseDoubles = [
            [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
            [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
            [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
        ];

        let traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
        let traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
        let traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

        traversePlaneTraverseData.push_back(traverseDataVector);
        traversePlaneTraverseData.push_back(traverseDataVector2);
        traversePlaneTraverseData.push_back(traverseDataVector3);

        // area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData
        let traversePlaneInstance = new moduleInstance.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

        // Release memory
        traverseDataVector.delete();
        traverseDataVector2.delete();
        traverseDataVector3.delete();
        traversePlaneTraverseData.delete();

        //AddlTraversePlanes
        //traverse_plane_vector
        traverseArea = area;
        traverseDryBulbTemp = 123;
        traverseBarometricPressure = 26.57;
        traverseStaticPressure = -17.0;
        pitotTubeCoefficient = 0.87292611371180784;
        traversePlaneTraverseData = new moduleInstance.DoubleVector2D();

        traversePlaneTraverseDoubles = [
            [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
            [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
            [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
        ];

        traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
        traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
        traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

        traversePlaneTraverseData.push_back(traverseDataVector);
        traversePlaneTraverseData.push_back(traverseDataVector2);
        traversePlaneTraverseData.push_back(traverseDataVector3);

        let traversePlaneInstance2 = new moduleInstance.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

        // Release memory
        traverseDataVector.delete();
        traverseDataVector2.delete();
        traverseDataVector3.delete();
        traversePlaneTraverseData.delete();

        traverseArea = area;
        traverseDryBulbTemp = 124;
        traverseBarometricPressure = 26.57;
        traverseStaticPressure = -16.5;
        pitotTubeCoefficient = 0.872;
        traversePlaneTraverseData = new moduleInstance.DoubleVector2D();

        traversePlaneTraverseDoubles = [
            [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
            [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
            [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
        ];

        traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
        traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
        traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

        traversePlaneTraverseData.push_back(traverseDataVector);
        traversePlaneTraverseData.push_back(traverseDataVector2);
        traversePlaneTraverseData.push_back(traverseDataVector3);

        let traversePlaneInstance3 = new moduleInstance.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

        // Release memory
        traverseDataVector.delete();
        traverseDataVector2.delete();
        traverseDataVector3.delete();
        traversePlaneTraverseData.delete();

        let AddlTraversePlanes = new moduleInstance.TraversePlaneVector();
        AddlTraversePlanes.push_back(traversePlaneInstance2);
        AddlTraversePlanes.push_back(traversePlaneInstance3);

        traversePlaneInstance2.delete();
        traversePlaneInstance3.delete();

        //MstPlane
        //InletMstPlane
        let mstArea = area * 2;
        let mstDryBulbTemp = 123;
        let mstBarometricPressure = 26.57;
        let mstStaticPressure = -17.55;

        let mstPlaneInstance = new moduleInstance.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);

        //OutletMstPlane
        mstArea = (55.42 * 60.49) / 144.0;
        mstDryBulbTemp = 132.7;
        mstBarometricPressure = 26.57;
        mstStaticPressure = 1.8;

        let mstPlaneInstance2 = new moduleInstance.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);


        //Plane Data
        let planeDataInstance = new moduleInstance.PlaneData(flangePlaneInstance, flangePlaneInstance2, traversePlaneInstance, AddlTraversePlanes, mstPlaneInstance, mstPlaneInstance2, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);

        flangePlaneInstance.delete();
        flangePlaneInstance2.delete();
        traversePlaneInstance.delete()
        AddlTraversePlanes.delete();
        mstPlaneInstance.delete();
        mstPlaneInstance2.delete();

        //BaseGasDensity
        let bgdDryBulbTemp = 123;
        let bgdStaticPressure = -17.6;
        let bgdBarometricPressure = 26.57;
        let bgdGasDensity = 0.0547;
        let gasType = moduleInstance.GasType.AIR;

        let baseGasDensityInstance = new moduleInstance.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

        let output = moduleInstance.PlaneDataNodeBindingCalculate(planeDataInstance, baseGasDensityInstance);

        baseGasDensityInstance.delete();



        validateResults(output.fanInletFlange, {
            "gasDensity": 0.054707937910736096,
            "gasVolumeFlowRate": 368484.70105160266,
            "gasVelocity": 5660.955271820326,
            "gasVelocityPressure": 1.4595154074095142,
            "gasTotalPressure": -16.090484592590485,
            "staticPressure": -17.55
        }, true, "fanInletFlange");
        validateResults(output.fanOrEvaseOutletFlange, {
            "gasDensity": 0.05781581992717993,
            "gasVolumeFlowRate": 348742.34384798247,
            "gasVelocity": 9197.600277309428,
            "gasVelocityPressure": 4.070924792774011,
            "gasTotalPressure": 12.156298668206892,
            "staticPressure": 8.085373875432882
        }, true, "fanOrEvaseOutletFlange");
        validateResults(output.flowTraverse, {
            "gasDensity": 0.0546206208926391,
            "gasVolumeFlowRate": 132250.42933608184,
            "gasVelocity": 4063.47271956754,
            "gasVelocityPressure": .75081,
            "gasTotalPressure": -17.34919
        }, false, "flowTraverse");
        validateResults(output.inletMstPlane, {
            "gasDensity": 0.054707937910736096,
            "gasVolumeFlowRate": 368484.70105160266,
            "gasVelocity": 5660.955271820326,
            "gasVelocityPressure": 1.4595154074095142,
            "gasTotalPressure": -16.090484592590485
        }, false, "inletMstPlane");
        validateResults(output.outletMstPlane, {
            "gasDensity": 0.05683429586662124,
            "gasVolumeFlowRate": 354698.4763125503,
            "gasVelocity": 15236.026136905648,
            "gasVelocityPressure": 10.983298668206892,
            "gasTotalPressure": 12.783298668206893
        }, false, "outletMstPlane");

        let trav = [
            {
                "gasDensity": 0.054795254928833075,
                "gasVolumeFlowRate": 118104.78734062292,
                "gasVelocity": 3628.839496538495,
                "gasVelocityPressure": 0.6007,
                "gasTotalPressure": -16.3993
            },
            {
                "gasDensity": 0.054780670621748434,
                "gasVolumeFlowRate": 117995.19024728928,
                "gasVelocity": 3625.472060975973,
                "gasVelocityPressure": 0.599426,
                "gasTotalPressure": -15.900574
            }
        ];

        //let addlTravPlanesVector = new Module.PlaneDataNodeBindingDataVector(output.addlTravPlanes);

        for (let i = 0; i < output.addlTravPlanes.length; i++) { // error: length = 0, was .size
            validateResults(output.addlTravPlanes[i], trav[i], false, "addlTravPlanes_" + (i+1));
        }
    });
});