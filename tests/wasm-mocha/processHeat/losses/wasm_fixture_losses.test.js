import { assert } from 'chai';

describe('Process Heat FixtureLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate fixture heat loss correctly', function () {
        const specific_heat = 0.122;
        const feed_rate = 1250.0;
        const initial_temperature = 300.0;
        const final_temperature = 1800.0;
        const correction_factor = 1.0;

        const fixtureLosses = new moduleInstance.FixtureLosses(
            specific_heat,
            feed_rate,
            initial_temperature,
            final_temperature,
            correction_factor
        );
        const heat_loss = fixtureLosses.getHeatLoss();
        assert.strictEqual(heat_loss, 228750.0);
        fixtureLosses.delete();
    });
});
