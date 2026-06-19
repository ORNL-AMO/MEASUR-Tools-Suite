import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type NaturalGasReductionInput,
    type NaturalGasReductionInputV,
    type NaturalGasReductionOutput,
} from 'measur-tools-suite';

describe('Natural Gas Reduction Tests', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate NaturalGasReduction Flow Meter Method correctly', function () {
        const inputData: NaturalGasReductionInput = {
            operatingHours: 8640,
            fuelCost: 0.12,
            measurementMethod: moduleInstance.NaturalGasMeasurementMethod.FlowMeter,
            flowMeterMethodData: { flowRate: 5 },
            otherMethodData: { consumption: 200000 },
            airMassFlowData: {
                isNameplate: true,
                measuredData: { areaOfDuct: 50, airVelocity: 200 },
                nameplateData: { airFlow: 10000 },
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 100
            },
            waterMassFlowData: {
                waterFlow: 400,
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 100
            },
            units: 2
        };

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        inputVec.push_back(inputData);
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 88.992, 0.001, "energyUse");
        assert.approximately(results.energyCost, 10.67904, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 10, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate NaturalGasReduction Air Mass Flow Nameplate correctly', function () {
        const inputData: NaturalGasReductionInput = {
            operatingHours: 8640,
            fuelCost: 0.12,
            measurementMethod: moduleInstance.NaturalGasMeasurementMethod.AirMassFlow,
            flowMeterMethodData: { flowRate: 5 },
            otherMethodData: { consumption: 200000 },
            airMassFlowData: {
                isNameplate: true,
                measuredData: { areaOfDuct: 50, airVelocity: 200 },
                nameplateData: { airFlow: 30 },
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            waterMassFlowData: {
                waterFlow: 400,
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            units: 2
        };

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        inputVec.push_back(inputData);
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 44.78976, 0.001, "energyUse");
        assert.approximately(results.energyCost, 5.37477, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0.002592, 0.000001, "heatFlow");
        assert.approximately(results.totalFlow, 60, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate NaturalGasReduction Air Mass Flow Measured correctly', function () {
        const inputData: NaturalGasReductionInput = {
            operatingHours: 8640,
            fuelCost: 0.12,
            measurementMethod: moduleInstance.NaturalGasMeasurementMethod.AirMassFlow,
            flowMeterMethodData: { flowRate: 5 },
            otherMethodData: { consumption: 200000 },
            airMassFlowData: {
                isNameplate: false,
                measuredData: { areaOfDuct: 50, airVelocity: 200 },
                nameplateData: { airFlow: 30 },
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            waterMassFlowData: {
                waterFlow: 400,
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            units: 2
        };

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        inputVec.push_back(inputData);
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 14929.92, 0.01, "energyUse");
        assert.approximately(results.energyCost, 1791.5904, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0.864, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 20000, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate NaturalGasReduction Water Mass Flow correctly', function () {
        const inputData: NaturalGasReductionInput = {
            operatingHours: 8640,
            fuelCost: 0.12,
            measurementMethod: moduleInstance.NaturalGasMeasurementMethod.WaterMassFlow,
            flowMeterMethodData: { flowRate: 5 },
            otherMethodData: { consumption: 200000 },
            airMassFlowData: {
                isNameplate: false,
                measuredData: { areaOfDuct: 50, airVelocity: 200 },
                nameplateData: { airFlow: 30 },
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            waterMassFlowData: {
                waterFlow: 400,
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            units: 2
        };

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        inputVec.push_back(inputData);
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 276480, 0.001, "energyUse");
        assert.approximately(results.energyCost, 33177.6, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 16, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 800, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate NaturalGasReduction Other Method correctly', function () {
        const inputData: NaturalGasReductionInput = {
            operatingHours: 8640,
            fuelCost: 0.12,
            measurementMethod: moduleInstance.NaturalGasMeasurementMethod.Other,
            flowMeterMethodData: { flowRate: 5 },
            otherMethodData: { consumption: 2000 },
            airMassFlowData: {
                isNameplate: false,
                measuredData: { areaOfDuct: 50, airVelocity: 200 },
                nameplateData: { airFlow: 30 },
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            waterMassFlowData: {
                waterFlow: 400,
                inletTemperature: 120,
                outletTemperature: 200,
                systemEfficiency: 1
            },
            units: 2
        };

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        inputVec.push_back(inputData);
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 2000, 0.001, "energyUse");
        assert.approximately(results.energyCost, 240, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 0, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate NaturalGasReduction All Methods correctly', function () {
        const inputs: NaturalGasReductionInput[] = [
            // flow meter method
            {
                operatingHours: 8640, fuelCost: 0.12,
                measurementMethod: moduleInstance.NaturalGasMeasurementMethod.FlowMeter,
                flowMeterMethodData: { flowRate: 5 },
                otherMethodData: { consumption: 200000 },
                airMassFlowData: { isNameplate: true, measuredData: { areaOfDuct: 50, airVelocity: 200 },
                    nameplateData: { airFlow: 10000 }, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 100 },
                waterMassFlowData: { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 100 },
                units: 2
            },
            // air mass flow nameplate
            {
                operatingHours: 8640, fuelCost: 0.12,
                measurementMethod: moduleInstance.NaturalGasMeasurementMethod.AirMassFlow,
                flowMeterMethodData: { flowRate: 5 },
                otherMethodData: { consumption: 200000 },
                airMassFlowData: { isNameplate: true, measuredData: { areaOfDuct: 50, airVelocity: 200 },
                    nameplateData: { airFlow: 30 }, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                waterMassFlowData: { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                units: 2
            },
            // air mass flow measured
            {
                operatingHours: 8640, fuelCost: 0.12,
                measurementMethod: moduleInstance.NaturalGasMeasurementMethod.AirMassFlow,
                flowMeterMethodData: { flowRate: 5 },
                otherMethodData: { consumption: 200000 },
                airMassFlowData: { isNameplate: false, measuredData: { areaOfDuct: 50, airVelocity: 200 },
                    nameplateData: { airFlow: 30 }, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                waterMassFlowData: { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                units: 2
            },
            // water mass flow method
            {
                operatingHours: 8640, fuelCost: 0.12,
                measurementMethod: moduleInstance.NaturalGasMeasurementMethod.WaterMassFlow,
                flowMeterMethodData: { flowRate: 5 },
                otherMethodData: { consumption: 200000 },
                airMassFlowData: { isNameplate: false, measuredData: { areaOfDuct: 50, airVelocity: 200 },
                    nameplateData: { airFlow: 30 }, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                waterMassFlowData: { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                units: 2
            },
            // other/off sheet method
            {
                operatingHours: 8640, fuelCost: 0.12,
                measurementMethod: moduleInstance.NaturalGasMeasurementMethod.Other,
                flowMeterMethodData: { flowRate: 5 },
                otherMethodData: { consumption: 2000 },
                airMassFlowData: { isNameplate: false, measuredData: { areaOfDuct: 50, airVelocity: 200 },
                    nameplateData: { airFlow: 30 }, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                waterMassFlowData: { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 },
                units: 2
            }
        ];

        const inputVec: NaturalGasReductionInputV = new moduleInstance.NaturalGasReductionInputV();
        for (let inp of inputs) {
            inputVec.push_back(inp);
        }
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasReduction(inputVec);
        assert.approximately(results.energyUse, 293543.70176, 0.001, "energyUse");
        assert.approximately(results.energyCost, 35225.2442112, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 16.866592, 0.0001, "heatFlow");
        assert.approximately(results.totalFlow, 20870, 0.001, "totalFlow");
        inputVec.delete();
    });

    it('should calculate flowMeterMethodReduction standalone correctly', function () {
        const results: NaturalGasReductionOutput = moduleInstance.flowMeterMethodReduction({ flowRate: 5 }, 8640, 0.12, 2);
        assert.approximately(results.energyUse, 88.992, 0.001, "energyUse");
        assert.approximately(results.energyCost, 10.67904, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 10, 0.001, "totalFlow");
    });

    it('should calculate waterMassFlowMethodReduction standalone correctly', function () {
        const results: NaturalGasReductionOutput = moduleInstance.waterMassFlowMethodReduction(
            { waterFlow: 400, inletTemperature: 120, outletTemperature: 200, systemEfficiency: 1 }, 8640, 0.12, 2);
        assert.approximately(results.energyUse, 276480, 0.001, "energyUse");
        assert.approximately(results.energyCost, 33177.6, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 16, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 800, 0.001, "totalFlow");
    });

    it('should calculate naturalGasOtherMethodReduction standalone correctly', function () {
        const results: NaturalGasReductionOutput = moduleInstance.naturalGasOtherMethodReduction({ consumption: 2000 }, 0.12);
        assert.approximately(results.energyUse, 2000, 0.001, "energyUse");
        assert.approximately(results.energyCost, 240, 0.001, "energyCost");
        assert.approximately(results.heatFlow, 0, 0.001, "heatFlow");
        assert.approximately(results.totalFlow, 0, 0.001, "totalFlow");
    });
});