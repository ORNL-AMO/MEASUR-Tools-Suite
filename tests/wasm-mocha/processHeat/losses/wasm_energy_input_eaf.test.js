const assert = require('chai').assert;
const path = require('path');

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat EnergyInputEAF', function () {
    let ToolsSuiteModule;
    before(async function () {
        // Dynamically import the Emscripten module with locateFile for .wasm
        const createModule = (await import(clientPath)).default;
        ToolsSuiteModule = await createModule({
            locateFile: (filename) => {
                if (filename.endsWith('.wasm')) {
                    return wasmPath;
                }
                return filename;
            }
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
        var energyInputEAF = new ToolsSuiteModule.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
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
        var energyInputEAF = new ToolsSuiteModule.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
        var totalChemicalEnergyInput = energyInputEAF.getTotalChemicalEnergyInput();
        energyInputEAF.delete();
        assert.equal(totalChemicalEnergyInput, 105700000);
    });
});