import { assert } from 'chai';

describe('Process Heat EnergyInputExhaustGasLosses', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate heatDelivered correctly', function () {
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var heatDelivered = enInputExhaustGasLosses.heat_delivered;
        assert.equal(heatDelivered, 4136397.1199000007);
    });

    it('should calculate exhaustGasLosses correctly', function () {
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var exhaustGasLosses = enInputExhaustGasLosses.exhaust_gas_losses;
        assert.equal(exhaustGasLosses, 863602.8800999995);
    });

    it('should calculate availableHeat correctly', function () {
        var totalHeatInput = 5000000;
        var excessAir = 65;
        var combustionAirTemp = 300;
        var exhaustGasTemp = 550;
        var enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        var availableHeat = enInputExhaustGasLosses.available_heat;
        assert.equal(availableHeat, 82.72794239800001);
    });
});