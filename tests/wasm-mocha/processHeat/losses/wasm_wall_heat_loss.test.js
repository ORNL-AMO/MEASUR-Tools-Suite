import { assert } from 'chai';

describe('Process Wall Heat Loss', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should verify defined wall types are correct', function () {
        const wallTypes = moduleInstance.getDefaultWallTypes();

        // Expected wall types and their shape factors
        const expected = [
            ['Horizontal cylinders', 1.016],
            ['Longer vertical cylinders', 1.235],
            ['Vertical plates', 1.394],
            ['Horizontal plate facing up, warmer than air', 1.79],
            ['Horizontal plate facing down, warmer than air', 0.89],
            ['Horizontal plate facing up, cooler than air', 0.89],
            ['Horizontal plate facing down, cooler than air', 1.79],
        ];

        // Assert the number of wall types
        assert.equal(wallTypes.size(), expected.length, 'wallTypes length mismatch');

        // Assert each shape factor's description and value
        expected.forEach(([description, factor], i) => {
            assert.equal(wallTypes.get(i).wallDescription, description, `Wall description ${i} mismatch`);
            assert.equal(wallTypes.get(i).shapeFactor, factor, `Shape factor ${i} mismatch`);
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
        const totalHeatLoss = moduleInstance.wallTotalHeatLoss(
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