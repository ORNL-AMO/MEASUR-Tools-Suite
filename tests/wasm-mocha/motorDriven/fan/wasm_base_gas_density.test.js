import { assert } from 'chai';

describe('Base Gas Density', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../../build-wasm/bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/build-wasm/bin/' + filename
        });
    });

    it('should calculate Relative Humidity Method Results', function () {
        let relativeHumidityInputs = {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.RelativeHumidity,
            relativeHumidity: 35,
            specificGravity: 1.05,
        }

        let relativeHumidityInstance = new moduleInstance.BaseGasDensity(
            relativeHumidityInputs.dryBulbTemp,
            relativeHumidityInputs.staticPressure,
            relativeHumidityInputs.barometricPressure,
            relativeHumidityInputs.relativeHumidity,
            relativeHumidityInputs.gasType,
            relativeHumidityInputs.inputType,
            relativeHumidityInputs.specificGravity);
        let gasDensityResult = relativeHumidityInstance.getGasDensity();
        let absolutePressureInResult = relativeHumidityInstance.getAbsolutePressureIn();
        let saturatedHumidityRatioResult = relativeHumidityInstance.getSaturatedHumidityRatio();
        let degreeOfSaturationResult = relativeHumidityInstance.getDegreeOfSaturation();
        let humidityRatioResult = relativeHumidityInstance.getHumidityRatio();
        let specificVolumeResult = relativeHumidityInstance.getSpecificVolume();
        let enthalpyResult = relativeHumidityInstance.getEnthalpy();
        let dewPointResult = relativeHumidityInstance.getDewPoint();
        let relativeHumidityResult = relativeHumidityInstance.getRelativeHumidity();
        let saturationPressureResult = relativeHumidityInstance.getSaturationPressure();
        let wetBulbTempResult = relativeHumidityInstance.getWetBulbTemp();
        relativeHumidityInstance.delete();


        assert.approximately(gasDensityResult, 0.05637830145287457, .001, "gasDensityResult");
        assert.approximately(absolutePressureInResult, 25.2767099634697, .001, "absolutePressureInResult");
        assert.approximately(saturatedHumidityRatioResult, 0.10830760118401817, .001, "saturatedHumidityRatioResult");
        assert.approximately(degreeOfSaturationResult, 0.3144126326912711, .001, "degreeOfSaturationResult");
        assert.approximately(humidityRatioResult, 0.03405327802874338, .001, "humidityRatioResult");
        assert.approximately(specificVolumeResult, 18.34133436767489, .001, "specificVolumeResult");
        assert.approximately(enthalpyResult, 68.37124560820246, .001, "enthalpyResult");
        assert.approximately(dewPointResult, 87.40387101362482, .001, "dewPointResult");
        assert.approximately(relativeHumidityResult, 0.35, .001, "relativeHumidityResult");
        assert.approximately(saturationPressureResult, 3.7487420264687445, .001, "saturationPressureResult");
        assert.approximately(wetBulbTempResult, 93.25804647868017, .001, "wetBulbTempResult");
    });


    it('should calculate Dew Point Method Results', function () {
        let dewPointInputs = {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.DewPoint,
            dewPoint: 0.35,
            specificGravity: 1.05,
        }

        let dewPointInstance = new moduleInstance.BaseGasDensity(
            dewPointInputs.dryBulbTemp,
            dewPointInputs.staticPressure,
            dewPointInputs.barometricPressure,
            dewPointInputs.dewPoint,
            dewPointInputs.gasType,
            dewPointInputs.inputType,
            dewPointInputs.specificGravity
        );

        let gasDensityResult = dewPointInstance.getGasDensity();
        let absolutePressureInResult = dewPointInstance.getAbsolutePressureIn();
        let saturatedHumidityRatioResult = dewPointInstance.getSaturatedHumidityRatio();
        let degreeOfSaturationResult = dewPointInstance.getDegreeOfSaturation();
        let humidityRatioResult = dewPointInstance.getHumidityRatio();
        let specificVolumeResult = dewPointInstance.getSpecificVolume();
        let enthalpyResult = dewPointInstance.getEnthalpy();
        let dewPointResult = dewPointInstance.getDewPoint();
        let relativeHumidityResult = dewPointInstance.getRelativeHumidity();
        let saturationPressureResult = dewPointInstance.getSaturationPressure();
        let wetBulbTempResult = dewPointInstance.getWetBulbTemp();
        dewPointInstance.delete();

        assert.approximately(gasDensityResult, 0.057473768082717605, .001, "gasDensityResult");
        assert.approximately(absolutePressureInResult, 25.2767099634697, .001, "absolutePressureInResult");
        assert.approximately(saturatedHumidityRatioResult, 0.10830760118401817, .001, "saturatedHumidityRatioResult");
        assert.approximately(degreeOfSaturationResult, 0.008730399075033634, .001, "degreeOfSaturationResult");
        assert.approximately(humidityRatioResult, 0.0009455685811960639, .001, "humidityRatioResult");
        assert.approximately(specificVolumeResult, 17.415694184877726, .001, "specificVolumeResult");
        assert.approximately(enthalpyResult, 31.435887656005303, .001, "enthalpyResult");
        assert.approximately(dewPointResult, 0.35, .001, "dewPointResult");
        assert.approximately(relativeHumidityResult, 0.010235, .001, "relativeHumidityResult");
        assert.approximately(saturationPressureResult, 3.7487420264687445, .001, "saturationPressureResult");
        assert.approximately(wetBulbTempResult, 62.94970394555405, .001, "wetBulbTempResult");
    })

    it('should calculate Wet Bulb Temp Method Results', function () {
        let wetBulbInputs = {
            dryBulbTemp: 123,
            wetBulbTemp: 110,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.WetBulbTemp,
            specificHeatGas: 1.03,
            specificGravity: 1.05,
        }

        let wetBulbInstance = new moduleInstance.BaseGasDensity(
            wetBulbInputs.dryBulbTemp,
            wetBulbInputs.staticPressure,
            wetBulbInputs.barometricPressure,
            wetBulbInputs.wetBulbTemp,
            wetBulbInputs.gasType,
            wetBulbInputs.inputType,
            wetBulbInputs.specificGravity,
            wetBulbInputs.specificHeatGas
        );
        let gasDensityResult = wetBulbInstance.getGasDensity();
        let absolutePressureInResult = wetBulbInstance.getAbsolutePressureIn();
        let saturatedHumidityRatioResult = wetBulbInstance.getSaturatedHumidityRatio();
        let degreeOfSaturationResult = wetBulbInstance.getDegreeOfSaturation();
        let humidityRatioResult = wetBulbInstance.getHumidityRatio();
        let specificVolumeResult = wetBulbInstance.getSpecificVolume();
        let enthalpyResult = wetBulbInstance.getEnthalpy();
        let dewPointResult = wetBulbInstance.getDewPoint();
        let relativeHumidityResult = wetBulbInstance.getRelativeHumidity();
        let saturationPressureResult = wetBulbInstance.getSaturationPressure();
        let wetBulbTempResult = wetBulbInstance.getWetBulbTemp();
        wetBulbInstance.delete();

        assert.approximately(gasDensityResult, 0.05536774050618011, 0.001, "gasDensityResult");
        assert.approximately(absolutePressureInResult, 25.2767099634697, 0.001, "absolutePressureInResult");
        assert.approximately(saturatedHumidityRatioResult, 0.10830760118401817, 0.001, "saturatedHumidityRatioResult");
        assert.approximately(degreeOfSaturationResult, 0.535317, 0.001, "degreeOfSaturationResult");
        assert.approximately(humidityRatioResult, 0.057979, 0.001, "humidityRatioResult");
        assert.approximately(specificVolumeResult, 19.010256, 0.001, "specificVolumeResult");
        assert.approximately(enthalpyResult, 95.062901, 0.001, "enthalpyResult");
        assert.approximately(dewPointResult, 103.567304, 0.001, "dewPointResult");
        assert.approximately(relativeHumidityResult, 0.574939, 0.001, "relativeHumidityResult");
        assert.approximately(saturationPressureResult, 3.7487420264687445, 0.001, "saturationPressureResult");
        assert.approximately(wetBulbTempResult, 110, 0.001, "wetBulbTempResult");
    });
});