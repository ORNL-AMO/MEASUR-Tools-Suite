import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpEnumsModule } from 'measur-tools-suite';

describe('Shared pump runtime enums', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    it('preserves every exported runtime member and native numeric value', function () {
        const enums: PumpEnumsModule = moduleInstance;
        const styles = [
            ['END_SUCTION_SLURRY', enums.PumpStyle.END_SUCTION_SLURRY, 0],
            ['END_SUCTION_SEWAGE', enums.PumpStyle.END_SUCTION_SEWAGE, 1],
            ['END_SUCTION_STOCK', enums.PumpStyle.END_SUCTION_STOCK, 2],
            ['END_SUCTION_SUBMERSIBLE_SEWAGE', enums.PumpStyle.END_SUCTION_SUBMERSIBLE_SEWAGE, 3],
            ['API_DOUBLE_SUCTION', enums.PumpStyle.API_DOUBLE_SUCTION, 4],
            ['MULTISTAGE_BOILER_FEED', enums.PumpStyle.MULTISTAGE_BOILER_FEED, 5],
            ['END_SUCTION_ANSI_API', enums.PumpStyle.END_SUCTION_ANSI_API, 6],
            ['AXIAL_FLOW', enums.PumpStyle.AXIAL_FLOW, 7],
            ['DOUBLE_SUCTION', enums.PumpStyle.DOUBLE_SUCTION, 8],
            ['VERTICAL_TURBINE', enums.PumpStyle.VERTICAL_TURBINE, 9],
            ['LARGE_END_SUCTION', enums.PumpStyle.LARGE_END_SUCTION, 10],
            ['SPECIFIED_OPTIMAL_EFFICIENCY', enums.PumpStyle.SPECIFIED_OPTIMAL_EFFICIENCY, 11],
            ['POSITIVE_DISPLACEMENT', enums.PumpStyle.POSITIVE_DISPLACEMENT, 12],
        ] as const;
        for (const [name, member, expected] of styles) {
            assert.property(enums.PumpStyle, name);
            // Embind enum members are runtime objects, despite the established enum declarations.
            assert.strictEqual(Object.getOwnPropertyDescriptor(member, 'value')?.value, expected);
        }
        assert.strictEqual(Object.getOwnPropertyDescriptor(enums.SpecificSpeed.FIXED_SPEED, 'value')?.value, 0);
        assert.strictEqual(Object.getOwnPropertyDescriptor(enums.SpecificSpeed.NOT_FIXED_SPEED, 'value')?.value, 1);
    });

    it('remains usable by new plain inputs and existing class consumers', function () {
        const style = moduleInstance.PumpStyle.END_SUCTION_SLURRY;
        assert.isNumber(moduleInstance.calculateOptimalPrePumpEfficiency({ style, flowRate: 2000 }));
        const correction = new moduleInstance.OptimalSpecificSpeedCorrection(style, 1170);
        try {
            assert.approximately(correction.calculate() * 100, 1.8942771852074485, 0.001);
        } finally {
            correction.delete();
        }
    });
});
