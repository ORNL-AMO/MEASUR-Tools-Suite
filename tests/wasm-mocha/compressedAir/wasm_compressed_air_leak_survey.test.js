import { assert } from 'chai';

describe('Compressed Air Leak Survey', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function buildInput(hoursPerYear, utilityType, utilityCost, measurementMethod,
        estimateLeakRate,
        decibelParams, bagParams, orificeParams,
        compressorControlAdjustment, compressorSpecificPower, units) {
        const estimate = { leakRateEstimate: estimateLeakRate, operatingTime: hoursPerYear };
        // DecibelsMethodInput is a value_object — constructed as a plain JS object
        const decibels = {
            operatingTime:  0,
            linePressure:   decibelParams[0],
            decibels:       decibelParams[1],
            decibelRatingA: decibelParams[2],
            pressureA:      decibelParams[3],
            firstFlowA:     decibelParams[4],
            secondFlowA:    decibelParams[5],
            decibelRatingB: decibelParams[6],
            pressureB:      decibelParams[7],
            firstFlowB:     decibelParams[8],
            secondFlowB:    decibelParams[9]
        };
        const bag = { ...bagParams };
        // orificeParams is now a plain object (OrificeMethodInput value_object)
        const orifice = { ...orificeParams };
        const compElec = { compressorControlAdjustment, compressorSpecificPower };

        const input = new moduleInstance.CompressedAirLeakSurveyInput(
            hoursPerYear, utilityType, utilityCost, measurementMethod,
            estimate, decibels, bag, orifice, compElec, units
        );

        return input;
    }

    function runSurvey(input) {
        const inputVec = new moduleInstance.CompressedAirLeakSurveyInputV();
        inputVec.push_back(input);
        const survey = new moduleInstance.CompressedAirLeakSurvey(inputVec);
        const result = survey.calculate();
        input.delete();
        inputVec.delete();
        survey.delete();
        return result;
    }

    const defaultDecibels = [130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65];
    const defaultOrifice = {
        operatingTime: 0, airTemp: 250, atmPressure: 14.7,
        dischargeCoef: 1.0, diameter: 6.0, supplyPressure: 6.2, numOrifices: 4
    };

    it('should calculate estimate method with electricity (8640 hrs)', function () {
        const bagParams = {
            operatingTime: 8760,
            bagFillTime: 12,
            bagVolume: 8.68,
            numberOfUnits: 1
        };

        const input = buildInput(8640, 1, 0.12, 0,
            0.1, defaultDecibels, bagParams, defaultOrifice,
            0.40, 0.16, 1);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 138.24, 0.01);
        assert.approximately(result.annualTotalElectricityCost, 16.5888, 0.001);
        assert.approximately(result.totalFlowRate, 0.1, 0.001);
        assert.approximately(result.annualTotalFlowRate, 51840, 1);
    });

    it('should calculate estimate method with electricity (3840 hrs)', function () {
        const bagParams = {
            operatingTime: 3840,
            bagFillTime: 12,
            bagVolume: 8.68,
            numberOfUnits: 1
        };
        const input = buildInput(3840, 1, 0.12, 0,
            0.1, defaultDecibels, bagParams, defaultOrifice,
            0.25, 0.16, 1);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 61.44, 0.01);
        assert.approximately(result.annualTotalElectricityCost, 7.3728, 0.001);
        assert.approximately(result.totalFlowRate, 0.1, 0.001);
        assert.approximately(result.annualTotalFlowRate, 23040, 1);
    });

    it('should calculate estimate method with electricity (large leak rate)', function () {
        const bagParams = {
            operatingTime: 8760,
            bagFillTime: 12,
            bagVolume: 8.68,
            numberOfUnits: 1
        };
        const input = buildInput(8760, 1, 0.12, 0,
            100, defaultDecibels, bagParams, defaultOrifice,
            0.25, 0.16, 1);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 140160.0, 0.1);
        assert.approximately(result.annualTotalElectricityCost, 16819.2, 0.01);
        assert.approximately(result.totalFlowRate, 100, 0.01);
        assert.approximately(result.annualTotalFlowRate, 52560000, 1);
    });

    it('should calculate decibels method with electricity', function () {
        const bagParams = {
            operatingTime: 15,
            bagFillTime: 10,
            bagVolume: 12,
            numberOfUnits: 1
        };
        const input = buildInput(8640, 1, 0.12, 1,
            0.1, defaultDecibels, bagParams, defaultOrifice,
            0.40, 0.16, 1);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 1975.4496, 0.01);
        assert.approximately(result.annualTotalElectricityCost, 237.053952, 0.001);
        assert.approximately(result.totalFlowRate, 1.429, 0.001);
        assert.approximately(result.annualTotalFlowRate, 740793.6, 1);
    });

    it('should calculate bag method with electricity', function () {
        const bagParams = {
            operatingTime: 15,
            bagFillTime: 10,
            bagVolume: 12,
            numberOfUnits: 1
        };
        const input = buildInput(8640, 1, 0.12, 2,
            0.1, defaultDecibels, bagParams, defaultOrifice,
            0.40, 0.16, 2);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 0.3456, 0.001);
        assert.approximately(result.annualTotalElectricityCost, 0.041472, 0.0001);
        assert.approximately(result.totalFlowRate, 144.0, 0.01);
        assert.approximately(result.annualTotalFlowRate, 129.6, 0.01);
    });

    it('should calculate orifice method with electricity', function () {
        const bagParams = {
            operatingTime: 15,
            bagFillTime: 10,
            bagVolume: 12,
            numberOfUnits: 1
        };
        const orificeParams = {
            operatingTime: 0, airTemp: 550, atmPressure: 14.7,
            dischargeCoef: 1.0, diameter: 0.375, supplyPressure: 100, numOrifices: 4
        };
        const input = buildInput(8640, 1, 0.12, 3,
            0.1, defaultDecibels, bagParams, orificeParams,
            0.40, 0.16, 1);
        const result = runSurvey(input);

        assert.approximately(result.annualTotalElectricity, 1790380.8424647334, 1);
        assert.approximately(result.annualTotalElectricityCost, 214845.701095768, 0.01);
        assert.approximately(result.totalFlowRate, 1295.1250307181, 0.001);
        assert.approximately(result.annualTotalFlowRate, 671392815.9242750406, 100);
    });
});
