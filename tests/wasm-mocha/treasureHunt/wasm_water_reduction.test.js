import { assert } from 'chai';

describe('Water Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function executeTest(measurInputData, waterUseExpected, waterCostExpected, annualWaterSavingsExpected, costSavingsExpected) {

        let inputList = new moduleInstance.WaterReductionInputV();
        for (let i = 0; i < measurInputData.waterReductionInputVec.length; i++) {
            let inpElem = measurInputData.waterReductionInputVec[i];
            let meteredFlowMethodData = new moduleInstance.MeteredFlowMethodData(inpElem.meteredFlowMethodData.meterReading);
            let volumeMeterMethodData = new moduleInstance.VolumeMeterMethodData(inpElem.volumeMeterMethodData.initialMeterReading,
                inpElem.volumeMeterMethodData.finalMeterReading, inpElem.volumeMeterMethodData.elapsedTime);
            let bucketMethodData = new moduleInstance.BucketMethodData(inpElem.bucketMethodData.bucketVolume, inpElem.bucketMethodData.bucketFillTime);
            let otherMethodData = new moduleInstance.WaterOtherMethodData(inpElem.otherMethodData.consumption);

            let input = new moduleInstance.WaterReductionInput(inpElem.hoursPerYear, inpElem.waterCost, inpElem.measurementMethod,
                meteredFlowMethodData, volumeMeterMethodData, bucketMethodData, otherMethodData);
            inputList.push_back(input);

            input.delete();
            otherMethodData.delete();
            bucketMethodData.delete();
            volumeMeterMethodData.delete();
            meteredFlowMethodData.delete();
        }

        let instance = new moduleInstance.WaterReduction(inputList);
        let results = instance.calculate();
        assert.approximately(results.waterUse, waterUseExpected, .001, "waterUse");
        assert.approximately(results.waterCost, waterCostExpected, .001, "waterCost");
        assert.approximately(results.annualWaterSavings, annualWaterSavingsExpected, .001, "annualWaterSavings");
        assert.approximately(results.costSavings, costSavingsExpected, .001, "costSavings");
        instance.delete();
        inputList.delete();
    }

    it('should calculate 1 WaterReduction correctly', function () {
        let measurInputData = {
            waterReductionInputVec: [
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: 0,
                    volumeMeterMethodData: {
                        initialMeterReading: 4235,
                        finalMeterReading: 5942,
                        elapsedTime: 15
                    },
                    meteredFlowMethodData: {
                        meterReading: 100
                    },
                    bucketMethodData: {
                        bucketVolume: 10,
                        bucketFillTime: 20
                    },
                    otherMethodData: {
                        consumption: 15000
                    }
                }
            ]
        };

        executeTest(measurInputData, 51840000, 259200, 0, 0);
    });

    it('should calculate 4 WaterReductions (all methods) correctly', function () {
        let measurInputData = {
            waterReductionInputVec: [
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: 0,
                    volumeMeterMethodData: {
                        initialMeterReading: 4235,
                        finalMeterReading: 5942,
                        elapsedTime: 15
                    },
                    meteredFlowMethodData: {
                        meterReading: 100
                    },
                    bucketMethodData: {
                        bucketVolume: 10,
                        bucketFillTime: 20
                    },
                    otherMethodData: {
                        consumption: 15000
                    }
                },
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: 1,
                    volumeMeterMethodData: {
                        initialMeterReading: 4235,
                        finalMeterReading: 5942,
                        elapsedTime: 15
                    },
                    meteredFlowMethodData: {
                        meterReading: 100
                    },
                    bucketMethodData: {
                        bucketVolume: 10,
                        bucketFillTime: 20
                    },
                    otherMethodData: {
                        consumption: 15000
                    }
                },
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: 2,
                    volumeMeterMethodData: {
                        initialMeterReading: 4235,
                        finalMeterReading: 5942,
                        elapsedTime: 15
                    },
                    meteredFlowMethodData: {
                        meterReading: 100
                    },
                    bucketMethodData: {
                        bucketVolume: 10,
                        bucketFillTime: 20
                    },
                    otherMethodData: {
                        consumption: 15000
                    }
                },
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: 3,
                    volumeMeterMethodData: {
                        initialMeterReading: 4235,
                        finalMeterReading: 5942,
                        elapsedTime: 15
                    },
                    meteredFlowMethodData: {
                        meterReading: 100
                    },
                    bucketMethodData: {
                        bucketVolume: 10,
                        bucketFillTime: 20
                    },
                    otherMethodData: {
                        consumption: 15000
                    }
                }
            ]
        };
        executeTest(measurInputData, 8413080, 42065.4, 0, 0);
    });
});