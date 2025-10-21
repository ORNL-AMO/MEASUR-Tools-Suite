import { assert } from 'chai';

describe('Electricity Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function executeTest(measurInputData, energyUseExpected, energyCostExpected, powerExpected) {
        let inputList = new moduleInstance.ElectricityReductionInputV();
        for (let i = 0; i < measurInputData.electricityReductionInputVec.length; i++) {
            let inpElem = measurInputData.electricityReductionInputVec[i];
            let multimeterData = new moduleInstance.MultimeterData(inpElem.multimeterData.numberOfPhases,
                inpElem.multimeterData.supplyVoltage, inpElem.multimeterData.averageCurrent, inpElem.multimeterData.powerFactor);
            let nameplateData = new moduleInstance.NameplateData(inpElem.nameplateData.ratedMotorPower, inpElem.nameplateData.variableSpeedMotor,
                inpElem.nameplateData.operationalFrequency, inpElem.nameplateData.lineFrequency, inpElem.nameplateData.motorAndDriveEfficiency, inpElem.nameplateData.loadFactor);
            let powerMeterData = new moduleInstance.PowerMeterData(inpElem.powerMeterData.power);
            let otherMethodData = new moduleInstance.OtherMethodData(inpElem.otherMethodData.energy);

            let input = new moduleInstance.ElectricityReductionInput(inpElem.operatingHours, inpElem.electricityCost, inpElem.measurementMethod,
                multimeterData, nameplateData, powerMeterData, otherMethodData, inpElem.units);
            inputList.push_back(input);
            input.delete();
            multimeterData.delete();
            nameplateData.delete();
            powerMeterData.delete();
            otherMethodData.delete();
        }

        let instance = new moduleInstance.ElectricityReduction(inputList);
        let results = instance.calculate();
        assert.approximately(results.energyUse, energyUseExpected, 0.00001, "energyUse");
        assert.approximately(results.energyCost, energyCostExpected, 0.00001, "energyCost");
        assert.approximately(results.power, powerExpected, 0.00001, "power");
        instance.delete();
        inputList.delete();
    }

    it('should calculate 1 ElectricityReduction correctly', function () {
        let measurInputData = {
            electricityReductionInputVec: [
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 0,
                    multimeterData: {
                        numberOfPhases: 3,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 1
                }
            ]
        };
        executeTest(measurInputData, 407045.7961851467, 48845.495542, 47.111782);
    });


    it('should calculate 5 ElectricityReductions correctly', function () {
        let measurInputData = {
            electricityReductionInputVec: [
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 0,
                    multimeterData: {
                        numberOfPhases: 3,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 0,
                    multimeterData: {
                        numberOfPhases: 1,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 1,
                    multimeterData: {
                        numberOfPhases: 1,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 2,
                    multimeterData: {
                        numberOfPhases: 3,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 2
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: 3,
                    multimeterData: {
                        numberOfPhases: 3,
                        supplyVoltage: 800,
                        averageCurrent: 40,
                        powerFactor: 0.85
                    },
                    nameplateData: {
                        ratedMotorPower: 100,
                        variableSpeedMotor: false,
                        operationalFrequency: 55,
                        lineFrequency: 60,
                        motorAndDriveEfficiency: 100,
                        loadFactor: 1
                    },
                    powerMeterData: {
                        power: 50
                    },
                    otherMethodData: {
                        energy: 432000
                    },
                    units: 2
                }
            ]
        };
        executeTest(measurInputData, 1945004.716987, 233400.566038, 432175.11628668837);
    });
});