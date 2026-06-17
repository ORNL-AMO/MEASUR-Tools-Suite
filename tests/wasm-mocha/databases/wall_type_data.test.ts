import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type WallType, type WallTypeV } from 'measur-tools-suite';

describe('Wall Type Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Wall Types Size', function () {
        const listItems: WallTypeV = moduleInstance.getDefaultWallTypes();
        assert.equal(listItems.size(), 7, "Select All Default Data");
        listItems.delete();
    });

    it('Wall Types First Entry', function () {
        const listItems: WallTypeV = moduleInstance.getDefaultWallTypes();
        const firstWallType: WallType = listItems.get(0);
        assert.equal(firstWallType.wallDescription, "Horizontal cylinders", "Wall Description");
        assert.equal(firstWallType.shapeFactor, 1.016, "Shape Factor");
        listItems.delete();
    });

    it('Wall Types Last Entry', function () {
        const listItems: WallTypeV = moduleInstance.getDefaultWallTypes();
        const lastWallType: WallType = listItems.get(6);
        assert.equal(lastWallType.wallDescription, "Horizontal plate facing down, cooler than air", "Wall Description");
        assert.equal(lastWallType.shapeFactor, 1.79, "Shape Factor");
        listItems.delete();
    });
});

