import { assert } from 'chai';

describe('Process Heat AuxiliaryPower', function () {

    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate power used correctly 1', function () {
        var motorPhase = 3;
        var supplyVoltage = 460;
        var avgCurrent = 19;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 43905.340549404726);
    });

    it('should calculate power used correctly 2', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 19;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 48677.66017434002);
    });

    it('should calculate power used correctly 3', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.85;
        var operatingTime = 100;
        var powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 64049.552860973716);
    });


    it('should calculate power used correctly 4', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.55;
        var operatingTime = 100;
        var powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 41443.828321806526);
    });


    it('should calculate power used correctly 5', function () {
        var motorPhase = 3;
        var supplyVoltage = 510;
        var avgCurrent = 25;
        var powerFactor = 0.55;
        var operatingTime = 75;
        var powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 31082.871241354896);
    });
});