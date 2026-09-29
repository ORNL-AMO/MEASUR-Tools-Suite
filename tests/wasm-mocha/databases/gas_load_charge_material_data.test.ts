import { assert } from 'chai';
import createModule, { type GasLoadChargeMaterial, type GasLoadChargeMaterialV, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Gas Load Charge Material Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Gas Load Charge Materials Size', function () {
        const listItems: GasLoadChargeMaterialV = moduleInstance.getDefaultGasLoadChargeMaterials();
        assert.equal(listItems.size(), 10, "Select All Default Data");
        listItems.delete();
    });

    it('Gas Load Charge Materials First Entry', function () {
        const listItems: GasLoadChargeMaterialV = moduleInstance.getDefaultGasLoadChargeMaterials();
        const firstMaterial: GasLoadChargeMaterial = listItems.get(0);
        assert.equal(firstMaterial.specificHeatVapor, 0.47, "Specific Heat Vapor");
        assert.equal(firstMaterial.substance, "Water vapor - Near Atm. Pressure", "Substance Name");
        listItems.delete();
    });
});
