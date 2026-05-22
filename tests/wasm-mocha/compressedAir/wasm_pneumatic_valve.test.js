import { assert } from 'chai';

describe('Compressed Air Pneumatic Valve', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate flow rate without a specified flow rate (case 1)', function () {
        const inp = { inletPressure: 100, outletPressure: 70 };

        const pneumaticValve = new moduleInstance.PneumaticValve(inp.inletPressure, inp.outletPressure);
        const result = pneumaticValve.calculate();

        assert.approximately(result, 49.09732, 0.01);

        pneumaticValve.delete();
    });

    it('should calculate flow rate without a specified flow rate (case 2)', function () {
        const inp = { inletPressure: 120, outletPressure: 90 };

        const pneumaticValve = new moduleInstance.PneumaticValve(inp.inletPressure, inp.outletPressure);
        const result = pneumaticValve.calculate();

        assert.approximately(result, 54.568621, 0.01);

        pneumaticValve.delete();
    });

    it('should calculate Cv coefficient with a specified flow rate (case 1)', function () {
        // When a flow rate is provided, the valve calculates the Cv coefficient
        const inp = { inletPressure: 80, outletPressure: 75, flowRate: 55 };

        const pneumaticValve = new moduleInstance.PneumaticValve(
            inp.inletPressure, inp.outletPressure, inp.flowRate
        );
        const result = pneumaticValve.calculate();

        assert.approximately(result, 2.873685, 0.01);

        pneumaticValve.delete();
    });

    it('should calculate Cv coefficient with a specified flow rate (case 2)', function () {
        const inp = { inletPressure: 90, outletPressure: 85, flowRate: 95 };

        const pneumaticValve = new moduleInstance.PneumaticValve(
            inp.inletPressure, inp.outletPressure, inp.flowRate
        );
        const result = pneumaticValve.calculate();

        assert.approximately(result, 4.671398, 0.01);

        pneumaticValve.delete();
    });
});
