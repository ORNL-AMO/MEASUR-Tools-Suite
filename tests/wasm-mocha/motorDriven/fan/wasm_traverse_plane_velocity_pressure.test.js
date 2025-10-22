import { assert } from 'chai';

describe('Traverse Plane Velocity Pressure', function () {
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

    it('should calculate Traverse plane pv3 and percent75Rule correctly (#1)', function () {
        let area = 143.63 * 32.63 / 144.0;
        let dryBulbTemp = 123;
        let barometricPressure = 26.57;
        let staticPressure = -18.1;
        let pitotTubeCoefficient = 0.87292611371180784;
        let traversePlaneTraverseData = new moduleInstance.DoubleVector2D();
        let traverseData = [
            [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
            [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
            [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
        ];

        let traverseDataVector = returnDoubleVector(traverseData[0]);
        let traverseDataVector2 = returnDoubleVector(traverseData[1]);
        let traverseDataVector3 = returnDoubleVector(traverseData[2]);

        traversePlaneTraverseData.push_back(traverseDataVector);
        traversePlaneTraverseData.push_back(traverseDataVector2);
        traversePlaneTraverseData.push_back(traverseDataVector3);

        let traversePlaneInstance = new moduleInstance.TraversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

        let pv3 = traversePlaneInstance.getPv3Value();
        let percent75Rule = traversePlaneInstance.get75percentRule() * 100; // Convert to percentage

        assert.approximately(pv3, 0.7508102988157324, .001, "pv3");
        assert.approximately(percent75Rule, 100, .001, "percent75Rule");
        traversePlaneInstance.delete();
        traverseDataVector.delete();
        traverseDataVector2.delete();
        traverseDataVector3.delete();
        traversePlaneTraverseData.delete();
    });

    it('should calculate Traverse plane pv3 and percent75Rule correctly (#2)', function () {
        let area = 143.63 * 32.63 / 144.0;
        let dryBulbTemp = 123;
        let barometricPressure = 26.57;
        let staticPressure = -17.0;
        let pitotTubeCoefficient = 0.87292611371180784;
        let traversePlaneTraverseData = new moduleInstance.DoubleVector2D();
        let traverseData = [
            [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
            [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
            [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
        ];

        let traverseDataVector = returnDoubleVector(traverseData[0]);
        let traverseDataVector2 = returnDoubleVector(traverseData[1]);
        let traverseDataVector3 = returnDoubleVector(traverseData[2]);

        traversePlaneTraverseData.push_back(traverseDataVector);
        traversePlaneTraverseData.push_back(traverseDataVector2);
        traversePlaneTraverseData.push_back(traverseDataVector3);

        let traversePlaneInstance = new moduleInstance.TraversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

        let pv3 = traversePlaneInstance.getPv3Value();
        let percent75Rule = traversePlaneInstance.get75percentRule() * 100; // Convert to percentage

        assert.approximately(pv3, 0.6007, .001, "pv3");
        assert.approximately(percent75Rule, 100, .001, "percent75Rule");

        traversePlaneInstance.delete();
        traverseDataVector.delete();
        traverseDataVector2.delete();
        traverseDataVector3.delete();
        traversePlaneTraverseData.delete();
    });
});