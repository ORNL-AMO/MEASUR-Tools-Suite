import { assert } from 'chai';
import createModule, { GasFlueGasMaterialV, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Gas Flue Gas Material Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Gas Flue Gas Materials Size', function () {
        const listItems: GasFlueGasMaterialV = moduleInstance.getDefaultGasFlueGasMaterials();
        assert.equal(listItems.size(), 4, "Select All Default Data");
        listItems.delete();
    });

    it('Gas Flue Gas Materials First Item', function () {
        const listItems: GasFlueGasMaterialV = moduleInstance.getDefaultGasFlueGasMaterials();
        assert.equal(listItems.get(0).substance, "Typical Natural Gas - US", "Substance Name");
        listItems.delete();
    });
});