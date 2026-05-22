import { assert } from 'chai';

describe('Compressed Air Pipe Sizing', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate pipe cross-sectional area and diameter (case 1)', function () {
        const inp = {
            airFlow: 1000,
            airlinePressure: 90,
            designVelocity: 25,
            atmosphericPressure: 14.5
        };

        const pipeSizing = new moduleInstance.PipeSizing(
            inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure
        );
        const result = pipeSizing.calculate();

        assert.approximately(result.crossSectionalArea, 13.320574, 0.01);
        assert.approximately(result.pipeDiameter, 4.132512, 0.01);

        pipeSizing.delete();
    });

    it('should calculate pipe cross-sectional area and diameter (case 2)', function () {
        const inp = {
            airFlow: 1400,
            airlinePressure: 110,
            designVelocity: 30,
            atmosphericPressure: 11.5
        };

        const pipeSizing = new moduleInstance.PipeSizing(
            inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure
        );
        const result = pipeSizing.calculate();

        assert.approximately(result.crossSectionalArea, 10.600823, 0.01);
        assert.approximately(result.pipeDiameter, 3.68657, 0.01);

        pipeSizing.delete();
    });
});
