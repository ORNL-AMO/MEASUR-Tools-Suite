import { assert } from 'chai';
import createModule, { type MeasurToolsSuite } from 'measur-tools-suite';

describe('Process Heat AuxiliaryPower', function () {

    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate power used correctly 1', function () {
        const motorPhase = 3;
        const supplyVoltage = 460;
        const avgCurrent = 19;
        const powerFactor = 0.85;
        const operatingTime = 100;
        const powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 43905.340549404726);
    });

    it('should calculate power used correctly 2', function () {
        const motorPhase = 3;
        const supplyVoltage = 510;
        const avgCurrent = 19;
        const powerFactor = 0.85;
        const operatingTime = 100;
        const powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 48677.66017434002);
    });

    it('should calculate power used correctly 3', function () {
        const motorPhase = 3;
        const supplyVoltage = 510;
        const avgCurrent = 25;
        const powerFactor = 0.85;
        const operatingTime = 100;
        const powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 64049.552860973716);
    });


    it('should calculate power used correctly 4', function () {
        const motorPhase = 3;
        const supplyVoltage = 510;
        const avgCurrent = 25;
        const powerFactor = 0.55;
        const operatingTime = 100;
        const powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 41443.828321806526);
    });


    it('should calculate power used correctly 5', function () {
        const motorPhase = 3;
        const supplyVoltage = 510;
        const avgCurrent = 25;
        const powerFactor = 0.55;
        const operatingTime = 75;
        const powerUsed = moduleInstance.auxiliaryCalculatePowerUsed(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
        assert.equal(powerUsed, 31082.871241354896);
    });
});