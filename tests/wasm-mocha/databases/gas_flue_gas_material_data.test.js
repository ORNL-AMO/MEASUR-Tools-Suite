import { assert } from 'chai';

describe('Gas Flue Gas Material Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Gas Flue Gas Materials Size', function () {
        let listItems = moduleInstance.getDefaultGasFlueGasMaterials();
        let count = listItems.size();
        assert.equal(count, 4, "Select All Default Data");
    });

    it('Gas Flue Gas Materials First Item', function () {
        let listItems = moduleInstance.getDefaultGasFlueGasMaterials();
        let firstMaterial = listItems.get(0);
        assert.equal(firstMaterial.substance, "Typical Natural Gas - US", "Substance Name");
    });
});