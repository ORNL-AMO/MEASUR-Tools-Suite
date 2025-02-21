// PneumaticAirRequirement
function pneumaticAirRequirement() {
    var inp = {
        pistonType: Module.PistonType.SingleActing,
        cylinderDiameter: 1.5,
        cylinderStroke: 6,
        airPressure: 100,
        cyclesPerMinute: 60
    };

    let pneumaticAirRequirement = new Module.PneumaticAirRequirement(inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke, inp.airPressure, inp.cyclesPerMinute);
    let result = pneumaticAirRequirement.calculate();
    testNumberValue(result.volumeAirIntakePiston, 0.367969, "Pneumatic Air Requirement (volumeAirIntakePiston-1)");
    testNumberValue(result.compressionRatio, 7.802721, "Pneumatic Air Requirement (compressionRatio-1)");
    testNumberValue(result.airRequirementPneumaticCylinder, 2.871158, "CHPneumatic Air RequirementP (airRequirementPneumaticCylinder-1)");

    inp.pistonType = Module.PistonType.DoubleActing;
    inp.pistonRodDiameter = 0.375;
    pneumaticAirRequirement = new Module.PneumaticAirRequirement(inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke, inp.pistonRodDiameter, inp.airPressure, inp.cyclesPerMinute);
    result = pneumaticAirRequirement.calculate();
    testNumberValue(result.volumeAirIntakePiston, 0.712939, "Pneumatic Air Requirement (volumeAirIntakePiston-2)");
    testNumberValue(result.compressionRatio, 7.802721, "Pneumatic Air Requirement (compressionRatio-2)");
    testNumberValue(result.airRequirementPneumaticCylinder, 5.562868, "CHPneumatic Air RequirementP (airRequirementPneumaticCylinder-2)");
    pneumaticAirRequirement.delete();
}

// usableAirCapacity
function usableAirCapacity() {
    var inp = { tankSize: 660, airPressureIn: 110, airPressureOut: 100 };

    let receiverTank = new Module.ReceiverTank();
    let result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 60.024009603, "Usable Air Capacity (calculateUsableCapacity-1)");

    inp = { tankSize: 760, airPressureIn: 110, airPressureOut: 100 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 69.1185565135, "Usable Air Capacity (calculateUsableCapacity-2)");

    inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 100 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 345.5927825676, "Usable Air Capacity (calculateUsableCapacity-3)");

    inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 130 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 138.237113027, "Usable Air Capacity (calculateUsableCapacity-4)");
    receiverTank.delete();
}
// Receiver Tank Size
function receiverTankSize() {
    var input = {
        method: Module.ReceiverTankMethod.General, airDemand: 150, allowablePressureDrop: 3, atmosphericPressure: 14.7
    };

    let receiverTank = new Module.ReceiverTank(input.method, input.airDemand, input.allowablePressureDrop, input.atmosphericPressure);
    let result = receiverTank.calculateSize();
    testNumberValue(result, 5497.8, "Receiver Tank (General-1)");

    input = {
        method: Module.ReceiverTankMethod.General, airDemand: 190, allowablePressureDrop: 8, atmosphericPressure: 12.7
    }
    receiverTank = new Module.ReceiverTank(input.method, input.airDemand, input.allowablePressureDrop, input.atmosphericPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 2256.155, "Receiver Tank (General-2)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 0.5, airFlowRequirement: 100, atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 549.78, "Receiver Tank (DedicatedStorage-1)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 0.5, airFlowRequirement: 100, atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 549.78, "Receiver Tank (DedicatedStorage-2)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 1.5, airFlowRequirement: 120, atmosphericPressure: 11.7, initialTankPressure: 150, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 315.0576, "Receiver Tank (DedicatedStorage-3)");

    input = {
        method: Module.ReceiverTankMethod.MeteredStorage, lengthOfDemand: 0.5, airFlowRequirement: 900, atmosphericPressure: 14.7, initialTankPressure: 100, finalTankPressure: 70, meteredControl: 45
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure, input.meteredControl);
    result = receiverTank.calculateSize();
    testNumberValue(result, 1566.873, "Receiver Tank (MeteredStorage-1)");

    input = {
        method: Module.ReceiverTankMethod.MeteredStorage, lengthOfDemand: 1.5, airFlowRequirement: 800, atmosphericPressure: 11.7, initialTankPressure: 120, finalTankPressure: 90, meteredControl: 75
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure, input.meteredControl);
    result = receiverTank.calculateSize();
    testNumberValue(result, 3172.455, "Receiver Tank (MeteredStorage-2)");


    input = {
        method: Module.ReceiverTankMethod.BridgingCompressorReactionDelay, distanceToCompressorRoom: 1000, speedOfAir: 250, atmosphericPressure: 14.7, airDemand: 600, allowablePressureDrop: 2
    }
    receiverTank = new Module.ReceiverTank(input.method, input.distanceToCompressorRoom, input.speedOfAir, input.atmosphericPressure, input.airDemand, input.allowablePressureDrop);
    result = receiverTank.calculateSize();
    testNumberValue(result, 2199.12, "Receiver Tank (BridgingCompressorReactionDelay-1)");

    input = {
        method: Module.ReceiverTankMethod.BridgingCompressorReactionDelay, distanceToCompressorRoom: 1200, speedOfAir: 350, atmosphericPressure: 11.7, airDemand: 800, allowablePressureDrop: 19
    }
    receiverTank = new Module.ReceiverTank(input.method, input.distanceToCompressorRoom, input.speedOfAir, input.atmosphericPressure, input.airDemand, input.allowablePressureDrop);
    result = receiverTank.calculateSize();
    testNumberValue(result, 210.564812, "Receiver Tank (BridgingCompressorReactionDelay-2)");

    receiverTank.delete();
}

// Operating Cost
function operatingCost() {
    var inp = {
        motorBhp: 215, bhpUnloaded: 25, annualOperatingHours: 6800, runTimeLoaded: 85, efficiencyLoaded: 95,
        efficiencyUnloaded: 90, costOfElectricity: 0.05
    };

    let operatingCost = new Module.OperatingCost(inp.motorBhp, inp.bhpUnloaded, inp.annualOperatingHours, inp.runTimeLoaded, inp.efficiencyLoaded, inp.efficiencyUnloaded, inp.costOfElectricity);
    let result = operatingCost.calculate();
    testNumberValue(result.runTimeUnloaded, 15, "Operating Cost (runTimeUnloaded-1)");
    testNumberValue(result.costForLoaded, 48792.326316, "Operating Cost (costForLoaded-1)");
    testNumberValue(result.costForUnloaded, 2272.191667, "Operating Cost (costForUnloaded-1)");
    testNumberValue(result.totalAnnualCost, 51064.517982, "Operating Cost (totalAnnualCost-1)");

    inp = {
        motorBhp: 255, bhpUnloaded: 35, annualOperatingHours: 6000, runTimeLoaded: 89, efficiencyLoaded: 93,
        efficiencyUnloaded: 90, costOfElectricity: 0.09
    };
    operatingCost = new Module.OperatingCost(inp.motorBhp, inp.bhpUnloaded, inp.annualOperatingHours, inp.runTimeLoaded, inp.efficiencyLoaded, inp.efficiencyUnloaded, inp.costOfElectricity);
    result = operatingCost.calculate();
    testNumberValue(result.runTimeUnloaded, 11, "Operating Cost (runTimeUnloaded-2)");
    testNumberValue(result.costForLoaded, 98305.954839, "Operating Cost (costForLoaded-2)");
    testNumberValue(result.costForUnloaded, 4394.313, "Operating Cost (costForUnloaded-2)");
    testNumberValue(result.totalAnnualCost, 102700.267839, "Operating Cost (totalAnnualCost-2)");

    operatingCost.delete();
}

function returnDoubleVector(doublesArray) {
    let doubleVector = new Module.DoubleVector();

    for (x of doublesArray) {
        doubleVector.push_back(x);
    }

    return doubleVector;
}
//airSystemCapacity
function airSystemCapacity() {
    var inp = {
        oneHalf: 3000, threeFourths: 2000, one: 1000, oneAndOneFourth: 200, oneAndOneHalf: 100, two: 500, twoAndOneHalf: 500, three: 300,
        threeAndOneHalf: 0, four: 1000, five: 0, six: 0, eight: 0, ten: 0, twelve: 0, fourteen: 0, sixteen: 0, eighteen: 0, twenty: 0,
        twentyFour: 0,
        receiverCapacities: returnDoubleVector([
            400, 500, 660, 1060
        ])
    };

    let pipeData = new Module.PipeData(inp.oneHalf, inp.threeFourths, inp.one, inp.oneAndOneFourth, inp.oneAndOneHalf, inp.two, inp.twoAndOneHalf, inp.three, inp.threeAndOneHalf, inp.four, inp.five, inp.six,
        inp.eight, inp.ten, inp.twelve, inp.fourteen, inp.sixteen, inp.eighteen, inp.twenty, inp.twentyFour);
    let airSystemCapacity = new Module.AirSystemCapacity(pipeData, inp.receiverCapacities);
    let result = airSystemCapacity.calculate();
    let receiverCapacities = new Array();
    for (let i = 0; i < result.receiverCapacities.size(); i++) {
        receiverCapacities.push(result.receiverCapacities.get(i));
    }
    testNumberValue(result.totalPipeVolume, 155.28, "Air System Capacity (totalPipeVolume)");
    testNumberValue(result.totalReceiverVolume, 350.26738, "Air System Capacity (totalReceiverVolume)");
    testNumberValue(result.totalCapacityOfCompressedAirSystem, 505.54738, "Air System Capacity (totalCapacityOfCompressedAirSystem)");
    testNumberValue(result.pipeLengths.oneHalf, 6.3, "Air System Capacity (pipeLengths.oneHalf)");
    testNumberValue(result.pipeLengths.threeFourths, 7.4, "Air System Capacity (pipeLengths.threeFourths)");
    testNumberValue(result.pipeLengths.one, 6, "Air System Capacity (pipeLengths.one)");
    testNumberValue(result.pipeLengths.oneAndOneFourth, 2.08, "Air System Capacity (pipeLengths.oneAndOneFourth)");
    testNumberValue(result.pipeLengths.oneAndOneHalf, 1.41, "Air System Capacity (pipeLengths.oneAndOneHalf)");
    testNumberValue(result.pipeLengths.two, 11.65, "Air System Capacity (pipeLengths.two)");
    testNumberValue(result.pipeLengths.twoAndOneHalf, 16.65, "Air System Capacity (pipeLengths.twoAndOneHalf)");
    testNumberValue(result.pipeLengths.three, 15.39, "Air System Capacity (pipeLengths.three)");
    testNumberValue(result.pipeLengths.threeAndOneHalf, 0, "Air System Capacity (pipeLengths.threeAndOneHalf)");
    testNumberValue(result.pipeLengths.four, 88.4, "Air System Capacity (pipeLengths.four)");
    testNumberValue(result.pipeLengths.five, 0, "Air System Capacity (pipeLengths.five)");
    testNumberValue(result.pipeLengths.six, 0, "Air System Capacity (pipeLengths.six)");
    testNumberValue(receiverCapacities[0], 53.475936, "Air System Capacity (receiverCapacities-1)");
    testNumberValue(receiverCapacities[1], 66.84492, "Air System Capacity (receiverCapacities-2)");
    testNumberValue(receiverCapacities[2], 88.235294, "Air System Capacity (receiverCapacities-3)");
    testNumberValue(receiverCapacities[3], 141.71123, "Air System Capacity (receiverCapacities-4)");
    inp.receiverCapacities.delete();
    pipeData.delete();
    airSystemCapacity.delete();
}
//airVelocity
function airVelocity() {
    var inp = {
        airFlow: 1800, pipePressure: 100, atmosphericPressure: 14.7
    };

    let airVelocity = new Module.AirVelocity(inp.airFlow, inp.pipePressure, inp.atmosphericPressure);

    let result = airVelocity.calculate();
    testNumberValue(result.oneHalf, 1845.510026, "Air Velocity (oneHalf)");
    testNumberValue(result.threeFourths, 1044.628317, "Air Velocity (threeFourths)");
    testNumberValue(result.one, 643.782567, "STANDALON Air Velocity (one)");
    testNumberValue(result.oneAndOneFourth, 369.102005, "Air Velocity (oneAndOneFourth)");
    testNumberValue(result.oneAndOneHalf, 271.398533, "Air Velocity (oneAndOneHalf)");
    testNumberValue(result.two, 164.777681, "Air Velocity (two)");
    testNumberValue(result.twoAndOneHalf, 115.585179, "Air Velocity (twoAndOneHalf)");
    testNumberValue(result.three, 74.919216, "Air Velocity (three)");
    testNumberValue(result.threeAndOneHalf, 55.981093, "Air Velocity (threeAndOneHalf)");
    testNumberValue(result.four, 43.491988, "Air Velocity (four)");
    testNumberValue(result.five, 27.68265, "Air Velocity (five)");
    testNumberValue(result.six, 19.164175, "Air Velocity (six)");
    airVelocity.delete();
}
// Pipe Sizing
function pipeSizing() {
    var inp = {
        airFlow: 1000, airlinePressure: 90, designVelocity: 25, atmosphericPressure: 14.5
    };

    let pipeSizing = new Module.PipeSizing(inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure);
    let result = pipeSizing.calculate();
    testNumberValue(result.crossSectionalArea, 13.320574, "Air Velocity (crossSectionalArea)");
    testNumberValue(result.pipeDiameter, 4.132512, "Air Velocity (pipeDiameter)");

    inp = {
        airFlow: 1400, airlinePressure: 110, designVelocity: 30, atmosphericPressure: 11.5
    };
    pipeSizing = new Module.PipeSizing(inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure);
    result = pipeSizing.calculate();
    testNumberValue(result.crossSectionalArea, 10.600823, "Air Velocity (crossSectionalArea)");
    testNumberValue(result.pipeDiameter, 3.68657, "Air Velocity (pipeDiameter)");
    pipeSizing.delete();
}
// Pneumatic Valve
function pneumaticValve() {
    var inp = { inletPressure: 100, outletPressure: 70 }

    let pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure);
    let result = pneumaticValve.calculate();
    testNumberValue(result, 49.09732, "Pneumatic Valve (calculate-1)");

    inp = { inletPressure: 120, outletPressure: 90 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure);
    result = pneumaticValve.calculate();
    testNumberValue(result, 54.568621, "Pneumatic Valve (calculate-2)");

    inp = { inletPressure: 80, outletPressure: 75, flowRate: 55 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure, inp.flowRate);
    result = pneumaticValve.calculate();
    testNumberValue(result, 2.873685, "Pneumatic Valve (calculate-3)");

    inp = { inletPressure: 90, outletPressure: 85, flowRate: 95 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure, inp.flowRate);
    result = pneumaticValve.calculate();
    testNumberValue(result, 4.671398, "Pneumatic Valve (calculate-4)");
    pneumaticValve.delete();
}

// Bag Method
function bagMethod() {
    var inp = { operatingTime: 115200 / 60.0, bagFillTime: 25, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 };

    let bagMethod = new Module.BagMethod(inp.operatingTime, inp.bagFillTime, inp.heightOfBag, inp.diameterOfBag, inp.numberOfUnits);
    let result = bagMethod.calculate();
    testNumberValue(result.flowRate, 1.092, "Bag Method (flowRate-1)");
    testNumberValue(result.annualConsumption, 125.7984, "Bag Method (annualConsumption-1)");

    inp = { operatingTime: 100000 / 60.0, bagFillTime: 20, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 };
    bagMethod = new Module.BagMethod(inp.operatingTime, inp.bagFillTime, inp.heightOfBag, inp.diameterOfBag, inp.numberOfUnits);
    result = bagMethod.calculate();
    testNumberValue(result.flowRate, 1.365, "Bag Method (flowRate-2)");
    testNumberValue(result.annualConsumption, 136.5, "Bag Method (annualConsumption-2)");
    bagMethod.delete();
}
// Estimate Method
function estimateMethod() {
    var inp = { operatingTime: 1280, leakRateEstimate: 0.1};

    let estimateMethod = new Module.EstimateMethod(inp.operatingTime, inp.leakRateEstimate);
    let result = estimateMethod.calculate();
    testNumberValue(result.annualConsumption, 7.68, "Estimate Method (annualConsumption-1)");

    inp = { operatingTime: 1280, leakRateEstimate: 1.429};
    estimateMethod = new Module.EstimateMethod(inp.operatingTime, inp.leakRateEstimate);
    result = estimateMethod.calculate();
    testNumberValue(result.annualConsumption, 109.7472, "Estimate Method (annualConsumption-2)");
    estimateMethod.delete();
}
// Decibels Method
function decibelsMethod() {
    var inp = { operatingTime: 1280, linePressure: 130, decibels: 25,
        decibelRatingA: 20, pressureA: 150, firstFlowA: 1.04, secondFlowA: 1.2,
        decibelRatingB: 30, pressureB: 125, firstFlowB:1.85, secondFlowB:1.65 };

    let decibelsMethod = new Module.DecibelsMethod(inp.operatingTime, inp.linePressure, inp.decibels,
        inp.decibelRatingA, inp.pressureA, inp.firstFlowA, inp.secondFlowA,
        inp.decibelRatingB, inp.pressureB, inp.firstFlowB, inp.secondFlowB);
    let result = decibelsMethod.calculate();
    testNumberValue(result.leakRateEstimate, 1.429, "Decibels Method (leakRateEstimate-1)");
    testNumberValue(result.annualConsumption, 109.7472, "Decibels Method (annualConsumption-1)");
    decibelsMethod.delete();
}
// Orifice Method
function orificeMethod() {
    var inp = { operatingTime: 115200 / 60.0, airTemp: 250, atmPressure: 14.7, dischargeCoef: 1, diameter: 6, supplyPressure: 6.2, numOrifices: 4 };

    let orificeMethod = new Module.OrificeMethod(inp.operatingTime, inp.airTemp, inp.atmPressure, inp.dischargeCoef, inp.diameter, inp.supplyPressure, inp.numOrifices);
    let result = orificeMethod.calculate();
    testNumberValue(result.standardDensity, 0.2256917885, "Orifice Method (standardDensity-1)");
    testNumberValue(result.sonicDensity, 0.0153403857, "Orifice Method (sonicDensity-1)");
    testNumberValue(result.leakVelocity, 707.7792735027, "Orifice Method (leakVelocity-1)");
    testNumberValue(result.leakRateLBMmin, 127.9131698485, "Orifice Method (leakRateLBMmin-1)");
    testNumberValue(result.leakRateScfm, 566.7604066752, "Orifice Method (leakRateScfm-1)");
    testNumberValue(result.leakRateEstimate, 2267.0416267007, "Orifice Method (leakRateEstimate-1)");
    testNumberValue(result.annualConsumption, 261163.1953959255, "Orifice Method (annualConsumption-1)");
    orificeMethod.delete();
}

pneumaticAirRequirement();

usableAirCapacity();
receiverTankSize();

operatingCost();
airSystemCapacity();
airVelocity();
pipeSizing();
pneumaticValve();

bagMethod();
estimateMethod();
decibelsMethod();
orificeMethod();