import { assert } from 'chai';
import createModule, { type AtmosphereGasTypeV, type MeasurToolsSuite, type AtmosphereGasType } from 'measur-tools-suite';

describe('Gas Type Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Gas Types Size', function () {
        const listItems: AtmosphereGasTypeV = moduleInstance.getDefaultGasTypes();
        assert.equal(listItems.size(), 6, "Select All Default Data");
        listItems.delete();
    });

    it('Gas Types First Entry', function () {
        const listItems: AtmosphereGasTypeV = moduleInstance.getDefaultGasTypes();
        const firstGasType: AtmosphereGasType = listItems.get(0);
        assert.equal(firstGasType.gasDescription, "Nitrogen", "Gas Description");
        assert.equal(firstGasType.specificHeat, 0.0185, "Specific Heat");
        listItems.delete();
    });

    it('Gas Types Last Entry', function () {
        const listItems: AtmosphereGasTypeV = moduleInstance.getDefaultGasTypes();
        const lastGasType: AtmosphereGasType = listItems.get(5);
        assert.equal(lastGasType.gasDescription, "Water Vapor", "Gas Description");
        assert.equal(lastGasType.specificHeat, 0.0212, "Specific Heat");
        listItems.delete();
    });
});

