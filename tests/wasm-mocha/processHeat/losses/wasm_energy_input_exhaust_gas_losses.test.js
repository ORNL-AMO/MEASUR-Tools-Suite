const assert = require('chai').assert;
const path = require('path');

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat EnergyInputExhaustGasLosses', function () {
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
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = new ToolsSuiteModule.EnergyInputExhaustGasLosses(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var heatDelivered = enInputExhaustGasLosses.getHeatDelivered();
        enInputExhaustGasLosses.delete();
        assert.equal(heatDelivered, 4136397.1199000007);
    });

    it('should calculate exhaustGasLosses correctly', function () {
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = new ToolsSuiteModule.EnergyInputExhaustGasLosses(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var exhaustGasLosses = enInputExhaustGasLosses.getExhaustGasLosses();
        enInputExhaustGasLosses.delete();
        assert.equal(exhaustGasLosses, 863602.8800999995);
    });

    it('should calculate availableHeat correctly', function () {
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = new ToolsSuiteModule.EnergyInputExhaustGasLosses(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var availableHeat = enInputExhaustGasLosses.getAvailableHeat();
        enInputExhaustGasLosses.delete();
        assert.equal(availableHeat, 82.72794239800001);
    });
});