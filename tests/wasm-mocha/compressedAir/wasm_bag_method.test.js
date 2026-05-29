import { assert } from 'chai';

describe('Compressed Air Bag Method', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate flow rate and annual consumption (45 gal bag, 50 s fill)', function () {
        // 45 gal * 0.133681 ft³/gal = 6.015645 ft³
        const inp = {
            operatingTime: 8760,
            bagFillTime: 50,
            bagVolume: 45 * 0.133681,
            numberOfUnits: 1
        };
        const result = m.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 7.218774, 0.01);
        assert.approximately(result.annualConsumption, 3794.19, 0.1);
    });

    it('should calculate flow rate and annual consumption (8.68 ft³ bag, 12 s fill)', function () {
        const inp = {
            operatingTime: 8760,
            bagFillTime: 12,
            bagVolume: 8.68,
            numberOfUnits: 1
        };
        const result = m.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 43.4, 0.01);
        assert.approximately(result.annualConsumption, 22811.04, 0.1);
    });

    it('should calculate flow rate and annual consumption (12 ft³ bag, 10 s fill)', function () {
        const inp = {
            operatingTime: 15,
            bagFillTime: 10,
            bagVolume: 12,
            numberOfUnits: 1
        };
        const result = m.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 72.0, 0.01);
        assert.approximately(result.annualConsumption, 64.8, 0.01);
    });

    it('should scale annual consumption by numberOfUnits', function () {
        const inp = {
            operatingTime: 8760,
            bagFillTime: 10,
            bagVolume: 12,
            numberOfUnits: 3
        };
        const result = m.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 72.0, 0.01);
        assert.approximately(result.annualConsumption, 113529.6, 0.1);
    });
});
