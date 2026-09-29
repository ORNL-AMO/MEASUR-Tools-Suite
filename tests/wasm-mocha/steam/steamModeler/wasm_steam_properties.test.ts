import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type SteamPropertiesOutput } from 'measur-tools-suite';

type ExpectedSteamProperties = Pick<
    SteamPropertiesOutput,
    | 'temperature'
    | 'pressure'
    | 'quality'
    | 'specificVolume'
    | 'density'
    | 'specificEnthalpy'
    | 'specificEntropy'
    | 'internalEnergy'
    | 'specificIsobaricHeatCapacity_cp'
    | 'specificIsochoricHeatCapacity_cv'
    | 'speedOfSound_w'
    | 'isentropicExponent'
>;

describe('Steam Properties', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function validateSteamProperties(pressure: number, temperature: number, expected: ExpectedSteamProperties): void {
        const steamProperties = new moduleInstance.SteamProperties(pressure, moduleInstance.ThermodynamicQuantity.TEMPERATURE, temperature);
        try {
            const steamPropertiesRes: SteamPropertiesOutput = steamProperties.calculate();
            try {
                assert.approximately(steamPropertiesRes.temperature, expected.temperature, .01, "temperature");
                assert.approximately(steamPropertiesRes.pressure, expected.pressure, .01, "pressure");

                assert.approximately(steamPropertiesRes.specificVolume, expected.specificVolume, .01, "specificVolume");
                assert.approximately(steamPropertiesRes.density, expected.density, .01, "density");
                assert.approximately(steamPropertiesRes.specificEnthalpy, expected.specificEnthalpy, .01, "specificEnthalpy");
                assert.approximately(steamPropertiesRes.specificEntropy, expected.specificEntropy, .01, "specificEntropy");
                assert.approximately(steamPropertiesRes.internalEnergy, expected.internalEnergy, .01, "internalEnergy");

                assert.approximately(steamPropertiesRes.specificIsobaricHeatCapacity_cp, expected.specificIsobaricHeatCapacity_cp, .01, "specificIsobaricHeatCapacity_cp");
                assert.approximately(steamPropertiesRes.specificIsochoricHeatCapacity_cv, expected.specificIsochoricHeatCapacity_cv, .01, "specificIsochoricHeatCapacity_cv");
                assert.approximately(steamPropertiesRes.speedOfSound_w, expected.speedOfSound_w, .01, "speedOfSound_w");
                assert.approximately(steamPropertiesRes.isentropicExponent, expected.isentropicExponent, .01, "isentropicExponent");
            } finally {
                steamPropertiesRes.delete();
            }
        } finally {
            steamProperties.delete();
        }
    }

    it('Calculates Steam Properties', function () {
        // Region 1
        validateSteamProperties(3, 300, {temperature:300, pressure:3, quality:0,
            specificVolume:0.00100215, density:997.853, specificEnthalpy:115.331, specificEntropy:0.392295, internalEnergy:0,
            specificIsobaricHeatCapacity_cp:4.17301, specificIsochoricHeatCapacity_cv:4.1212, speedOfSound_w:1507.74, isentropicExponent:1.25});
        validateSteamProperties(80, 300, {temperature:300, pressure:80, quality:0,
            specificVolume:0.000971181, density:1029.67, specificEnthalpy:184.143, specificEntropy:0.368564, internalEnergy:0,
            specificIsobaricHeatCapacity_cp:4.01009, specificIsochoricHeatCapacity_cv:3.91737, speedOfSound_w:1634.69, isentropicExponent:1.25});
        validateSteamProperties(3, 500, {temperature:500, pressure:3, quality:0,
            specificVolume:0.00120242, density:831.658, specificEnthalpy:975.542, specificEntropy:2.58042, internalEnergy:0,
            specificIsobaricHeatCapacity_cp:4.65581, specificIsochoricHeatCapacity_cv:3.22139, speedOfSound_w:1240.71, isentropicExponent:1.25});

        // Region 2
        validateSteamProperties(0.0035, 300, {temperature:300, pressure:0.0035, quality:1,
            specificVolume:39.4914, density:0.025322, specificEnthalpy:2549.91, specificEntropy:8.52239, internalEnergy:2411.69,
            specificIsobaricHeatCapacity_cp:1.913, specificIsochoricHeatCapacity_cv:1.44133, speedOfSound_w:427.92, isentropicExponent:1.3248});
        validateSteamProperties(0.0035, 700, {temperature:700, pressure:0.0035, quality:1,
            specificVolume:92.3016, density:0.010834, specificEnthalpy:3335.68, specificEntropy:10.175, internalEnergy:3012.63,
            specificIsobaricHeatCapacity_cp:2.08141, specificIsochoricHeatCapacity_cv:1.61978, speedOfSound_w:644.289, isentropicExponent:1.28494});
        validateSteamProperties(30, 700, {temperature:700, pressure:30, quality:1,
            specificVolume:0.00542947, density:184.18, specificEnthalpy:2631.49, specificEntropy:5.1754, internalEnergy:2468.61,
            specificIsobaricHeatCapacity_cp:10.3505, specificIsochoricHeatCapacity_cv:2.97554, speedOfSound_w:480.387, isentropicExponent:1.34});

        // Region 3
        validateSteamProperties(25.5837018, 650, {temperature:650, pressure:25.5837, quality:0,
            specificVolume:0.002, density:500, specificEnthalpy:1863.43, specificEntropy:4.05427, internalEnergy:1812.26,
            specificIsobaricHeatCapacity_cp:13.8936, specificIsochoricHeatCapacity_cv:3.19132, speedOfSound_w:502.006, isentropicExponent:1.25});
        validateSteamProperties(22.2930643, 650, {temperature:650, pressure:22.2931, quality:0,
            specificVolume:0.005, density:200, specificEnthalpy:2375.12, specificEntropy:4.85439, internalEnergy:2263.66,
            specificIsobaricHeatCapacity_cp:44.6579, specificIsochoricHeatCapacity_cv:4.04118, speedOfSound_w:383.445, isentropicExponent:1.31906});
        validateSteamProperties(78.3095639, 750, {temperature:750, pressure:78.3096, quality:0,
            specificVolume:0.002, density:500, specificEnthalpy:2258.69, specificEntropy:4.46972, internalEnergy:2102.07,
            specificIsobaricHeatCapacity_cp:6.34165, specificIsochoricHeatCapacity_cv:2.71702, speedOfSound_w:760.696, isentropicExponent:1.25});
    });
});
