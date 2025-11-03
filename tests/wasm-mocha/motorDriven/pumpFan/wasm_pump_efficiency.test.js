import { assert } from 'chai';

describe('PumpFan PumpEfficiency', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate PumpEfficiency correctly', function () {
        let pumpStyle = moduleInstance.PumpStyle.END_SUCTION_ANSI_API;
        let flowRate = 2000;
        let pumpEfficiency = .90;
        let rpm = 2000;
        let kinematicViscosity = 1.107;
        let stageCount = 1;
        let head = 137;

        let instance = new moduleInstance.PumpEfficiency(
            pumpStyle,
            pumpEfficiency,
            rpm,
            kinematicViscosity,
            stageCount,
            flowRate,
            head,
        );
        let results = instance.calculate();
        instance.delete();

        assert.approximately(results.average, .84, .001, "average");
        assert.approximately(results.max, .869, .001, "max");
    });
});