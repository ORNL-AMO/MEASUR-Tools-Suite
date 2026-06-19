import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type SolidLiquidFlueGasMaterial, type SolidLiquidFlueGasMaterialV } from 'measur-tools-suite';

describe('Solid Flue Gas Material Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Solid Liquid Flue Gas Materials Size', function () {
        const listItems: SolidLiquidFlueGasMaterialV = moduleInstance.getDefaultSolidLiquidFlueGasMaterials();
        assert.equal(listItems.size(), 6, "Select All Default Data");
        listItems.delete();
    });

    it('Solid Liquid Flue Gas Materials First Item', function () {
        const listItems: SolidLiquidFlueGasMaterialV = moduleInstance.getDefaultSolidLiquidFlueGasMaterials();
        const firstMaterial: SolidLiquidFlueGasMaterial = listItems.get(0);
        assert.equal(firstMaterial.substance, "Typical Bituminous Coal - US", "Substance Name");
        listItems.delete();
    });
});
