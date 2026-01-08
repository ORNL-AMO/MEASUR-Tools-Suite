function waterHeatingUsingSteam(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.tempWaterOut), rnd(expected[0]), "tempWaterOut");
        testNumberValue(rnd(results.bpTempWaterOut), rnd(expected[1]), "bpTempWaterOut");
        testNumberValue(rnd(results.enthalpySteamIn), rnd(expected[2]), "enthalpySteamIn");
        testNumberValue(rnd(results.enthalpySteamOut), rnd(expected[3]),"enthalpySteamOut");
        testNumberValue(rnd(results.enthalpyMakeUpWater), rnd(expected[4]),"enthalpyMakeUpWater");
        testNumberValue(rnd(results.flowByPassSteam), rnd(expected[5]),"flowByPassSteam");
        testNumberValue(rnd(results.energySavedDWH), rnd(expected[6]),"energySavedDWH");
        testNumberValue(rnd(results.energySavedBoiler), rnd(expected[7]),"energySavedBoiler");
        testNumberValue(rnd(results.waterSaved), rnd(expected[8]),"waterSaved");
        testNumberValue(rnd(results.heatGainRate), rnd(expected[9]),"heatGainRate");

        logMessage('bpTempWarningFlag : ' + results.bpTempWarningFlag);
    };

    let instance = new Module.WaterHeatingUsingSteam();

    logMessage('Water Heating Using Steam Heat Exchanger: Test# 1', true);
    validate(instance.calculate(0.1565, 340.2, 285.93, 0.5150, 2.7255, 285.93, 0.2048, 0.72, 0.8, 7000),
        [352.304, 426.1, 2695.04, 472.5, 53.876, 0,
            7351062329.1926, 1246124501.2457, 2381.4, 756109.2681]);

    logMessage('Water Heating Using Steam Heat Exchanger: Test# 2', true);
    validate(instance.calculate(0.1703, 226.79, 285.93, 0.2737, 0.6814, 285.93, 0.2048, 0.7, 0.7, 8000),
        [388.75, 403.57, 2698.89, 483.41, 53.876, 94.61,
            3346757808.4035, 648872153.14, 1057.44, 292841.3082]);
    instance.delete();
}

function airWaterCoolingUsingFlue(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.excessAir), rnd(expected[0]), "excessAir");
        testNumberValue(rnd(results.flowFlueGas), rnd(expected[1]), "flowFlueGas");
        testNumberValue(rnd(results.specHeat), rnd(expected[2]),"specHeat");
        testNumberValue(rnd(results.fracCondensed), rnd(expected[3]),"fracCondensed");
        testNumberValue(rnd(results.effThermal), rnd(expected[4]), "effThermal");
        testNumberValue(rnd(results.effThermalLH), rnd(expected[5]), "effThermalLH");
        testNumberValue(rnd(results.effLH), rnd(expected[6]),"effLH");
        testNumberValue(rnd(results.heatRecovery), rnd(expected[7]),"heatRecovery");
        testNumberValue(rnd(results.sensibleHeatRecovery), rnd(expected[8]),"sensibleHeatRecovery");
    };

    logMessage('Air Water Cooling Using Flue: Test# 1', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
    let instance = new Module.AirWaterCoolingUsingFlue();
    let results = instance.calculate(gasInstance, 116, 300, 125, 70, 60, 0.04, 60, 0);
    validate(results, [0.21596, 107119.17, 0.2578, 0.19816, 0.8444, 0.86454, 0.02014, 2.3362, 4.83]);
    instance.delete();
    gasInstance.delete();
}

waterHeatingUsingSteam();
airWaterCoolingUsingFlue();