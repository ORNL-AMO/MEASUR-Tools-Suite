/**
 * Contains calculations for Fan Shaft Power
 * @author Preston Shires (pshires)
 * @author Allie Ledbetter (Aeledbetter)
 * @bug No Known Bugs.
 * 
 */
#ifndef TOOLS_SUITE_FANSHAFTPOWER_H
#define TOOLS_SUITE_FANSHAFTPOWER_H

#include <cmath>

class FanShaftPower {
public:
/**
 * @param motorShaftPower double, motor shaft power in hp
 *
 */
	FanShaftPower(const double motorShaftPower, const double efficiencyMotor, const double efficiencyVFD,
				  const double efficiencyBelt, const double sumSEF)
			: efficiencyMotor(efficiencyMotor / 100), efficiencyVFD(efficiencyVFD / 100), efficiencyBelt(efficiencyBelt / 100),
			  sumSEF(sumSEF)
	{
		motorPowerOutput = motorShaftPower * this->efficiencyMotor * this->efficiencyVFD;
		fanPowerInput = motorPowerOutput * this->efficiencyBelt;
	}

	/**
	 * Calculates and returns motorShaftPower 
	 * @param voltage const double, the measured bus voltage in volts
	 * @param amps const double, amps
	 * @param powerFactorAtLoad const double, unitless
	 * @return MotorShaftPower, const double, motor shaft power as defined in hp
	 */
	static double calculateMotorShaftPower(const double voltage, const double amps, const double powerFactorAtLoad) {
		return voltage * amps * powerFactorAtLoad * std::sqrt(3);
	}
/**
 * Gets the Fan Power Input 
 * 
 * @return double, Fan power input
 */
	double getFanPowerInput() const { return fanPowerInput; }
/**
 * Gets the SEF
 * 
 * @return double, Sum SEF 
 */
	double getSEF() const { return sumSEF; }

private:
	const double efficiencyMotor, efficiencyVFD, efficiencyBelt;
	const double sumSEF;

	double motorPowerOutput, fanPowerInput;
};

#endif //TOOLS_SUITE_FANSHAFTPOWER_H
