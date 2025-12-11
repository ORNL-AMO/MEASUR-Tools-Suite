import { assert } from 'chai';

describe('Gas Composition', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate GasComposition heatingValue correctly', function () {
        var inp = {
            CH4: 94.1,
            C2H6: 2.4,
            N2: 1.41,
            H2: 0.03,
            C3H8: 0.49,
            C4H10_CnH2n: 0.29,
            H2O: 0,
            CO: 0.42,
            CO2: 0.71,
            SO2: 0,
            O2: 0
        }

        var flueGasByVolumeCalculateHeatingValue = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        var heatingValue = flueGasByVolumeCalculateHeatingValue.heatingValue;
        flueGasByVolumeCalculateHeatingValue.delete();
        assert.equal(heatingValue, 22630.355481082846);
    });

    it('should calculate GasComposition heatingValueVolume correctly', function () {
        var inp = {
            CH4: 94.1,
            C2H6: 2.4,
            N2: 1.41,
            H2: 0.03,
            C3H8: 0.49,
            C4H10_CnH2n: 0.29,
            H2O: 0,
            CO: 0.42,
            CO2: 0.71,
            SO2: 0,
            O2: 0
        }

        var flueGasByVolumeCalculateHeatingValue = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        var heatingValueVolume = flueGasByVolumeCalculateHeatingValue.heatingValueVolume;
        flueGasByVolumeCalculateHeatingValue.delete();
        assert.equal(heatingValueVolume, 1019.664897346019);
    });

    it('should calculate GasComposition specificGravity correctly', function () {
        var inp = {
            CH4: 94.1,
            C2H6: 2.4,
            N2: 1.41,
            H2: 0.03,
            C3H8: 0.49,
            C4H10_CnH2n: 0.29,
            H2O: 0,
            CO: 0.42,
            CO2: 0.71,
            SO2: 0,
            O2: 0
        }

        var flueGasByVolumeCalculateHeatingValue = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        var specificGravity = flueGasByVolumeCalculateHeatingValue.specificGravity;
        flueGasByVolumeCalculateHeatingValue.delete();
        assert.equal(specificGravity, 0.6317829589672002);
    });

    it('should calculate GasComposition excessAir correctly 1', function () {
        var inp = {
            CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        // /100 convert to decimal
        var o2InFlueGas = .5 / 100;
        var flueGasCalculateExcessAir = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
        flueGasCalculateExcessAir.delete();
        assert.equal(excessAir, 2.3172209488353976);
    });

    it('should calculate GasComposition excessAir correctly 2', function () {
        var inp = {
            CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        var o2InFlueGas = 3 / 100;
        var flueGasCalculateExcessAir = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
        flueGasCalculateExcessAir.delete();
        assert.equal(excessAir, 15.52234414568954);
    });

    it('should calculate GasComposition excessAir correctly 3', function () {
        var inp = {
            CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        var o2InFlueGas = 7 / 100;
        var flueGasCalculateExcessAir = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var excessAir = flueGasCalculateExcessAir.calculateExcessAir(o2InFlueGas) * 100;
        flueGasCalculateExcessAir.delete();
        assert.equal(excessAir, 45.197503654937584);
    });


    it('should calculate GasComposition o2InFlueGas correctly 1', function () {
        var inp = {
            excessAir: 2.3172, CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        // /100 convert to decimal
        var o2InFlueGas = 2.3172 / 100;
        var flueGasCalculateO2 = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
        flueGasCalculateO2.delete();
        assert.equal(o2, 0.49366866893805406);
    });

    it('should calculate GasComposition o2InFlueGas correctly 2', function () {
        var inp = {
            excessAir: 2.3172, CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        // /100 convert to decimal
        var o2InFlueGas = 15.5223 / 100;
        var flueGasCalculateO2 = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
        flueGasCalculateO2.delete();
        assert.equal(o2, 2.947933114396894);
    });

    it('should calculate GasComposition o2InFlueGas correctly 3', function () {
        var inp = {
            excessAir: 2.3172, CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0, O2: 0
        }

        // /100 convert to decimal
        var o2InFlueGas = 45.197 / 100;
        var flueGasCalculateO2 = new moduleInstance.GasCompositions('some substance', inp.CH4, inp.C2H6, inp.N2, inp.H2, inp.C3H8, inp.C4H10_CnH2n, inp.H2O, inp.CO, inp.CO2, inp.SO2, inp.O2);
        //x100 to convert to %
        var o2 = flueGasCalculateO2.calculateO2(o2InFlueGas) * 100;
        flueGasCalculateO2.delete();
        assert.equal(o2, 6.900194873506534);
    });
});