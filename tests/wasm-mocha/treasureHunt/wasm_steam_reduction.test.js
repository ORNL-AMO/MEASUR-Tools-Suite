import { assert } from 'chai';

describe('Steam Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });


    function executeTest(measurInputData, expectedSteamUse, expectedEnergyUse, expectedEnergyCost) {
        let inputList = new moduleInstance.SteamReductionInputV();
        for (let i = 0; i < measurInputData.steamReductionInputVec.length; i++) {
            let inpElem = measurInputData.steamReductionInputVec[i];
            let flowMeterMethodData = new moduleInstance.SteamFlowMeterMethodData(inpElem.flowMeterMethodData.flowRate);

            let massFlowMeasuredData = new moduleInstance.SteamMassFlowMeasuredData(inpElem.airMassFlowMethodData.massFlowMeasuredData.areaOfDuct,
                inpElem.airMassFlowMethodData.massFlowMeasuredData.airVelocity);
            let massFlowNameplateData = new moduleInstance.SteamMassFlowNameplateData(inpElem.airMassFlowMethodData.massFlowNameplateData.flowRate);
            let airMassFlowMethodData = new moduleInstance.SteamMassFlowMethodData(inpElem.airMassFlowMethodData.isNameplate,
                massFlowMeasuredData, massFlowNameplateData,
                inpElem.airMassFlowMethodData.inletTemperature, inpElem.airMassFlowMethodData.outletTemperature);

            massFlowMeasuredData = new moduleInstance.SteamMassFlowMeasuredData(inpElem.waterMassFlowMethodData.massFlowMeasuredData.areaOfDuct,
                inpElem.waterMassFlowMethodData.massFlowMeasuredData.airVelocity);
            massFlowNameplateData = new moduleInstance.SteamMassFlowNameplateData(inpElem.waterMassFlowMethodData.massFlowNameplateData.flowRate);
            let waterMassFlowMethodData = new moduleInstance.SteamMassFlowMethodData(inpElem.waterMassFlowMethodData.isNameplate,
                massFlowMeasuredData, massFlowNameplateData,
                inpElem.waterMassFlowMethodData.inletTemperature, inpElem.waterMassFlowMethodData.outletTemperature);

            let offsheetMethodData = new moduleInstance.SteamOffsheetMethodData(inpElem.offsheetMethodData.consumption);

            let input = new moduleInstance.SteamReductionInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost,
                inpElem.measurementMethod, inpElem.systemEfficiency, inpElem.pressure,
                flowMeterMethodData, airMassFlowMethodData, waterMassFlowMethodData, offsheetMethodData, inpElem.units,
                inpElem.boilerEfficiency, inpElem.steamVariableOption, inpElem.steamVariable, inpElem.feedWaterTemperature);
            inputList.push_back(input);

            input.delete();
            offsheetMethodData.delete();
            waterMassFlowMethodData.delete();
            airMassFlowMethodData.delete();
            massFlowNameplateData.delete();
            massFlowMeasuredData.delete();
            flowMeterMethodData.delete();
        }

        let instance = new moduleInstance.SteamReduction(inputList);
        let results = instance.calculate();
        assert.approximately(results.steamUse, expectedSteamUse, .001, "steamUse");
        assert.approximately(results.energyUse, expectedEnergyUse, .001, "energyUse");
        assert.approximately(results.energyCost, expectedEnergyCost, .001, "energyCost");

        instance.delete();
        inputList.delete();
    }

    it('should calculate SteamReduction (Flow Meter Method Data) correctly', function () {
        let measurInputData = {
            steamReductionInputVec: [
                {
                    hoursPerYear: 8000,
                    utilityType: 1,
                    utilityCost: 5.5,
                    measurementMethod: 0,
                    systemEfficiency: 0.8,
                    pressure: 3.5,
                    flowMeterMethodData: {
                        flowRate: 1000
                    },
                    airMassFlowMethodData: {
                        isNameplate: false,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 4000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    waterMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 40000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    offsheetMethodData: {
                        consumption: 13000000
                    },
                    units: 1,
                    boilerEfficiency: 0.75,
                    steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                    steamVariable: 560,
                    feedWaterTemperature: 283.15
                }
            ]
        };

        executeTest(measurInputData, 10000000.0, 38671503020.03, 212693266610.1651);
    });

    it('should calculate SteamReduction (Air Mass Flow - Measured) correctly', function () {
        let measurInputData = {
            steamReductionInputVec: [
                {
                    hoursPerYear: 8000,
                    utilityType: 1,
                    utilityCost: 5.5,
                    measurementMethod: 1,
                    systemEfficiency: 0.8,
                    pressure: 3.5,
                    flowMeterMethodData: {
                        flowRate: 1000
                    },
                    airMassFlowMethodData: {
                        isNameplate: false,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 4000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    waterMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 40000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    offsheetMethodData: {
                        consumption: 13000000
                    },
                    units: 1,
                    boilerEfficiency: 0.75,
                    steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                    steamVariable: 560,
                    feedWaterTemperature: 283.15
                }
            ]
        };
        executeTest(measurInputData, 9982.3376, 38603200.0, 212317600.0);
    });

    it('should calculate SteamReduction (Air Mass Flow - Nameplate) correctly', function () {
        let measurInputData = {
            steamReductionInputVec: [
                {
                    hoursPerYear: 8000,
                    utilityType: 1,
                    utilityCost: 5.5,
                    measurementMethod: 1,
                    systemEfficiency: 0.8,
                    pressure: 3.5,
                    flowMeterMethodData: {
                        flowRate: 1000
                    },
                    airMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 4000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    waterMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 40000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    offsheetMethodData: {
                        consumption: 13000000
                    },
                    units: 1,
                    boilerEfficiency: 0.75,
                    steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                    steamVariable: 560,
                    feedWaterTemperature: 283.15
                }
            ]
        };
        executeTest(measurInputData, 399293.5054, 1544127999.9999, 8492703999.9999);
    });

    it('should calculate SteamReduction (Water Mass Flow - Nameplate) correctly', function () {
        let measurInputData = {
            steamReductionInputVec: [
                {
                    hoursPerYear: 8000,
                    utilityType: 1,
                    utilityCost: 5.5,
                    measurementMethod: 2,
                    systemEfficiency: 0.8,
                    pressure: 3.5,
                    flowMeterMethodData: {
                        flowRate: 1000
                    },
                    airMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 100,
                            airVelocity: 5
                        },
                        massFlowNameplateData: {
                            flowRate: 400
                        },
                        inletTemperature: 70,
                        outletTemperature: 200
                    },
                    waterMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 1
                        },
                        inletTemperature: 25,
                        outletTemperature: 225
                    },
                    offsheetMethodData: {
                        consumption: 13000000
                    },
                    units: 1,
                    boilerEfficiency: 0.75,
                    steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                    steamVariable: 560,
                    feedWaterTemperature: 283.15
                }
            ]
        };
        executeTest(measurInputData, 173112830.1340, 669453333333.3332, 3681993333333.3330);
    });

    it('should calculate SteamReduction (Offsheet Method) correctly', function () {
        let measurInputData = {
            steamReductionInputVec: [
                {
                    hoursPerYear: 8000,
                    utilityType: 0,
                    utilityCost: 5.5,
                    measurementMethod: 3,
                    systemEfficiency: 0.8,
                    pressure: 3.5,
                    flowMeterMethodData: {
                        flowRate: 50000
                    },
                    airMassFlowMethodData: {
                        isNameplate: false,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 4000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    waterMassFlowMethodData: {
                        isNameplate: true,
                        massFlowMeasuredData: {
                            areaOfDuct: 1,
                            airVelocity: 100
                        },
                        massFlowNameplateData: {
                            flowRate: 4000
                        },
                        inletTemperature: 25,
                        outletTemperature: 425
                    },
                    offsheetMethodData: {
                        consumption: 13000000
                    },
                    units: 1,
                    boilerEfficiency: 0.75,
                    steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                    steamVariable: 560,
                    feedWaterTemperature: 283.15
                }
            ]
        };
        executeTest(measurInputData, 3361.6485, 13000000.0, 18489.0667);
    });

});