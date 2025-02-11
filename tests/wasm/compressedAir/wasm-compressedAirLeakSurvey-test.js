function validateCompressedAirLeakSurvey(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.annualTotalElectricity), rnd(expected[0]), "annualTotalElectricity");
        testNumberValue(rnd(results.annualTotalElectricityCost), rnd(expected[1]), "annualTotalElectricityCost");
        testNumberValue(rnd(results.totalFlowRate), rnd(expected[2]), "totalFlowRate");
        testNumberValue(rnd(results.annualTotalFlowRate), rnd(expected[3]), "annualTotalFlowRate");
    };

    logMessage('Calculator - Compressed Air Leak Survey: Test# ' + testName, true);
    let inputList = new Module.CompressedAirLeakSurveyInputV();
    for (let i = 0; i < inp.compressedAirLeakSurveyInputVec.length; i++) {
        let inpElem = inp.compressedAirLeakSurveyInputVec[i];
        let estimateMethodData = new Module.EstimateMethodData(inpElem.estimateMethodData.leakRateEstimate);
        let bagMethodData = new Module.BagMethodData(inpElem.bagMethodData.height, inpElem.bagMethodData.diameter, inpElem.bagMethodData.fillTime);
        let decibelsMethodData = new Module.DecibelsMethodData(inpElem.decibelsMethodData.linePressure,
            inpElem.decibelsMethodData.decibels, inpElem.decibelsMethodData.decibelRatingA, inpElem.decibelsMethodData.pressureA,
            inpElem.decibelsMethodData.firstFlowA, inpElem.decibelsMethodData.secondFlowA, inpElem.decibelsMethodData.decibelRatingB,
            inpElem.decibelsMethodData.pressureB, inpElem.decibelsMethodData.firstFlowB, inpElem.decibelsMethodData.secondFlowB);
        let orificeMethodData = new Module.OrificeMethodData(inpElem.orificeMethodData.compressorAirTemp,
            inpElem.orificeMethodData.atmosphericPressure, inpElem.orificeMethodData.dischargeCoefficient,
            inpElem.orificeMethodData.orificeDiameter, inpElem.orificeMethodData.supplyPressure, inpElem.orificeMethodData.numberOfOrifices);
        let compressorElectricityData = new Module.CompressorElectricityData(inpElem.compressorElectricityData.compressorControlAdjustment,
            inpElem.compressorElectricityData.compressorSpecificPower);

        let input = new Module.CompressedAirLeakSurveyInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost, inpElem.measurementMethod,
            estimateMethodData, decibelsMethodData, bagMethodData, orificeMethodData, compressorElectricityData, inpElem.units);
        inputList.push_back(input);

        input.delete();
        compressorElectricityData.delete();
        orificeMethodData.delete();
        decibelsMethodData.delete();
        bagMethodData.delete();
        estimateMethodData.delete();
    }

    let instance = new Module.CompressedAirLeakSurvey(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function compressedAirLeakSurvey(){
    let inp = {
        compressedAirLeakSurveyInputVec: [
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('1', inp, [138.24, 16.5888, 0.1, 51840]);

    inp = {
        compressedAirLeakSurveyInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 100
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 2
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 14
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.785398163397448
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 6.32517756495803
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('2 - Additional', inp, [309908.582941, 37189.029953, 221.110576, 116215718.602824]);

    inp = {
        compressedAirLeakSurveyInputVec: [
            // estimate method with electricity
            // energyUse = 55.296
            // energyCost = 6.63552
            // flowRate = 0.1
            // compressedAirUse = 51840
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // decibels method with electricity
            // energyUse = 790.17984
            // energyCost = 94.8215808
            // flowRate = 1.429
            // compressedAirUse = 740793.6
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 1,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // bag method with electricity
            // energyUse = 3769.9111
            // energyCost = 452.3893
            // flowRate = 6.8176923906
            // compressedAirUse = 3534291.73528
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 2,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 2
            },
            // orifice method with electricity
            // energyUse = 1253583.3379004421
            // energyCost = 150430.000548053
            // flowRate = 2267.0416267007
            // compressedAirUse = 1175234379
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 3,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('3 - All', inp, [3145496.812312, 377459.617477, 2275.388319, 1179561304.616953]);
}

compressedAirLeakSurvey();
