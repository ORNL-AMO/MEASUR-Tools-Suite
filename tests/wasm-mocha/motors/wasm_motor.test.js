import { assert } from 'chai';

describe('Motor Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    // Helper function to match the original tolerance checking (Math.abs(num1 - num2) < 0.005)
    function assertNumberWithTolerance(actual, expected, description) {
        const tolerance = 0.005;
        const diff = Math.abs(actual - expected);
        assert.isTrue(diff < tolerance, 
            `${description}: Expected ${expected}, got ${actual}, difference ${diff} exceeds tolerance ${tolerance}`);
    }

    it('should calculate NEMA motor efficiency correctly', function () {
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        let motorRatedSpeed = 1200;
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        let efficiency = 0;
        let motorRatedPower = 200;
        let loadFactor = 1;
        let instance = new moduleInstance.MotorEfficiency(lineFrequency, motorRatedSpeed, efficiencyClass, motorRatedPower);
        let motorEfficiency = instance.calculate(loadFactor, efficiency) * 100;
        instance.delete();
        
        assertNumberWithTolerance(motorEfficiency, 95.33208465291122, 'Nema (Motor Efficiency * 100)');
    });

    it('should estimate FLA correctly', function () {
        let motorRatedPower = 200;
        let motorRPM = 1780;
        let lineFrequency = moduleInstance.LineFrequency.FREQ50;
        // Either specify an efficiency class OR provide efficiency percentage
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        let specifiedEfficiency = 0;
        let ratedVoltage = 460;
        let instance = new moduleInstance.EstimateFLA(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency, ratedVoltage);
        let estimatedFLA = instance.getEstimatedFLA();
        instance.delete();
        
        assertNumberWithTolerance(estimatedFLA, 225.800612262395, 'EstimateFLA');
    });

    it('should calculate motor performance correctly', function () {
        // Line frequency 60
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        // Energy efficient
        let motorEfficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        let motorRatedPower = 200;
        let motorRPM = 1780;
        let specifiedEfficiency = 0;
        let loadFactor = .25;
        let motorRatedVoltage = 460;
        let fullLoadAmps = 225.8;

        //Implementation after adding MotorPerformance.h/MotorPerformance.cpp
        let instance = new moduleInstance.MotorPerformance(lineFrequency, motorRPM, motorEfficiencyClass, motorRatedPower, specifiedEfficiency, loadFactor, motorRatedVoltage, fullLoadAmps);
        let calculatedResults = instance.calculate();
        instance.delete();

        assertNumberWithTolerance(calculatedResults.current, 36.1065805345533, "Motor Performance (current)");
        assertNumberWithTolerance(calculatedResults.efficiency, 93.03933838910918, "Motor Performance (efficiency)");
        assertNumberWithTolerance(calculatedResults.powerFactor, 61.718229798145316, "Motor Performance (powerFactor)");
    });
});