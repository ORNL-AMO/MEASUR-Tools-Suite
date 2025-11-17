import { assert } from 'chai';

describe('Compressed Air Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    function executeTest(measurInputData, energyUseExpected, energyCostExpected, flowRateExpected, singleNozzleFlowRateExpected, consumptionExpected) {

        let inputList = new moduleInstance.CompressedAirReductionInputV();
        for (let i = 0; i < measurInputData.compressedAirReductionInputVec.length; i++) {
            let inpElem = measurInputData.compressedAirReductionInputVec[i];
            let compressedAirFlowMeterMethodData = new moduleInstance.CompressedAirFlowMeterMethodData(inpElem.flowMeterMethodData.meterReading);
            let bagMethod = new moduleInstance.BagMethod(inpElem.bagMethod.operatingTime, inpElem.bagMethod.bagFillTime, inpElem.bagMethod.bagVolume, inpElem.bagMethod.numberOfUnits);
            let pressureMethodData = new moduleInstance.PressureMethodData(inpElem.pressureMethodData.nozzleType, inpElem.pressureMethodData.numberOfNozzles,
                inpElem.pressureMethodData.supplyPressure);
            let compressedAirOtherMethodData = new moduleInstance.CompressedAirOtherMethodData(inpElem.otherMethodData.consumption);
            let compressorElectricityData = new moduleInstance.CompressorElectricityData(inpElem.compressorElectricityData.compressorControlAdjustment,
                inpElem.compressorElectricityData.compressorSpecificPower);

            let input = new moduleInstance.CompressedAirReductionInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost, inpElem.measurementMethod,
                compressedAirFlowMeterMethodData, bagMethod, pressureMethodData, compressedAirOtherMethodData, compressorElectricityData, inpElem.units);
            inputList.push_back(input);

            input.delete();
            compressorElectricityData.delete();
            compressedAirOtherMethodData.delete();
            pressureMethodData.delete();
            bagMethod.delete();
            compressedAirFlowMeterMethodData.delete();
        }

        let instance = new moduleInstance.CompressedAirReduction(inputList);
        let results = instance.calculate();
        assert.approximately(results.energyUse, energyUseExpected, 0.01, "energyUse");
        assert.approximately(results.energyCost, energyCostExpected, 0.01, "energyCost");
        assert.approximately(results.flowRate, flowRateExpected, 0.01, "flowRate");
        assert.approximately(results.singleNozzleFlowRate, singleNozzleFlowRateExpected, 0.01, "singleNozzleFlowRate");
        assert.approximately(results.consumption, consumptionExpected, 0.01, "consumption");
        instance.delete();
        inputList.delete();
    }


    it('should calculate 1 CompressedAirReduction (air flow method) correctly', function () {
        let measurInputData = {
            compressedAirReductionInputVec: [
                {
                    hoursPerYear: 8640,
                    utilityType: 1,
                    utilityCost: 0.12,
                    measurementMethod: 0,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8640,
                        bagFillTime: 30,
                        bagVolume: 1.36,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 0.8,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                }
            ]
        };
        executeTest(measurInputData, 276480000, 33177600, 200000, 0, 103680000000);
    });


    it('should calculate 1 CompressedAirReduction (bag method) correctly', function () {
        let measurInputData = {
            compressedAirReductionInputVec: [
                {
                    hoursPerYear: 8760,
                    utilityType: 1,
                    utilityCost: 0.066,
                    measurementMethod: 1,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8760,
                        bagFillTime: 12,
                        bagVolume: 6.68403122278085,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 25,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                }
            ]
        };
        executeTest(measurInputData, 46841.69, 3091.55, 33.42245989, 0, 17565634.05);
    });


    it('should calculate 4 CompressedAirReduction (all methods) correctly', function () {
        let measurInputData = {
            compressedAirReductionInputVec: [
                // flow measurement with electricity
                // energyUse = 221184000.0
                // energyCost = 26542080.0
                // flowRate = 0.0
                // singleNozzleFlowRate = 0.0
                // consumption = 103680000000.0
                {
                    hoursPerYear: 8640,
                    utilityType: 1,
                    utilityCost: 0.066,
                    measurementMethod: 0,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8640,
                        bagFillTime: 30,
                        bagVolume: 1.36,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 0.8,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                },
                // bag method with electricity
                // energyUse = 3769.9111
                // energyCost = 452.3893
                // flowRate = 3.408846
                // singleNozzleFlowRate = 0.0
                // consumption = 3534291.73528
                {
                    hoursPerYear: 8640,
                    utilityType: 1,
                    utilityCost: 0.12,
                    measurementMethod: 1,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8640,
                        bagFillTime: 12,
                        bagVolume: 8.68,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 0.8,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                },
                // pressure method, no electricity
                // flowRate = 1.778508
                // singleNozzleFlowRate = 1.778508
                // consumption = 921978.5471999
                {
                    hoursPerYear: 8640,
                    utilityType: 0,
                    utilityCost: 0.12,
                    measurementMethod: 2,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8640,
                        bagFillTime: 30,
                        bagVolume: 1.36,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 0.8,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                },
                // other method with electricity
                // consumption = 200000.0
                // energyUse = 213.3333
                // energyCost = 25.6
                {
                    hoursPerYear: 8640,
                    utilityType: 1,
                    utilityCost: 0.12,
                    measurementMethod: 3,
                    flowMeterMethodData: {
                        meterReading: 200000.0
                    },
                    bagMethod: {
                        operatingTime: 8640,
                        bagFillTime: 30,
                        bagVolume: 1.36,
                        numberOfUnits: 1
                    },
                    pressureMethodData: {
                        nozzleType: 0,
                        numberOfNozzles: 1,
                        supplyPressure: 80
                    },
                    otherMethodData: {
                        consumption: 200000
                    },
                    compressorElectricityData: {
                        compressorControlAdjustment: 0.8,
                        compressorSpecificPower: 0.16
                    },
                    units: 1
                }
            ]
        };
        executeTest(measurInputData, 276540529.49, 18365580.96, 200045.18, 1.778508, 103703620538.55);
    });


});