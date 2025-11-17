import { assert } from 'chai';

describe('Insulated Tank Calculator Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    function executeTest(measurInputData, expectedHeatLoss, expectedAnnualHeatLoss) {
        let insulatedTankInput = new moduleInstance.InsulatedTankInput(
            measurInputData.operatingHours,
            measurInputData.tankHeight,
            measurInputData.tankDiameter,
            measurInputData.tankThickness,
            measurInputData.tankEmissivity,
            measurInputData.tankConductivity,
            measurInputData.tankTemperature,
            measurInputData.ambientTemperature,
            measurInputData.systemEfficiency,
            measurInputData.insulationThickness,
            measurInputData.insulationConductivity,
            measurInputData.jacketEmissivity,
            measurInputData.surfaceTemperature);
        let instance = new moduleInstance.InsulatedTankReduction(insulatedTankInput);
        let results = instance.calculate();
        assert.approximately(results.getHeatLoss(), expectedHeatLoss, .001, "heatLoss");
        assert.approximately(results.getAnnualHeatLoss(), expectedAnnualHeatLoss, .001, "annualHeatLoss");

        instance.delete();
        insulatedTankInput.delete();
    }

    it('should calculate InsulatedTankCalculator (With Insulation) correctly', function () {
        let measurInputData = {
            operatingHours: 8760,
            tankHeight: 10,
            tankDiameter: 5,
            tankThickness: 0.5,
            tankEmissivity: 0.8,
            tankConductivity: 46.2320,
            tankTemperature: 959.67,
            ambientTemperature: 529.67,
            systemEfficiency: 90,
            insulationThickness: 0.5,
            insulationConductivity: 0.0191,
            jacketEmissivity: 0.9,
            surfaceTemperature: 959.67
        };
        executeTest(measurInputData, 0.044464, 0.43278176);
    });


    it('should calculate InsulatedTankCalculator (With Insulation #2) correctly', function () {
        let measurInputData = {
            operatingHours: 8760,
            tankHeight: 50,
            tankDiameter: 1,
            tankThickness: 0.25,
            tankEmissivity: 0.3,
            tankConductivity: 9.25,
            tankTemperature: 759.67,
            ambientTemperature: 539.67,
            systemEfficiency: 90,
            insulationThickness: 0.5,
            insulationConductivity: 0.0231,
            jacketEmissivity: 0.1,
            surfaceTemperature: 759.67
        };
        executeTest(measurInputData, 0.030515, 0.29701354);
    });

    it('should calculate InsulatedTankCalculator (No Insulation) correctly', function () {
        let measurInputData = {
            operatingHours: 8760,
            tankHeight: 10,
            tankDiameter: 5,
            tankThickness: 0.5,
            tankEmissivity: 0.8,
            tankConductivity: 46.2320,
            tankTemperature: 959.67,
            ambientTemperature: 529.67,
            systemEfficiency: 90,
            insulationThickness: 0,
            insulationConductivity: 0,
            jacketEmissivity: 0.9,
            surfaceTemperature: 959.67
        };
        executeTest(measurInputData, 1.1112001223, 10.81568119);
    });
});