import { assert } from 'chai';
import createModule, {
    type CompressorPerformancePoint,
    type CompressorPerformancePointInput,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Assessment - Performance Points', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function defaultPoint(): CompressorPerformancePoint {
        return {
            dischargePressurePsig: 0,
            isDefaultPressure: true,
            airflowAcfm: 0,
            isDefaultAirflow: true,
            powerKw: 0,
            isDefaultPower: true,
        };
    }

    function screwModulationWithUnloadInput(): CompressorPerformancePointInput {
        return {
            nameplate: {
                compressorType: moduleInstance.CompressorType.Screw,
                stage: moduleInstance.CompressorStage.Single,
                lubricant: moduleInstance.CompressorLubricant.Injected,
                motorPowerHp: 0,
                fullLoadOperatingPressurePsig: 100,
                fullLoadRatedCapacityAcfm: 1048,
                ratedLoadPowerKw: 0,
                polytropicCompressorExponent: 1.4,
                fullLoadAmps: 0,
                totalPackageInputPowerKw: 166.5,
            },
            controls: {
                control: moduleInstance.CompressorControl.ModulationUnload,
                unloadPointCapacityPct: 90,
                numberOfUnloadSteps: 0,
                automaticShutdown: false,
                unloadSumpPressurePsig: 15,
            },
            design: {
                blowdownTimeSec: 0.003,
                modulatingPressurePsig: 5,
                inputPressurePsia: 14.5,
                designEfficiencyPct: 75,
                serviceFactor: 1,
                noLoadPowerFMPercent: 70,
                noLoadPowerULPercent: 25,
                maxFullFlowPressurePsig: 110,
            },
            centrifugal: {
                surgeAirflowAcfm: 0,
                maxFullLoadPressurePsig: 0,
                maxFullLoadCapacityAcfm: 0,
                minFullLoadPressurePsig: 0,
                minFullLoadCapacityAcfm: 0,
            },
            points: {
                fullLoad: defaultPoint(),
                maxFullFlow: defaultPoint(),
                midTurndown: defaultPoint(),
                turndown: defaultPoint(),
                unloadPoint: defaultPoint(),
                noLoad: defaultPoint(),
                blowoff: defaultPoint(),
            },
            atmosphericPressurePsia: 14.7,
        };
    }

    it('generates Desktop-parity default performance points as plain objects', function () {
        const points = moduleInstance.generatePerformancePoints(screwModulationWithUnloadInput());

        assert.approximately(points.fullLoad.dischargePressurePsig, 100, 0.001);
        assert.approximately(points.fullLoad.airflowAcfm, 1048, 0.001);
        assert.approximately(points.fullLoad.powerKw, 166.5, 0.001);

        assert.approximately(points.maxFullFlow.dischargePressurePsig, 110, 0.001);
        assert.approximately(points.maxFullFlow.airflowAcfm, 1040, 0.001);
        assert.approximately(points.maxFullFlow.powerKw, 175.6, 0.001);

        assert.approximately(points.unloadPoint.airflowAcfm, 943, 0.001);
        assert.approximately(points.unloadPoint.dischargePressurePsig, 110.5, 0.001);
        assert.approximately(points.unloadPoint.powerKw, 170.3, 0.001);

        assert.approximately(points.noLoad.dischargePressurePsig, 15, 0.001);
        assert.approximately(points.noLoad.airflowAcfm, 0, 0.001);
        assert.approximately(points.noLoad.powerKw, 41.6, 0.001);
    });

    it('exposes scalar helper formulas', function () {
        assert.approximately(moduleInstance.calculateUnloadPointPower(70, 90, 1, 175.6), 170.3, 0.001);
        assert.approximately(moduleInstance.calculateUnloadPointAirflow(1048, 90), 943.2, 0.001);
        assert.approximately(moduleInstance.calculateUnloadPointDischargePressure(110, 5, 1048, 943.2), 110.5, 0.001);
        assert.approximately(moduleInstance.calculateRatedSpecificPower(166.5, 1048), 15.8874, 0.0001);
        assert.approximately(moduleInstance.calculateRatedIsentropicEfficiency(15.8874, 100), 83.6711, 0.0001);
    });
});
