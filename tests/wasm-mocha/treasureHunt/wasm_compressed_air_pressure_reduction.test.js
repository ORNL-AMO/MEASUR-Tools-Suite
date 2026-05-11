import { assert } from 'chai';

describe('Compressed Air Pressure Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function executeTest(measurInputData, energyUseExpected, energyCostExpected) {
        let inputList = new moduleInstance.CompressedAirPressureReductionInputV();
        for (let i = 0; i < measurInputData.compressedAirPressureReductionInputVec.length; i++) {
            let inpElem = measurInputData.compressedAirPressureReductionInputVec[i];
            inputList.push_back(inpElem);
        }

        let results = moduleInstance.compressedAirPressureReduction(inputList);
        assert.approximately(results.energyUse, energyUseExpected, 0.01, "energyUse");
        assert.approximately(results.energyCost, energyCostExpected, 0.01, "energyCost");

        inputList.delete();
    }

    it('should calculate 4 CompressedAirPressureReduction (baseline) correctly', function () {
        let measurInputData = {
            compressedAirPressureReductionInputVec: [
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
            ]
        };
        executeTest(measurInputData, 14688000, 73440);
    });


    it('should calculate 1 CompressedAirPressureReduction (modification) correctly', function () {
        let measurInputData = {
            compressedAirPressureReductionInputVec: [
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
            ]
        };
        executeTest(measurInputData, 1650714.710542, 8253.57355271);
    });
});
