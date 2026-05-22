import { assert } from 'chai';

describe('Compressed Air Pneumatic Air Requirement', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate air requirement for a single-acting piston', function () {
        const inp = {
            pistonType: moduleInstance.PistonType.SingleActing,
            cylinderDiameter: 1.5,
            cylinderStroke: 6,
            airPressure: 100,
            cyclesPerMinute: 60
        };

        const pneumaticAirReq = new moduleInstance.PneumaticAirRequirement(
            inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke,
            inp.airPressure, inp.cyclesPerMinute
        );
        const result = pneumaticAirReq.calculate();

        assert.approximately(result.volumeAirIntakePiston, 0.367969, 0.01);
        assert.approximately(result.compressionRatio, 7.802721, 0.01);
        assert.approximately(result.airRequirementPneumaticCylinder, 2.871158, 0.01);

        pneumaticAirReq.delete();
    });

    it('should calculate air requirement for a double-acting piston', function () {
        const inp = {
            pistonType: moduleInstance.PistonType.DoubleActing,
            cylinderDiameter: 1.5,
            cylinderStroke: 6,
            pistonRodDiameter: 0.375,
            airPressure: 100,
            cyclesPerMinute: 60
        };

        // Double-acting pistons require the piston rod diameter as an additional parameter
        const pneumaticAirReq = new moduleInstance.PneumaticAirRequirement(
            inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke,
            inp.pistonRodDiameter, inp.airPressure, inp.cyclesPerMinute
        );
        const result = pneumaticAirReq.calculate();

        assert.approximately(result.volumeAirIntakePiston, 0.712939, 0.01);
        assert.approximately(result.compressionRatio, 7.802721, 0.01);
        assert.approximately(result.airRequirementPneumaticCylinder, 5.562868, 0.01);

        pneumaticAirReq.delete();
    });
});
