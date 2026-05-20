import { assert } from 'chai';

describe('Steam Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function executeTest(inputVec, expectedSteamUse, expectedEnergyUse, expectedEnergyCost) {
        let inputList = new moduleInstance.SteamReductionInputV();
        for (let i = 0; i < inputVec.length; i++) {
            inputList.push_back(inputVec[i]);
        }

        let results = moduleInstance.steamReduction(inputList);
        assert.approximately(results.steamUse,   expectedSteamUse,   0.001, 'steamUse');
        assert.approximately(results.energyUse,  expectedEnergyUse,  0.001, 'energyUse');
        assert.approximately(results.energyCost, expectedEnergyCost, 0.001, 'energyCost');

        inputList.delete();
    }

    it('should calculate steamReduction (Flow Meter Method) correctly', function () {
        executeTest([
            {
                hoursPerYear: 8000,
                utilityType: moduleInstance.SteamUtilityType.NaturalGas,
                utilityCost: 5.5,
                measurementMethod: moduleInstance.SteamMeasurementMethod.FlowMeter,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: { flowRate: 1000 },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 4000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 40000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: { consumption: 13000000 },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ], 10000000.0, 38671503020.03, 212693266610.1651);
    });

    it('should calculate steamReduction (Air Mass Flow - Measured) correctly', function () {
        executeTest([
            {
                hoursPerYear: 8000,
                utilityType: moduleInstance.SteamUtilityType.NaturalGas,
                utilityCost: 5.5,
                measurementMethod: moduleInstance.SteamMeasurementMethod.AirMassFlow,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: { flowRate: 1000 },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 4000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 40000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: { consumption: 13000000 },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ], 9982.3376, 38603200.0, 212317600.0);
    });

    it('should calculate steamReduction (Air Mass Flow - Nameplate) correctly', function () {
        executeTest([
            {
                hoursPerYear: 8000,
                utilityType: moduleInstance.SteamUtilityType.NaturalGas,
                utilityCost: 5.5,
                measurementMethod: moduleInstance.SteamMeasurementMethod.AirMassFlow,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: { flowRate: 1000 },
                airMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 4000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 40000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: { consumption: 13000000 },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ], 399293.5054, 1544127999.9999, 8492703999.9999);
    });

    it('should calculate steamReduction (Water Mass Flow - Nameplate) correctly', function () {
        executeTest([
            {
                hoursPerYear: 8000,
                utilityType: moduleInstance.SteamUtilityType.NaturalGas,
                utilityCost: 5.5,
                measurementMethod: moduleInstance.SteamMeasurementMethod.WaterMassFlow,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: { flowRate: 1000 },
                airMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 100, airVelocity: 5 },
                    massFlowNameplateData: { flowRate: 400 },
                    inletTemperature: 70,
                    outletTemperature: 200
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 1 },
                    inletTemperature: 25,
                    outletTemperature: 225
                },
                offsheetMethodData: { consumption: 13000000 },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ], 173112830.1340, 669453333333.3332, 3681993333333.3330);
    });

    it('should calculate steamReduction (Offsheet Method) correctly', function () {
        executeTest([
            {
                hoursPerYear: 8000,
                utilityType: moduleInstance.SteamUtilityType.Steam,
                utilityCost: 5.5,
                measurementMethod: moduleInstance.SteamMeasurementMethod.Offsheet,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: { flowRate: 50000 },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 4000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: { areaOfDuct: 1, airVelocity: 100 },
                    massFlowNameplateData: { flowRate: 4000 },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: { consumption: 13000000 },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: moduleInstance.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ], 3361.6485, 13000000.0, 18489.0667);
    });
});