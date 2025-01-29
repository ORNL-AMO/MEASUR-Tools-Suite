/**
 * @brief Contains the declaration of MotorPower class including the getters and setters as well as the calculators.
 *          for motor efficiency.
 *      calculate(): Calculates the motor power
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_MOTORPOWER_H
#define TOOLS_SUITE_MOTORPOWER_H

class MotorPower {
public:
    /**
     * Constructor
     * @param ratedVoltage double, Rated voltage of motor in volts
     * @param motorCurrent double, Motor current as defined in amps.
     * @param powerFactor double, Power factor - unitless
     */
    MotorPower(
        double ratedVoltage,
        double motorCurrent,
        double powerFactor
    ) :
        ratedVoltage(ratedVoltage),
        motorCurrent(motorCurrent),
        powerFactor(powerFactor)
    {};

    /**
     * Calculates the motor power
     * @return double, motor power in hp
     */
    double calculate();

private:
    /**
     * Rated voltage of motor in volts
     */
    double ratedVoltage;
    /**
     * Motor current in amps
     */
    double motorCurrent;
    /**
     * Power factor of motor
     */
    double powerFactor;
};


#endif //TOOLS_SUITE_MOTORPOWER_H
