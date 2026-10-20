import { assert } from 'chai';
import createModule, {
    type DryerType,
    type DryerOperatingCostInput,
    type DryerOperatingCostResult,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

describe('Dryer Operating Cost V2', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function workbookInput(
        dryerType: DryerType,
        purgeRate: number,
        designDDCPercentage: number,
        regenerationCycleLength: number,
        heatingHoursPerDay: number
    ): DryerOperatingCostInput {
        return {
            dryerType,
            flowRate: 1752,
            pressure: 50,
            temperature: 100,
            annualOperatingHours: 8736,
            costOfElectricity: 0.08,
            costOfCompressedAir: 0.2,
            costOfCoolingWater: 0.25,
            heaterPower: 0,
            heatingHoursPerDay,
            purgeRate,
            purgeFlowRate: 0,
            designDDCPercentage,
            regenerationCycleLength,
            motorPower: 0,
            purgeInputMode: moduleInstance.PurgeInputMode.PercentOfDryerCapacity,
        };
    }

    function validateOutput(actual: DryerOperatingCostResult, expected: DryerOperatingCostResult): void {
        assert.approximately(actual.waterRemoved, expected.waterRemoved, 0.01, 'waterRemoved');
        assert.approximately(actual.totalCostPerYear, expected.totalCostPerYear, 0.02, 'totalCostPerYear');
        assert.approximately(actual.heaterPower, expected.heaterPower, 0.001, 'heaterPower');
        assert.approximately(actual.heatingHoursPerDay, expected.heatingHoursPerDay, 0.001, 'heatingHoursPerDay');
        assert.approximately(actual.purgeRate, expected.purgeRate, 0.001, 'purgeRate');
        assert.approximately(actual.designDDCPercentage, expected.designDDCPercentage, 0.001, 'designDDCPercentage');
        assert.approximately(actual.purgeFlowRate, expected.purgeFlowRate, 0.001, 'purgeFlowRate');
        assert.approximately(actual.motorPower, expected.motorPower, 0.001, 'motorPower');
        assert.approximately(actual.regenerationCycleLength, expected.regenerationCycleLength, 0.001, 'regenerationCycleLength');
    }

    function calculate(input: DryerOperatingCostInput): DryerOperatingCostResult {
        return moduleInstance.calculateDryerOperatingCost(input);
    }

    it('matches the v2 workbook fixture for all dryer types', function () {
        validateOutput(calculate(workbookInput(moduleInstance.DryerType.Heatless, 15, 16.33, 4, 0)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 60020.8602,
            heaterPower: 0,
            heatingHoursPerDay: 0,
            purgeRate: 15,
            designDDCPercentage: 16.33,
            purgeFlowRate: 465.8912,
            motorPower: 0,
            regenerationCycleLength: 4,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.HeatedExternally, 7, 16.33, 4, 18)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 38227.1610,
            heaterPower: 19.3755,
            heatingHoursPerDay: 18,
            purgeRate: 7,
            designDDCPercentage: 16.33,
            purgeFlowRate: 217.6046,
            motorPower: 0,
            regenerationCycleLength: 4,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.BlowerPurgeWithSweep, 7, 16.33, 4, 18)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 51488.3255,
            heaterPower: 69.1983,
            heatingHoursPerDay: 18,
            purgeRate: 7,
            designDDCPercentage: 16.33,
            purgeFlowRate: 217.6046,
            motorPower: 15.6328,
            regenerationCycleLength: 4,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.BlowerPurgeWithoutSweep, 0, 16.33, 4, 18)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 47203.6804,
            heaterPower: 69.1983,
            heatingHoursPerDay: 18,
            purgeRate: 0,
            designDDCPercentage: 16.33,
            purgeFlowRate: 0,
            motorPower: 20.8437,
            regenerationCycleLength: 4,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.HeatOfCompressionHC, 2, 16.33, 4, 3)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 3336.4933,
            heaterPower: 3.0501,
            heatingHoursPerDay: 3,
            purgeRate: 2,
            designDDCPercentage: 16.33,
            purgeFlowRate: 62.1727,
            motorPower: 0,
            regenerationCycleLength: 4,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.HeatOfCompressionSP, 0, 4, 2, 0)), {
            waterRemoved: 73.4048,
            totalCostPerYear: 69.888,
            heaterPower: 0,
            heatingHoursPerDay: 0,
            purgeRate: 0,
            designDDCPercentage: 4,
            purgeFlowRate: 0,
            motorPower: 0,
            regenerationCycleLength: 2,
        });

        validateOutput(calculate(workbookInput(moduleInstance.DryerType.Refrigerated, 0, 0, 0, 0)), {
            waterRemoved: 64.0029,
            totalCostPerYear: 8639.0886,
            heaterPower: 0,
            heatingHoursPerDay: 0,
            purgeRate: 0,
            designDDCPercentage: 0,
            purgeFlowRate: 0,
            motorPower: 13.0526,
            regenerationCycleLength: 0,
        });
    });

    it('supports direct purge flow and manual sizing overrides', function () {
        const percentageInput = workbookInput(moduleInstance.DryerType.HeatedExternally, 7, 16.33, 4, 18);
        const percentageResult = calculate(percentageInput);
        const purgeFlowRate = percentageResult.purgeFlowRate;
        const percentageTotal = percentageResult.totalCostPerYear;

        const directInput: DryerOperatingCostInput = {
            ...percentageInput,
            purgeInputMode: moduleInstance.PurgeInputMode.DirectFlow,
            purgeRate: 0,
            purgeFlowRate,
            heaterPower: 15,
        };
        const directResult = calculate(directInput);
        assert.approximately(directResult.purgeRate, 7, 0.001);
        assert.strictEqual(directResult.heaterPower, 15);
        assert.notStrictEqual(directResult.totalCostPerYear, percentageTotal);

        const motorInput = workbookInput(moduleInstance.DryerType.BlowerPurgeWithoutSweep, 0, 16.33, 4, 18);
        motorInput.motorPower = 10;
        const motorResult = calculate(motorInput);
        assert.strictEqual(motorResult.motorPower, 10);
    });
});
