import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type WaterReductionInput,
    type WaterReductionInputV,
    type WaterReductionOutput,
} from 'measur-tools-suite';

describe('Water Reduction Tests', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate WaterReduction Metered Method correctly', function () {
        const inputData: WaterReductionInput = {
            hoursPerYear: 8640,
            waterCost: 0.005,
            measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Metered,
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
        };
        const waterReductionInputVec: WaterReductionInputV = new moduleInstance.WaterReductionInputV();
        waterReductionInputVec.push_back(inputData)

        const results: WaterReductionOutput = moduleInstance.waterReduction(waterReductionInputVec)
        assert.approximately(results.waterUse, 51840000, .001, "waterUse");
        assert.approximately(results.waterCost, 259200, .001, "waterCost");
        waterReductionInputVec.delete();
    });

    it('should calculate WaterReduction Volume Method correctly', function () {
        const inputData: WaterReductionInput = {
            hoursPerYear: 8640,
            waterCost: 0.005,
            measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Volume,
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
        };

        const waterReductionInputVec: WaterReductionInputV = new moduleInstance.WaterReductionInputV();
        waterReductionInputVec.push_back(inputData)

        const results: WaterReductionOutput = moduleInstance.waterReduction(waterReductionInputVec)
        assert.approximately(results.waterUse, 58993920.0, .001, "waterUse");
        assert.approximately(results.waterCost, 294969.6, .001, "waterCost");
        waterReductionInputVec.delete();

    });


    it('should calculate 1 WaterReduction correctly', function () {
        const inputData: WaterReductionInput = {
            hoursPerYear: 8640,
            waterCost: 0.005,
            measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Bucket,
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
        };

        const waterReductionInputVec: WaterReductionInputV = new moduleInstance.WaterReductionInputV();
        waterReductionInputVec.push_back(inputData)

        const results: WaterReductionOutput = moduleInstance.waterReduction(waterReductionInputVec)
        assert.approximately(results.waterUse, 15552000.0, .001, "waterUse");
        assert.approximately(results.waterCost, 77760.0, .001, "waterCost");
        waterReductionInputVec.delete();
    });


    it('should calculate WaterReduction Other Method correctly', function () {
        const inputData: WaterReductionInput = {
            hoursPerYear: 8640,
            waterCost: 0.005,
            measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Other,
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
        };

        const waterReductionInputVec: WaterReductionInputV = new moduleInstance.WaterReductionInputV();
        waterReductionInputVec.push_back(inputData)

        const results: WaterReductionOutput = moduleInstance.waterReduction(waterReductionInputVec)
        assert.approximately(results.waterUse, 15000.0, .001, "waterUse");
        assert.approximately(results.waterCost, 75.0, .001, "waterCost");
        waterReductionInputVec.delete();
    });

    it('should calculate 4 WaterReductions (all methods) correctly', function () {
        const measurInputData: { waterReductionInputVec: WaterReductionInput[] } = {
            waterReductionInputVec: [
                {
                    hoursPerYear: 8640,
                    waterCost: 0.005,
                    measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Metered,
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
                    measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Volume,
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
                    measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Bucket,
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
                    measurementMethod: moduleInstance.WaterReductionMeasurementMethod.Other,
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


        const inputList: WaterReductionInputV = new moduleInstance.WaterReductionInputV();
        for (let i = 0; i < measurInputData.waterReductionInputVec.length; i++) {
            let inpElem = measurInputData.waterReductionInputVec[i];
            inputList.push_back(inpElem);
        }
        const results: WaterReductionOutput = moduleInstance.waterReduction(inputList)
        assert.approximately(results.waterUse, 126400920, .001, "waterUse");
        assert.approximately(results.waterCost, 632004.6, .001, "waterCost");
        inputList.delete();
    });
});
