import { assert } from 'chai';

describe('Process Wall Heat Loss', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should verify defined shape factors are correct', function () {
        const shapeFactors = moduleInstance.shapeFactors();

        // Expected shape factors
        const expected = [
            ['Horizontal cylinders', 1.016],
            ['Longer vertical cylinders', 1.235],
            ['Vertical plates', 1.394],
            ['Horizontal plate facing up, warmer than air', 1.79],
            ['Horizontal plate facing down, warmer than air', 0.89],
            ['Horizontal plate facing up, cooler than air', 0.89],
            ['Horizontal plate facing down, cooler than air', 1.79],
        ];

        // Assert the number of shape factors
        assert.equal(shapeFactors.size(), expected.length, 'shapeFactors length mismatch');

        // Assert each shape factor's description and value
        expected.forEach(([desc, factor], i) => {
            assert.equal(shapeFactors.get(i).surfaceConfiguration, desc, `Configuration description ${i} mismatch`);
            assert.equal(shapeFactors.get(i).value, factor, `Shape factor ${i} mismatch`);
        });
    });

    it('should calculate the total heat loss for a wall (convective & radiative)', function () {
        // Input parameters
        const inp = {
            surfaceArea: 500,
            ambientTemperature: 80,
            surfaceTemperature: 225,
            windSpeed: 10,
            surfaceEmissivity: 0.9,
            shapeFactor: 1.394,
            correctionFactor: 1
        };

        // Calculate total heat loss
        const totalHeatLoss = moduleInstance.totalHeatLoss(
            inp.surfaceArea,
            inp.ambientTemperature,
            inp.surfaceTemperature,
            inp.windSpeed,
            inp.surfaceEmissivity,
            inp.shapeFactor,
            inp.correctionFactor
        );

        // Assert the result
        assert.equal(totalHeatLoss, 404487.58875827474, 'Incorrect total heat loss');
    });
});