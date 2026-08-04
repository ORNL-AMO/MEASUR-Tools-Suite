import { assert } from 'chai';
import createModule, {
    type CalculationsTable,
    type CalculationsTableV,
    type DoubleVector,
    type MeasurToolsSuite,
    type WasteWater_Treatment,
    type WasteWater_TreatmentOutput,
} from 'measur-tools-suite';

describe('Wastewater Treatment', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('returns calculation rows as registered double vectors', function () {
        const treatment: WasteWater_Treatment = new moduleInstance.WasteWater_Treatment(
            20, 200, 1, 1, 40, 35, 0.85, 200, 20, 8,
            10000, 3000, 0.1, 0.6, 60, 0.1, 8, 72, 2, 4.5,
            0.84, 0.92, 2.7, 150, 200, 24, 1, 100, 0.09, 1
        );
        let output: WasteWater_TreatmentOutput | undefined;
        let calculationsTable: CalculationsTableV | undefined;
        let calculationRow: CalculationsTable | undefined;
        let rowValues: DoubleVector | undefined;

        try {
            output = treatment.calculate();
            calculationsTable = output.calculationsTable;
            calculationRow = calculationsTable.get(0);
            rowValues = calculationRow.getArray();

            assert.approximately(output.SolidsRetentionTime, 29, 0.01);
            assert.isAbove(calculationsTable.size(), 0);
            assert.equal(rowValues.size(), 26);
            assert.approximately(rowValues.get(0), calculationRow.Se, 0.0001);
            assert.approximately(rowValues.get(25), calculationRow.SRT, 0.0001);
        } finally {
            rowValues?.delete();
            calculationRow?.delete();
            calculationsTable?.delete();
            output?.delete();
            treatment.delete();
        }
    });
});
