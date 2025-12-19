import { assert } from 'chai';

describe('Wall Type Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Wall Types Size', function () {
        let listItems = moduleInstance.getDefaultWallTypes();
        let count = listItems.size();
        assert.equal(count, 7, "Select All Default Data");
    });

    it('Wall Types First Entry', function () {
        let listItems = moduleInstance.getDefaultWallTypes();
        let firstWallType = listItems.get(0);
        assert.equal(firstWallType.wallDescription, "Horizontal cylinders", "Wall Description");
        assert.equal(firstWallType.shapeFactor, 1.016, "Shape Factor");
    });

    it('Wall Types Last Entry', function () {
        let listItems = moduleInstance.getDefaultWallTypes();
        let lastWallType = listItems.get(6);
        assert.equal(lastWallType.wallDescription, "Horizontal plate facing down, cooler than air", "Wall Description");
        assert.equal(lastWallType.shapeFactor, 1.79, "Shape Factor");
    });
});
