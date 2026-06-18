import { assert } from 'chai';
import createModule, {
    type CompressedAirReductionInput,
    type CompressedAirReductionInputV,
    type CompressedAirReductionOutput,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Compressed Air Reduction Tests', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate CompressedAirReduction Flow Meter Method (compressed air utility) correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.CompressedAir,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.FlowMeter,
            flowMeterMethodData: { meterReading: 200 },
            bagMethodData: { bagFillTime: 0, bagVolume: 0 },
            pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
            otherMethodData: { consumption: 0 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0 },
            units: 1
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.consumption,           103680000.0, 0.01,   'consumption');
        assert.approximately(results.flowRate,              200.0,       0.001,  'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 0.0,         0.001,  'singleNozzleFlowRate');
        assert.approximately(results.energyUse,            0.0,         0.001,  'energyUse');
        assert.approximately(results.energyCost,           12441600.0,  0.01,   'energyCost');
        inputVec.delete();
    });

    it('should calculate CompressedAirReduction Flow Meter Method (electricity utility) correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.FlowMeter,
            flowMeterMethodData: { meterReading: 200000 },
            bagMethodData: { bagFillTime: 0, bagVolume: 0 },
            pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
            otherMethodData: { consumption: 0 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
            units: 1
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.energyUse,            276480000.0,       0.01,   'energyUse');
        assert.approximately(results.energyCost,           33177600.0,        0.01,   'energyCost');
        assert.approximately(results.flowRate,             200000.0,          0.001,  'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 0.0,              0.001,  'singleNozzleFlowRate');
        assert.approximately(results.consumption,          103680000000.0,    0.01,   'consumption');
        inputVec.delete();
    });

    it('should calculate CompressedAirReduction Bag Method (electricity utility) correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Bag,
            flowMeterMethodData: { meterReading: 0 },
            bagMethodData: { bagFillTime: 12, bagVolume: 8.68 },
            pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
            otherMethodData: { consumption: 0 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
            units: 2
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.energyUse,            119992.32,   0.01,  'energyUse');
        assert.approximately(results.energyCost,           14399.0784,  0.01,  'energyCost');
        assert.approximately(results.flowRate,             43.4,        0.001, 'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 0.0,        0.001, 'singleNozzleFlowRate');
        assert.approximately(results.consumption,          44997120,  0.01,  'consumption');
        inputVec.delete();
    });

    it('should calculate CompressedAirReduction Pressure Method (electricity utility) correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Pressure,
            flowMeterMethodData: { meterReading: 0 },
            bagMethodData: { bagFillTime: 0, bagVolume: 0 },
            pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 80 },
            otherMethodData: { consumption: 0 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
            units: 1
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.energyUse,            2458.6094592,    0.001, 'energyUse');
        assert.approximately(results.energyCost,           295.033135104,   0.001, 'energyCost');
        assert.approximately(results.flowRate,             1.778508,        0.001, 'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 1.778508,       0.001, 'singleNozzleFlowRate');
        assert.approximately(results.consumption,          921978.5471999,  0.01,  'consumption');
        inputVec.delete();
    });

    it('should calculate CompressedAirReduction Pressure Method with multiple nozzles correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Pressure,
            flowMeterMethodData: { meterReading: 0 },
            bagMethodData: { bagFillTime: 0, bagVolume: 0},
            pressureMethodData: { nozzleType: 2, numberOfNozzles: 4, supplyPressure: 50 },
            otherMethodData: { consumption: 0 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
            units: 3
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.flowRate,             363.9248,       0.001, 'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 90.9812,       0.001, 'singleNozzleFlowRate');
        assert.approximately(results.consumption,          188658616.32,   0.01,  'consumption');
        assert.approximately(results.energyUse,            503089.64352,   0.001, 'energyUse');
        assert.approximately(results.energyCost,           60370.7572224,  0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate CompressedAirReduction Other Method (electricity utility) correctly', function () {
        const inputData: CompressedAirReductionInput = {
            hoursPerYear: 8640,
            utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
            utilityCost: 0.12,
            measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Other,
            flowMeterMethodData: { meterReading: 0 },
            bagMethodData: { bagFillTime: 0, bagVolume: 0 },
            pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
            otherMethodData: { consumption: 200000 },
            compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
            units: 1
        };

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        inputVec.push_back(inputData);

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.consumption, 200000.0,      0.01,  'consumption');
        assert.approximately(results.energyUse,   533.33333333,  0.001, 'energyUse');
        assert.approximately(results.energyCost,  64.0,          0.001, 'energyCost');
        inputVec.delete();
    });

    it('should calculate 4 CompressedAirReductions (all methods) correctly', function () {
        const inputs: CompressedAirReductionInput[] = [
            // Flow meter with electricity (utilityCost=0.066)
            {
                hoursPerYear: 8640,
                utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
                utilityCost: 0.066,
                measurementMethod: moduleInstance.CompressedAirMeasurementMethod.FlowMeter,
                flowMeterMethodData: { meterReading: 200000 },
                bagMethodData: { bagFillTime: 0, bagVolume: 0 },
                pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
                otherMethodData: { consumption: 0 },
                compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
                units: 1
            },
            // Bag method with electricity
            {
                hoursPerYear: 8640,
                utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
                utilityCost: 0.12,
                measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Bag,
                flowMeterMethodData: { meterReading: 0 },
                bagMethodData: { bagFillTime: 12, bagVolume: 8.68 },
                pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
                otherMethodData: { consumption: 0 },
                compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
                units: 1
            },
            // Pressure method with compressed air utility
            {
                hoursPerYear: 8640,
                utilityType: moduleInstance.CompressedAirUtilityType.CompressedAir,
                utilityCost: 0.12,
                measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Pressure,
                flowMeterMethodData: { meterReading: 0 },
                bagMethodData: { bagFillTime: 0, bagVolume: 0 },
                pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 80 },
                otherMethodData: { consumption: 0 },
                compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
                units: 1
            },
            // Other method with electricity
            {
                hoursPerYear: 8640,
                utilityType: moduleInstance.CompressedAirUtilityType.Electricity,
                utilityCost: 0.12,
                measurementMethod: moduleInstance.CompressedAirMeasurementMethod.Other,
                flowMeterMethodData: { meterReading: 0 },
                bagMethodData: { bagFillTime: 0, bagVolume: 0 },
                pressureMethodData: { nozzleType: 0, numberOfNozzles: 1, supplyPressure: 0 },
                otherMethodData: { consumption: 200000 },
                compressorElectricityData: { compressorControlAdjustment: 100, compressorSpecificPower: 0.16 },
                units: 1
            }
        ];

        const inputVec: CompressedAirReductionInputV = new moduleInstance.CompressedAirReductionInputV();
        for (let i = 0; i < inputs.length; i++) {
            inputVec.push_back(inputs[i]);
        }

        const results: CompressedAirReductionOutput = moduleInstance.compressedAirReduction(inputVec);
        assert.approximately(results.energyUse,            276540529.49,       0.01,  'energyUse');
        assert.approximately(results.energyCost,           18365580.96,        0.01,  'energyCost');
        assert.approximately(results.flowRate,             200045.178508,      0.001, 'flowRate');
        assert.approximately(results.singleNozzleFlowRate, 1.778508,          0.001, 'singleNozzleFlowRate');
        assert.approximately(results.consumption,          103703620538.55,    0.01,  'consumption');
        inputVec.delete();
    });
});
