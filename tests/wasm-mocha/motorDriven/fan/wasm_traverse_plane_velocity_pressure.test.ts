import { assert } from 'chai';
import createModule, {
    type DoubleVector,
    type DoubleVector2D,
    type MeasurToolsSuite
} from 'measur-tools-suite';

type TraverseData = {
    vector: DoubleVector2D;
    rows: DoubleVector[];
};

describe('Traverse Plane Velocity Pressure', function () {
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

    function createDoubleVector2D(values: number[][]): TraverseData {
        const vector = new moduleInstance.DoubleVector2D();
        const rows = values.map((row) => createDoubleVector(row));

        for (const row of rows) {
            vector.push_back(row);
        }

        return { vector, rows };
    }

    function deleteTraverseData(traverseData: TraverseData): void {
        for (const row of traverseData.rows) {
            row.delete();
        }
        traverseData.vector.delete();
    }

    it('should calculate Traverse plane pv3 and percent75Rule correctly (#1)', function () {
        const area = 143.63 * 32.63 / 144.0;
        const dryBulbTemp = 123;
        const barometricPressure = 26.57;
        const staticPressure = -18.1;
        const pitotTubeCoefficient = 0.87292611371180784;
        const traverseData = createDoubleVector2D([
            [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
            [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
            [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
        ]);

        const traversePlaneInstance = new moduleInstance.TraversePlane(
            area,
            dryBulbTemp,
            barometricPressure,
            staticPressure,
            pitotTubeCoefficient,
            traverseData.vector
        );

        try {
            assert.approximately(traversePlaneInstance.getPv3Value(), 0.7508102988157324, 0.001, "pv3");
            assert.approximately(traversePlaneInstance.get75percentRule() * 100, 100, 0.001, "percent75Rule");
        } finally {
            traversePlaneInstance.delete();
            deleteTraverseData(traverseData);
        }
    });

    it('should calculate Traverse plane pv3 and percent75Rule correctly (#2)', function () {
        const area = 143.63 * 32.63 / 144.0;
        const dryBulbTemp = 123;
        const barometricPressure = 26.57;
        const staticPressure = -17.0;
        const pitotTubeCoefficient = 0.87292611371180784;
        const traverseData = createDoubleVector2D([
            [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
            [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
            [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
        ]);

        const traversePlaneInstance = new moduleInstance.TraversePlane(
            area,
            dryBulbTemp,
            barometricPressure,
            staticPressure,
            pitotTubeCoefficient,
            traverseData.vector
        );

        try {
            assert.approximately(traversePlaneInstance.getPv3Value(), 0.6007, 0.001, "pv3");
            assert.approximately(traversePlaneInstance.get75percentRule() * 100, 100, 0.001, "percent75Rule");
        } finally {
            traversePlaneInstance.delete();
            deleteTraverseData(traverseData);
        }
    });
});
