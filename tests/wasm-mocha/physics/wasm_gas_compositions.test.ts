import { assert } from 'chai';
import createModule, { type GasCompositions, type MeasurToolsSuite } from 'measur-tools-suite';

type GasCompositionInput = {
    CH4: number;
    C2H6: number;
    N2: number;
    H2: number;
    C3H8: number;
    C4H10_CnH2n: number;
    H2O: number;
    CO: number;
    CO2: number;
    SO2: number;
    O2: number;
};

describe('Gas Composition', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    const gasCompositionInput: GasCompositionInput = {
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
    };

    function createGasCompositions(input: GasCompositionInput): GasCompositions {
        return new moduleInstance.GasCompositions(
            'some substance',
            input.CH4,
            input.C2H6,
            input.N2,
            input.H2,
            input.C3H8,
            input.C4H10_CnH2n,
            input.H2O,
            input.CO,
            input.CO2,
            input.SO2,
            input.O2
        );
    }

    it('should calculate GasComposition heatingValue correctly', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            assert.equal(gasCompositions.heatingValue, 22630.355481082846);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition heatingValueVolume correctly', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            assert.equal(gasCompositions.heatingValueVolume, 1019.664897346019);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition specificGravity correctly', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            assert.equal(gasCompositions.specificGravity, 0.6317829589672002);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition excessAir correctly 1', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const o2InFlueGas = 0.5 / 100;
            const excessAir = gasCompositions.calculateExcessAir(o2InFlueGas) * 100;
            assert.equal(excessAir, 2.3172209488353976);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition excessAir correctly 2', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const o2InFlueGas = 3 / 100;
            const excessAir = gasCompositions.calculateExcessAir(o2InFlueGas) * 100;
            assert.equal(excessAir, 15.52234414568954);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition excessAir correctly 3', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const o2InFlueGas = 7 / 100;
            const excessAir = gasCompositions.calculateExcessAir(o2InFlueGas) * 100;
            assert.equal(excessAir, 45.197503654937584);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition o2InFlueGas correctly 1', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const excessAir = 2.3172 / 100;
            const o2 = gasCompositions.calculateO2(excessAir) * 100;
            assert.equal(o2, 0.49366866893805406);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition o2InFlueGas correctly 2', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const excessAir = 15.5223 / 100;
            const o2 = gasCompositions.calculateO2(excessAir) * 100;
            assert.equal(o2, 2.947933114396894);
        } finally {
            gasCompositions.delete();
        }
    });

    it('should calculate GasComposition o2InFlueGas correctly 3', function () {
        const gasCompositions = createGasCompositions(gasCompositionInput);

        try {
            const excessAir = 45.197 / 100;
            const o2 = gasCompositions.calculateO2(excessAir) * 100;
            assert.equal(o2, 6.900194873506534);
        } finally {
            gasCompositions.delete();
        }
    });
});
