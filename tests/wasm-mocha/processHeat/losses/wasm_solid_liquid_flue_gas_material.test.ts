import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat SolidLiquidFlueGasMaterial', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate heatLoss correctly', function () {
        const inp = {
            flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
            moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
            carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5, ambientAirTempF: 60
        };
        const heatLoss = moduleInstance.solidLiquidFlueGasMaterialTotalHeatLoss(inp.flueGasTemperature, inp.excessAirPercentage, inp.combustionAirTemperature,
            inp.fuelTemperature, inp.moistureInAirCombustion, inp.ashDischargeTemperature,
            inp.unburnedCarbonInAsh, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture,
            inp.nitrogen, inp.ambientAirTempF);
        assert.equal(heatLoss, 0.8222977480707968);
    });

    it('should calculate heatingValue correctly', function () {
        const inp = {
            flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
            moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
            carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
        };
        const heatingValue = moduleInstance.calculateHeatingValueFuel(inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen);
        assert.equal(heatingValue, 13877.969543147206);
    });

    it('should calculate flueGasO2 correctly 1', function () {
        const inp = {
            excessAir: 2.29427817 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const flueGasO2 = moduleInstance.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 0.49370451442164515);
    });

    it('should calculate flueGasO2 correctly 2', function () {
        const inp = {
            excessAir: 15.36865757 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const flueGasO2 = moduleInstance.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 2.9440141519451095);
    });

    it('should calculate flueGasO2 correctly 3', function () {
        const inp = {
            excessAir: 44.75000362 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const flueGasO2 = moduleInstance.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 6.875606606194022);
    });

    it('should calculate excessAir correctly 1', function () {
        const inp = {
            o2InFlueGas: 0.5 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const excessAir = moduleInstance.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 2.29427816716376);
    });

    it('should calculate excessAir correctly 2', function () {
        const inp = {
            o2InFlueGas: 3.0 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const excessAir = moduleInstance.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 15.368657569989644);
    });

    it('should calculate excessAir correctly 3', function () {
        const inp = {
            o2InFlueGas: 7.0 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        const excessAir = moduleInstance.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 44.75000361875009);
    });

    it('should calculate heatLoss correctly', function () {
        const inp = {
            "gasTypeId": 1,
            "flueGasTemperature": 600,
            "oxygenCalculationMethod": "Excess Air",
            "excessAirPercentage": 20,
            "o2InFlueGas": 3.573146432264344,
            "ambientAirTemp": 65,
            "combustionAirTemperature": 65,
            "fuelTemperature": 65,
            "ashDischargeTemperature": 400,
            "moistureInAirCombustion": 0.0077,
            "unburnedCarbonInAsh": 1,
            "carbon": 70.3,
            "hydrogen": 4.9,
            "sulphur": 2.2,
            "inertAsh": 1.5,
            "o2": 8.7,
            "moisture": 4.9,
            "nitrogen": 7.5,
            "heatInput": 10,
            "ambientAirTempF": 65,
            "combAirMoisturePerc": 0.0077
        };

        const heatLoss = moduleInstance.solidLiquidFlueGasMaterialTotalHeatLoss(inp.flueGasTemperature, inp.excessAirPercentage, inp.combustionAirTemperature,
            inp.fuelTemperature, inp.moistureInAirCombustion, inp.ashDischargeTemperature,
            inp.unburnedCarbonInAsh, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture,
            inp.nitrogen, inp.ambientAirTempF);
        assert.equal(heatLoss, 0.82606233456934197);
    });
});