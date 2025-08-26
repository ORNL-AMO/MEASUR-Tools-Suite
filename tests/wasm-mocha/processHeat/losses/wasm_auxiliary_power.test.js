const path = require('path');
const assert = require('chai').assert;

// Adjust the path to your client.js as needed
const clientPath = path.resolve(__dirname, '../../../../bin/client.js');
const wasmPath = path.resolve(__dirname, '../../../../bin/client.wasm');
describe('Process Heat AuxiliaryPower', function () {

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

    it('should calculate power used correctly 1', function () {
        var motorPhase = 3;
        var supplyVoltage = 460;
        var avgCurrent = 19;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var auxiliaryPowerLoss = new ToolsSuiteModule.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        var powerUsed = auxiliaryPowerLoss.getPowerUsed();
        assert.equal(powerUsed, 43905.340549404726);
        auxiliaryPowerLoss.delete();
    });

    it('should calculate power used correctly 2', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 19;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var auxiliaryPowerLoss = new ToolsSuiteModule.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        var powerUsed = auxiliaryPowerLoss.getPowerUsed();
        assert.equal(powerUsed, 48677.66017434002);
        auxiliaryPowerLoss.delete();
    });

    it('should calculate power used correctly 3', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var auxiliaryPowerLoss = new ToolsSuiteModule.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        var powerUsed = auxiliaryPowerLoss.getPowerUsed();
        assert.equal(powerUsed, 64049.552860973716);
        auxiliaryPowerLoss.delete();
    });


    it('should calculate power used correctly 4', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.55;
        var operatingTime = 100;
        var auxiliaryPowerLoss = new ToolsSuiteModule.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        var powerUsed = auxiliaryPowerLoss.getPowerUsed();
        assert.equal(powerUsed, 41443.828321806526);
        auxiliaryPowerLoss.delete();
    });


    it('should calculate power used correctly 5', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.55;
        var operatingTime = 75;
        var auxiliaryPowerLoss = new ToolsSuiteModule.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        var powerUsed = auxiliaryPowerLoss.getPowerUsed();
        assert.equal(powerUsed, 31082.871241354896);
        auxiliaryPowerLoss.delete();
    });
});