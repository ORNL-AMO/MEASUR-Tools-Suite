import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Atmosphere Heat Loss', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    // Test Atmosphere Gas Types
    it('should verify defined gas types are correct', function () {
        const gasTypes = moduleInstance.getDefaultGasTypes();

        // Expected gas types
        const expected: Array<[string, number]> = [
            ['Nitrogen', 0.0185],
            ['Hydrogen', 0.0182],
            ['Exothermic Gas', 0.0185],
            ['Endothermic Gas', 0.0185],
            ['Air', 0.0184],
            ['Water Vapor', 0.0212]
        ];

        try {
            // Assert the number of gas types
            assert.equal(gasTypes.size(), expected.length, 'gasTypes length mismatch');

            // Assert each gas type's description and specific heat
            expected.forEach(([description, specificHeat], i) => {
                assert.equal(gasTypes.get(i).gasDescription, description, `Gas description ${i} mismatch`);
                assert.equal(gasTypes.get(i).specificHeat, specificHeat, `Specific heat ${i} mismatch`);
            });
        } finally {
            gasTypes.delete();
        }
    });

    // Test Atmosphere Total Heat Loss Calculation
    it('should calculate the total heat loss for atmosphere', function () {
        // Input parameters
        const inp = {
            flowRate: 1200.0,
            specificHeat: 0.02,
            outletTemperature: 1400.0,
            inletTemperature: 100.0,
            correctionFactor: 1.0
        }

        // Calculate total heat loss
        const totalHeatLoss = moduleInstance.atmosphereTotalHeatLoss(
            inp.flowRate,
            inp.specificHeat,
            inp.inletTemperature,
            inp.outletTemperature,
            inp.correctionFactor
        );

        // Assert the result
        assert.equal(totalHeatLoss, 31200.0);
    });
});
