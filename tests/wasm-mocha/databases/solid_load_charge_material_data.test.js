import { assert } from 'chai';

describe('Solid Load Charge Material Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Solid Load Charge Materials Size', function () {
        let listItems = moduleInstance.getDefaultSolidLoadChargeMaterials();
        let count = listItems.size();
        assert.equal(count, 40, "Select All Default Data");
    });

    it('Solid Load Charge Materials First Item', function () {
        let listItems = moduleInstance.getDefaultSolidLoadChargeMaterials();
        let firstMaterial = listItems.get(0);
        //specificHeatSolid
        assert.equal(firstMaterial.specificHeatSolid, 0.247910198232625, "Specific Heat Solid");
        //substance
        assert.equal(firstMaterial.substance, "Aluminum", "Substance Name");
        //latentHeat
        assert.equal(firstMaterial.latentHeat, 169, "Latent Heat");
        //specificHeatLiquid
        assert.equal(firstMaterial.specificHeatLiquid, 0.2601, "Specific Heat Liquid");
        //meltingPoint
        assert.equal(firstMaterial.meltingPoint, 1215, "Melting Point");
    });
});