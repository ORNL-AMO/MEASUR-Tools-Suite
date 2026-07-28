import { assert } from 'chai';
import createModule, {
    type BagMethodInput,
    type BagMethodResult,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Bag Method', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate flow rate and annual consumption (45 gal bag, 50 s fill)', function () {
        const inp: BagMethodInput = {
            operatingTime: 8760,
            bagFillTime: 50,
            bagVolume: 45 * 0.133681
        };
        const result: BagMethodResult = moduleInstance.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 7.218774, 0.01);
        assert.approximately(result.annualConsumption, 3794.19, 0.1);
    });

    it('should calculate flow rate and annual consumption (8.68 ft³ bag, 12 s fill)', function () {
        const inp: BagMethodInput = {
            operatingTime: 8760,
            bagFillTime: 12,
            bagVolume: 8.68
        };
        const result: BagMethodResult = moduleInstance.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 43.4, 0.01);
        assert.approximately(result.annualConsumption, 22811.04, 0.1);
    });

    it('should calculate flow rate and annual consumption (12 ft³ bag, 10 s fill)', function () {
        const inp: BagMethodInput = {
            operatingTime: 15,
            bagFillTime: 10,
            bagVolume: 12
        };
        const result: BagMethodResult = moduleInstance.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 72.0, 0.01);
        assert.approximately(result.annualConsumption, 64.8, 0.01);
    });

    it('should scale annual consumption by numberOfUnits', function () {
        const inp: BagMethodInput = {
            operatingTime: 8760,
            bagFillTime: 10,
            bagVolume: 12
        };
        const result: BagMethodResult = moduleInstance.calculateBagMethod(inp);
        assert.approximately(result.flowRate, 72.0, 0.01);
        assert.approximately(result.annualConsumption, 37843.2, 0.1);
    });
});
