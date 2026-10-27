import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type PumpHeadResult,
    type PumpHeadSuctionGaugeInput,
    type PumpHeadSuctionTankInput,
} from 'measur-tools-suite';

describe('Pump Head', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('calculates pump head from suction- and discharge-gauge measurements', function () {
        const input: PumpHeadSuctionGaugeInput = {
            specificGravity: 1.0,
            flowRate: 2000,
            suctionPipeDiameter: 17.9,
            suctionGaugePressure: 5,
            suctionGaugeElevation: 5,
            suctionLineLossCoefficients: 1,
            dischargePipeDiameter: 15,
            dischargeGaugePressure: 50,
            dischargeGaugeElevation: 1,
            dischargeLineLossCoefficients: 1,
        };

        const result: PumpHeadResult = moduleInstance.calculatePumpHeadFromSuctionGauge(input);

        assert.approximately(result.pumpHead, 100.39593224945455, 0.001, 'pumpHead');
        assert.approximately(result.differentialElevationHead, -4, 0.001, 'differentialElevationHead');
        assert.approximately(result.differentialPressureHead, 103.98613494168427, 0.001, 'differentialPressureHead');
        assert.approximately(result.differentialVelocityHead, 0.10385896098722718, 0.001, 'differentialVelocityHead');
        assert.approximately(
            result.estimatedDischargeFrictionHead,
            0.20489865388514306,
            0.001,
            'estimatedDischargeFrictionHead'
        );
        assert.approximately(
            result.estimatedSuctionFrictionHead,
            0.10103969289791588,
            0.001,
            'estimatedSuctionFrictionHead'
        );
        assert.notProperty(result, 'delete');
    });

    it('calculates pump head for a pressurized suction tank', function () {
        const input: PumpHeadSuctionTankInput = {
            specificGravity: 1.0,
            flowRate: 2000,
            suctionPipeDiameter: 17.9,
            suctionTankGasOverPressure: 115,
            suctionTankFluidSurfaceElevation: 0,
            suctionLineLossCoefficients: 1,
            dischargePipeDiameter: 10,
            dischargeGaugePressure: 124,
            dischargeGaugeElevation: 0,
            dischargeLineLossCoefficients: 1,
        };

        const result: PumpHeadResult = moduleInstance.calculatePumpHeadFromSuctionTank(input);

        assert.approximately(result.pumpHead, 22.972865551821844, 0.001, 'pumpHead');
        assert.approximately(result.differentialElevationHead, 0, 0.001, 'differentialElevationHead');
        assert.approximately(result.differentialPressureHead, 20.797226988336853, 0.001, 'differentialPressureHead');
        assert.approximately(result.differentialVelocityHead, 1.0372994352935365, 0.001, 'differentialVelocityHead');
        assert.approximately(
            result.estimatedDischargeFrictionHead,
            1.0372994352935365,
            0.001,
            'estimatedDischargeFrictionHead'
        );
        assert.approximately(
            result.estimatedSuctionFrictionHead,
            0.10103969289791588,
            0.001,
            'estimatedSuctionFrictionHead'
        );
        assert.notProperty(result, 'delete');
    });

    it('does not expose the removed runtime classes', function () {
        assert.notProperty(moduleInstance, 'HeadTool');
        assert.notProperty(moduleInstance, 'HeadToolSuctionTank');
        assert.notProperty(moduleInstance, 'HeadToolOutput');
    });
});
