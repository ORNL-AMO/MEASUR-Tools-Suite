import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type MoverShaftPowerOutput } from 'measur-tools-suite';

describe('PumpFan Mover Shaft Power', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate moverShaftPower correctly', function () {
        const instance = new moduleInstance.MoverShaftPower(50, moduleInstance.Drive.N_V_BELT_DRIVE, 0);
        let output: MoverShaftPowerOutput | undefined;

        try {
            output = instance.calculate();
            assert.approximately(output.moverShaftPower, 48.4814329723, 0.001, "moverShaftPower");
        } finally {
            output?.delete();
            instance.delete();
        }
    });
});
