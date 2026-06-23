import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Compressed Air Assessment - Compressor EEMs', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates leak reduction and end-use efficiency results as plain objects', function () {
        const leak = moduleInstance.reduceAirLeaks(473, 100, 10, 0.5);
        assert.approximately(leak.reducedLeakAirflowAcfm, 5, 0.001);
        assert.approximately(leak.adjustedUseAirflowAcfm, 95, 0.001);
        assert.approximately(leak.adjustedUseFraction, 0.20084, 0.005);

        const efficiency = moduleInstance.improveEndUseEfficiency(473, 236, 20);
        assert.approximately(efficiency.reducedAirflowAcfm, 216, 0.001);
        assert.approximately(efficiency.reducedAirflowFraction, 0.45666, 0.0001);
    });

    it('calculates pressure reduction, cascading set point, and savings results', function () {
        const pressure = moduleInstance.reduceSystemAirPressure(473, 100, 100, 85.4, 5, 14.7, 14.7);
        assert.approximately(pressure.adjustedFullLoadPressurePsig, 95, 0.001);
        assert.approximately(pressure.adjustedFullLoadPowerKw, 82.972, 0.001);
        assert.approximately(pressure.adjustedUseAirflowAcfm, 97.384, 0.001);
        assert.approximately(pressure.adjustedUseFraction, 0.2059, 0.005);

        const setPoint = moduleInstance.adjustCascadingSetPoint(2578, 1000, 100, 414.4, 105, 14.7, 14.7);
        assert.approximately(setPoint.adjustedFullLoadPowerKw, 425.82, 0.01);
        assert.approximately(setPoint.adjustedUseAirflowAcfm, 1026.16, 0.01);
        assert.approximately(setPoint.adjustedUseFraction, 0.39804313, 0.0001);

        const savings = moduleInstance.pressureReductionSaving(8760, 0.066, 75, 125, 110, 100, 14.7, 14.7);
        assert.approximately(savings.powerSavingsKw, 3.6031, 0.0001);
        assert.approximately(savings.energySavingsKwh, 31563.3423, 0.01);
        assert.approximately(savings.costSavings, 2083.18, 0.01);

        assert.approximately(moduleInstance.adjustedPower(75, 125, 110, 14.7, 14.7), 69.9653, 0.0001);
        assert.approximately(moduleInstance.pressureReducedAirflow(1000, 95, 14.7, 100, 14.7), 973.8448, 0.001);
    });

    it('calculates reusable receiver and sequencer transforms', function () {
        const receiver = moduleInstance.addReceiverVolume(140, 50);
        assert.approximately(receiver.addedReceiverVolumeFt3, 50, 0.001);
        assert.approximately(receiver.totalReceiverVolumeFt3, 190, 0.001);

        const sequencer = moduleInstance.automaticSequencerSetPoints(100, 4);
        assert.approximately(sequencer.fullLoadPressurePsig, 96, 0.001);
        assert.approximately(sequencer.upperPressurePsig, 104, 0.001);
    });
});
