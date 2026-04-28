import { assert } from 'chai';

describe('Steam Properties', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    function validateSteamProperties(pressure, temperature, expected) {
        let steamProperties = new moduleInstance.SteamProperties(pressure, moduleInstance.ThermodynamicQuantity.TEMPERATURE, temperature).calculate();

        assert.approximately(steamProperties.temperature, expected.temperature, .01, "temperature");
        assert.approximately(steamProperties.pressure, expected.pressure, .01, "pressure");

        assert.approximately(steamProperties.specificVolume, expected.specificVolume, .01, "specificVolume");
        assert.approximately(steamProperties.density, expected.density, .01, "density");
        assert.approximately(steamProperties.specificEnthalpy, expected.specificEnthalpy, .01, "specificEnthalpy");
        assert.approximately(steamProperties.specificEntropy, expected.specificEntropy, .01, "specificEntropy");
        assert.approximately(steamProperties.internalEnergy, expected.internalEnergy, .01, "internalEnergy");

        assert.approximately(steamProperties.specificIsobaricHeatCapacity_cp, expected.specificIsobaricHeatCapacity_cp, .01, "specificIsobaricHeatCapacity_cp");
        assert.approximately(steamProperties.specificIsochoricHeatCapacity_cv, expected.specificIsochoricHeatCapacity_cv, .01, "specificIsochoricHeatCapacity_cv");
        assert.approximately(steamProperties.speedOfSound_w, expected.speedOfSound_w, .01, "speedOfSound_w");
        assert.approximately(steamProperties.isentropicExponent, expected.isentropicExponent, .01, "isentropicExponent");

        steamProperties.delete();
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
            specificVolume:39.4914, density:0.025322, specificEnthalpy:2549.91, specificEntropy:8.52239, internalEnergy:-119.803,
            specificIsobaricHeatCapacity_cp:1.913, specificIsochoricHeatCapacity_cv:1.44133, speedOfSound_w:427.92, isentropicExponent:1.3248});
        validateSteamProperties(0.0035, 700, {temperature:700, pressure:0.0035, quality:1,
            specificVolume:92.3016, density:0.010834, specificEnthalpy:3335.68, specificEntropy:10.175, internalEnergy:-312.731,
            specificIsobaricHeatCapacity_cp:2.08141, specificIsochoricHeatCapacity_cv:1.61978, speedOfSound_w:644.289, isentropicExponent:1.28494});
        validateSteamProperties(30, 700, {temperature:700, pressure:30, quality:1,
            specificVolume:0.00542947, density:184.18, specificEnthalpy:2631.49, specificEntropy:5.1754, internalEnergy:-154.739,
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