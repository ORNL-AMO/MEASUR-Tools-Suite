import { assert } from 'chai';

describe('Pump Head Tool', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate HeadTool correctly', function () {
        let specificGravity = 1.0;
        let flowRate = 2000;
        let suctionPipeDiameter = 17.9;
        let suctionGaugePressure = 5;
        let suctionGaugeElevation = 5;
        let suctionLineLossCoefficients = 1;
        let dischargePipeDiameter = 15;
        let dischargeGaugePressure = 50;
        let dischargeGaugeElevation = 1;
        let dischargeLineLossCoefficients = 1;
        let instance = new moduleInstance.HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
            suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
            dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
        let results = instance.calculate();
        instance.delete();

        assert.approximately(results.pumpHead, 100.39593224945455, .001, 'pumpHead');
        assert.approximately(results.differentialElevationHead, -4, .001, 'differentialElevationHead');
        assert.approximately(results.differentialPressureHead, 103.98613494168427, .001, 'differentialPressureHead');
        assert.approximately(results.differentialVelocityHead, 0.10385896098722718, .001, 'differentialVelocityHead');
        assert.approximately(results.estimatedDischargeFrictionHead, 0.20489865388514306, .001, 'estimatedDischargeFrictionHead');
        assert.approximately(results.estimatedSuctionFrictionHead, 0.10103969289791588, .001, 'estimatedSuctionFrictionHead');

    });
})