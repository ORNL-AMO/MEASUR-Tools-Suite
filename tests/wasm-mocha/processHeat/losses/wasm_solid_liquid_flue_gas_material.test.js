const path = require('path');
const assert = require('chai').assert;

const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');

describe('Process Heat SolidLiquidFlueGasMaterial', function () {
    let ToolsSuiteModule;
    before(async function () {
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

    it('should calculate heatLoss correctly', function () {
        var inp = {
            flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
            moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
            carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5, ambientAirTempF: 60
        };
        var flueGasLossesByMass = new ToolsSuiteModule.SolidLiquidFlueGasMaterial(inp.flueGasTemperature, inp.excessAirPercentage, inp.combustionAirTemperature,
            inp.fuelTemperature, inp.moistureInAirCombustion, inp.ashDischargeTemperature,
            inp.unburnedCarbonInAsh, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture,
            inp.nitrogen, inp.ambientAirTempF);
        var heatLoss = flueGasLossesByMass.getHeatLoss();
        assert.equal(heatLoss, 0.8222977480707968);
        flueGasLossesByMass.delete();
    });

    it('should calculate heatingValue correctly', function () {
        var inp = {
            flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
            moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
            carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var heatingValue = solidLiquidFlueGasMaterial.calculateHeatingValueFuel(inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen);
        assert.equal(heatingValue, 13877.969543147206);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate flueGasO2 correctly 1', function () {
        var inp = {
            excessAir: 2.29427817 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 0.49370451442164515);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate flueGasO2 correctly 2', function () {
        var inp = {
            excessAir: 15.36865757 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 2.9440141519451095);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate flueGasO2 correctly 3', function () {
        var inp = {
            excessAir: 44.75000362 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(flueGasO2, 6.875606606194022);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate excessAir correctly 1', function () {
        var inp = {
            o2InFlueGas: 0.5 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 2.29427816716376);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate excessAir correctly 2', function () {
        var inp = {
            o2InFlueGas: 3.0 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 15.368657569989644);
        solidLiquidFlueGasMaterial.delete();
    });

    it('should calculate excessAir correctly 3', function () {
        var inp = {
            o2InFlueGas: 7.0 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
            nitrogen: 0.0, moistureInAirCombustion: 1.5
        };
        var solidLiquidFlueGasMaterial = new ToolsSuiteModule.SolidLiquidFlueGasMaterial();
        var excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
        assert.equal(excessAir, 44.75000361875009);
        solidLiquidFlueGasMaterial.delete();
    });
});