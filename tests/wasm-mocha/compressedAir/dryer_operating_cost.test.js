import { assert } from 'chai';

describe('Steam Leak Survey', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function logMessage(msg, header) {
        if (header) console.log(`[${header}] ${msg}`);
        else console.log(msg);
    }

    function validateDryerOutput(results, expected) {
        assert.approximately(results.waterRemoved, expected.waterRemoved, .01, "waterRemoved");
        assert.approximately(results.totalCostPerYear, expected.totalCostPerYear, .01, "totalCostPerYear");

        results.delete();
    }

    it('calculates Dryer Operating Cost', function () {
        logMessage('Dryer Type Heatless: ', true);
        let dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.Heatless),
            {waterRemoved:73.34, totalCostPerYear: 60020.86, heaterPower: 0, heatingHoursPerDay: 0, purgeRate: 15, designDDCPercentage: 16.33});

        logMessage('Dryer Type HeatedExternally: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatedExternally),
            {waterRemoved:73.34, totalCostPerYear: 38193.08, heaterPower: 19.36, heatingHoursPerDay: 18, purgeRate: 7, designDDCPercentage: 16.33});

        logMessage('Dryer Type BlowerPurgeWithSweep: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.BlowerPurgeWithSweep),
            {waterRemoved:73.34, totalCostPerYear: 51442.40, heaterPower: 69.14, heatingHoursPerDay: 18, purgeRate: 7, designDDCPercentage: 16.33});

        logMessage('Dryer Type BlowerPurgeWithoutSweep: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.BlowerPurgeWithoutSweep),
            {waterRemoved:73.34, totalCostPerYear: 47161.58, heaterPower: 69.14, heatingHoursPerDay: 18, purgeRate: 7, designDDCPercentage: 16.33});

        logMessage('Dryer Type HeatOfCompressionHC: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC),
            {waterRemoved:73.34, totalCostPerYear: 3333.81, heaterPower: 3.05, heatingHoursPerDay: 3, purgeRate: 2, designDDCPercentage: 16.33});

        logMessage('Dryer Type HeatOfCompressionSP: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionSP),
            {waterRemoved:73.34, totalCostPerYear: 69.888, heaterPower: 0, heatingHoursPerDay: 0, purgeRate: 0, designDDCPercentage: 16.33});

        logMessage('Dryer Type Refrigerated: ', true);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.Refrigerated),
            {waterRemoved:63.944, totalCostPerYear: 8639.09, heaterPower: 0, heatingHoursPerDay: 0, purgeRate: 0, designDDCPercentage: 0});


        logMessage('Dryer Type HeatOfCompressionHC With Heater Power ', true);
        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            3.05, 0, 0, 0);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC),
            {waterRemoved:73.34, totalCostPerYear: 3333.81, heaterPower: 3.05, heatingHoursPerDay: 3, purgeRate: 2, designDDCPercentage: 16.33});

        logMessage('Dryer Type HeatOfCompressionHC With design DDC %: ', true);
        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            0, 0, 0, 16.33);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC),
            {waterRemoved:73.34, totalCostPerYear: 3333.81, heaterPower: 3.05, heatingHoursPerDay: 3, purgeRate: 2, designDDCPercentage: 16.33})

        logMessage('Dryer Type HeatOfCompressionHC With Heater Power, Heating Hours per Day, Purge Rate, design DDC %: ', true);
        dryerOperatingCost = new moduleInstance.DryerOperatingCost(1752, 50, 100,
            24, 7, 52,
            0.08, 0.2, 0.25,
            3.05, 3, 2, 16.33);
        validateDryerOutput(dryerOperatingCost.calculate(moduleInstance.DryerType.HeatOfCompressionHC),
            {waterRemoved:73.34, totalCostPerYear: 3333.81, heaterPower: 3.05, heatingHoursPerDay: 3, purgeRate: 2, designDDCPercentage: 16.33})

        dryerOperatingCost.delete();
    });
});