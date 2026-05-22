import { assert } from 'chai';

describe('Compressed Air Leak Orifice Method', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate leak rate and annual consumption from orifice measurements', function () {
        const inp = {
            operatingTime: 115200 / 60.0,  // convert seconds to minutes
            airTemp: 250,
            atmPressure: 14.7,
            dischargeCoef: 1,
            diameter: 6,
            supplyPressure: 6.2,
            numOrifices: 4
        };

        const orificeMethod = new moduleInstance.OrificeMethod(
            inp.operatingTime, inp.airTemp, inp.atmPressure,
            inp.dischargeCoef, inp.diameter, inp.supplyPressure, inp.numOrifices
        );
        const result = orificeMethod.calculate();

        assert.approximately(result.standardDensity, 0.2256917885, 0.01);
        assert.approximately(result.sonicDensity, 0.0153403857, 0.01);
        assert.approximately(result.leakVelocity, 707.7792735027, 0.01);
        assert.approximately(result.leakRateLBMmin, 127.9131698485, 0.01);
        assert.approximately(result.leakRateScfm, 566.7604066752, 0.01);
        assert.approximately(result.leakRateEstimate, 2267.0416267007, 0.01);
        assert.approximately(result.annualConsumption, 261163.1953959255, 0.01);

        orificeMethod.delete();
    });
});
