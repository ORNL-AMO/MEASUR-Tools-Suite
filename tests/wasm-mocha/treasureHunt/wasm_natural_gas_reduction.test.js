import { assert } from 'chai';

describe('Natural Gas Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate 1 NaturalGasReduction correctly', function () {
        let inp = {
            naturalGasReductionInputVec: [
                {
                    operatingHours: 8640,
                    fuelCost: 0.12,
                    measurementMethod: 0,
                    flowMeterMethodData: {
                        flowRate: 5
                    },
                    naturalGasOtherMethodData: {
                        consumption: 30.00
                    },
                    airMassFlowData: {
                        isNameplate: false,
                        airMassFlowMeasuredData: {
                            areaOfDuct: 3,
                            airVelocity: 15
                        },
                        airMassFlowNameplateData: {
                            airFlow: 30
                        },
                        inletTemperature: 70,
                        outletTemperature: 800,
                        systemEfficiency: 80
                    },
                    waterMassFlowData: {
                        waterFlow: 10,
                        inletTemperature: 70,
                        outletTemperature: 100,
                        systemEfficiency: 80
                    },
                    units: 2
                }
            ]
        };
        let inputList = new moduleInstance.NaturalGasReductionInputV();
        for (let i = 0; i < inp.naturalGasReductionInputVec.length; i++) {
            let inpElem = inp.naturalGasReductionInputVec[i];
            let flowMeterMethodData = new moduleInstance.FlowMeterMethodData(inpElem.flowMeterMethodData.flowRate);
            let naturalGasOtherMethodData = new moduleInstance.NaturalGasOtherMethodData(inpElem.naturalGasOtherMethodData.consumption);
            let airMassFlowMeasuredData = new moduleInstance.AirMassFlowMeasuredData(inpElem.airMassFlowData.airMassFlowMeasuredData.areaOfDuct,
                inpElem.airMassFlowData.airMassFlowMeasuredData.airVelocity);
            let airMassFlowNameplateData = new moduleInstance.AirMassFlowNameplateData(inpElem.airMassFlowData.airMassFlowNameplateData.airFlow);
            let airMassFlowData = new moduleInstance.AirMassFlowData(inpElem.airMassFlowData.isNameplate, airMassFlowMeasuredData, airMassFlowNameplateData,
                inpElem.airMassFlowData.inletTemperature, inpElem.airMassFlowData.outletTemperature, inpElem.airMassFlowData.systemEfficiency);
            let waterMassFlowData = new moduleInstance.WaterMassFlowData(inpElem.waterMassFlowData.waterFlow,
                inpElem.waterMassFlowData.inletTemperature, inpElem.waterMassFlowData.outletTemperature, inpElem.waterMassFlowData.systemEfficiency);

            let input = new moduleInstance.NaturalGasReductionInput(inpElem.operatingHours, inpElem.fuelCost, inpElem.measurementMethod,
                flowMeterMethodData, naturalGasOtherMethodData, airMassFlowData, waterMassFlowData, inpElem.units);
            inputList.push_back(input);

            input.delete();
            waterMassFlowData.delete();
            airMassFlowData.delete();
            airMassFlowNameplateData.delete();
            airMassFlowMeasuredData.delete();
            naturalGasOtherMethodData.delete();
            flowMeterMethodData.delete();
        }

        let instance = new moduleInstance.NaturalGasReduction(inputList);
        let results = instance.calculate();
        assert.approximately(results.energyUse, 88.992, 0.001, "energyUse");
        assert.approximately(results.energyCost, 10.67904, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 10, 0.001, "totalFlow");
        instance.delete();
        inputList.delete();
    });


});