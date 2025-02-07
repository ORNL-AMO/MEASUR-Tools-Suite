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
// energyEquivalencyElectric
function energyEquivalencyElectric() {

    var inp = {
        fuelFiredEfficiency: 6.59,
        electricallyHeatedEfficiency: 50,
        fuelFiredHeatInput: 87.3
    };

    var energyEquivalencyElectric = new Module.ElectricalEnergyEquivalency(inp.fuelFiredEfficiency, inp.electricallyHeatedEfficiency, inp.fuelFiredHeatInput);
    var electricalHeatInput = energyEquivalencyElectric.getElectricalHeatInput();

    testNumberValue(electricalHeatInput, 3371.268678581893, "Process Heat Energy Equivalency Electric (electricalHeatInput)");
    energyEquivalencyElectric.delete();
}
// energyEquivalencyFuel
function energyEquivalencyFuel() {
    var inp = {
        electricallyHeatedEfficiency: 52.3,
        fuelFiredEfficiency: 58.9,
        electricalHeatInput: 700
    };
    var energyEquivalencyFuel = new Module.FuelFiredEnergyEquivalency(inp.electricallyHeatedEfficiency, inp.fuelFiredEfficiency, inp.electricalHeatInput);
    var fuelFiredHeatInput = energyEquivalencyFuel.getFuelFiredHeatInput();
    testNumberValue(fuelFiredHeatInput, 2.121391001697793, "Process Heat Energy Equivalency Fuel (fuelFiredHeatInput)");
    energyEquivalencyFuel.delete();
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
// o2Enrichment
function o2Enrichment() {
    var inp = {
        o2CombAir: 21, o2CombAirEnriched: 100, flueGasTemp: 1800, flueGasTempEnriched: 1900, o2FlueGas: 5,
        o2FlueGasEnriched: 1, combAirTemp: 900, combAirTempEnriched: 80, fuelConsumption: 10
    };
    var o2Enrichment = new Module.O2Enrichment(inp.o2CombAir, inp.o2CombAirEnriched, inp.flueGasTemp, inp.flueGasTempEnriched, inp.o2FlueGas, inp.o2FlueGasEnriched, inp.combAirTemp, inp.combAirTempEnriched, inp.fuelConsumption);
    var availableHeat = o2Enrichment.getAvailableHeat();
    var availableHeatEnriched = o2Enrichment.getAvailableHeatEnriched();
    var fuelSavingsEnriched = o2Enrichment.getFuelSavingsEnriched();
    var fuelConsumptionEnriched = o2Enrichment.getFuelConsumptionEnriched();

    testNumberValue(availableHeat, 61.97028577716948, "Process Heat O2 Enrichment (availableHeat-1)");
    testNumberValue(availableHeatEnriched, 74.2210855230995, "Process Heat O2 Enrichment (availableHeatEnriched-1)");
    testNumberValue(fuelSavingsEnriched, 16.505821303458657, "Process Heat O2 Enrichment (fuelSavingsEnriched-1)");
    testNumberValue(fuelConsumptionEnriched, 8.349417869654134, "Process Heat O2 Enrichment (fuelConsumptionEnriched-1)");

    inp.flueGasTemp = 2200;
    inp.flueGasTempEnriched = 2300;
    o2Enrichment = new Module.O2Enrichment(inp.o2CombAir, inp.o2CombAirEnriched, inp.flueGasTemp, inp.flueGasTempEnriched, inp.o2FlueGas, inp.o2FlueGasEnriched, inp.combAirTemp, inp.combAirTempEnriched, inp.fuelConsumption);
    availableHeat = o2Enrichment.getAvailableHeat();
    availableHeatEnriched = o2Enrichment.getAvailableHeatEnriched();
    fuelSavingsEnriched = o2Enrichment.getFuelSavingsEnriched();
    fuelConsumptionEnriched = o2Enrichment.getFuelConsumptionEnriched();

    testNumberValue(availableHeat, 49.7183629149, "Process Heat O2 Enrichment (availableHeat-2)");
    testNumberValue(availableHeatEnriched, 69.9474376972, "Process Heat O2 Enrichment (availableHeatEnriched-2)");
    testNumberValue(fuelSavingsEnriched, 28.9203942964, "Process Heat O2 Enrichment (fuelSavingsEnriched-2)");
    testNumberValue(fuelConsumptionEnriched, 7.1079605704, "Process Heat O2 Enrichment (fuelConsumptionEnriched-2)");

    inp.o2FlueGas = 8;
    inp.o2FlueGasEnriched = 3;
    o2Enrichment = new Module.O2Enrichment(inp.o2CombAir, inp.o2CombAirEnriched, inp.flueGasTemp, inp.flueGasTempEnriched, inp.o2FlueGas, inp.o2FlueGasEnriched, inp.combAirTemp, inp.combAirTempEnriched, inp.fuelConsumption);
    availableHeat = o2Enrichment.getAvailableHeat();
    availableHeatEnriched = o2Enrichment.getAvailableHeatEnriched();
    fuelSavingsEnriched = o2Enrichment.getFuelSavingsEnriched();
    fuelConsumptionEnriched = o2Enrichment.getFuelConsumptionEnriched();

    testNumberValue(availableHeat, 42.6248055296, "Process Heat O2 Enrichment (availableHeat-3)");
    testNumberValue(availableHeatEnriched, 65.7672982588, "Process Heat O2 Enrichment (availableHeatEnriched-3)");
    testNumberValue(fuelSavingsEnriched, 35.1884497948, "Process Heat O2 Enrichment (fuelSavingsEnriched-3)");
    testNumberValue(fuelConsumptionEnriched, 6.4811550205, "Process Heat O2 Enrichment (fuelConsumptionEnriched-3)");

    inp.combAirTemp = 1100;
    inp.combAirTempEnriched = 110;
    o2Enrichment = new Module.O2Enrichment(inp.o2CombAir, inp.o2CombAirEnriched, inp.flueGasTemp, inp.flueGasTempEnriched, inp.o2FlueGas, inp.o2FlueGasEnriched, inp.combAirTemp, inp.combAirTempEnriched, inp.fuelConsumption);
    availableHeat = o2Enrichment.getAvailableHeat();
    availableHeatEnriched = o2Enrichment.getAvailableHeatEnriched();
    fuelSavingsEnriched = o2Enrichment.getFuelSavingsEnriched();
    fuelConsumptionEnriched = o2Enrichment.getFuelConsumptionEnriched();

    testNumberValue(availableHeat, 49.1204784776, "Process Heat O2 Enrichment (availableHeat-4)");
    testNumberValue(availableHeatEnriched, 66.3723712295, "Process Heat O2 Enrichment (availableHeatEnriched-4)");
    testNumberValue(fuelSavingsEnriched, 25.9925816002, "Process Heat O2 Enrichment (fuelSavingsEnriched-4)");
    testNumberValue(fuelConsumptionEnriched, 7.40074184, "Process Heat O2 Enrichment (fuelConsumptionEnriched-4)");
    o2Enrichment.delete();
}
// humidityRatio
function humidityRatio() {
    var inp = {
        atmosphericPressure: 0.8,
        dryBulbTemp: 120,
        relativeHumidity: 30,
        wetBulbTemp: 85
    };
    var humidityRatio = new Module.HumidityRatio(inp.atmosphericPressure, inp.dryBulbTemp, inp.relativeHumidity, inp.wetBulbTemp);
    var humidityRatioUsingRH = humidityRatio.getHumidityRatioUsingRH();
    var humidityRatioUsingWBT = humidityRatio.getHumidityRatioUsingWBT();
    testNumberValue(humidityRatioUsingRH, 0.028113628942036617, "Process Heat Humidity Ratio (humidityRatioUsingRH)");
    testNumberValue(humidityRatioUsingWBT, 0.024579434176341366, "Process Heat Humidity Ratio (humidityRatioUsingWBT)");
    humidityRatio.delete();
}

efficiencyImprovement();
energyEquivalencyElectric();
energyEquivalencyFuel();
flowCalculations();
o2Enrichment();
humidityRatio();
