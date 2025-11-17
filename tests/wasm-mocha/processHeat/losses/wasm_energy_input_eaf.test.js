import { assert } from 'chai';

describe('Process Heat EnergyInputEAF', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
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
        var energyInputEAF = new moduleInstance.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
        var heatDelivered = energyInputEAF.getHeatDelivered();
        energyInputEAF.delete();
        assert.equal(heatDelivered, 167116000.0);
    });

    it('should calculate totalChemicalEnergyInput correctly', function () {
        var naturalGasHeatInput = 50;
        var coalCarbonInjection = 3300;
        var coalHeatingValue = 9000;
        var electrodeUse = 500;
        var electrodeHeatingValue = 12000;
        var otherFuels = 20;
        var electricityInput = 18000;
        var energyInputEAF = new moduleInstance.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
        var totalChemicalEnergyInput = energyInputEAF.getTotalChemicalEnergyInput();
        energyInputEAF.delete();
        assert.equal(totalChemicalEnergyInput, 105700000);
    });
});