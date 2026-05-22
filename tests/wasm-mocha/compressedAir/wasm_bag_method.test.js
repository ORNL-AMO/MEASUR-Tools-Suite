import { assert } from 'chai';

describe('Compressed Air Leak Bag Method', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate leak flow rate and annual consumption', function () {
        const bagVolumeGal = 45;
        // Convert gallons to cubic feet for the module input
        const bagVolumeCuFt = bagVolumeGal * 0.133681;

        const inp = {
            operatingTime: 8760,
            bagFillTime: 50,
            bagVolume: bagVolumeCuFt,
            numberOfUnits: 1
        };

        const bagMethod = new moduleInstance.BagMethod(
            inp.operatingTime, inp.bagFillTime, inp.bagVolume, inp.numberOfUnits
        );
        const result = bagMethod.calculate();

        assert.approximately(result.flowRate, 7.219251337, 0.01);
        assert.approximately(result.annualConsumption, 3794.187614, 0.01);

        bagMethod.delete();
    });
});
