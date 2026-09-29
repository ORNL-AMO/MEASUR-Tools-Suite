import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type ReceiverTankBridgingInput,
    type ReceiverTankCompressorCycleInput,
    type ReceiverTankCompressorCycleResult,
    type ReceiverTankDedicatedStorageInput,
    type ReceiverTankGeneralInput,
    type ReceiverTankMeteredStorageInput,
    type ReceiverTankMeteredStorageResult,
    type ReceiverTankSizeResult,
    type ReceiverTankUsableCapacityInput,
    type ReceiverTankUsableCapacityResult,
} from 'measur-tools-suite';

describe('Compressed Air Receiver Tank', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate usable capacity (10 psi differential, 660 gal tank)', function () {
        const inp: ReceiverTankUsableCapacityInput = { tankSize: 660, airPressureIn: 110, airPressureOut: 100 };
        const result: ReceiverTankUsableCapacityResult = moduleInstance.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 60.024009603, 0.01);
    });

    it('should calculate usable capacity (10 psi differential, 760 gal tank)', function () {
        const inp: ReceiverTankUsableCapacityInput = { tankSize: 760, airPressureIn: 110, airPressureOut: 100 };
        const result: ReceiverTankUsableCapacityResult = moduleInstance.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 69.1185565135, 0.01);
    });

    it('should calculate usable capacity (50 psi differential)', function () {
        const inp: ReceiverTankUsableCapacityInput = { tankSize: 760, airPressureIn: 150, airPressureOut: 100 };
        const result: ReceiverTankUsableCapacityResult = moduleInstance.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 345.5927825676, 0.01);
    });

    it('should calculate usable capacity (20 psi differential at higher pressure)', function () {
        const inp: ReceiverTankUsableCapacityInput = { tankSize: 760, airPressureIn: 150, airPressureOut: 130 };
        const result: ReceiverTankUsableCapacityResult = moduleInstance.calculateReceiverTankUsableCapacity(inp);
        assert.approximately(result.usableCapacity, 138.237113027, 0.01);
    });

    it('should calculate tank size using the General method (case 1)', function () {
        const inp: ReceiverTankGeneralInput = { airDemand: 150, allowablePressureDrop: 3, atmosphericPressure: 14.7 };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankGeneralSize(inp);
        assert.approximately(result.tankSize, 5497.8, 0.01);
    });

    it('should calculate tank size using the General method (case 2)', function () {
        const inp: ReceiverTankGeneralInput = { airDemand: 190, allowablePressureDrop: 8, atmosphericPressure: 12.7 };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankGeneralSize(inp);
        assert.approximately(result.tankSize, 2256.155, 0.01);
    });

    it('should calculate tank size using the Dedicated Storage method (case 1)', function () {
        const inp: ReceiverTankDedicatedStorageInput = {
            lengthOfDemand: 0.5, airFlowRequirement: 100,
            atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
        };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankDedicatedStorageSize(inp);
        assert.approximately(result.tankSize, 549.78, 0.01);
    });

    it('should calculate tank size using the Dedicated Storage method (case 2)', function () {
        const inp: ReceiverTankDedicatedStorageInput = {
            lengthOfDemand: 1.5, airFlowRequirement: 120,
            atmosphericPressure: 11.7, initialTankPressure: 150, finalTankPressure: 100
        };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankDedicatedStorageSize(inp);
        assert.approximately(result.tankSize, 315.0576, 0.01);
    });

    it('should calculate tank size using the Metered Storage method (case 1)', function () {
        const inp: ReceiverTankMeteredStorageInput = {
            lengthOfDemand: 0.5, airFlowRequirement: 900,
            atmosphericPressure: 14.7, initialTankPressure: 100, finalTankPressure: 70,
            meteredFlowControl: 45
        };
        const result: ReceiverTankMeteredStorageResult = moduleInstance.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.tankSize, 1566.873, 0.01);
    });

    it('should calculate tank size using the Metered Storage method (case 2)', function () {
        const inp: ReceiverTankMeteredStorageInput = {
            lengthOfDemand: 1.5, airFlowRequirement: 800,
            atmosphericPressure: 11.7, initialTankPressure: 120, finalTankPressure: 90,
            meteredFlowControl: 75
        };
        const result: ReceiverTankMeteredStorageResult = moduleInstance.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.tankSize, 3172.455, 0.01);
    });

    it('should calculate refill time using the Metered Storage method', function () {
        const inp: ReceiverTankMeteredStorageInput = {
            lengthOfDemand: 0.333, airFlowRequirement: 640,
            atmosphericPressure: 14.7, initialTankPressure: 97, finalTankPressure: 90,
            meteredFlowControl: 300
        };
        const result: ReceiverTankMeteredStorageResult = moduleInstance.calculateReceiverTankMeteredStorageSize(inp);
        assert.approximately(result.refillTime, 22.642, 0.01);
    });

    it('should calculate tank size using the Bridging method (case 1)', function () {
        const inp: ReceiverTankBridgingInput = {
            distanceToCompressorRoom: 1000, speedOfAir: 250,
            atmosphericPressure: 14.7, airDemandCfm: 600, allowablePressureDrop: 2
        };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankBridgingSize(inp);
        assert.approximately(result.tankSize, 2199.12, 0.01);
    });

    it('should calculate tank size using the Bridging method (case 2)', function () {
        const inp: ReceiverTankBridgingInput = {
            distanceToCompressorRoom: 1200, speedOfAir: 350,
            atmosphericPressure: 11.7, airDemandCfm: 800, allowablePressureDrop: 19
        };
        const result: ReceiverTankSizeResult = moduleInstance.calculateReceiverTankBridgingSize(inp);
        assert.approximately(result.tankSize, 210.56481203, 0.01);
    });

    it('should calculate tank size using the Compressor Cycle method (case 1)', function () {
        const inp: ReceiverTankCompressorCycleInput = {
            loadTime: 15, unloadTime: 5, compressorCapacity: 100,
            unloadPressure: 110, fullLoadPressure: 100, atmosphericPressure: 14.7
        };
        const result: ReceiverTankCompressorCycleResult = moduleInstance.calculateReceiverTankCompressorCycleSize(inp);
        assert.approximately(result.tankSize, 68.7225, 0.01);
        assert.approximately(result.effectiveCapacity, 75.0, 0.01);
        assert.approximately(result.pressureChange, 10.0, 0.01);
        assert.approximately(result.volumeCf, 9.1875, 0.01);
    });

    it('should calculate tank size using the Compressor Cycle method (case 2)', function () {
        const inp: ReceiverTankCompressorCycleInput = {
            loadTime: 20, unloadTime: 10, compressorCapacity: 200,
            unloadPressure: 120, fullLoadPressure: 100, atmosphericPressure: 14.7
        };
        const result: ReceiverTankCompressorCycleResult = moduleInstance.calculateReceiverTankCompressorCycleSize(inp);
        assert.approximately(result.tankSize, 122.1733333, 0.01);
        assert.approximately(result.effectiveCapacity, 133.3333333, 0.01);
        assert.approximately(result.pressureChange, 20.0, 0.01);
        assert.approximately(result.volumeCf, 16.3333333, 0.01);
    });

    it('should calculate tank size using the Compressor Cycle method (case 3)', function () {
        const inp: ReceiverTankCompressorCycleInput = {
            loadTime: 10, unloadTime: 5, compressorCapacity: 150,
            unloadPressure: 105, fullLoadPressure: 100, atmosphericPressure: 14.7
        };
        const result: ReceiverTankCompressorCycleResult = moduleInstance.calculateReceiverTankCompressorCycleSize(inp);
        assert.approximately(result.tankSize, 183.26, 0.01);
        assert.approximately(result.effectiveCapacity, 100.0, 0.01);
        assert.approximately(result.pressureChange, 5.0, 0.01);
        assert.approximately(result.volumeCf, 24.5, 0.01);
    });

    it('should calculate tank size using the Compressor Cycle method (non-default atmospheric pressure)', function () {
        const inp: ReceiverTankCompressorCycleInput = {
            loadTime: 10, unloadTime: 5, compressorCapacity: 150,
            unloadPressure: 105, fullLoadPressure: 100, atmosphericPressure: 12.0
        };
        const result: ReceiverTankCompressorCycleResult = moduleInstance.calculateReceiverTankCompressorCycleSize(inp);
        assert.approximately(result.tankSize, 149.6, 0.01);
        assert.approximately(result.effectiveCapacity, 100.0, 0.01);
        assert.approximately(result.pressureChange, 5.0, 0.01);
        assert.approximately(result.volumeCf, 20.0, 0.01);
    });

    it('should calculate tank size using the Compressor Cycle method (case 5)', function () {
        const inp: ReceiverTankCompressorCycleInput = {
            loadTime: 25, unloadTime: 15, compressorCapacity: 300,
            unloadPressure: 115, fullLoadPressure: 95, atmosphericPressure: 14.7
        };
        const result: ReceiverTankCompressorCycleResult = moduleInstance.calculateReceiverTankCompressorCycleSize(inp);
        assert.approximately(result.tankSize, 257.709375, 0.01);
        assert.approximately(result.effectiveCapacity, 187.5, 0.01);
        assert.approximately(result.pressureChange, 20.0, 0.01);
        assert.approximately(result.volumeCf, 34.453125, 0.01);
    });
});
