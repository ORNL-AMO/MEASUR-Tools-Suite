import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat Gas Flue Gas', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate getProcessHeatProperties heatLoss correctly', function () {
        const inp = {
            CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29,
            H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }
        const flueGasTemperature = 700;
        const flueGasO2Percentage = 0.0;
        const combustionAirTemperature = 125;
        const fuelTemperature = 125;
        const ambientAirTemp = 60;
        const combAirMoisturePerc = 0;
        const excessAirPercentage = 0.09;
        const gasComposition = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        try {
            const heatLoss = moduleInstance.gasFlueGasMaterialProcessHeatProperties(gasComposition, flueGasTemperature, flueGasO2Percentage, combustionAirTemperature, fuelTemperature, ambientAirTemp, combAirMoisturePerc, excessAirPercentage).availableHeat;
            assert.equal(heatLoss, 0.7858766581499935);
        } finally {
            gasComposition.delete();
        }
    });
});
