import { assert } from 'chai';

describe('PumpFan Mover Shaft Power', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate moverShaftPower correctly', function () {
        let instance = new moduleInstance.MoverShaftPower(50, moduleInstance.Drive.N_V_BELT_DRIVE, 0);
        let moverShaftPower = instance.calculate().moverShaftPower;
        instance.delete();
        assert.approximately(moverShaftPower, 48.4814329723, .001, "moverShaftPower");
    });
});