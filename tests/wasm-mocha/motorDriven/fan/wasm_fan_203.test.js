import { assert } from 'chai';

describe('Fan 203', function () {
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

    it('should calculate Fan 203 Results correctly', function () {
        let area = 143.63 * 32.63 / 144.0;

        //FanRatedInfo
        let fanSpeed = 1191;
        let motorSpeed = 1191;
        let fanSpeedCorrected = 1170;
        let densityCorrected = 0.05;
        let pressureBarometricCorrected = 26.28;

        //getFanRatedInfo()
        let fanRatedInfoInstance = new moduleInstance.FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);

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

        let AddlTraversePlanes = new moduleInstance.TraversePlaneVector();
        AddlTraversePlanes.push_back(traversePlaneInstance2);
        traversePlaneInstance2.delete();

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


        //getPlaneData()
        let planeDataInstance = new moduleInstance.PlaneData(flangePlaneInstance, flangePlaneInstance2, traversePlaneInstance, AddlTraversePlanes, mstPlaneInstance, mstPlaneInstance2, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);

        // Release memory
        flangePlaneInstance.delete();
        flangePlaneInstance2.delete();
        AddlTraversePlanes.delete()
        mstPlaneInstance.delete()
        mstPlaneInstance2.delete();

        //BaseGasDensity
        let bgdDryBulbTemp = 123;
        let bgdStaticPressure = -17.6;
        let bgdBarometricPressure = 26.57;
        let bgdGasDensity = 0.0547;
        let gasType = moduleInstance.GasType.AIR;

        //getBaseGasDensity()
        let baseGasDensityInstance = new moduleInstance.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

        //FanShaftPower
        //const double motorShaftPower, const double efficiencyMotor, const double efficiencyVFD,
        //const double efficiencyBelt, const double sumSEF
        let fspMotorShaftPower = (4200 * 205 * 0.88 * Math.sqrt(3)) / 746.0;
        let fspEfficiencyMotor = 95;
        let fspEfficiencyVFD = 100;
        let fspEfficiencyBelt = 100;
        let fspSumSEF = 0;

        //getFanShaftPower()
        let fanShaftPowerInstance = new moduleInstance.FanShaftPower(fspMotorShaftPower, fspEfficiencyMotor, fspEfficiencyVFD, fspEfficiencyBelt, fspSumSEF);

        //Calculation procedure
        let fan203Instance = new moduleInstance.Fan203(fanRatedInfoInstance, planeDataInstance, baseGasDensityInstance, fanShaftPowerInstance);
        let fan203Output = fan203Instance.calculate();

        //release memory
        fanShaftPowerInstance.delete();
        baseGasDensityInstance.delete();
        fan203Instance.delete();

        //Tests
        assert.approximately(fan203Output.fanEfficiencyTotalPressure, 53.60738684355601, 0.0001, "fanEfficiencyTotalPressure");
        assert.approximately(fan203Output.fanEfficiencyStaticPressure, 49.20691409764023, 0.0001, "fanEfficiencyStaticPressure");
        assert.approximately(fan203Output.fanEfficiencyStaticPressureRise, 50.768875240824116, 0.0001, "fanEfficiencyStaticPressureRise");

        assert.approximately(fan203Output.asTested.flow, 250332.6394178045, 0.0001, "fanAsTestedFlow");
        assert.approximately(fan203Output.asTested.kpc, 0.9982905074, 0.0001, "fanAsTestedKPC");
        assert.approximately(fan203Output.asTested.power, 1671.2107816151, 0.0001, "fanAsTestedPower");
        assert.approximately(fan203Output.asTested.pressureStatic, 21.2207447999, 0.0001, "fanAsTestedPressureStatic");
        assert.approximately(fan203Output.asTested.pressureTotal, 23.1184721997, 0.0001, "fanAsTestedPressureTotal");
        assert.approximately(fan203Output.asTested.staticPressureRise, 21.8943488943, 0.0001, "fanAsTestedStaticPressureRise");

        assert.approximately(fan203Output.converted.flow, 245498.3175715673, 0.0001, "fanConvertedFlow");
        assert.approximately(fan203Output.converted.kpc, 0.986542913, 0.0001, "fanConvertedKPC");
        assert.approximately(fan203Output.converted.power, 1445.5400545013, 0.0001, "fanConvertedPower");
        assert.approximately(fan203Output.converted.pressureStatic, 18.6846696404, 0.0001, "fanConvertedPressureStatic");
        assert.approximately(fan203Output.converted.pressureTotal, 20.355601074, 0.0001, "fanConvertedPressureTotal");
        assert.approximately(fan203Output.converted.staticPressureRise, 19.277771819, 0.0001, "fanConvertedStaticPressureRise");

        // Release memory
        fanRatedInfoInstance.delete();
    });

});