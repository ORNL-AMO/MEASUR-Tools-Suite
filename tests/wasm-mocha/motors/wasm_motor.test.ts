import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type MotorPerformanceOutput } from 'measur-tools-suite';

describe('Motor Tests', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    function createMotorPerformance(): InstanceType<MeasurToolsSuite['MotorPerformance']> {
        const lineFrequency = moduleInstance.LineFrequency.FREQ60;
        const motorEfficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        const motorRatedPower = 200;
        const motorRPM = 1780;
        const specifiedEfficiency = 0;
        const loadFactor = 0.25;
        const motorRatedVoltage = 460;
        const fullLoadAmps = 225.8;

        return new moduleInstance.MotorPerformance(
            lineFrequency,
            motorRPM,
            motorEfficiencyClass,
            motorRatedPower,
            specifiedEfficiency,
            loadFactor,
            motorRatedVoltage,
            fullLoadAmps
        );
    }

    it('should calculate MotorEfficiency correctly', function () {
        const lineFrequency = moduleInstance.LineFrequency.FREQ60;
        const motorRatedSpeed = 1200;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        const efficiency = 0;
        const motorRatedPower = 200;
        const loadFactor = 1;
        const instance = new moduleInstance.MotorEfficiency(lineFrequency, motorRatedSpeed, efficiencyClass, motorRatedPower);

        try {
            const motorEfficiency = instance.calculate(loadFactor, efficiency) * 100;
            assert.equal(motorEfficiency, 95.33208465291122);
        } finally {
            instance.delete();
        }
    });

    it('should calculate EstimateFLA correctly', function () {
        const motorRatedPower = 200;
        const motorRPM = 1780;
        const lineFrequency = moduleInstance.LineFrequency.FREQ50;
        const efficiencyClass = moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT;
        const specifiedEfficiency = 0;
        const ratedVoltage = 460;
        const instance = new moduleInstance.EstimateFLA(
            motorRatedPower,
            motorRPM,
            lineFrequency,
            efficiencyClass,
            specifiedEfficiency,
            ratedVoltage
        );

        try {
            const estimatedFLA = instance.getEstimatedFLA();
            assert.equal(estimatedFLA, 225.800612262395);
        } finally {
            instance.delete();
        }
    });

    it('should calculate MotorPerformance (current) correctly', function () {
        const instance = createMotorPerformance();
        let calculatedResults: MotorPerformanceOutput | undefined;

        try {
            calculatedResults = instance.calculate();
            assert.equal(calculatedResults.current, 36.1065805345533);
        } finally {
            calculatedResults?.delete();
            instance.delete();
        }
    });

    it('should calculate MotorPerformance (powerFactor) correctly', function () {
        const instance = createMotorPerformance();
        let calculatedResults: MotorPerformanceOutput | undefined;

        try {
            calculatedResults = instance.calculate();
            assert.equal(calculatedResults.powerFactor, 61.718229798145316);
        } finally {
            calculatedResults?.delete();
            instance.delete();
        }
    });

    it('should calculate MotorPerformance (efficiency) correctly', function () {
        const instance = createMotorPerformance();
        let calculatedResults: MotorPerformanceOutput | undefined;

        try {
            calculatedResults = instance.calculate();
            assert.equal(calculatedResults.efficiency, 93.03933838910918);
        } finally {
            calculatedResults?.delete();
            instance.delete();
        }
    });
});
