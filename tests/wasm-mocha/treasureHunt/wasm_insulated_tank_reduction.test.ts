import { assert } from 'chai';
import createModule, { type InsulatedTankInput, type InsulatedTankOutput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Insulated Tank Reduction Tests', function () {
    let m: MeasurToolsSuite;
    before(async function () {
        m = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function makeInput(data: InsulatedTankInput): InsulatedTankInput {
        return {
            operatingHours:         data.operatingHours,
            tankHeight:             data.tankHeight,
            tankDiameter:           data.tankDiameter,
            tankThickness:          data.tankThickness,
            tankEmissivity:         data.tankEmissivity,
            tankConductivity:       data.tankConductivity,
            tankTemperature:        data.tankTemperature,
            ambientTemperature:     data.ambientTemperature,
            systemEfficiency:       data.systemEfficiency,
            insulationThickness:    data.insulationThickness,
            insulationConductivity: data.insulationConductivity,
            jacketEmissivity:       data.jacketEmissivity,
            surfaceTemperature:     data.surfaceTemperature
        };
    }

    const baseInsulatedInput: InsulatedTankInput = {
        operatingHours:         8760,
        tankHeight:             10,
        tankDiameter:           5,
        tankThickness:          0.5,
        tankEmissivity:         0.8,
        tankConductivity:       46.2320,
        tankTemperature:        959.67,
        ambientTemperature:     529.67,
        systemEfficiency:       0.9,
        insulationThickness:    0.5,
        insulationConductivity: 0.0191,
        jacketEmissivity:       0.9,
        surfaceTemperature:     959.67
    };

    it('should calculate heat loss for an insulated tank (case 1)', function () {
        const result: InsulatedTankOutput = m.insulatedTankReduction(makeInput(baseInsulatedInput));
        assert.approximately(result.heatLoss,       0.0444638799, 0.0001, 'heatLoss');
        assert.approximately(result.annualHeatLoss, 43.278176,    0.01,   'annualHeatLoss');
    });

    it('should calculate heat loss for an insulated tank (case 2)', function () {
        const input = makeInput({
            operatingHours:         8760,
            tankHeight:             50,
            tankDiameter:           1,
            tankThickness:          0.25,
            tankEmissivity:         0.3,
            tankConductivity:       9.25,
            tankTemperature:        759.67,
            ambientTemperature:     539.67,
            systemEfficiency:       0.9,
            insulationThickness:    0.5,
            insulationConductivity: 0.0231,
            jacketEmissivity:       0.1,
            surfaceTemperature:     759.67
        });
        const result: InsulatedTankOutput = m.insulatedTankReduction(input);
        assert.approximately(result.heatLoss,       0.030515,  0.0001, 'heatLoss');
        assert.approximately(result.annualHeatLoss, 29.70135,  0.01,   'annualHeatLoss');
    });

    it('should calculate heat loss for a bare (uninsulated) tank', function () {
        const input = makeInput({
            ...baseInsulatedInput,
            insulationThickness:    0,
            insulationConductivity: 0
        });
        const result: InsulatedTankOutput = m.insulatedTankReduction(input);
        assert.approximately(result.heatLoss,       1.1112001223, 0.001, 'heatLoss');
        assert.approximately(result.annualHeatLoss, 1081.568119,  0.1,   'annualHeatLoss');
    });

    it('should match insulatedTankHeatLoss output when insulation is present', function () {
        const input    = makeInput(baseInsulatedInput);
        const fromCalc = m.insulatedTankReduction(input);
        const fromIns  = m.insulatedTankHeatLoss(input);
        assert.approximately(fromCalc.heatLoss,       fromIns.heatLoss,       0.0001, 'heatLoss');
        assert.approximately(fromCalc.annualHeatLoss, fromIns.annualHeatLoss, 0.01,   'annualHeatLoss');
    });

    it('should match bareTankHeatLoss output when no insulation', function () {
        const input    = makeInput({ ...baseInsulatedInput, insulationThickness: 0, insulationConductivity: 0 });
        const fromCalc = m.insulatedTankReduction(input);
        const fromBare = m.bareTankHeatLoss(input);
        assert.approximately(fromCalc.heatLoss,       fromBare.heatLoss,       0.001, 'heatLoss');
        assert.approximately(fromCalc.annualHeatLoss, fromBare.annualHeatLoss, 0.1,   'annualHeatLoss');
    });

    it('should compute the natural convection coefficient correctly', function () {
        // h = 0.125 * Ra^(1/3) * k / d
        // For Ra = 1e9, k = 0.015, d = 5: h = 0.125 * 1000 * 0.015 / 5 = 0.375
        const h = m.insulatedTankNaturalConvectionCoeff(1.0e9, 0.015, 5.0);
        assert.approximately(h, 0.375, 0.0001, 'naturalConvectionCoeff');
    });
});
