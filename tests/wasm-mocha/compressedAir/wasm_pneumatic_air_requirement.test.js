import { assert } from 'chai';

describe('Compressed Air Pneumatic Air Requirement', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    // ---- Single-Acting Piston ----

    it('should calculate air requirement for a single-acting piston (1.5 in bore, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 6, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementSingleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           0.36816, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 2.87261, 0.001);
    });

    it('should calculate air requirement for a single-acting piston (3.5 in bore, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 3.5, cylinderStroke: 6, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementSingleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           2.00440, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 15.6398, 0.01);
    });

    it('should calculate air requirement for a single-acting piston (9 in stroke, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 9, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementSingleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           0.55223, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 4.30892, 0.001);
    });

    it('should calculate air requirement for a single-acting piston (140 psi, 90 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 6, airPressure: 140, cyclesPerMin: 90 };
        const result = m.calculatePneumaticAirRequirementSingleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           0.55223, 0.001);
        assert.approximately(result.compressionRatio,                10.5238, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 5.81159, 0.001);
    });

    // ---- Double-Acting Piston ----

    it('should calculate air requirement for a double-acting piston (1.5 in bore, 0.375 in rod, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 6, pistonRodDiameter: 0.375, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementDoubleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           0.71330, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 5.56569, 0.001);
    });

    it('should calculate air requirement for a double-acting piston (3.5 in bore, 0.375 in rod, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 3.5, cylinderStroke: 6, pistonRodDiameter: 0.375, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementDoubleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           3.98579, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 31.1000, 0.01);
    });

    it('should calculate air requirement for a double-acting piston (9 in stroke, 0.375 in rod, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 9, pistonRodDiameter: 0.375, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementDoubleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           1.06995, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 8.34853, 0.001);
    });

    it('should calculate air requirement for a double-acting piston (0.575 in rod, 100 psi, 60 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 6, pistonRodDiameter: 0.575, airPressure: 100, cyclesPerMin: 60 };
        const result = m.calculatePneumaticAirRequirementDoubleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           0.68231, 0.001);
        assert.approximately(result.compressionRatio,                7.80272, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 5.32389, 0.001);
    });

    it('should calculate air requirement for a double-acting piston (0.575 in rod, 140 psi, 90 cpm)', function () {
        const inp = { cylinderDiameter: 1.5, cylinderStroke: 6, pistonRodDiameter: 0.575, airPressure: 140, cyclesPerMin: 90 };
        const result = m.calculatePneumaticAirRequirementDoubleActing(inp);
        assert.approximately(result.volumeAirIntakePiston,           1.02332, 0.001);
        assert.approximately(result.compressionRatio,                10.5238, 0.001);
        assert.approximately(result.airRequirementPneumaticCylinder, 10.7692, 0.001);
    });
});
