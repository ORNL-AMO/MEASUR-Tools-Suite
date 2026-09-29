import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpEfficiencyResults } from 'measur-tools-suite';

describe('PumpFan PumpEfficiency', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate PumpEfficiency correctly', function () {
        const pumpStyle = moduleInstance.PumpStyle.END_SUCTION_ANSI_API;
        const flowRate = 2000;
        const pumpEfficiency = 0.90;
        const rpm = 2000;
        const kinematicViscosity = 1.107;
        const stageCount = 1;
        const head = 137;

        const instance = new moduleInstance.PumpEfficiency(
            pumpStyle,
            pumpEfficiency,
            rpm,
            kinematicViscosity,
            stageCount,
            flowRate,
            head,
        );
        let results: PumpEfficiencyResults | undefined;

        try {
            results = instance.calculate();

            assert.approximately(results.average, 0.84, 0.001, "average");
            assert.approximately(results.max, 0.869, 0.001, "max");
        } finally {
            results?.delete();
            instance.delete();
        }
    });
});
