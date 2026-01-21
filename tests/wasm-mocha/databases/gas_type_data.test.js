import { assert } from 'chai';

describe('Gas Type Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Gas Types Size', function () {
        let listItems = moduleInstance.getDefaultGasTypes();
        let count = listItems.size();
        assert.equal(count, 6, "Select All Default Data");
    });

    it('Gas Types First Entry', function () {
        let listItems = moduleInstance.getDefaultGasTypes();
        let firstGasType = listItems.get(0);
        assert.equal(firstGasType.gasDescription, "Nitrogen", "Gas Description");
        assert.equal(firstGasType.specificHeat, 0.0185, "Specific Heat");
    });

    it('Gas Types Last Entry', function () {
        let listItems = moduleInstance.getDefaultGasTypes();
        let lastGasType = listItems.get(5);
        assert.equal(lastGasType.gasDescription, "Water Vapor", "Gas Description");
        assert.equal(lastGasType.specificHeat, 0.0212, "Specific Heat");
    });
});
