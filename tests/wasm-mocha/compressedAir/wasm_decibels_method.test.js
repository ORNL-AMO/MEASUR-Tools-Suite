import { assert } from 'chai';

describe('Compressed Air Leak Decibels Method', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate leak rate estimate and annual consumption from decibel readings', function () {
        // Two reference points (A and B) bracketing the measured decibel level are used
        // to interpolate the actual leak rate at the measured line pressure
        const inp = {
            operatingTime: 1280,
            linePressure: 130,
            decibels: 25,
            decibelRatingA: 20,
            pressureA: 150,
            firstFlowA: 1.04,
            secondFlowA: 1.2,
            decibelRatingB: 30,
            pressureB: 125,
            firstFlowB: 1.85,
            secondFlowB: 1.65
        };

        const decibelsMethod = new moduleInstance.DecibelsMethod(
            inp.operatingTime, inp.linePressure, inp.decibels,
            inp.decibelRatingA, inp.pressureA, inp.firstFlowA, inp.secondFlowA,
            inp.decibelRatingB, inp.pressureB, inp.firstFlowB, inp.secondFlowB
        );
        const result = decibelsMethod.calculate();

        assert.approximately(result.leakRateEstimate, 1.429, 0.01);
        assert.approximately(result.annualConsumption, 109.7472, 0.01);

        decibelsMethod.delete();
    });
});
