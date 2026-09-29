import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type SolidLoadChargeMaterial, type SolidLoadChargeMaterialV } from 'measur-tools-suite';

describe('Solid Load Charge Material Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Solid Load Charge Materials Size', function () {
        const listItems: SolidLoadChargeMaterialV = moduleInstance.getDefaultSolidLoadChargeMaterials();
        assert.equal(listItems.size(), 40, "Select All Default Data");
        listItems.delete();
    });

    it('Solid Load Charge Materials First Item', function () {
        const listItems: SolidLoadChargeMaterialV = moduleInstance.getDefaultSolidLoadChargeMaterials();
        const firstMaterial: SolidLoadChargeMaterial = listItems.get(0);
        assert.equal(firstMaterial.specificHeatSolid, 0.247910198232625, "Specific Heat Solid");
        assert.equal(firstMaterial.substance, "Aluminum", "Substance Name");
        assert.equal(firstMaterial.latentHeat, 169, "Latent Heat");
        assert.equal(firstMaterial.specificHeatLiquid, 0.2601, "Specific Heat Liquid");
        assert.equal(firstMaterial.meltingPoint, 1215, "Melting Point");
        listItems.delete();
    });
});
