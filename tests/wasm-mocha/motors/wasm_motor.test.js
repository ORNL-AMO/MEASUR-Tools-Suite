import { assert } from 'chai';

describe('Motor Tests', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });
    
    it('should calculate MotorEfficiency correctly', function () {
        let lineFrequency = moduleInstance.LineFrequency.FREQ60;
        let motorRatedSpeed = 1200;
        let efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        let efficiency = 0;
        let motorRatedPower = 200;
        let loadFactor = 1;
        let instance = new moduleInstance.MotorEfficiency(lineFrequency, motorRatedSpeed, efficiencyClass, motorRatedPower);
        let motorEfficiency = instance.calculate(loadFactor, efficiency) * 100;
        instance.delete();
        assert.equal(motorEfficiency, 95.33208465291122);
    });

    it('should calculate EstimateFLA correctly', function () {
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
        assert.equal(estimatedFLA, 225.800612262395);
    });

    it('should calculate MotorPerformance (current) correctly', function () {
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
        assert.equal(calculatedResults.current, 36.1065805345533);
    });

     it('should calculate MotorPerformance (powerFactor) correctly', function () {
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
        assert.equal(calculatedResults.powerFactor, 61.718229798145316);
     })

      it('should calculate MotorPerformance (efficiency) correctly', function () {
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
        assert.equal(calculatedResults.efficiency, 93.03933838910918);
      })
});