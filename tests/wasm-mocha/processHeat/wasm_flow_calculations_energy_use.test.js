import { assert } from 'chai';

describe('Steam water heating using exhaust', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate flowCalculationsEnergyUse results correctly 1', function () {
        let results = moduleInstance.flowCalculationsEnergyUse(0.14, 5, 9, 0.6, 7325, 52, 63, 26, 16);
        assert.approximately(results.flowPerHour, 647521.0285703765694052, 0.001);
        assert.approximately(results.heatInput, 75889.4645484481297899, 0.001);
    });


    it('should calculate flowCalculationsEnergyUse results correctly 2', function () {
        let results = moduleInstance.flowCalculationsEnergyUse(1, 3.5, 8, 0.6, 0, 85, 20, 10, 10);
        assert.approximately(results.totalFlow, 462143.21201163821388036, 0.001);
    });

    it('should calculate flowCalculationsEnergyUse results correctly 3', function () {
        let results = moduleInstance.flowCalculationsEnergyUse(7, 6, 18, 0.8, 60000, 85, 55, 20, 10);
        assert.approximately(results.flowPerHour, 135485.24457904856535606, 0.001);
        assert.approximately(results.heatInput, 81291.14674742914212402, 0.001);
    });

    it('should calculate flowCalculationsEnergyUse results correctly 4', function () {
        let results = moduleInstance.flowCalculationsEnergyUse(1, 3.5, 8, 0.8, 0, 85, 20, 10, 10);
        assert.approximately(results.totalFlow, 616190.94934885110706091, 0.001);
    });

});