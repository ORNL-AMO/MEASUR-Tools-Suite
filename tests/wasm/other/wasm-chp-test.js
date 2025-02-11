// CHP
function CHP() {
    var inp = {
        annualOperatingHours: 4160,
        annualElectricityConsumption: 23781908,
        annualThermalDemand: 122581,
        boilerThermalFuelCosts: 5.49,
        avgElectricityCosts: 0.214,
        option: Module.CHPOption.PercentAvgkWhElectricCostAvoided,
        boilerThermalFuelCostsCHPcase: 5.49,
        CHPfuelCosts: 5.49,
        percentAvgkWhElectricCostAvoidedOrStandbyRate: 90,
        displacedThermalEfficiency: 85,
        chpAvailability: 95,
        thermalUtilization: 90
    };

    let chp = new Module.CHP(inp.annualOperatingHours, inp.annualElectricityConsumption, inp.annualThermalDemand, inp.boilerThermalFuelCosts, inp.avgElectricityCosts, inp.option, inp.boilerThermalFuelCostsCHPcase, inp.CHPfuelCosts, inp.percentAvgkWhElectricCostAvoidedOrStandbyRate, inp.displacedThermalEfficiency, inp.chpAvailability, inp.thermalUtilization);
    let result = chp.getCostInfo();
    testNumberValue(result.annualOperationSavings, 3251705.06182641, "CHP (annualOperationSavings-1)");
    testNumberValue(result.totalInstalledCostsPayback, 11890954.0, "CHP (totalInstalledCostsPayback-1)");
    testNumberValue(result.simplePayback, 3.595330381, "CHP (simplePayback-1)");
    testNumberValue(result.fuelCosts, 0.0648161938, "CHP (fuelCosts-1)");
    testNumberValue(result.thermalCredit, -0.0284427212, "CHP (thermalCredit-1)");
    testNumberValue(result.incrementalOandM, 0.0123, "CHP (incrementalOandM-1)");
    testNumberValue(result.totalOperatingCosts, 0.0486734726, "CHP (totalOperatingCosts-1)");

    inp.option = Module.CHPOption.StandbyRate;
    inp.percentAvgkWhElectricCostAvoidedOrStandbyRate = 9.75;
    chp = new Module.CHP(inp.annualOperatingHours, inp.annualElectricityConsumption, inp.annualThermalDemand, inp.boilerThermalFuelCosts, inp.avgElectricityCosts, inp.option, inp.boilerThermalFuelCostsCHPcase, inp.CHPfuelCosts, inp.percentAvgkWhElectricCostAvoidedOrStandbyRate, inp.displacedThermalEfficiency, inp.chpAvailability, inp.thermalUtilization);
    result = chp.getCostInfo();
    testNumberValue(result.annualOperationSavings, 3066325.0889664106, "CHP (annualOperationSavings-2)");
    testNumberValue(result.simplePayback, 3.8126922817, "CHP (simplePayback-2)");
    chp.delete();
}

CHP();
