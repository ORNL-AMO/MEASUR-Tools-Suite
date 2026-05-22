import { assert } from 'chai';

describe('Compressed Air Receiver Tank', function () {
    let m;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        m = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    // ---- Usable Air Capacity ----

    it('should calculate usable capacity (10 psi differential, 660 gal tank)', function () {
        const inp = { tankSize: 660, airPressureIn: 110, airPressureOut: 100 };
        const result = m.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 60.024009603, 0.01);
    });

    it('should calculate usable capacity (10 psi differential, 760 gal tank)', function () {
        const inp = { tankSize: 760, airPressureIn: 110, airPressureOut: 100 };
        const result = m.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 69.1185565135, 0.01);
    });

    it('should calculate usable capacity (50 psi differential)', function () {
        const inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 100 };
        const result = m.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 345.5927825676, 0.01);
    });

    it('should calculate usable capacity (20 psi differential at higher pressure)', function () {
        const inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 130 };
        const result = m.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 138.237113027, 0.01);
    });

    // ---- General Method ----

    it('should calculate tank size using the General method (case 1)', function () {
        const inp = { airDemand: 150, allowablePressureDrop: 3, atmosphericPressure: 14.7 };
        const result = m.calculateReceiverTankGeneralSize(inp);
        assert.approximately(result.tankSize, 5497.8, 0.01);
    });

    it('should calculate tank size using the General method (case 2)', function () {
        const inp = { airDemand: 190, allowablePressureDrop: 8, atmosphericPressure: 12.7 };
        const result = m.calculateReceiverTankGeneralSize(inp);
        assert.approximately(result.tankSize, 2256.155, 0.01);
    });

    // ---- Dedicated Storage Method ----

    it('should calculate tank size using the Dedicated Storage method (case 1)', function () {
        const inp = {
            lengthOfDemand: 0.5, airFlowRequirement: 100,
            atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
        };
        const result = m.calculateReceiverTankDedicatedStorageSize(inp);
        assert.approximately(result.tankSize, 549.78, 0.01);
    });

    it('should calculate tank size using the Dedicated Storage method (case 2)', function () {
        const inp = {
            lengthOfDemand: 1.5, airFlowRequirement: 120,
            atmosphericPressure: 11.7, initialTankPressure: 150, finalTankPressure: 100
        };
        const result = m.calculateReceiverTankDedicatedStorageSize(inp);
        assert.approximately(result.tankSize, 315.0576, 0.01);
    });

    // ---- Metered Storage Method ----

    it('should calculate tank size using the Metered Storage method (case 1)', function () {
        const inp = {
            lengthOfDemand: 0.5, airFlowRequirement: 900,
            atmosphericPressure: 14.7, initialTankPressure: 100, finalTankPressure: 70,
            meteredFlowControl: 45
        };
        const result = m.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.tankSize, 1566.873, 0.01);
    });

    it('should calculate tank size using the Metered Storage method (case 2)', function () {
        const inp = {
            lengthOfDemand: 1.5, airFlowRequirement: 800,
            atmosphericPressure: 11.7, initialTankPressure: 120, finalTankPressure: 90,
            meteredFlowControl: 75
        };
        const result = m.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.tankSize, 3172.455, 0.01);
    });

    it('should calculate refill time using the Metered Storage method', function () {
        const inp = {
            lengthOfDemand: 0.333, airFlowRequirement: 640,
            atmosphericPressure: 14.7, initialTankPressure: 97, finalTankPressure: 90,
            meteredFlowControl: 300
        };
        const result = m.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.refillTime, 22.642, 0.01);
    });

    // ---- Bridging Compressor Reaction Delay Method ----

    it('should calculate tank size using the Bridging method (case 1)', function () {
        const inp = {
            distanceToCompressorRoom: 1000, speedOfAir: 250,
            atmosphericPressure: 14.7, airDemandCfm: 600, allowablePressureDrop: 2
        };
        const result = m.calculateReceiverTankBridgingSize(inp);
        assert.approximately(result.tankSize, 2199.12, 0.01);
    });

    it('should calculate tank size using the Bridging method (case 2)', function () {
        const inp = {
            distanceToCompressorRoom: 1200, speedOfAir: 350,
            atmosphericPressure: 11.7, airDemandCfm: 800, allowablePressureDrop: 19
        };
        const result = m.calculateReceiverTankBridgingSize(inp);
        assert.approximately(result.tankSize, 210.56481203, 0.01);
    });
});
