const path = require('path');
const assert = require('chai').assert;

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat FixtureLosses', function () {
    let ToolsSuiteModule;

    before(async function () {
        const createModule = (await import(clientPath)).default;
        ToolsSuiteModule = await createModule({
            locateFile: (filename) => {
                if (filename.endsWith('.wasm')) {
                    return wasmPath;
                }
                return filename;
            }
        });
    });

    it('should calculate fixture heat loss correctly', function () {
        const specific_heat = 0.122;
        const feed_rate = 1250.0;
        const initial_temperature = 300.0;
        const final_temperature = 1800.0;
        const correction_factor = 1.0;

        const fixtureLosses = new ToolsSuiteModule.FixtureLosses(
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
