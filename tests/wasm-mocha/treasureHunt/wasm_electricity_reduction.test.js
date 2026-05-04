import { assert } from 'chai';

describe('Electricity Reduction Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate ElectricityReduction Multimeter Method (3-phase) correctly', function () {
        let inputData = {
            operatingHours: 8640,
            electricityCost: 0.12,
            measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Multimeter,
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
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        inputVec.push_back(inputData);

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 407045.796185, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 48845.495542, 0.001, 'energyCost');
        assert.approximately(results.power, 47.111781, 0.001, 'power');
        inputVec.delete();
    });

    it('should calculate ElectricityReduction Multimeter Method (1-phase) correctly', function () {
        let inputData = {
            operatingHours: 8640,
            electricityCost: 0.12,
            measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Multimeter,
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
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        inputVec.push_back(inputData);

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 235008, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 28200.96, 0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate ElectricityReduction Nameplate Method correctly', function () {
        let inputData = {
            operatingHours: 8640,
            electricityCost: 0.12,
            measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Nameplate,
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
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        inputVec.push_back(inputData);

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 6950.9206, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 834.11047, 0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate ElectricityReduction Power Meter Method correctly', function () {
        let inputData = {
            operatingHours: 8640,
            electricityCost: 0.12,
            measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.PowerMeter,
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
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        inputVec.push_back(inputData);

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 864000, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 103680, 0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate ElectricityReduction Other Method correctly', function () {
        let inputData = {
            operatingHours: 8640,
            electricityCost: 0.12,
            measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Other,
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
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        inputVec.push_back(inputData);

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 432000, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 51840, 0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate 5 ElectricityReductions (all methods) correctly', function () {
        let measurInputData = {
            electricityReductionInputVec: [
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Multimeter,
                    multimeterData: { numberOfPhases: 3, supplyVoltage: 800, averageCurrent: 40, powerFactor: 0.85 },
                    nameplateData: { ratedMotorPower: 100, variableSpeedMotor: false, operationalFrequency: 55, lineFrequency: 60, motorAndDriveEfficiency: 100, loadFactor: 1 },
                    powerMeterData: { power: 50 },
                    otherMethodData: { energy: 432000 },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Multimeter,
                    multimeterData: { numberOfPhases: 1, supplyVoltage: 800, averageCurrent: 40, powerFactor: 0.85 },
                    nameplateData: { ratedMotorPower: 100, variableSpeedMotor: false, operationalFrequency: 55, lineFrequency: 60, motorAndDriveEfficiency: 100, loadFactor: 1 },
                    powerMeterData: { power: 50 },
                    otherMethodData: { energy: 432000 },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Nameplate,
                    multimeterData: { numberOfPhases: 1, supplyVoltage: 800, averageCurrent: 40, powerFactor: 0.85 },
                    nameplateData: { ratedMotorPower: 100, variableSpeedMotor: false, operationalFrequency: 55, lineFrequency: 60, motorAndDriveEfficiency: 100, loadFactor: 1 },
                    powerMeterData: { power: 50 },
                    otherMethodData: { energy: 432000 },
                    units: 1
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.PowerMeter,
                    multimeterData: { numberOfPhases: 3, supplyVoltage: 800, averageCurrent: 40, powerFactor: 0.85 },
                    nameplateData: { ratedMotorPower: 100, variableSpeedMotor: false, operationalFrequency: 55, lineFrequency: 60, motorAndDriveEfficiency: 100, loadFactor: 1 },
                    powerMeterData: { power: 50 },
                    otherMethodData: { energy: 432000 },
                    units: 2
                },
                {
                    operatingHours: 8640,
                    electricityCost: 0.12,
                    measurementMethod: moduleInstance.ElectricityReductionMeasurementMethod.Other,
                    multimeterData: { numberOfPhases: 3, supplyVoltage: 800, averageCurrent: 40, powerFactor: 0.85 },
                    nameplateData: { ratedMotorPower: 100, variableSpeedMotor: false, operationalFrequency: 55, lineFrequency: 60, motorAndDriveEfficiency: 100, loadFactor: 1 },
                    powerMeterData: { power: 50 },
                    otherMethodData: { energy: 432000 },
                    units: 2
                }
            ]
        };

        let inputVec = new moduleInstance.ElectricityReductionInputV();
        for (let i = 0; i < measurInputData.electricityReductionInputVec.length; i++) {
            inputVec.push_back(measurInputData.electricityReductionInputVec[i]);
        }

        let results = moduleInstance.electricityReduction(inputVec);
        assert.approximately(results.energyUse, 1945004.716785, 0.001, 'energyUse');
        assert.approximately(results.energyCost, 233400.566012, 0.001, 'energyCost');
        inputVec.delete();
    });
});