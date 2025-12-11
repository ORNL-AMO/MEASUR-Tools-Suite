import { assert } from 'chai';

describe('Process Heat Gas Flue Gas', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate getProcessHeatProperties heatLoss correctly', function () {
        var inp = {
            CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29,
            H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }
        var flueGasTemperature = 700;
        var flueGasO2Percentage = 0.0;
        var combustionAirTemperature = 125;
        var fuelTemperature = 125;
        var ambientAirTemp = 60;
        var combAirMoisturePerc = 0;
        var excessAirPercentage = 0.09;
        var gasComposition = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        var heatLoss = moduleInstance.gasFlueGasMaterialProcessHeatProperties(gasComposition, flueGasTemperature, flueGasO2Percentage, combustionAirTemperature, fuelTemperature, ambientAirTemp, combAirMoisturePerc, excessAirPercentage).availableHeat;
        gasComposition.delete();
        assert.equal(heatLoss, 0.7858766581499935);
    });
});