/**
 * @file
 * @brief Calculator for auxiliary power usage
 *
 * This contains the inputs for calculating the auxiliary power used.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_AUXILIARYPOWER_H
#define TOOLS_SUITE_AUXILIARYPOWER_H

#include <cmath>

/**
 * Auxiliary Power Losses class
 * Used to calculateThermalResistance the energy use of systems using electricity associated with the heating system.
 */
class AuxiliaryPower {
public:
	/**
	 * Constructor for the auxiliary power used with all inputs specified
	 *
	 * @param motorPhase double, current motor phase
	 * @param supplyVoltage double, supply voltage in volts
	 * @param avgCurrent double, average current in Amperes
	 * @param powerFactor double, average power factor value - unitless
	 * @param operatingTime double, percent operating time
	 *
	 */
	AuxiliaryPower(const double motorPhase, const double supplyVoltage, const double avgCurrent,
	               const double powerFactor, const double operatingTime) :
			motorPhase(motorPhase),
			supplyVoltage(supplyVoltage),
	        avgCurrent(avgCurrent),
	        powerFactor(powerFactor),
	        operatingTime(operatingTime / 100.0)
			{}

	/**
     * Calculates the auxiliary power used
     *
     * @return double, auxiliary power used in btu/hr
     */
	double getPowerUsed() const;


private:
	const double motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime;
};

#endif //TOOLS_SUITE_AUXILIARYPOWER_H
