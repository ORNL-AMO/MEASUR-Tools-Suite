import { assert } from 'chai';

describe('PumpFan OptimalSpecificSpeedCorrection', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate OptimalSpecificSpeedCorrection correctly', function () {
        let pumpStyle = moduleInstance.PumpStyle.END_SUCTION_SLURRY;
        let specificSpeed = 1170;
        let instance = new moduleInstance.OptimalSpecificSpeedCorrection(pumpStyle, specificSpeed);
        let achievableEfficiency = instance.calculate() * 100;
        instance.delete();
        assert.approximately(achievableEfficiency, 1.8942771852074485, .001, "achievableEfficiency");
    });
});