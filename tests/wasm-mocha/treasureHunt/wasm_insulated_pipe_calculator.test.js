import { assert } from 'chai';

describe('Insulated Pipe Calculator Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function executeTest(measurInputData, expectedHeatLength, expectedAnnualHeatLoss) {

        let pipeMaterialCoefficients = new moduleInstance.DoubleVector();
        let insulationMaterialCoefficients = new moduleInstance.DoubleVector();
        measurInputData.pipeMaterialCoefficients.forEach(dblVal =>
            pipeMaterialCoefficients.push_back(dblVal));

        measurInputData.insulationMaterialCoefficients.forEach(dblVal =>
            insulationMaterialCoefficients.push_back(dblVal));
        let input = new moduleInstance.InsulatedPipeInput(measurInputData.operatingHours, measurInputData.pipeLength, measurInputData.pipeDiameter, measurInputData.pipeThickness,
            measurInputData.pipeTemperature, measurInputData.ambientTemperature, measurInputData.windVelocity, measurInputData.systemEfficiency, measurInputData.insulationThickness,
            measurInputData.pipeEmissivity, measurInputData.jacketEmissivity, pipeMaterialCoefficients, insulationMaterialCoefficients);
        let instance = new moduleInstance.InsulatedPipeReduction(input);
        let results = instance.calculate();
        assert.approximately(results.getHeatLength(), expectedHeatLength, .001, "heatLength");
        assert.approximately(results.getAnnualHeatLoss(), expectedAnnualHeatLoss, .001, "annualHeatLoss");

        instance.delete();
        input.delete();
        insulationMaterialCoefficients.delete();
        pipeMaterialCoefficients.delete();
    }

    it('should calculate InsulatedPipeCalculator (With Insulation) correctly', function () {
        let measurInputData = {
            operatingHours: 8640,
            pipeLength: 15.24,
            pipeDiameter: 0.025399,
            pipeThickness: 0.0033782,
            pipeTemperature: 422.039,
            ambientTemperature: 299.817,
            windVelocity: 0.89408,
            systemEfficiency: 90,
            insulationThickness: 0.0762,
            pipeEmissivity: 0.8000,
            jacketEmissivity: 0.1,
            pipeMaterialCoefficients: [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
            insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
        };
        executeTest(measurInputData, 19.385877, 28362.313687633672);
    });


    it('should calculate InsulatedPipeCalculator (No Insulation) correctly', function () {
        let measurInputData = {
            operatingHours: 8640,
            pipeLength: 15.24,
            pipeDiameter: 0.025399,
            pipeThickness: 0.0033782,
            pipeTemperature: 422.039,
            ambientTemperature: 299.817,
            windVelocity: 0.89408,
            systemEfficiency: 90,
            insulationThickness: -1,
            pipeEmissivity: 0.8000,
            jacketEmissivity: 0.1,
            pipeMaterialCoefficients: [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
            insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
        };
        executeTest(measurInputData, 278.8984025085, 408039.51880608);
    });
});