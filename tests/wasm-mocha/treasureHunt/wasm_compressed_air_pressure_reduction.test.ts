import { assert } from 'chai';
import createModule, {
    type CompressedAirPressureReductionInput,
    type CompressedAirPressureReductionInputV,
    type CompressedAirPressureReductionOutput,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Pressure Reduction Tests', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function executeTest(inputData: CompressedAirPressureReductionInput[], energyUseExpected: number, energyCostExpected: number) {
        const inputList: CompressedAirPressureReductionInputV = new moduleInstance.CompressedAirPressureReductionInputV();
        try {
            for (let i = 0; i < inputData.length; i++) {
                inputList.push_back(inputData[i]);
            }

            const results: CompressedAirPressureReductionOutput = moduleInstance.compressedAirPressureReduction(inputList);
            assert.approximately(results.energyUse, energyUseExpected, 0.01, "energyUse");
            assert.approximately(results.energyCost, energyCostExpected, 0.01, "energyCost");
        } finally {
            inputList.delete();
        }
    }

    it('should calculate 4 CompressedAirPressureReduction (baseline) correctly', function () {
        const inputData: CompressedAirPressureReductionInput[] = [
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 150,
                proposedPressure: 0,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 250,
                pressure: 150,
                proposedPressure: 0,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 120,
                proposedPressure: 120,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 450,
                pressure: 170,
                proposedPressure: 100,
                atmosphericPressure: 0,
                pressureRated: 0
            }
        ];
        executeTest(inputData, 14688000, 73440);
    });


    it('should calculate 1 CompressedAirPressureReduction (modification) correctly', function () {
        const inputData: CompressedAirPressureReductionInput[] = [
            {
                isBaseline: false,
                hoursPerYear: 8760,
                electricityCost: 0.005,
                compressorPower: 200,
                pressure: 100,
                proposedPressure: 90,
                atmosphericPressure: 14.7,
                pressureRated: 100
            }
        ];
        executeTest(inputData, 1650714.710542, 8253.57355271);
    });
});
