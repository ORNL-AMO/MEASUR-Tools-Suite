import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OrificeMethodInput,
    type OrificeMethodResult,
} from 'measur-tools-suite';

describe('Compressed Air Orifice Method', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate leak rate and annual consumption (survey reference case)', function () {
        const inp: OrificeMethodInput = {
            operatingTime:  8640,
            airTemp:        550,
            atmPressure:    14.7,
            dischargeCoef:  1.0,
            diameter:       0.375,
            supplyPressure: 100,
            numOrifices:    4
        };
        const result: OrificeMethodResult = moduleInstance.calculateOrificeMethod(inp);

        assert.approximately(result.leakRateEstimate,  1295.1250307181,  0.001);
        assert.approximately(result.annualConsumption, 671392.816,       1.0);
    });

    it('should return per-orifice intermediate values', function () {
        const inp: OrificeMethodInput = {
            operatingTime:  0,
            airTemp:        550,
            atmPressure:    14.7,
            dischargeCoef:  1.0,
            diameter:       0.375,
            supplyPressure: 100,
            numOrifices:    4
        };
        const result: OrificeMethodResult = moduleInstance.calculateOrificeMethod(inp);

        assert.approximately(result.standardDensity,  0.0393, 0.001);
        assert.approximately(result.leakVelocity,     1422.0, 5.0);
        assert.approximately(result.leakRateScfm,     result.leakRateEstimate / 4.0, 0.001);
    });

    it('should scale leak rate estimate with number of orifices', function () {
        const singleInput: OrificeMethodInput = {
            operatingTime: 0, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        };
        const quadInput: OrificeMethodInput = {
            operatingTime: 0, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 4
        };
        const single: OrificeMethodResult = moduleInstance.calculateOrificeMethod(singleInput);
        const quad: OrificeMethodResult = moduleInstance.calculateOrificeMethod(quadInput);

        assert.approximately(quad.leakRateEstimate, single.leakRateEstimate * 4, 0.001);
        assert.approximately(quad.leakRateScfm, single.leakRateScfm, 0.001);
    });

    it('should scale annual consumption with operating time', function () {
        const r1Input: OrificeMethodInput = {
            operatingTime: 8640, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        };
        const r2Input: OrificeMethodInput = {
            operatingTime: 4320, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        };
        const r1: OrificeMethodResult = moduleInstance.calculateOrificeMethod(r1Input);
        const r2: OrificeMethodResult = moduleInstance.calculateOrificeMethod(r2Input);

        assert.approximately(r1.leakRateEstimate, r2.leakRateEstimate, 0.001);
        assert.approximately(r1.annualConsumption, r2.annualConsumption * 2, 0.01);
    });
});
