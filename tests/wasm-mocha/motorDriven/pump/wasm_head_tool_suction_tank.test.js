import { assert } from 'chai';

describe('Pump Head Tool Suction Tank', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate HeadToolSuctionTank correctly', function () {
        let specificGravity = 1.0;
        let flowRate = 2000;
        let suctionPipeDiameter = 17.9;
        let suctionTankGasOverPressure = 115;
        let suctionTankFluidSurfaceElevation = 0;
        let suctionLineLossCoefficients = 1;
        let dischargePipeDiameter = 10;
        let dischargeGaugePressure = 124;
        let dischargeGaugeElevation = 0;
        let dischargeLineLossCoefficients = 1;
        let instance = new moduleInstance.HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure, suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter, dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
        let results = instance.calculate();
        instance.delete();

        assert.approximately(results.pumpHead, 22.972865551821844, .001, 'pumpHead');
        assert.approximately(results.differentialElevationHead, 0.0, .001, 'differentialElevationHead');
        assert.approximately(results.differentialPressureHead, 20.797226988336853, .001, 'differentialPressureHead');
        assert.approximately(results.differentialVelocityHead, 1.0372994352935365, .001, 'differentialVelocityHead');
        assert.approximately(results.estimatedDischargeFrictionHead, 1.0372994352935365, .001, 'estimatedDischargeFrictionHead');
        assert.approximately(results.estimatedSuctionFrictionHead, 0.10103969289791588, .001, 'estimatedSuctionFrictionHead');
    });
})