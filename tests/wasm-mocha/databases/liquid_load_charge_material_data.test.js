import { assert } from 'chai';

describe('Liquid Load Charge Material Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Liquid Load Charge Materials Size', function () {
        let listItems = moduleInstance.getDefaultLiquidLoadChargeMaterials();
        let count = listItems.size();
        assert.equal(count, 13, "Select All Default Data");
    });

    it('Liquid Load Charge Materials First Item', function () {
        let listItems = moduleInstance.getDefaultLiquidLoadChargeMaterials();
        let firstMaterial = listItems.get(0);
        //specificHeat
        assert.equal(firstMaterial.specificHeat, 0.6501, "Specific Heat");
        //substance
        assert.equal(firstMaterial.substance, "Crude", "Substance Name");
        //latentHeat
        assert.equal(firstMaterial.latentHeat, 105, "Latent Heat");
        //vaporSpecificHeat
        assert.equal(firstMaterial.vaporSpecificHeat, 0.55, "Vapor Specific Heat");
        //boilingPoint
        assert.equal(firstMaterial.boilingPoint, 900, "Boiling Point");
    });
});