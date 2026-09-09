import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PositiveDisplacementPumpOutput } from 'measur-tools-suite';

describe('PositiveDisplacementPump', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates pump power and annual energy use', function () {
        const instance = new moduleInstance.PositiveDisplacementPump(100, 50, 0.8, 2000);
        let results: PositiveDisplacementPumpOutput | undefined;

        try {
            results = instance.calculate();

            assert.approximately(results.power, 2.7198784761, 0.000001, 'power');
            assert.approximately(results.energy, 5439.75695224, 0.000001, 'energy');
        } finally {
            results?.delete();
            instance.delete();
        }
    });
});
