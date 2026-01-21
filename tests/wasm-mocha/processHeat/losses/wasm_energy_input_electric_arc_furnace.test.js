import { assert } from 'chai';

describe('Process Heat EnergyInputEAF', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate heatDelivered correctly', function () {
        var naturalGasHeatInput = 50;
        var coalCarbonInjection = 3300;
        var coalHeatingValue = 9000;
        var electrodeUse = 500;
        var electrodeHeatingValue = 12000;
        var otherFuels = 20;
        var electricityInput = 18000;
        var totalChemicalEnergyInput = moduleInstance.energyInputEAFTotalChemicalEnergyInput(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
        var heatDelivered = moduleInstance.energyInputEAFTotalHeatDelivered(totalChemicalEnergyInput, electricityInput);
        assert.equal(heatDelivered, 167118452.4607751);
    });

    it('should calculate totalChemicalEnergyInput correctly', function () {
        var naturalGasHeatInput = 50;
        var coalCarbonInjection = 3300;
        var coalHeatingValue = 9000;
        var electrodeUse = 500;
        var electrodeHeatingValue = 12000;
        var otherFuels = 20;
        var totalChemicalEnergyInput = moduleInstance.energyInputEAFTotalChemicalEnergyInput(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
        assert.equal(totalChemicalEnergyInput, 105700000);
    });
});