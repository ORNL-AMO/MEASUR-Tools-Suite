import { assert } from 'chai';
import createModule, { type HeadToolOutput, type MeasurToolsSuite } from 'measur-tools-suite';

describe('Pump Head Tool Suction Tank', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate HeadToolSuctionTank correctly', function () {
        const specificGravity = 1.0;
        const flowRate = 2000;
        const suctionPipeDiameter = 17.9;
        const suctionTankGasOverPressure = 115;
        const suctionTankFluidSurfaceElevation = 0;
        const suctionLineLossCoefficients = 1;
        const dischargePipeDiameter = 10;
        const dischargeGaugePressure = 124;
        const dischargeGaugeElevation = 0;
        const dischargeLineLossCoefficients = 1;
        const instance = new moduleInstance.HeadToolSuctionTank(
            specificGravity,
            flowRate,
            suctionPipeDiameter,
            suctionTankGasOverPressure,
            suctionTankFluidSurfaceElevation,
            suctionLineLossCoefficients,
            dischargePipeDiameter,
            dischargeGaugePressure,
            dischargeGaugeElevation,
            dischargeLineLossCoefficients
        );
        let results: HeadToolOutput | undefined;

        try {
            results = instance.calculate();

            assert.approximately(results.pumpHead, 22.972865551821844, 0.001, 'pumpHead');
            assert.approximately(results.differentialElevationHead, 0.0, 0.001, 'differentialElevationHead');
            assert.approximately(results.differentialPressureHead, 20.797226988336853, 0.001, 'differentialPressureHead');
            assert.approximately(results.differentialVelocityHead, 1.0372994352935365, 0.001, 'differentialVelocityHead');
            assert.approximately(results.estimatedDischargeFrictionHead, 1.0372994352935365, 0.001, 'estimatedDischargeFrictionHead');
            assert.approximately(results.estimatedSuctionFrictionHead, 0.10103969289791588, 0.001, 'estimatedSuctionFrictionHead');
        } finally {
            results?.delete();
            instance.delete();
        }
    });
});
