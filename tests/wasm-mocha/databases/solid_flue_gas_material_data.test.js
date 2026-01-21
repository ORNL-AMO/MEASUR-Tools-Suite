import { assert } from 'chai';

describe('Solid Flue Gas Material Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Solid Liquid Flue Gas Materials Size', function () {
        let listItems = moduleInstance.getDefaultSolidLiquidFlueGasMaterials();
        let count = listItems.size();
        assert.equal(count, 6, "Select All Default Data");
    });

    it('Solid Liquid Flue Gas Materials First Item', function () {
        let listItems = moduleInstance.getDefaultSolidLiquidFlueGasMaterials();
        let firstMaterial = listItems.get(0);
        assert.equal(firstMaterial.substance, "Typical Bituminous Coal - US", "Substance Name");
    });
});