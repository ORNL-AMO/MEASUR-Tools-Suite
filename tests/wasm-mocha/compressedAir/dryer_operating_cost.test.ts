import { assert } from 'chai';
import createModule, {
    type DryerOperatingCost,
    type DryerOperatingCostInput,
    type DryerOperatingCostOutput,
    type MeasurToolsSuite,
} from 'measur-tools-suite';

type DryerOutputValues = Omit<DryerOperatingCostOutput, 'delete'>;

describe('Dryer Operating Cost', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function logMessage(msg: string): void {
        console.log(msg);
    }

    function validateDryerOutput(results: DryerOperatingCostOutput, expected: DryerOutputValues): void {
        try {
            assert.approximately(results.waterRemoved, expected.waterRemoved, 0.01, "waterRemoved");
            assert.approximately(results.totalCostPerYear, expected.totalCostPerYear, 0.01, "totalCostPerYear");
            assert.approximately(results.heaterPower, expected.heaterPower, 0.01, "heaterPower");
            assert.approximately(results.heatingHoursPerDay, expected.heatingHoursPerDay, 0.01, "heatingHoursPerDay");
            assert.approximately(results.purgeRate, expected.purgeRate, 0.01, "purgeRate");
            assert.approximately(results.designDDCPercentage, expected.designDDCPercentage, 0.01, "designDDCPercentage");
        } finally {
            results.delete();
        }
    }

    it('calculates Dryer Operating Cost', function () {
        let dryerOperatingCost: DryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25);

        try {
            logMessage('Dryer Type Heatless: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.Heatless), {
                waterRemoved: 73.34,
                totalCostPerYear: 60020.86,
                heaterPower: 0,
                heatingHoursPerDay: 0,
                purgeRate: 15,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type HeatedExternally: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatedExternally), {
                waterRemoved: 73.34,
                totalCostPerYear: 38193.08,
                heaterPower: 19.358,
                heatingHoursPerDay: 18,
                purgeRate: 7,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type BlowerPurgeWithSweep: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.BlowerPurgeWithSweep), {
                waterRemoved: 73.34,
                totalCostPerYear: 51442.40,
                heaterPower: 69.136,
                heatingHoursPerDay: 18,
                purgeRate: 7,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type BlowerPurgeWithoutSweep: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.BlowerPurgeWithoutSweep), {
                waterRemoved: 73.34,
                totalCostPerYear: 47161.58,
                heaterPower: 69.136,
                heatingHoursPerDay: 18,
                purgeRate: 7,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type HeatOfCompressionHC: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.0489,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type HeatOfCompressionSP: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionSP), {
                waterRemoved: 73.34,
                totalCostPerYear: 69.888,
                heaterPower: 0,
                heatingHoursPerDay: 0,
                purgeRate: 0,
                designDDCPercentage: 16.3299
            });

            logMessage('Dryer Type Refrigerated: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.Refrigerated), {
                waterRemoved: 63.944,
                totalCostPerYear: 8639.09,
                heaterPower: 0,
                heatingHoursPerDay: 0,
                purgeRate: 0,
                designDDCPercentage: 16.3299
            });
        } finally {
            dryerOperatingCost.delete();
        }

        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            3.05, 0, 0, 0);
        try {
            logMessage('Dryer Type HeatOfCompressionHC With Heater Power ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.05,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.3299
            });
        } finally {
            dryerOperatingCost.delete();
        }

        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            0, 0, 0, 16.33);
        try {
            logMessage('Dryer Type HeatOfCompressionHC With design DDC %: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.0501,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.33
            });
        } finally {
            dryerOperatingCost.delete();
        }

        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            3.05, 3, 2, 16.33);
        try {
            logMessage('Dryer Type HeatOfCompressionHC With Heater Power, Heating Hours per Day, Purge Rate, design DDC %: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.05,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.33
            });
        } finally {
            dryerOperatingCost.delete();
        }

        const input: DryerOperatingCostInput = {
            flowRate: 1752,
            pressure: 50,
            temperature: 100,
            operatingHoursPerDay: 24,
            operatingDaysPerWeek: 7,
            operatingWeeksPerYear: 52,
            costOfElectricity: 0.08,
            costOfCompressedAir: 0.2,
            costOfCoolingWater: 0.25,
            heaterPower: 3.05,
            heatingHoursPerDay: 3,
            purgeRate: 2,
            designDDCPercentage: 16.33
        };

        dryerOperatingCost = new moduleInstance.DryerOperatingCost(input);
        try {
            logMessage('Dryer Type HeatOfCompressionHC With Input: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.05,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.33
            });
        } finally {
            dryerOperatingCost.delete();
        }

        dryerOperatingCost = new moduleInstance.DryerOperatingCost({ ...input });
        try {
            logMessage('Dryer Type HeatOfCompressionHC With Literal Input: ');
            validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC), {
                waterRemoved: 73.34,
                totalCostPerYear: 3333.81,
                heaterPower: 3.05,
                heatingHoursPerDay: 3,
                purgeRate: 2,
                designDDCPercentage: 16.33
            });
        } finally {
            dryerOperatingCost.delete();
        }
    });
});
