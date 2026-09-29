import { assert } from 'chai';
import createModule, { type LiquidLoadChargeMaterial, type LiquidLoadChargeMaterialV, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Liquid Load Charge Material Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Liquid Load Charge Materials Size', function () {
        const listItems: LiquidLoadChargeMaterialV = moduleInstance.getDefaultLiquidLoadChargeMaterials();
        assert.equal(listItems.size(), 13, "Select All Default Data");
        listItems.delete();
    });

    it('Liquid Load Charge Materials First Item', function () {
        const listItems: LiquidLoadChargeMaterialV = moduleInstance.getDefaultLiquidLoadChargeMaterials();
        const firstMaterial: LiquidLoadChargeMaterial = listItems.get(0);
        assert.equal(firstMaterial.specificHeat, 0.6501, "Specific Heat");
        assert.equal(firstMaterial.substance, "Crude", "Substance Name");
        assert.equal(firstMaterial.latentHeat, 105, "Latent Heat");
        assert.equal(firstMaterial.vaporSpecificHeat, 0.55, "Vapor Specific Heat");
        assert.equal(firstMaterial.boilingPoint, 900, "Boiling Point");
        listItems.delete();
    });
});
