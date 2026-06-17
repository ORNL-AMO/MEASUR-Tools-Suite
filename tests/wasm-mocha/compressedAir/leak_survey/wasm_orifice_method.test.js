import { assert } from 'chai';

describe('Compressed Air Orifice Method', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate leak rate and annual consumption (survey reference case)', function () {
        // 550°F, 14.7 psia atm, Cd=1.0, 0.375 in, 100 psig, 4 orifices, 8640 hr/yr
        // Expected leak_rate_estimate verified against CompressedAirLeakSurvey test.
        const result = m.calculateOrificeMethod({
            operatingTime:  8640,
            airTemp:        550,
            atmPressure:    14.7,
            dischargeCoef:  1.0,
            diameter:       0.375,
            supplyPressure: 100,
            numOrifices:    4
        });

        assert.approximately(result.leakRateEstimate,  1295.1250307181,  0.001);
        assert.approximately(result.annualConsumption, 671392.816,       1.0);
    });

    it('should return per-orifice intermediate values', function () {
        const result = m.calculateOrificeMethod({
            operatingTime:  0,
            airTemp:        550,
            atmPressure:    14.7,
            dischargeCoef:  1.0,
            diameter:       0.375,
            supplyPressure: 100,
            numOrifices:    4
        });

        // standard_density ≈ 0.039302 lb/ft³ at 14.7 psia and 1009.67 °R
        assert.approximately(result.standardDensity,  0.0393, 0.001);
        // sonic velocity ≈ 1422 ft/s
        assert.approximately(result.leakVelocity,     1422.0, 5.0);
        // per-orifice flow = total / 4
        assert.approximately(result.leakRateScfm,     result.leakRateEstimate / 4.0, 0.001);
    });

    it('should scale leak rate estimate with number of orifices', function () {
        const single = m.calculateOrificeMethod({
            operatingTime: 0, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        });
        const quad = m.calculateOrificeMethod({
            operatingTime: 0, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 4
        });

        assert.approximately(quad.leakRateEstimate, single.leakRateEstimate * 4, 0.001);
        // Per-orifice intermediate values must not change
        assert.approximately(quad.leakRateScfm, single.leakRateScfm, 0.001);
    });

    it('should scale annual consumption with operating time', function () {
        const r1 = m.calculateOrificeMethod({
            operatingTime: 8640, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        });
        const r2 = m.calculateOrificeMethod({
            operatingTime: 4320, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 1
        });

        assert.approximately(r1.leakRateEstimate, r2.leakRateEstimate, 0.001);
        assert.approximately(r1.annualConsumption, r2.annualConsumption * 2, 0.01);
    });
});
