import { assert } from 'chai';
import createModule, {
    type DecibelsMethodInput,
    type DecibelsMethodResult,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Decibels Method', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate leak rate estimate and annual consumption from decibel readings', function () {
        const inp: DecibelsMethodInput = {
            operatingTime:  1280,
            linePressure:   130,
            decibels:       25,
            decibelRatingA: 20,
            pressureA:      150,
            firstFlowA:     1.04,
            secondFlowA:    1.2,
            decibelRatingB: 30,
            pressureB:      125,
            firstFlowB:     1.85,
            secondFlowB:    1.65
        };
        const result: DecibelsMethodResult = moduleInstance.calculateDecibelsMethod(inp);
        assert.approximately(result.leakRateEstimate, 1.429, 0.01);
        assert.approximately(result.annualConsumption, 109.7472, 0.01);
    });

    it('should return firstFlowA when measuring at reference corner (pressureA, decibelRatingA)', function () {
        const inp: DecibelsMethodInput = {
            operatingTime:  0,
            linePressure:   150,
            decibels:       20,
            decibelRatingA: 20,
            pressureA:      150,
            firstFlowA:     1.04,
            secondFlowA:    1.2,
            decibelRatingB: 30,
            pressureB:      125,
            firstFlowB:     1.85,
            secondFlowB:    1.65
        };
        const result: DecibelsMethodResult = moduleInstance.calculateDecibelsMethod(inp);
        assert.approximately(result.leakRateEstimate, 1.04, 0.001);
    });

    it('should return average of four corners when measuring at grid center', function () {
        const inp: DecibelsMethodInput = {
            operatingTime:  8760,
            linePressure:   100,
            decibels:       40,
            decibelRatingA: 30,
            pressureA:      90,
            firstFlowA:     2.0,
            secondFlowA:    2.5,
            decibelRatingB: 50,
            pressureB:      110,
            firstFlowB:     3.0,
            secondFlowB:    3.5
        };
        const result: DecibelsMethodResult = moduleInstance.calculateDecibelsMethod(inp);
        assert.approximately(result.leakRateEstimate, 2.75, 0.001);
        assert.approximately(result.annualConsumption, 1445.4, 0.1);
    });
});
