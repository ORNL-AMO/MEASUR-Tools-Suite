import { assert } from 'chai';

describe('Gas Load Charge Material Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Gas Load Charge Materials Size', function () {
        let listItems = moduleInstance.getDefaultGasLoadChargeMaterials();
        let count = listItems.size();
        assert.equal(count, 10, "Select All Default Data");
    });

    it('Gas Load Charge Materials Size', function () {
        let listItems = moduleInstance.getDefaultGasLoadChargeMaterials();
        let firstMaterial = listItems.get(0);
        assert.equal(firstMaterial.specificHeatVapor, 0.47, "Specific Heat Vapor");
        assert.equal(firstMaterial.substance, "Water vapor - Near Atm. Pressure", "Substance Name");
    });
});