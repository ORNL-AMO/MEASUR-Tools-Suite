/**
 * @brief
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "motorDriven/motor/MotorPerformance.h"

#include "motorDriven/motor/MotorPowerFactor.h"
#include "motorDriven/motor/motor_current.h"
#include "motorDriven/motor/motor_efficiency.h"

MotorPerformance::Output MotorPerformance::calculate() {
    double current     = 0;
    double efficiency  = 0;
    double powerFactor = 0;

    const double calculatedEfficiency =
        motor_efficiency::calculate(
            {lineFrequency, motorRpm, efficiencyClass, motorRatedPower, loadFactor, specifiedEfficiency})
            .efficiency;
    // Motor Current
    const double calculatedCurrent =
        motor_current::calculate(
            {motorRatedPower, motorRpm, lineFrequency, efficiencyClass, specifiedEfficiency, loadFactor, ratedVoltage},
            fullLoadAmps)
            .current;
    // Motor Power Factor
    MotorPowerFactor motorPowerFactor(motorRatedPower, loadFactor, calculatedCurrent, calculatedEfficiency,
                                      ratedVoltage);
    powerFactor = motorPowerFactor.calculate() * 100;
    efficiency  = calculatedEfficiency * 100;
    current     = calculatedCurrent / fullLoadAmps * 100;
    return {current, efficiency, powerFactor};
}
