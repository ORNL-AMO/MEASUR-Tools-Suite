import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat EnergyInputEAF', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatDelivered correctly', function () {
        const naturalGasHeatInput = 50;
        const coalCarbonInjection = 3300;
        const coalHeatingValue = 9000;
        const electrodeUse = 500;
        const electrodeHeatingValue = 12000;
        const otherFuels = 20;
        const electricityInput = 18000;
        const totalChemicalEnergyInput = moduleInstance.energyInputEAFTotalChemicalEnergyInput(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
        const heatDelivered = moduleInstance.energyInputEAFTotalHeatDelivered(totalChemicalEnergyInput, electricityInput);
        assert.equal(heatDelivered, 167118452.4607751);
    });

    it('should calculate totalChemicalEnergyInput correctly', function () {
        const naturalGasHeatInput = 50;
        const coalCarbonInjection = 3300;
        const coalHeatingValue = 9000;
        const electrodeUse = 500;
        const electrodeHeatingValue = 12000;
        const otherFuels = 20;
        const totalChemicalEnergyInput = moduleInstance.energyInputEAFTotalChemicalEnergyInput(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels);
        assert.equal(totalChemicalEnergyInput, 105700000);
    });
});