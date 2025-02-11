function atmosphere() {
    var inletTemperature = 100.0
    var outletTemperature = 1400.0;
    var flowRate = 1200.0;
    var correctionFactor = 1.0;
    var specificHeat = 0.02;

    let atmosphere = new Module.Atmosphere(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
    let result = atmosphere.getTotalHeat();
    testNumberValue(result, 31200.0, "Process Heat Atmosphere (atmosphere)");
    atmosphere.delete();
}

function auxiliaryPowerLoss() {
    var motorPhase = 3;
    var supplyVoltage = 460;
    var avgCurrent = 19;
    var powerFactor = 0.85;
    var operatingTime = 100;

    var auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    var powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 43905.3405494047, "Process Heat AuxiliaryPower 1 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();


    supplyVoltage = 510;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();

    testNumberValue(powerUsed, 48677.66017434, "Process Heat AuxiliaryPower 2 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();

    avgCurrent = 25;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 64049.5528609737, "Process Heat AuxiliaryPower 3 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();


    powerFactor = 0.55;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 41443.8283218065, "Process Heat AuxiliaryPower 4 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();

    operatingTime = 75;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 31082.8712413549, "Process Heat AuxiliaryPower 5 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();
}

function fixtureLosses() {
    var specificHeat = 0.122;
    var feedRate = 1250.0;
    var initialTemperature = 300.0;
    var finalTemperature = 1800.0;
    var correctionFactor = 1.0;

    var fixtureLosses = new Module.FixtureLosses(specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor);
    var heatLoss = fixtureLosses.getHeatLoss();
    fixtureLosses.delete();
    testNumberValue(heatLoss, 228750.0, "Process Heat FixtureLosses (fixtureLosses)");
}

function energyInputEAF() {
    var naturalGasHeatInput = 50;
    var coalCarbonInjection = 3300;
    var coalHeatingValue = 9000;
    var electrodeUse = 500;
    var electrodeHeatingValue = 12000;
    var otherFuels = 20;
    var electricityInput = 18000;
    var energyInputEAF = new Module.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
    var heatDelivered = energyInputEAF.getHeatDelivered();
    var totalChemicalEnergyInput = energyInputEAF.getTotalChemicalEnergyInput();
    energyInputEAF.delete();
    testNumberValue(heatDelivered, 167116000.0, "Process Heat Energy Input EAF (heatDelivered)");
    testNumberValue(totalChemicalEnergyInput, 105700000, "Process Heat Energy Input EAF (totalChemicalEnergyInput)");
}

function energyInputExhaustGasLosses() {
    var totalHeatInput = 5000000;
    var excessAir = 65;
    var combustionAirTemp = 300;
    var exhaustGasTemp = 550;

    var enInputExhaustGasLosses = new Module.EnergyInputExhaustGasLosses(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
    var heatDelivered = enInputExhaustGasLosses.getHeatDelivered();
    var exhaustGasLosses = enInputExhaustGasLosses.getExhaustGasLosses();
    var availableHeat = enInputExhaustGasLosses.getAvailableHeat();
    enInputExhaustGasLosses.delete();

    testNumberValue(heatDelivered, 4136397.1199000007, "Process Heat Energy Input Ex. Gas Losses (heatDelivered)");
    testNumberValue(exhaustGasLosses, 863602.8800999995, "Process Heat Energy Input Ex. Gas Losses (exhaustGasLosses)");
    testNumberValue(availableHeat, 82.727942, "Process Heat Energy Input Ex. Gas Losses (availableHeat)");
}

function exhaustGasEAF() {
    var offGasTemp = 2800;
    var CO = 12;
    var H2 = 10;
    var combustibleGases = 3;
    var vfr = 8000;
    var dustLoading = 0.001;

    var exGasEAF = new Module.ExhaustGasEAF(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
    var totalHeatExhaust = exGasEAF.getTotalHeatExhaust();
    exGasEAF.delete();
    testNumberValue(totalHeatExhaust, 12553119.018404908, "Process Heat Exhaust Gas EAF (totalHeatExhaust)");
}

// flueGasByVolumeCalculateHeatingValue
function flueGasByVolumeCalculateHeatingValue() {
    var inp = {
        CH4: 94.1,
        C2H6: 2.4,
        N2: 1.41,
        H2: 0.03,
        C3H8: 0.49,
        C4H10_CnH2n: 0.29,
        H2O: 0,
        CO: 0.42,
        CO2: 0.71,
        SO2: 0,
        O2: 0
    }

    var flueGasByVolumeCalculateHeatingValue = new Module.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
    var heatingValue = flueGasByVolumeCalculateHeatingValue.getHeatingValue();
    var heatingValueVolume = flueGasByVolumeCalculateHeatingValue.getHeatingValueVolume();
    var specificGravity = flueGasByVolumeCalculateHeatingValue.getSpecificGravity();
    flueGasByVolumeCalculateHeatingValue.delete();
    testNumberValue(heatingValue, 22630.355481, "Process Heat Flue Gas Volume Calculate Heating Value (heatingValue)");
    testNumberValue(heatingValueVolume, 1019.664897, "Process Heat Flue Gas Volume Calculate Heating Value (heatingValueVolume)");
    testNumberValue(specificGravity, 0.631783, "Process Heat Flue Gas Volume Calculate Heating Value (specificGravity)");
}
// flueGasCalculateExcessAir
function flueGasCalculateExcessAir() {
    var inp = {
        CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
    }

    // /100 convert to decimal
    var o2InFlueGas = .5 / 100;
    var flueGasCalculateExcessAir = new Module.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
    //x100 to convert to %
    var excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
    testNumberValue(excessAir, 2.3172209488353976, "Process Heat Flue Gas Calculate Excess Air (excessAir1)");
    // /100 convert to decimal
    o2InFlueGas = 3 / 100;
    //x100 to convert to %
    excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
    testNumberValue(excessAir, 15.52234414568954, "Process Heat Flue Gas Calculate Excess Air (excessAir2)");
    // /100 convert to decimal
    o2InFlueGas = 7 / 100;
    //x100 to convert to %
    excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
    testNumberValue(excessAir, 45.197503654937584, "Process Heat Flue Gas Calculate Excess Air (excessAir3)");
    flueGasCalculateExcessAir.delete();
}
// flueGasCalculateO2
function flueGasCalculateO2() {
    var inp = {
        excessAir: 2.3172, CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
    }
    // /100 convert to decimal
    var o2InFlueGas = 2.3172 / 100;
    var flueGasCalculateO2 = new Module.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
    //x100 to convert to %
    var o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
    testNumberValue(o2, 0.49366866893805417, "Process Heat Flue Gas Calculate O2 (calculateO2-1)");
    // /100 convert to decimal
    o2InFlueGas = 15.5223 / 100;
    //x100 to convert to %
    o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
    testNumberValue(o2, 2.947933114396894, "Process Heat Flue Gas Calculate O2 (calculateO2-2)");
    // /100 convert to decimal
    o2InFlueGas = 45.197 / 100;
    o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
    //x100 to convert to %
    testNumberValue(o2, 6.900194873506535, "Process Heat Flue Gas Calculate O2 (calculateO2-3)");
    flueGasCalculateO2.delete();
}

// flueGasLossesByVolume
function flueGasLossesByVolume() {
    var inp = {
        CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29,
        H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
    }
    var flueGasTemperature = 700;
    var flueGasO2Percentage = 0.0;
    var combustionAirTemperature = 125;
    var fuelTemperature = 125;
	var ambientAirTemp = 60;
	var combAirMoisturePerc = 0;
	var excessAirPercentage = 0.09;
    
    var gasComposition = new Module.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
    var heatLoss = gasComposition.getProcessHeatProperties(flueGasTemperature, flueGasO2Percentage, combustionAirTemperature, fuelTemperature, ambientAirTemp, combAirMoisturePerc, excessAirPercentage).availableHeat;
    testNumberValue(heatLoss, 0.785877, "Process Heat Flue Gas By Volume (heatLoss)");
    gasComposition.delete();
}
// flueGasLossesByMass
function flueGasLossesByMass() {
    var inp = {
        flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
        moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
        carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5, ambientAirTempF : 60
    };
    var flueGasLossesByMass = new Module.SolidLiquidFlueGasMaterial(inp.flueGasTemperature, inp.excessAirPercentage, inp.combustionAirTemperature,
        inp.fuelTemperature, inp.moistureInAirCombustion, inp.ashDischargeTemperature,
        inp.unburnedCarbonInAsh, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture,
        inp.nitrogen, inp.ambientAirTempF);
    var heatLoss = flueGasLossesByMass.getHeatLoss();
    testNumberValue(heatLoss, 0.8222977480707968, "Process Heat Flue Losses By Mass (heatLoss)");
    flueGasLossesByMass.delete();
}
// flueGasByMassCalculateHeatingValue
function flueGasByMassCalculateHeatingValue() {
    var inp = {
        flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
        moistureInAirCombustion: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
        carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
    };
    var solidLiquidFlueGasMaterial = new Module.SolidLiquidFlueGasMaterial();
    var heatingValue = solidLiquidFlueGasMaterial.calculateHeatingValueFuel(inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen);
    testNumberValue(heatingValue, 13877.969543, "Process Heat Flue Gas By Mass Calculate Heating Value (heatingValue)");
    solidLiquidFlueGasMaterial.delete();
}
// flueGasByMassCalculateO2
function flueGasByMassCalculateO2() {
    var inp = {
        excessAir: 2.29427817 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
        nitrogen: 0.0, moistureInAirCombustion: 1.5
    };
    var solidLiquidFlueGasMaterial = new Module.SolidLiquidFlueGasMaterial();
    var flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(flueGasO2, 0.49370451442164515, "Process Heat Flue Gas By Mass Calculate O2 (flueGasO2-1)");
    inp.excessAir = 15.36865757 / 100;
    flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(flueGasO2, 2.9440141519451095, "Process Heat Flue Gas By Mass Calculate O2 (flueGasO2-2)");
    inp.excessAir = 44.75000362 / 100;
    flueGasO2 = solidLiquidFlueGasMaterial.calculateFlueGasO2(inp.excessAir, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(flueGasO2, 6.875606606194022, "Process Heat Flue Gas By Mass Calculate O2 (flueGasO2-3)");
    solidLiquidFlueGasMaterial.delete();
}
// flueGasByMassCalculateExcessAir
function flueGasByMassCalculateExcessAir() {
    var inp = {
        o2InFlueGas: 0.5 / 100, carbon: 1.0, hydrogen: 75.0, sulphur: 5.0, inertAsh: 1.0, o2: 9.0, moisture: 7.0,
        nitrogen: 0.0, moistureInAirCombustion: 1.5
    };
    var solidLiquidFlueGasMaterial = new Module.SolidLiquidFlueGasMaterial();
    var excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(excessAir, 2.29427816716376, "Process Heat Flue Gas By Mass Excess Air (excessAir-1)");
    inp.o2InFlueGas = 3.0 / 100;
    excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(excessAir, 15.368657569989644, "Process Heat Flue Gas By Mass Excess Air (excessAir-2)");
    inp.o2InFlueGas = 7.0 / 100;
    excessAir = solidLiquidFlueGasMaterial.calculateExcessAirFromFlueGasO2(inp.o2InFlueGas, inp.carbon, inp.hydrogen, inp.sulphur, inp.inertAsh, inp.o2, inp.moisture, inp.nitrogen, inp.moistureInAirCombustion) * 100;
    testNumberValue(excessAir, 44.75000361875009, "Process Heat Flue Gas By Mass Excess Air (excessAir-3)");
    solidLiquidFlueGasMaterial.delete();
}
// gasCoolingLosses
function gasCoolingLosses() {
    var inp = {
        flowRate: 2500, initialTemperature: 80, finalTemperature: 280, specificHeat: 0.02, correctionFactor: 1.0,
        gasDensity: 1
    };
    var gasCoolingLosses = new Module.GasCoolingLosses(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
    var heatLoss = gasCoolingLosses.getHeatLoss()
    testNumberValue(heatLoss, 600000.0, "Process Heat Gas Cooling Losses (heatLoss-1)");
    inp.flowRate = 600;
    inp.finalTemperature = 350;
    gasCoolingLosses = new Module.GasCoolingLosses(inp.flowRate, inp.initialTemperature, inp.finalTemperature, inp.specificHeat, inp.correctionFactor, inp.correctionFactor);
    heatLoss = gasCoolingLosses.getHeatLoss()
    testNumberValue(heatLoss, 194400.0, "Process Heat Gas Cooling Losses (heatLoss-2)");
    gasCoolingLosses.delete();
}
// gasLoadChargeMaterial
function gasLoadChargeMaterial() {
    var inp = {
        thermicReactionType: 0, specificHeatGas: 0.24, feedRate: 1000, percentVapor: 15, initialTemperature: 80,
        dischargeTemperature: 1150, specificHeatVapor: 0.5, percentReacted: 100, reactionHeat: 80, additionalHeat: 5000
    };
    var gasLoadChargeMaterial = new Module.GasLoadChargeMaterial(Module.ThermicReactionType.ENDOTHERMIC, inp.specificHeatGas, inp.feedRate, inp.percentVapor, inp.initialTemperature, inp.dischargeTemperature, inp.specificHeatVapor, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
    var heatLoss = gasLoadChargeMaterial.getTotalHeat()
    testNumberValue(heatLoss, 383530.0, "Process Heat Gas Load Charge Material (heatLoss)");
    gasLoadChargeMaterial.delete();
}
// leakageLosses
function leakageLosses() {
    var inp = {
        draftPressure: 0.1, openingArea: 3, leakageGasTemperature: 1600, ambientTemperature: 80,
        coefficient: 0.8052, specificGravity: 1.02, correctionFactor: 1.0
    };
    var leakingLosses = new Module.LeakageLosses(inp.draftPressure, inp.openingArea, inp.leakageGasTemperature, inp.ambientTemperature, inp.coefficient, inp.specificGravity, inp.correctionFactor);
    var exfiltratedGasesHeatContent = leakingLosses.getExfiltratedGasesHeatContent()
    testNumberValue(exfiltratedGasesHeatContent, 2850767.216228273, "Process Heat Leakage Losses (exfiltratedGasesHeatContent)");
    leakingLosses.delete();
}
// liquidCoolingLosses
function liquidCoolingLosses() {
    var inp = {
        flowRate: 100, density: 9.35, initialTemperature: 80, outletTemperature: 210,
        specificHeat: 0.52, correctionFactor: 1.0
    };
    var liquidCoolingLosses = new Module.LiquidCoolingLosses(inp.flowRate, inp.density, inp.initialTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
    var heatLoss = liquidCoolingLosses.getHeatLoss()
    testNumberValue(heatLoss, 3792360.0, "Process Heat Liquid Cooling Losses (heatLoss)");
    liquidCoolingLosses.delete();
}
// liquidLoadChargeMaterial
function liquidLoadChargeMaterial() {
    var inp = {
        thermicReactionType: 0, specificHeatLiquid: 0.48, vaporizingTemperature: 240, latentHeat: 250,
        specificHeatVapor: 0.25, chargeFeedRate: 1000, initialTemperature: 70, dischargeTemperature: 320,
        percentVaporized: 100, percentReacted: 25, reactionHeat: 50, additionalHeat: 0
    };
    var liquidLoadChargeMaterial = new Module.LiquidLoadChargeMaterial(Module.ThermicReactionType.ENDOTHERMIC, inp.specificHeatLiquid, inp.vaporizingTemperature, inp.latentHeat, inp.specificHeatVapor, inp.chargeFeedRate, inp.initialTemperature, inp.dischargeTemperature, inp.percentVaporized, inp.percentReacted, inp.reactionHeat, inp.additionalHeat);
    var totalHeat = liquidLoadChargeMaterial.getTotalHeat()
    testNumberValue(totalHeat, 364100.0, "Process Heat Liquid Load Charge Material (totalHeat)");
    liquidLoadChargeMaterial.delete();
}
// openingLossesCircular
function openingLossesCircular() {
    var inp = {
        emissivity: 0.95, diameter: 12, thickness: 9, ratio: 1.33, ambientTemperature: 75,
        insideTemperature: 1600, percentTimeOpen: 100, viewFactor: 0.70
    };
    var openingLossesCircular = new Module.OpeningLosses(inp.emissivity, inp.diameter, inp.thickness, inp.ratio, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
    var heatLoss = openingLossesCircular.getHeatLoss()
    testNumberValue(heatLoss, 16038.269976979091, "Process Heat Opening Losses Circular (heatLoss)");
    openingLossesCircular.delete();
}
// openingLossesQuad
function openingLossesQuad() {
    var inp = {
        emissivity: 0.95, length: 48, width: 15, thickness: 9, ratio: 1.67, ambientTemperature: 75,
        insideTemperature: 1600, percentTimeOpen: 20, viewFactor: 0.64
    };
    var openingLossesQuad = new Module.OpeningLosses(inp.emissivity, inp.length, inp.width, inp.thickness, inp.ratio, inp.ambientTemperature, inp.insideTemperature, inp.percentTimeOpen, inp.viewFactor);
    var heatLoss = openingLossesQuad.getHeatLoss()
    testNumberValue(heatLoss, 18670.22588692891, "Process Heat Opening Losses Quad (heatLoss)");
    openingLossesQuad.delete();
}
// viewFactorCalculation
function viewFactorCalculation() {
    var inp = {
        openingShape: 0, // CIRCULAR
        thickness: 3,
        diameter: 5
    };
    var openingLosses = new Module.OpeningLosses();
    var viewFactor = openingLosses.calculateViewFactorCircular(inp.thickness, inp.diameter);
    testNumberValue(viewFactor, 0.624519890259, "Process Heat Opening Losses Circular View Factor (viewFactor)");
    inp = {
        openingShape: 1, // RECTANGULAR
        thickness: 2,
        length: 10,
        width: 5
    };
    var viewFactor = openingLosses.calculateViewFactorQuad(inp.thickness, inp.length, inp.width);
    testNumberValue(viewFactor, 0.786933593749, "Process Heat Opening Losses Quad View Factor (viewFactor)");
    openingLosses.delete();
}
// slagOtherMaterialLosses
function slagOtherMaterialLosses() {
    var inp = {
        weight: 3, inletTemperature: 500, outletTemperature: 550, specificHeat: 0.2479, correctionFactor: 1.0
    };
    var slagOtherMaterialLosses = new Module.SlagOtherMaterialLosses(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
    var heatLoss = slagOtherMaterialLosses.getHeatLoss()
    testNumberValue(heatLoss, 37.185, "Process Heat Opening Losses Quad (heatLoss)");
    inp = {
        weight: 10, inletTemperature: 725, outletTemperature: 850, specificHeat: 0.033, correctionFactor: 0.8
    };
    slagOtherMaterialLosses = new Module.SlagOtherMaterialLosses(inp.weight, inp.inletTemperature, inp.outletTemperature, inp.specificHeat, inp.correctionFactor);
    heatLoss = slagOtherMaterialLosses.getHeatLoss()
    testNumberValue(heatLoss, 33.0, "Process Heat Opening Losses Quad (heatLoss)");
    slagOtherMaterialLosses.delete();
}
// solidLoadChargeMaterial
function solidLoadChargeMaterial() {
    var inp = {
        thermicReactionType: 1, specificHeatSolid: 0.15, latentHeat: 60, specificHeatLiquid: 0.481, meltingPoint: 2900,
        chargeFeedRate: 10000, waterContentCharged: 0.1, waterContentDischarged: 0, initialTemperature: 70,
        dischargeTemperature: 2200, waterVaporDischargeTemperature: 500, chargeMelted: 0, chargeReacted: 1,
        reactionHeat: 100, additionalHeat: 0
    };
    var solidLoadChargeMaterial = new Module.SolidLoadChargeMaterial(Module.ThermicReactionType.EXOTHERMIC, inp.specificHeatSolid, inp.latentHeat, inp.specificHeatLiquid, inp.meltingPoint, inp.chargeFeedRate, inp.waterContentCharged, inp.waterContentDischarged, inp.initialTemperature, inp.dischargeTemperature, inp.waterVaporDischargeTemperature, inp.chargeMelted, inp.chargeReacted, inp.reactionHeat, inp.additionalHeat);
    var totalHeat = solidLoadChargeMaterial.getTotalHeat()
    testNumberValue(totalHeat, 3204310.28, "Process Heat Solid Load Charge Material (totalHeat)");
    solidLoadChargeMaterial.delete();
}
// wallLosses
function wallLosses() {
    var inp = {
        surfaceArea: 500, ambientTemperature: 80, surfaceTemperature: 225, windVelocity: 10,
        surfaceEmissivity: 0.9, conditionFactor: 1.394, correctionFactor: 1
    };
    var wallLosses = new Module.WallLosses(inp.surfaceArea, inp.ambientTemperature, inp.surfaceTemperature, inp.windVelocity, inp.surfaceEmissivity, inp.conditionFactor, inp.correctionFactor);
    var heatLoss = wallLosses.getHeatLoss()
    testNumberValue(heatLoss, 404627.551342992, "Process Heat Wall Losses (heatLoss)");
    wallLosses.delete();
}
// waterCoolingLosses
function waterCoolingLosses() {

    var inp = {
        flowRate: 100, initialTemperature: 80, outletTemperature: 120, correctionFactor: 1
    };
    var waterCoolingLosses = new Module.WaterCoolingLosses(inp.flowRate, inp.initialTemperature, inp.outletTemperature, inp.correctionFactor);
    var heatLoss = waterCoolingLosses.getHeatLoss()
    testNumberValue(heatLoss, 1989032.7936134234, "Process Heat Water Cooling Losses (heatLoss)");
    waterCoolingLosses.delete();
}

atmosphere();
auxiliaryPowerLoss();
fixtureLosses();
energyInputEAF();
energyInputExhaustGasLosses();
exhaustGasEAF();
flueGasByVolumeCalculateHeatingValue();
flueGasCalculateExcessAir();
flueGasCalculateO2();
flueGasLossesByVolume();
flueGasLossesByMass();
flueGasByMassCalculateHeatingValue();
flueGasByMassCalculateO2();
flueGasByMassCalculateExcessAir();
gasCoolingLosses();
gasLoadChargeMaterial();
leakageLosses();
liquidCoolingLosses();
liquidLoadChargeMaterial();
openingLossesCircular();
openingLossesQuad();
viewFactorCalculation();
slagOtherMaterialLosses();
solidLoadChargeMaterial();
wallLosses();
waterCoolingLosses();
