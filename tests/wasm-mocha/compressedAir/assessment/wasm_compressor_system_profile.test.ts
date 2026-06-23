import { assert } from 'chai';
import createModule, {
    type CompressorPerformancePoint,
    type CompressorProfileCompressor,
    type CompressorProfileOptions,
    type CompressorProfileRow,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Assessment - System Profile', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function point(pressure: number, airflow: number, power: number): CompressorPerformancePoint {
        return {
            dischargePressurePsig: pressure,
            isDefaultPressure: false,
            airflowAcfm: airflow,
            isDefaultAirflow: false,
            powerKw: power,
            isDefaultPower: false,
        };
    }

    function modulationCompressor(id: string, airflow: number, fullPower: number, noLoadPower: number): CompressorProfileCompressor {
        return {
            compressorId: id,
            compressorType: moduleInstance.CompressorType.Screw,
            control: moduleInstance.CompressorControl.ModulationWithoutUnload,
            stage: moduleInstance.CompressorStage.Single,
            lubricant: moduleInstance.CompressorLubricant.Injected,
            automaticShutdown: false,
            performancePoints: {
                fullLoad: point(100, airflow, fullPower),
                maxFullFlow: point(110, airflow, fullPower),
                midTurndown: point(0, 0, 0),
                turndown: point(0, 0, 0),
                unloadPoint: point(0, 0, 0),
                noLoad: point(105, 0, noLoadPower),
                blowoff: point(0, 0, 0),
            },
            blowdownTimeSec: 0.003,
            unloadSumpPressurePsig: 15,
            noLoadPowerFractionForModulation: 0.7,
            modulatingPressurePsig: 5,
        };
    }

    function profileRow(compressorId: string, operatingOrder: number): CompressorProfileRow {
        return {
            compressorId,
            dayTypeId: 'weekday',
            timeIntervalHr: 0,
            operatingOrder,
            powerKw: 0,
            airflowAcfm: 0,
            powerFraction: 0,
            airflowFraction: 0,
            systemPowerFraction: 0,
            systemAirflowFraction: 0,
            powerFactor: 0,
            amps: 0,
            volts: 0,
        };
    }

    function profileOptions(controlMode: number): CompressorProfileOptions {
        return {
            dayTypeId: 'weekday',
            inputBasis: moduleInstance.CompressorInputBasis.MeasuredCapacity,
            controlMode,
            atmosphericPressurePsia: 14.7,
            totalAirStorageFt3: 140,
            additionalReceiverVolumeFt3: 0,
            canShutdown: true,
        };
    }

    it('calculates baseline rows and totals with registered vectors', function () {
        const compressors = new moduleInstance.CompressorProfileCompressorV();
        const rows = new moduleInstance.CompressorProfileRowV();

        try {
            compressors.push_back(modulationCompressor('a', 1000, 100, 50));
            const row = profileRow('a', 1);
            row.airflowAcfm = 500;
            rows.push_back(row);

            const result = moduleInstance.calculateBaselineProfile(
                compressors,
                rows,
                profileOptions(moduleInstance.CompressorSystemControlMode.Cascading)
            );

            try {
                assert.strictEqual(result.size(), 1);
                const calculated = result.get(0);
                assert.approximately(calculated.airflowAcfm, 500, 0.001);
                assert.approximately(calculated.powerKw, 75, 0.001);
                assert.approximately(calculated.airflowFraction, 0.5, 0.0001);
                assert.approximately(calculated.powerFraction, 0.75, 0.0001);

                const totals = moduleInstance.calculateProfileTotals(compressors, result, 1);
                try {
                    assert.strictEqual(totals.size(), 1);
                    assert.approximately(totals.get(0).airflowAcfm, 500, 0.001);
                    assert.approximately(totals.get(0).powerKw, 75, 0.001);
                } finally {
                    totals.delete();
                }
            } finally {
                result.delete();
            }
        } finally {
            rows.delete();
            compressors.delete();
        }
    });

    it('reallocates load-sharing flow and calculates savings', function () {
        const compressors = new moduleInstance.CompressorProfileCompressorV();
        const rows = new moduleInstance.CompressorProfileRowV();
        const demandRows = new moduleInstance.CompressorProfileTotalV();
        const runtimeStates = new moduleInstance.CompressorRuntimeStateV();
        const trimSelections = new moduleInstance.CompressorTrimSelectionV();

        try {
            compressors.push_back(modulationCompressor('a', 1000, 100, 50));
            compressors.push_back(modulationCompressor('b', 500, 60, 30));
            rows.push_back(profileRow('a', 1));
            rows.push_back(profileRow('b', 2));
            demandRows.push_back({
                dayTypeId: 'weekday',
                timeIntervalHr: 0,
                airflowAcfm: 750,
                powerKw: 0,
                totalPowerKw: 0,
                airflowFraction: 0,
                powerFraction: 0,
                auxiliaryPowerKw: 0,
            });

            const result = moduleInstance.reallocateProfileFlow(
                compressors,
                rows,
                demandRows,
                profileOptions(moduleInstance.CompressorSystemControlMode.LoadSharing),
                runtimeStates,
                trimSelections
            );

            try {
                assert.strictEqual(result.size(), 2);
                assert.approximately(result.get(0).airflowAcfm, 750, 0.001);
                assert.approximately(result.get(0).powerKw, 87.5, 0.001);
                assert.strictEqual(result.get(1).operatingOrder, 0);

                const baselineRows = new moduleInstance.CompressorProfileRowV();
                const adjustedRows = new moduleInstance.CompressorProfileRowV();
                try {
                    const baselineA = profileRow('a', 1);
                    baselineA.powerKw = 100;
                    const baselineB = profileRow('b', 2);
                    baselineB.powerKw = 42;
                    const adjustedA = profileRow('a', 1);
                    adjustedA.powerKw = 87.5;
                    const adjustedB = profileRow('b', 0);
                    adjustedB.powerKw = 0;
                    baselineRows.push_back(baselineA);
                    baselineRows.push_back(baselineB);
                    adjustedRows.push_back(adjustedA);
                    adjustedRows.push_back(adjustedB);

                    const savings = moduleInstance.calculateProfileSavings(baselineRows, adjustedRows, {
                        dayTypeId: 'weekday',
                        electricityCostPerKwh: 0.1,
                        intervalHours: 1,
                        operatingDays: 10,
                        auxiliaryEnergyKwh: 0,
                        implementationCost: 100,
                        salvageValue: 0,
                    });

                    assert.approximately(savings.energySavingsKwh, 545, 0.001);
                    assert.approximately(savings.costSavings, 54.5, 0.001);
                    assert.approximately(savings.paybackMonths, 22.0183, 0.0001);
                } finally {
                    adjustedRows.delete();
                    baselineRows.delete();
                }
            } finally {
                result.delete();
            }
        } finally {
            trimSelections.delete();
            runtimeStates.delete();
            demandRows.delete();
            rows.delete();
            compressors.delete();
        }
    });
});
