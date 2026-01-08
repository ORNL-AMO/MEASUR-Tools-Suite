// efficiencyImprovement
function efficiencyImprovement() {

    var inp = {
        currentFlueGasOxygen: 6,
        newFlueGasOxygen: 2,
        currentFlueGasTemp: 1600,
        currentCombustionAirTemp: 80,
        newCombustionAirTemp: 750,
        currentEnergyInput: 10,
        newFlueGasTemp: 1200
    };

    var efficiencyImprovement = new Module.EfficiencyImprovement(inp.currentFlueGasOxygen, inp.newFlueGasOxygen, inp.currentFlueGasTemp, inp.newFlueGasTemp, inp.currentCombustionAirTemp, inp.newCombustionAirTemp, inp.currentEnergyInput);
    var currentExcessAir = efficiencyImprovement.getCurrentExcessAir();
    var newExcessAir = efficiencyImprovement.getNewExcessAir();
    var currentAvailableHeat = efficiencyImprovement.getCurrentAvailableHeat();
    var newAvailableHeat = efficiencyImprovement.getNewAvailableHeat();
    var newFuelSavings = efficiencyImprovement.getNewFuelSavings();
    var newEnergyInput = efficiencyImprovement.getNewEnergyInput();

    testNumberValue(currentExcessAir, 35.80000271600005, "Process Heat Efficiency Improvement (currentExcessAir)");
    testNumberValue(newExcessAir, 9.421053207479227, "Process Heat Efficiency Improvement (newExcessAir)");
    testNumberValue(currentAvailableHeat, 45.550889, "Process Heat Efficiency Improvement (currentAvailableHeat)");
    testNumberValue(newAvailableHeat, 77.893119, "Process Heat Efficiency Improvement (newAvailableHeat)");
    testNumberValue(newFuelSavings, 41.521293, "Process Heat Efficiency Improvement (newFuelSavings)");
    testNumberValue(newEnergyInput, 5.847870740975683, "Process Heat Efficiency Improvement (newEnergyInput)");
    efficiencyImprovement.delete();
}
// flowCalculations
function flowCalculations() {
    var inp = {
        // 7 is helium
        gasType: Module.Gas.HELIUM,
        specificGravity: 0.14,
        orificeDiameter: 5,
        insidePipeDiameter: 9,
        // 1 is sharp edge
        sectionType: Module.Section.SHARP_EDGE,
        dischargeCoefficient: 0.6,
        gasHeatingValue: 7325,
        gasTemperature: 52,
        gasPressure: 63,
        orificePressureDrop: 26,
        operatingTime: 16
    };
    var flowCalculations = new Module.FlowCalculationsEnergyUse(inp.gasType, inp.specificGravity, inp.orificeDiameter, inp.insidePipeDiameter, inp.sectionType, inp.dischargeCoefficient, inp.gasHeatingValue, inp.gasTemperature, inp.gasPressure, inp.orificePressureDrop, inp.operatingTime);
    var flow = flowCalculations.getFlow();
    var heatInput = flowCalculations.getHeatInput();
    var totalFlow = flowCalculations.getTotalFlow();
    testNumberValue(flow, 647312.3211663722, "Process Heat Flow Calculations (flow)");
    testNumberValue(heatInput, 75865.00404069883, "Process Heat Flow Calculations (heatInput)");
    testNumberValue(totalFlow, 10356997.138661955, "Process Heat Flow Calculations (totalFlow)");
    flowCalculations.delete();
}
efficiencyImprovement();
flowCalculations();