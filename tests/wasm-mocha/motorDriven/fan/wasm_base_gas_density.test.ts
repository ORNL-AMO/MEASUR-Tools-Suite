import { assert } from 'chai';
import createModule, {
    type BaseGasDensity,
    type BaseGasDensityInputType,
    type GasType,
    type MeasurToolsSuite
} from 'measur-tools-suite';

type BaseGasDensityResults = {
    gasDensity: number;
    absolutePressureIn: number;
    saturatedHumidityRatio: number;
    degreeOfSaturation: number;
    humidityRatio: number;
    specificVolume: number;
    enthalpy: number;
    dewPoint: number;
    relativeHumidity: number;
    saturationPressure: number;
    wetBulbTemp: number;
};

describe('Base Gas Density', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function calculateResults(baseGasDensity: BaseGasDensity): BaseGasDensityResults {
        try {
            return {
                gasDensity: baseGasDensity.getGasDensity(),
                absolutePressureIn: baseGasDensity.getAbsolutePressureIn(),
                saturatedHumidityRatio: baseGasDensity.getSaturatedHumidityRatio(),
                degreeOfSaturation: baseGasDensity.getDegreeOfSaturation(),
                humidityRatio: baseGasDensity.getHumidityRatio(),
                specificVolume: baseGasDensity.getSpecificVolume(),
                enthalpy: baseGasDensity.getEnthalpy(),
                dewPoint: baseGasDensity.getDewPoint(),
                relativeHumidity: baseGasDensity.getRelativeHumidity(),
                saturationPressure: baseGasDensity.getSaturationPressure(),
                wetBulbTemp: baseGasDensity.getWetBulbTemp()
            };
        } finally {
            baseGasDensity.delete();
        }
    }

    it('should calculate Relative Humidity Method Results', function () {
        const relativeHumidityInputs: {
            dryBulbTemp: number;
            staticPressure: number;
            barometricPressure: number;
            gasType: GasType;
            inputType: BaseGasDensityInputType;
            relativeHumidity: number;
            specificGravity: number;
        } = {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.RelativeHumidity,
            relativeHumidity: 35,
            specificGravity: 1.05
        };

        const results = calculateResults(new moduleInstance.BaseGasDensity(
            relativeHumidityInputs.dryBulbTemp,
            relativeHumidityInputs.staticPressure,
            relativeHumidityInputs.barometricPressure,
            relativeHumidityInputs.relativeHumidity,
            relativeHumidityInputs.gasType,
            relativeHumidityInputs.inputType,
            relativeHumidityInputs.specificGravity
        ));

        assert.approximately(results.gasDensity, 0.05637830145287457, 0.001, "gasDensityResult");
        assert.approximately(results.absolutePressureIn, 25.2767099634697, 0.001, "absolutePressureInResult");
        assert.approximately(results.saturatedHumidityRatio, 0.10830760118401817, 0.001, "saturatedHumidityRatioResult");
        assert.approximately(results.degreeOfSaturation, 0.3144126326912711, 0.001, "degreeOfSaturationResult");
        assert.approximately(results.humidityRatio, 0.03405327802874338, 0.001, "humidityRatioResult");
        assert.approximately(results.specificVolume, 18.34133436767489, 0.001, "specificVolumeResult");
        assert.approximately(results.enthalpy, 68.37124560820246, 0.001, "enthalpyResult");
        assert.approximately(results.dewPoint, 87.40387101362482, 0.001, "dewPointResult");
        assert.approximately(results.relativeHumidity, 0.35, 0.001, "relativeHumidityResult");
        assert.approximately(results.saturationPressure, 3.7487420264687445, 0.001, "saturationPressureResult");
        assert.approximately(results.wetBulbTemp, 93.25804647868017, 0.001, "wetBulbTempResult");
    });

    it('should calculate Dew Point Method Results', function () {
        const dewPointInputs: {
            dryBulbTemp: number;
            staticPressure: number;
            barometricPressure: number;
            gasType: GasType;
            inputType: BaseGasDensityInputType;
            dewPoint: number;
            specificGravity: number;
        } = {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.DewPoint,
            dewPoint: 0.35,
            specificGravity: 1.05
        };

        const results = calculateResults(new moduleInstance.BaseGasDensity(
            dewPointInputs.dryBulbTemp,
            dewPointInputs.staticPressure,
            dewPointInputs.barometricPressure,
            dewPointInputs.dewPoint,
            dewPointInputs.gasType,
            dewPointInputs.inputType,
            dewPointInputs.specificGravity
        ));

        assert.approximately(results.gasDensity, 0.057473768082717605, 0.001, "gasDensityResult");
        assert.approximately(results.absolutePressureIn, 25.2767099634697, 0.001, "absolutePressureInResult");
        assert.approximately(results.saturatedHumidityRatio, 0.10830760118401817, 0.001, "saturatedHumidityRatioResult");
        assert.approximately(results.degreeOfSaturation, 0.008730399075033634, 0.001, "degreeOfSaturationResult");
        assert.approximately(results.humidityRatio, 0.0009455685811960639, 0.001, "humidityRatioResult");
        assert.approximately(results.specificVolume, 17.415694184877726, 0.001, "specificVolumeResult");
        assert.approximately(results.enthalpy, 31.435887656005303, 0.001, "enthalpyResult");
        assert.approximately(results.dewPoint, 0.35, 0.001, "dewPointResult");
        assert.approximately(results.relativeHumidity, 0.010235, 0.001, "relativeHumidityResult");
        assert.approximately(results.saturationPressure, 3.7487420264687445, 0.001, "saturationPressureResult");
        assert.approximately(results.wetBulbTemp, 62.94970394555405, 0.001, "wetBulbTempResult");
    });

    it('should calculate Wet Bulb Temp Method Results', function () {
        const wetBulbInputs: {
            dryBulbTemp: number;
            wetBulbTemp: number;
            staticPressure: number;
            barometricPressure: number;
            gasType: GasType;
            inputType: BaseGasDensityInputType;
            specificHeatGas: number;
            specificGravity: number;
        } = {
            dryBulbTemp: 123,
            wetBulbTemp: 110,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasType: moduleInstance.GasType.AIR,
            inputType: moduleInstance.BaseGasDensityInputType.WetBulbTemp,
            specificHeatGas: 1.03,
            specificGravity: 1.05
        };

        const results = calculateResults(new moduleInstance.BaseGasDensity(
            wetBulbInputs.dryBulbTemp,
            wetBulbInputs.staticPressure,
            wetBulbInputs.barometricPressure,
            wetBulbInputs.wetBulbTemp,
            wetBulbInputs.gasType,
            wetBulbInputs.inputType,
            wetBulbInputs.specificGravity,
            wetBulbInputs.specificHeatGas
        ));

        assert.approximately(results.gasDensity, 0.05536774050618011, 0.001, "gasDensityResult");
        assert.approximately(results.absolutePressureIn, 25.2767099634697, 0.001, "absolutePressureInResult");
        assert.approximately(results.saturatedHumidityRatio, 0.10830760118401817, 0.001, "saturatedHumidityRatioResult");
        assert.approximately(results.degreeOfSaturation, 0.535317, 0.001, "degreeOfSaturationResult");
        assert.approximately(results.humidityRatio, 0.057979, 0.001, "humidityRatioResult");
        assert.approximately(results.specificVolume, 19.010256, 0.001, "specificVolumeResult");
        assert.approximately(results.enthalpy, 95.062901, 0.001, "enthalpyResult");
        assert.approximately(results.dewPoint, 103.567304, 0.001, "dewPointResult");
        assert.approximately(results.relativeHumidity, 0.574939, 0.001, "relativeHumidityResult");
        assert.approximately(results.saturationPressure, 3.7487420264687445, 0.001, "saturationPressureResult");
        assert.approximately(results.wetBulbTemp, 110, 0.001, "wetBulbTempResult");
    });
});
