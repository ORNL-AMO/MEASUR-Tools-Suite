import { assert } from 'chai';

describe('Compressed Air Pipe Sizing', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate cross-sectional area and diameter (1000 cfm, 90 psig, 25 ft/s)', function () {
        const inp = { airflow: 1000, airlinePressure: 90, designVelocity: 25, atmosphericPressure: 14.5 };
        const result = m.calculatePipeSize(inp);
        assert.approximately(result.crossSectionalArea, 13.3205741627, 0.01);
        assert.approximately(result.pipeDiameter,        4.1325124540, 0.01);
    });

    it('should calculate cross-sectional area and diameter (1400 cfm, 90 psig, 25 ft/s)', function () {
        const inp = { airflow: 1400, airlinePressure: 90, designVelocity: 25, atmosphericPressure: 14.5 };
        const result = m.calculatePipeSize(inp);
        assert.approximately(result.crossSectionalArea, 18.6488038278, 0.01);
        assert.approximately(result.pipeDiameter,        4.8896546766, 0.01);
    });

    it('should calculate cross-sectional area and diameter (1400 cfm, 110 psig, 25 ft/s)', function () {
        const inp = { airflow: 1400, airlinePressure: 110, designVelocity: 25, atmosphericPressure: 14.5 };
        const result = m.calculatePipeSize(inp);
        assert.approximately(result.crossSectionalArea, 15.6530120482, 0.01);
        assert.approximately(result.pipeDiameter,        4.4797281351, 0.01);
    });

    it('should calculate cross-sectional area and diameter (1400 cfm, 110 psig, 30 ft/s)', function () {
        const inp = { airflow: 1400, airlinePressure: 110, designVelocity: 30, atmosphericPressure: 14.5 };
        const result = m.calculatePipeSize(inp);
        assert.approximately(result.crossSectionalArea, 13.0441767068, 0.01);
        assert.approximately(result.pipeDiameter,        4.0894135851, 0.01);
    });

    it('should calculate cross-sectional area and diameter (1400 cfm, 110 psig, 30 ft/s, 11.5 psia)', function () {
        const inp = { airflow: 1400, airlinePressure: 110, designVelocity: 30, atmosphericPressure: 11.5 };
        const result = m.calculatePipeSize(inp);
        assert.approximately(result.crossSectionalArea, 10.6008230453, 0.01);
        assert.approximately(result.pipeDiameter,        3.6865700558, 0.01);
    });
});
