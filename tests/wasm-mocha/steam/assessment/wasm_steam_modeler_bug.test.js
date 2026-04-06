import { assert } from 'chai';
import { getHighPressureHeaderObject, getCondensingTurbineOperation, getNotHighPressureHeaderObject, getPressureTurbineOperation } from './modelerHelpers.js';

describe('Steam Modeler Bug', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should model without error', function () {
        let inputData = {
            "operationsInput": {
                "sitePowerImport": 0,
                "makeUpWaterTemperature": 366.48333333333335,
                "operatingHoursPerYear": 8760,
                "fuelCosts": 0.000010757682027562413,
                "electricityCosts": 0.0000311111164689024,
                "makeUpWaterCosts": 2.4462331974687497
            },
            "co2SavingsData": {
                "energyType": "electricity",
                "energySource": "Natural Gas",
                "fuelType": "Natural Gas",
                "totalEmissionOutputRate": 401.07,
                "electricityUse": 0,
                "eGridRegion": "",
                "eGridSubregion": "U.S. Average",
                "totalEmissionOutput": 0,
                "totalFuelEmissionOutputRate": 53.06,
                "userEnteredBaselineEmissions": false,
                "userEnteredModificationEmissions": false,
                "zipcode": "00000"
            },
            "boilerInput": {
                "fuelType": 1,
                "fuel": 1,
                "combustionEfficiency": 87.33,
                "blowdownRate": 8,
                "blowdownFlashed": true,
                "preheatMakeupWater": false,
                "steamQuality": 0,
                "pressureOrTemperature": 0,
                "saturatedPressure": 105,
                "steamTemperature": 444.81666666666666,
                "deaeratorVentRate": 10,
                "deaeratorPressure": 0.10132539296661526,
                "approachTemperature": 61.11111111111106,
                "blowdownConductivity": 2500,
                "feedwaterConductivity": 10
            },
            "headerInput": {
                "numberOfHeaders": 1,
                "highPressureHeader": {
                    "pressure": 0.82527519301388,
                    "processSteamUsage": 1923230.08,
                    "condensationRecoveryRate": 70,
                    "heatLoss": 5,
                    "condensateReturnTemperature": 358.15,
                    "flashCondensateReturn": false
                },
                "mediumPressureHeader": null,
                "lowPressureHeader": null
            },
            "turbineInput": {
                "condensingTurbine": {
                    "isentropicEfficiency": 0,
                    "generationEfficiency": 0,
                    "condenserPressure": 0,
                    "operationType": 0,
                    "operationValue": 0,
                    "useTurbine": false
                },
                "highToLowTurbine": {
                    "isentropicEfficiency": 0,
                    "generationEfficiency": 0,
                    "operationType": 0,
                    "operationValue1": 0,
                    "operationValue2": 0,
                    "useTurbine": false
                },
                "highToMediumTurbine": {
                    "isentropicEfficiency": 0,
                    "generationEfficiency": 0,
                    "operationType": 0,
                    "operationValue1": 0,
                    "operationValue2": 0,
                    "useTurbine": false
                },
                "mediumToLowTurbine": {
                    "isentropicEfficiency": 0,
                    "generationEfficiency": 0,
                    "operationType": 0,
                    "operationValue1": 0,
                    "operationValue2": 0,
                    "useTurbine": false
                }
            },
            "baselinePowerDemand": 0,
            "isBaselineCalc": true
        }



        let boilerInputObj = new moduleInstance.BoilerInput(
            inputData.boilerInput.fuelType,
            inputData.boilerInput.fuel,
            inputData.boilerInput.combustionEfficiency,
            inputData.boilerInput.blowdownRate,
            inputData.boilerInput.blowdownFlashed,
            inputData.boilerInput.preheatMakeupWater,
            inputData.boilerInput.steamTemperature,
            inputData.boilerInput.deaeratorVentRate,
            inputData.boilerInput.deaeratorPressure,
            inputData.boilerInput.approachTemperature
        );


        let highPressureHeaderObj;
        if (inputData.headerInput.highPressureHeader) {
            highPressureHeaderObj = getHighPressureHeaderObject(inputData.headerInput.highPressureHeader, moduleInstance);
        }

        let operationsInputObj = new moduleInstance.OperationsInput(
            inputData.operationsInput.sitePowerImport,
            inputData.operationsInput.makeUpWaterTemperature,
            inputData.operationsInput.operatingHoursPerYear,
            inputData.operationsInput.fuelCosts,
            inputData.operationsInput.electricityCosts,
            inputData.operationsInput.makeUpWaterCosts
        );

        inputData.turbineInput.condensingTurbine.operationType = getCondensingTurbineOperation(inputData.turbineInput.condensingTurbine.operationType, moduleInstance);
        inputData.turbineInput.highToLowTurbine.operationType = getPressureTurbineOperation(inputData.turbineInput.highToLowTurbine.operationType, moduleInstance);
        inputData.turbineInput.highToMediumTurbine.operationType = getPressureTurbineOperation(inputData.turbineInput.highToMediumTurbine.operationType, moduleInstance);
        inputData.turbineInput.mediumToLowTurbine.operationType = getPressureTurbineOperation(inputData.turbineInput.mediumToLowTurbine.operationType, moduleInstance);


        let mediumPressureHeaderObj = null;
        if (inputData.headerInput.mediumPressureHeader !== null && inputData.headerInput.mediumPressureHeader !== undefined) {
            // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.headerInput.mediumPressureHeader);
            mediumPressureHeaderObj = getNotHighPressureHeaderObject(inputData.headerInput.mediumPressureHeader, moduleInstance);
        } else if (inputData.headerInput.mediumPressure !== null && inputData.headerInput.mediumPressure !== undefined) {
            // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.headerInput.mediumPressure);
            mediumPressureHeaderObj = getNotHighPressureHeaderObject(inputData.headerInput.mediumPressure, moduleInstance);
        }
        let lowPressureHeaderObj = null;
        if (inputData.headerInput.lowPressureHeader !== null && inputData.headerInput.lowPressureHeader !== undefined) {
            // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.headerInput.lowPressureHeader);
            lowPressureHeaderObj = getNotHighPressureHeaderObject(inputData.headerInput.lowPressureHeader, moduleInstance);
        } else if (inputData.headerInput.lowPressure !== null && inputData.headerInput.lowPressure !== undefined) {
            // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.headerInput.lowPressure);
            lowPressureHeaderObj = getNotHighPressureHeaderObject(inputData.headerInput.lowPressure, moduleInstance);
        }

        let headerInputObj = new moduleInstance.HeaderInput(highPressureHeaderObj, mediumPressureHeaderObj, lowPressureHeaderObj);
        if (mediumPressureHeaderObj) {
            mediumPressureHeaderObj.delete();
        }
        if (lowPressureHeaderObj) {
            lowPressureHeaderObj.delete();
        }

        // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.turbineInput.condensingTurbine);
        let condensingTurbineObj = new moduleInstance.CondensingTurbine(
            inputData.turbineInput.condensingTurbine.isentropicEfficiency,
            inputData.turbineInput.condensingTurbine.generationEfficiency,
            inputData.turbineInput.condensingTurbine.condenserPressure,
            inputData.turbineInput.condensingTurbine.operationType,
            inputData.turbineInput.condensingTurbine.operationValue,
            inputData.turbineInput.condensingTurbine.useTurbine
        );
        // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.turbineInput.highToLowTurbine);
        let highToLowTurbineObj = new moduleInstance.PressureTurbine(
            inputData.turbineInput.highToLowTurbine.isentropicEfficiency,
            inputData.turbineInput.highToLowTurbine.generationEfficiency,
            inputData.turbineInput.highToLowTurbine.operationType,
            inputData.turbineInput.highToLowTurbine.operationValue1,
            inputData.turbineInput.highToLowTurbine.operationValue2,
            inputData.turbineInput.highToLowTurbine.useTurbine
        );
        // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.turbineInput.highToMediumTurbine);
        let highToMediumTurbineObj = new moduleInstance.PressureTurbine(
            inputData.turbineInput.highToMediumTurbine.isentropicEfficiency,
            inputData.turbineInput.highToMediumTurbine.generationEfficiency,
            inputData.turbineInput.highToMediumTurbine.operationType,
            inputData.turbineInput.highToMediumTurbine.operationValue1,
            inputData.turbineInput.highToMediumTurbine.operationValue2,
            inputData.turbineInput.highToMediumTurbine.useTurbine
        );
        // this.suiteApiHelperService.convertNullInputsForObjectConstructor(inputData.turbineInput.mediumToLowTurbine);
        let mediumToLowTurbineObj = new moduleInstance.PressureTurbine(
            inputData.turbineInput.mediumToLowTurbine.isentropicEfficiency,
            inputData.turbineInput.mediumToLowTurbine.generationEfficiency,
            inputData.turbineInput.mediumToLowTurbine.operationType,
            inputData.turbineInput.mediumToLowTurbine.operationValue1,
            inputData.turbineInput.mediumToLowTurbine.operationValue2,
            inputData.turbineInput.mediumToLowTurbine.useTurbine
        );

        let turbineInputObj = new moduleInstance.TurbineInput(
            condensingTurbineObj,
            highToLowTurbineObj,
            highToMediumTurbineObj,
            mediumToLowTurbineObj
        );

        let steamModelerInput = new moduleInstance.SteamModelerInput(
            inputData.isBaselineCalc,
            inputData.baselinePowerDemand,
            boilerInputObj,
            headerInputObj,
            operationsInputObj,
            turbineInputObj
        );

        let modeler = new moduleInstance.SteamModeler();
        let wasmOutput = modeler.model(steamModelerInput);
        console.log(wasmOutput);
        // ssmtOutput = this.getSSMTOutputFromWASMOutput(wasmOutput);

        wasmOutput.delete();
        modeler.delete();
        boilerInputObj.delete();
        highPressureHeaderObj.delete();
        headerInputObj.delete();
        operationsInputObj.delete();
        condensingTurbineObj.delete();
        highToLowTurbineObj.delete();
        highToMediumTurbineObj.delete();
        mediumToLowTurbineObj.delete();
        turbineInputObj.delete();
        steamModelerInput.delete();

        //assertation to check that code ran without error
        assert.isOk(true);
    });
});