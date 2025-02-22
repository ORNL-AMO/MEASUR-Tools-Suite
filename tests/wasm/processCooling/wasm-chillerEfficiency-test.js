function chillerCapacityEfficiency(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.baselineActualEfficiency), rnd(expected[0]), "baselineActualEfficiency");
        testNumberValue(rnd(results.baselineActualCapacity), rnd(expected[1]), "baselineActualCapacity");
        testNumberValue(rnd(results.baselinePower), rnd(expected[2]), "baselinePower");
        testNumberValue(rnd(results.baselineEnergy), rnd(expected[3]), "baselineEnergy");
        testNumberValue(rnd(results.modActualEfficiency), rnd(expected[4]), "modActualEfficiency");
        testNumberValue(rnd(results.modActualCapacity), rnd(expected[5]), "modActualCapacity");
        testNumberValue(rnd(results.modPower), rnd(expected[6]), "modPower");
        testNumberValue(rnd(results.modEnergy), rnd(expected[7]), "modEnergy");
        testNumberValue(rnd(results.savingsEnergy), rnd(expected[8]), "savingsEnergy");
    };

    let validateChillerCapacityEfficiency = function(input, output) {
        validate(Module.ChillerCapacityEfficiency(input.chillerType, input.condenserCoolingType, input.compressorConfigType,
            input.ariCapacity, input.ariEfficiency, input.maxCapacityRatio, input.operatingHours, input.waterFlowRate, input.waterDeltaT,
            input.baselineWaterSupplyTemp, input.baselineWaterEnteringTemp, input.modWaterSupplyTemp, input.modWaterEnteringTemp),  output);
    }

    let input = {
        chillerType: Module.ChillerType.Centrifugal,
        condenserCoolingType: Module.CondenserCoolingType.Water,
        compressorConfigType: Module.CompressorConfigType.NoVFD,

        ariCapacity: 1000,
        ariEfficiency: 0.676,
        maxCapacityRatio: 1.0,

        operatingHours: 1.0,
        waterFlowRate: 2000,
        waterDeltaT: 10,

        baselineWaterSupplyTemp: 42,
        baselineWaterEnteringTemp: 82.12,
        modWaterSupplyTemp:43,
        modWaterEnteringTemp:82.12
    };

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 1', true);
    validateChillerCapacityEfficiency(input, [0.552199,995.546437,549.740164,549.740164,0.526177,1033.117955,543.60299,543.60299,6.137174]);

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 2', true);
    input.compressorConfigType = Module.CompressorConfigType.VFD;
    validateChillerCapacityEfficiency(input, [0.50594,1017.8465,514.9762,514.9762,0.477184,1038.2663,495.4494,495.4494,19.5268]);

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 3', true);
    input.compressorConfigType = Module.CompressorConfigType.MagneticBearing;
    validateChillerCapacityEfficiency(input, [0.5335,985.4549,525.74132,525.74132,0.486282,1047.968,509.608,509.608,16.13328]);

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 4', true);
    input.chillerType = Module.ChillerType.Screw;
    input.compressorConfigType = Module.CompressorConfigType.NoVFD;
    validateChillerCapacityEfficiency(input, [0.5899,963.0877,568.13317,568.13317,0.56246,1000.57839,562.7885,562.7885,5.34465]);

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 5', true);
    input.condenserCoolingType =  Module.CondenserCoolingType.Air;
    validateChillerCapacityEfficiency(input, [0.47777,1050.0458,501.67899,501.67899,0.4604,1081.77855,498.0641,498.0641,3.61489]);

    logMessage('Chiller Efficiency Capacity Energy Consumption: Test# 6', true);
    input.chillerType = Module.ChillerType.Centrifugal;
    validateChillerCapacityEfficiency(input, [0.442926,1130.9202,500.91377,500.91377,0.4285,1168.492,500.7157,500.7157,0.19807]);
}

function chillerStagingEfficiency(){
    let validate = function(results, expected, baselinePowerList, modPowerList) {
        testNumberValue(rnd(results.baselineTotalPower), rnd(expected[0]), "baselineTotalPower");
        testNumberValue(rnd(results.baselineTotalEnergy), rnd(expected[1]), "baselineTotalEnergy");
        testNumberValue(rnd(results.modTotalPower), rnd(expected[2]), "modTotalPower");
        testNumberValue(rnd(results.modTotalEnergy), rnd(expected[3]), "modTotalEnergy");
        testNumberValue(rnd(results.savingsEnergy), rnd(expected[4]), "savingsEnergy");

        for (let i = 0; i < baselinePowerList.length; i++) {
            testNumberValue(rnd(results.baselinePowerList.get(i)), baselinePowerList[i], 'baselinePower' + (i+1));
            testNumberValue(rnd(results.modPowerList.get(i)), modPowerList[i], 'modPower' + (i+1));
        }
    };

    logMessage('Chiller Efficiency Staging: Test# 1', true);
    let baselineLoadList = new Module.DoubleVector();
    baselineLoadList.push_back(300);
    baselineLoadList.push_back(300);
    baselineLoadList.push_back(300);

    let modLoadList = new Module.DoubleVector();
    modLoadList.push_back(450);
    modLoadList.push_back(450);
    modLoadList.push_back(0);

    validate(
        Module.ChillerStagingEfficiency(Module.ChillerType.Centrifugal, Module.CondenserCoolingType.Water , Module.CompressorConfigType.VFD,
            1000, 0.676, 1.0, 1.0, 42, 82.12, baselineLoadList, modLoadList),
        [820.5018,820.5018,603.9089,603.9089,216.5928], [273.5006,273.5006,273.5006], [301.9545,301.9545,0]);

    baselineLoadList.delete();
    modLoadList.delete();
}


chillerCapacityEfficiency();
chillerStagingEfficiency();