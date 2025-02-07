function coolingTowerMakeupWater(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.wcBaseline), rnd(expected[0]), "wcBaseline");
        testNumberValue(rnd(results.wcModification), rnd(expected[1]), "wcModification");
        testNumberValue(rnd(results.waterSavings), rnd(expected[2]), "waterSavings");
    };

    logMessage('Cooling Tower Makeup Water: Test# 1', true);
    let instanceOC = new Module.CoolingTowerOperatingConditionsData(2500, 10.00, 1000, 1.00);
    let instanceWCB = new Module.CoolingTowerWaterConservationData(3, 0.002);
    let instanceWCM = new Module.CoolingTowerWaterConservationData(3, 0.0001);
    let instance = new Module.CoolingTowerMakeupWaterCalculator(instanceOC, instanceWCB, instanceWCM);
    validate(instance.calculate(), [2100000, 1815000, 285000]);

    logMessage('Cooling Tower Makeup Water: Test# 2', true);
    instanceOC = new Module.CoolingTowerOperatingConditionsData(2500, 5.00, 2000, 1.00);
    instance = new Module.CoolingTowerMakeupWaterCalculator(instanceOC, instanceWCB, instanceWCM);
    validate(instance.calculate(), [2400000, 1830000, 570000]);

    logMessage('Cooling Tower Makeup Water: Test# 3', true);
    instanceOC = new Module.CoolingTowerOperatingConditionsData(2500, 2.00, 3000, 1.00);
    instance = new Module.CoolingTowerMakeupWaterCalculator(instanceOC, instanceWCB, instanceWCM);
    validate(instance.calculate(), [1980000, 1125000, 855000]);

    instanceOC.delete();
    instanceWCB.delete();
    instanceWCM.delete();
    instance.delete();
}

function basinHeaterEnergyConsumption(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.baselinePower), rnd(expected[0]), "baselinePower");
        testNumberValue(rnd(results.baselineEnergy), rnd(expected[1]), "baselineEnergy");
        testNumberValue(rnd(results.modPower), rnd(expected[2]), "modPower");
        testNumberValue(rnd(results.modEnergy), rnd(expected[3]), "modEnergy");
        testNumberValue(rnd(results.savingsEnergy), rnd(expected[4]), "savingsEnergy");
    };

    logMessage('Cooling Tower Basin Heater Energy Consumption: Test# 1', true);
    validate(Module.BasinHeaterEnergyConsumption(1201.67, 40, -10, 45, 28, 9.21, 1, 40, 39, 0.011), [3.842840959, 3.842840959, 3.4512519642, 3.4512519642, 0.3915889948]);
}

function fanEnergyConsumption(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.baselinePower), rnd(expected[0]), "baselinePower");
        testNumberValue(rnd(results.baselineEnergy), rnd(expected[1]), "baselineEnergy");
        testNumberValue(rnd(results.modPower), rnd(expected[2]), "modPower");
        testNumberValue(rnd(results.modEnergy), rnd(expected[3]), "modEnergy");
        testNumberValue(rnd(results.savingsEnergy), rnd(expected[4]), "savingsEnergy");
    };

    logMessage('Cooling Tower Fan Energy Consumption: Test# 1', true);
    validate(Module.FanEnergyConsumption(59.5119, 81.6495, 87.98386, 76, 1, 0, Module.FanControlSpeedType.Two),
        [55.149962, 41.141872, 50.503133, 37.675337, 3.466535]);

    logMessage('Cooling Tower Fan Energy Consumption: Test# 2', true);
    validate(Module.FanEnergyConsumption(59.5119, 81.6495, 87.98386, 76, 1, 0, Module.FanControlSpeedType.Variable),
        [55.149962, 41.141872, 44.789615, 33.413053, 7.728819]);
}

coolingTowerMakeupWater();
basinHeaterEnergyConsumption();
fanEnergyConsumption();
