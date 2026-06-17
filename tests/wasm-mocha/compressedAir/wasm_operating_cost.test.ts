import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type OperatingCostInput,
    type OperatingCostResult,
} from 'measur-tools-suite';

describe('Compressed Air Operating Cost', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('should calculate annual operating cost (case 1)', function () {
        const inp: OperatingCostInput = {
            motorBhp: 215,
            bhpUnloaded: 25,
            annualOperatingHours: 6800,
            runTimeLoaded: 85,
            efficiencyLoaded: 95,
            efficiencyUnloaded: 90,
            costOfElectricity: 0.05
        };

        const result: OperatingCostResult = moduleInstance.calculateOperatingCost(inp);

        assert.approximately(result.runTimeUnloaded, 15, 0.01);
        assert.approximately(result.costForLoaded, 48792.326316, 0.01);
        assert.approximately(result.costForUnloaded, 2272.191667, 0.01);
        assert.approximately(result.totalAnnualCost, 51064.517982, 0.01);
    });

    it('should calculate annual operating cost (case 2)', function () {
        const inp: OperatingCostInput = {
            motorBhp: 255,
            bhpUnloaded: 35,
            annualOperatingHours: 6000,
            runTimeLoaded: 89,
            efficiencyLoaded: 93,
            efficiencyUnloaded: 90,
            costOfElectricity: 0.09
        };

        const result: OperatingCostResult = moduleInstance.calculateOperatingCost(inp);

        assert.approximately(result.runTimeUnloaded, 11, 0.01);
        assert.approximately(result.costForLoaded, 98305.954839, 0.01);
        assert.approximately(result.costForUnloaded, 4394.313, 0.01);
        assert.approximately(result.totalAnnualCost, 102700.267839, 0.01);
    });
});
