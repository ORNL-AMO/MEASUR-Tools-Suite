import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat EnergyInputExhaustGasLosses', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatDelivered correctly', function () {
        const totalHeatInput = 5000000;
        const excessAir = 65;
        const combustionAirTemp = 300;
        const exhaustGasTemp = 550;
        const enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        const heatDelivered = enInputExhaustGasLosses.heat_delivered;
        assert.equal(heatDelivered, 4136397.1199000007);
    });

    it('should calculate exhaustGasLosses correctly', function () {
        const totalHeatInput = 5000000;
        const excessAir = 65;
        const combustionAirTemp = 300;
        const exhaustGasTemp = 550;
        const enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        const exhaustGasLosses = enInputExhaustGasLosses.exhaust_gas_losses;
        assert.equal(exhaustGasLosses, 863602.8800999995);
    });

    it('should calculate availableHeat correctly', function () {
        const totalHeatInput = 5000000;
        const excessAir = 65;
        const combustionAirTemp = 300;
        const exhaustGasTemp = 550;
        const enInputExhaustGasLosses = moduleInstance.energyInputExhaustGasHeatLossCalculate(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
        const availableHeat = enInputExhaustGasLosses.available_heat;
        assert.equal(availableHeat, 82.72794239800001);
    });
});