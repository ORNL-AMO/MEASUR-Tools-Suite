import { assert } from 'chai';

describe('Compressed Air Receiver Tank Size', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate tank size using the General method (case 1)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.General,
            airDemand: 150,
            allowablePressureDrop: 3,
            atmosphericPressure: 14.7
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.airDemand, inp.allowablePressureDrop, inp.atmosphericPressure
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 5497.8, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the General method (case 2)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.General,
            airDemand: 190,
            allowablePressureDrop: 8,
            atmosphericPressure: 12.7
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.airDemand, inp.allowablePressureDrop, inp.atmosphericPressure
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 2256.155, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the DedicatedStorage method (case 1)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.DedicatedStorage,
            lengthOfDemand: 0.5,
            airFlowRequirement: 100,
            atmosphericPressure: 14.7,
            initialTankPressure: 110,
            finalTankPressure: 100
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 549.78, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the DedicatedStorage method (case 2)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.DedicatedStorage,
            lengthOfDemand: 0.5,
            airFlowRequirement: 100,
            atmosphericPressure: 14.7,
            initialTankPressure: 110,
            finalTankPressure: 100
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 549.78, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the DedicatedStorage method (case 3)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.DedicatedStorage,
            lengthOfDemand: 1.5,
            airFlowRequirement: 120,
            atmosphericPressure: 11.7,
            initialTankPressure: 150,
            finalTankPressure: 100
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 315.0576, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the MeteredStorage method (case 1)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.MeteredStorage,
            lengthOfDemand: 0.5,
            airFlowRequirement: 900,
            atmosphericPressure: 14.7,
            initialTankPressure: 100,
            finalTankPressure: 70,
            meteredControl: 45
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure, inp.meteredControl
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 1566.873, 0.01);

        receiverTank.delete();
    });

    it('should calculate refill time using the MeteredStorage method', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.MeteredStorage,
            lengthOfDemand: 0.333,
            airFlowRequirement: 640,
            atmosphericPressure: 14.7,
            initialTankPressure: 97,
            finalTankPressure: 90,
            meteredControl: 300
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure, inp.meteredControl
        );
        const result = receiverTank.calculateRefillTime();

        assert.approximately(result, 22.642, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the MeteredStorage method (case 2)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.MeteredStorage,
            lengthOfDemand: 1.5,
            airFlowRequirement: 800,
            atmosphericPressure: 11.7,
            initialTankPressure: 120,
            finalTankPressure: 90,
            meteredControl: 75
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.lengthOfDemand, inp.airFlowRequirement,
            inp.atmosphericPressure, inp.initialTankPressure, inp.finalTankPressure, inp.meteredControl
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 3172.455, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the BridgingCompressorReactionDelay method (case 1)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.BridgingCompressorReactionDelay,
            distanceToCompressorRoom: 1000,
            speedOfAir: 250,
            atmosphericPressure: 14.7,
            airDemand: 600,
            allowablePressureDrop: 2
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.distanceToCompressorRoom, inp.speedOfAir,
            inp.atmosphericPressure, inp.airDemand, inp.allowablePressureDrop
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 2199.12, 0.01);

        receiverTank.delete();
    });

    it('should calculate tank size using the BridgingCompressorReactionDelay method (case 2)', function () {
        const inp = {
            method: moduleInstance.ReceiverTankMethod.BridgingCompressorReactionDelay,
            distanceToCompressorRoom: 1200,
            speedOfAir: 350,
            atmosphericPressure: 11.7,
            airDemand: 800,
            allowablePressureDrop: 19
        };

        const receiverTank = new moduleInstance.ReceiverTank(
            inp.method, inp.distanceToCompressorRoom, inp.speedOfAir,
            inp.atmosphericPressure, inp.airDemand, inp.allowablePressureDrop
        );
        const result = receiverTank.calculateSize();

        assert.approximately(result, 210.564812, 0.01);

        receiverTank.delete();
    });
});
