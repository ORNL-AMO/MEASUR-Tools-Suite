import { assert } from 'chai';

describe('Compressed Air Pneumatic Valve', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    // ---- Flow Rate (Cv = 1) ----

    it('should calculate flow rate for Cv = 1 (case 1: 100 / 70 psia)', function () {
        const result = m.calculatePneumaticValveFlowRate({ inletPressure: 100, outletPressure: 70 });
        assert.approximately(result.flowRate, 49.097320446, 0.01);
    });

    it('should calculate flow rate for Cv = 1 (case 2: 120 / 90 psia)', function () {
        const result = m.calculatePneumaticValveFlowRate({ inletPressure: 120, outletPressure: 90 });
        assert.approximately(result.flowRate, 54.56862079, 0.01);
    });

    it('should calculate flow rate for Cv = 1 (case 3: 120 / 70 psia)', function () {
        const result = m.calculatePneumaticValveFlowRate({ inletPressure: 120, outletPressure: 70 });
        assert.approximately(result.flowRate, 67.00921112, 0.01);
    });

    // ---- Flow Coefficient (Cv) ----

    it('should calculate Cv coefficient (case 1: 80 / 75 psia, 55 scfm)', function () {
        const result = m.calculatePneumaticValveCv({ inletPressure: 80, outletPressure: 75, flowRate: 55 });
        assert.approximately(result.flowCoefficient, 2.873684832, 0.01);
    });

    it('should calculate Cv coefficient (case 2: 90 / 85 psia, 95 scfm)', function () {
        const result = m.calculatePneumaticValveCv({ inletPressure: 90, outletPressure: 85, flowRate: 95 });
        assert.approximately(result.flowCoefficient, 4.671398062, 0.01);
    });

    it('should calculate Cv coefficient (case 3: 90 / 75 psia, 55 scfm)', function () {
        const result = m.calculatePneumaticValveCv({ inletPressure: 90, outletPressure: 75, flowRate: 55 });
        assert.approximately(result.flowCoefficient, 1.608060504, 0.01);
    });

    it('should calculate Cv coefficient (case 4: 90 / 85 psia, 55 scfm)', function () {
        const result = m.calculatePneumaticValveCv({ inletPressure: 90, outletPressure: 85, flowRate: 55 });
        assert.approximately(result.flowCoefficient, 2.7044936151, 0.01);
    });
});
