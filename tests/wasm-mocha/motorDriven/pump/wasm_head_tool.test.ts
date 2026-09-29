import { assert } from 'chai';
import createModule, { type HeadToolOutput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Pump Head Tool', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate HeadTool correctly', function () {
        const specificGravity = 1.0;
        const flowRate = 2000;
        const suctionPipeDiameter = 17.9;
        const suctionGaugePressure = 5;
        const suctionGaugeElevation = 5;
        const suctionLineLossCoefficients = 1;
        const dischargePipeDiameter = 15;
        const dischargeGaugePressure = 50;
        const dischargeGaugeElevation = 1;
        const dischargeLineLossCoefficients = 1;
        const instance = new moduleInstance.HeadTool(
            specificGravity,
            flowRate,
            suctionPipeDiameter,
            suctionGaugePressure,
            suctionGaugeElevation,
            suctionLineLossCoefficients,
            dischargePipeDiameter,
            dischargeGaugePressure,
            dischargeGaugeElevation,
            dischargeLineLossCoefficients
        );
        let results: HeadToolOutput | undefined;

        try {
            results = instance.calculate();

            assert.approximately(results.pumpHead, 100.39593224945455, 0.001, 'pumpHead');
            assert.approximately(results.differentialElevationHead, -4, 0.001, 'differentialElevationHead');
            assert.approximately(results.differentialPressureHead, 103.98613494168427, 0.001, 'differentialPressureHead');
            assert.approximately(results.differentialVelocityHead, 0.10385896098722718, 0.001, 'differentialVelocityHead');
            assert.approximately(results.estimatedDischargeFrictionHead, 0.20489865388514306, 0.001, 'estimatedDischargeFrictionHead');
            assert.approximately(results.estimatedSuctionFrictionHead, 0.10103969289791588, 0.001, 'estimatedSuctionFrictionHead');
        } finally {
            results?.delete();
            instance.delete();
        }
    });
});
