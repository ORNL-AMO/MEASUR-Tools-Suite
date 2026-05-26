import { assert } from 'chai';

describe('Insulated Pipe Reduction Tests', function () {
    let m;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function makeInput(data) {
        let pipeMaterialCoefficients       = new m.DoubleVector();
        let insulationMaterialCoefficients = new m.DoubleVector();
        data.pipeMaterialCoefficients.forEach(v => pipeMaterialCoefficients.push_back(v));
        data.insulationMaterialCoefficients.forEach(v => insulationMaterialCoefficients.push_back(v));

        let input = {
            operatingHours:                data.operatingHours,
            pipeLength:                    data.pipeLength,
            pipeDiameter:                  data.pipeDiameter,
            pipeThickness:                 data.pipeThickness,
            pipeTemperature:               data.pipeTemperature,
            ambientTemperature:            data.ambientTemperature,
            windVelocity:                  data.windVelocity,
            systemEfficiency:              data.systemEfficiency,
            insulationThickness:           data.insulationThickness,
            pipeEmissivity:                data.pipeEmissivity,
            jacketEmissivity:              data.jacketEmissivity,
            pipeMaterialCoefficients,
            insulationMaterialCoefficients
        };
        return { input, pipeMaterialCoefficients, insulationMaterialCoefficients };
    }

    it('should calculate heat loss for an insulated pipe correctly', function () {
        let { input, pipeMaterialCoefficients, insulationMaterialCoefficients } = makeInput({
            operatingHours:                8640,
            pipeLength:                    15.24,
            pipeDiameter:                  0.025399,
            pipeThickness:                 0.0033782,
            pipeTemperature:               422.039,
            ambientTemperature:            299.817,
            windVelocity:                  0.89408,
            systemEfficiency:              0.9,
            insulationThickness:           0.0762,
            pipeEmissivity:                0.8,
            jacketEmissivity:              0.1,
            pipeMaterialCoefficients:       [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
            insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
        });

        let result = m.insulatedPipeReduction(input);
        assert.approximately(result.heatLossPerLength, 19.385877,        0.001, 'heatLossPerLength');
        assert.approximately(result.annualHeatLoss,    2836231.3687633, 1.0,   'annualHeatLoss');

        pipeMaterialCoefficients.delete();
        insulationMaterialCoefficients.delete();
    });

    it('should calculate heat loss for a bare (uninsulated) pipe correctly', function () {
        let { input, pipeMaterialCoefficients, insulationMaterialCoefficients } = makeInput({
            operatingHours:                8640,
            pipeLength:                    15.24,
            pipeDiameter:                  0.025399,
            pipeThickness:                 0.0033782,
            pipeTemperature:               422.039,
            ambientTemperature:            299.817,
            windVelocity:                  0.89408,
            systemEfficiency:              0.9,
            insulationThickness:           -1,
            pipeEmissivity:                0.8,
            jacketEmissivity:              0.1,
            pipeMaterialCoefficients:       [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
            insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
        });

        let result = m.insulatedPipeReduction(input);
        assert.approximately(result.heatLossPerLength, 278.8984025085, 0.001, 'heatLossPerLength');
        assert.approximately(result.annualHeatLoss,    40803955.00651534,    1.0,   'annualHeatLoss');

        pipeMaterialCoefficients.delete();
        insulationMaterialCoefficients.delete();
    });

    it('should compute the Reynolds number correctly', function () {
        assert.approximately(
            m.insulatedPipeReynoldsNumber(0.1778, 0.89408, 0.0000159),
            9997.951, 0.01, 'reynoldsNumber'
        );
    });

    it('should compute the Rayleigh number correctly', function () {
        assert.approximately(
            m.insulatedPipeRayleighNumber(0.003329819, 300.817, 299.817, 0.177799, 0.0000159, 0.0000225),
            513213.337, 0.1, 'rayleighNumber'
        );
    });

    it('should compute the radiative heat transfer coefficient correctly', function () {
        assert.approximately(
            m.insulatedPipeRadiativeHeatTransferCoeff(0.1, 300.817, 299.817),
            0.6143453478, 0.0001, 'radiativeHTC'
        );
    });

    it('should compute the convective heat transfer coefficient correctly', function () {
        assert.approximately(
            m.insulatedPipeConvectiveHeatTransferCoeff(32.8, 0.02534, 0.13335),
            6.2328608924, 0.0001, 'convectiveHTC'
        );
    });
});
