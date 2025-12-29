import { assert } from 'chai';

describe('Process Heat Efficiency Improvement', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate processHeatEfficiencyImprovement results correctly', function () {
        var inp = {
            currentFlueGasOxygen: 6,
            newFlueGasOxygen: 2,
            currentFlueGasTemp: 1600,
            currentCombustionAirTemp: 80,
            newCombustionAirTemp: 750,
            currentEnergyInput: 10,
            newFlueGasTemp: 1200
        };
        let results = moduleInstance.processHeatEfficiencyImprovement(inp.currentFlueGasOxygen, inp.newFlueGasOxygen, inp.currentFlueGasTemp, inp.newFlueGasTemp, inp.currentCombustionAirTemp, inp.newCombustionAirTemp, inp.currentEnergyInput);
        assert.approximately(results.currentExcessAir, 35.80000271600005, .001, "Process Heat Efficiency Improvement (currentExcessAir)");
        assert.approximately(results.newExcessAir, 9.421053207479227, .001, "Process Heat Efficiency Improvement (newExcessAir)");
        assert.approximately(results.currentAvailableHeat, 45.550889, .001, "Process Heat Efficiency Improvement (currentAvailableHeat)");
        assert.approximately(results.newAvailableHeat, 77.893119, .001, "Process Heat Efficiency Improvement (newAvailableHeat)");
        assert.approximately(results.newFuelSavings, 41.521293, .001, "Process Heat Efficiency Improvement (newFuelSavings)");
        assert.approximately(results.newEnergyInput, 5.847870740975683, .001, "Process Heat Efficiency Improvement (newEnergyInput)");
    });

});