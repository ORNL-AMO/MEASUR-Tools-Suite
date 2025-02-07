/**
 * @file
 * @brief Function prototypes for the Pump result fields
 *
 * This contains the prototypes for the Pump results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing, modified and optimal results.
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PUMPRESULT_H
#define TOOLS_SUITE_PUMPRESULT_H

#include "motorDriven/pump/PumpData.h"

/**
 * Pump Result class
 * Contains all of the final results of the pump calculations.
 * Used to calculateThermalResistance the existing efficiency of the pump and the optimal efficiency of the pump so they can be compared.
 */
class PumpResult
{
public:
    /**
       * Constructor
       * @param pumpInput Pump::Input, contains all pump-related data, passed by reference
       * @param motor Motor, contains all motor-related calculations, passed by reference
       * @param fieldData FieldData, contains all field data-related calculations, passed by reference
       * @param operatingHours double, fraction(%) of calendar hours the equipment is operating
       * @param unitCost double, per unit energy cost of electricity in $/kwh
       */
    PumpResult(Pump::Input pumpInput, Motor motor, Pump::FieldData fieldData, double operatingHours, double unitCost)
            : pumpInput(pumpInput), motor(motor), fieldData(fieldData), operatingHours(operatingHours),
              unitCost(unitCost){};

    /**
       * Result (output) structure captures the same fields for the existing as well as the optimal condition.
       */
    struct Output
    {

        Output(double pumpEfficiency, double motorRatedPower, double motorShaftPower, double pumpShaftPower,
               double motorEfficiency, double motorPowerFactor, double motorCurrent, double motorPower,
               double annualEnergy, double annualCost, double loadFactor, double driveEfficiency, double estimatedFLA = 0)
                : pumpEfficiency(pumpEfficiency), motorRatedPower(motorRatedPower), motorShaftPower(motorShaftPower), pumpShaftPower(pumpShaftPower),
                  motorEfficiency(motorEfficiency), motorPowerFactor(motorPowerFactor), motorCurrent(motorCurrent), motorPower(motorPower),
                  annualEnergy(annualEnergy), annualCost(annualCost), loadFactor(loadFactor), driveEfficiency(driveEfficiency), estimatedFLA(estimatedFLA)
        {
        }
        Output() = default;

        double pumpEfficiency; ///< Existing: Existing pump efficiency is fluid power added by the pump divided by pump input shaft power.
        ///< Optimal: Optimal pump efficiency is estimated based on the efficiency estimating algorithms contained in Hydraulic Institute Standard HI 1.3-2000, Centrifugal Pump Design and Application.
        double motorRatedPower; ///< Existing: Existing motor nameplate power (same as Rated power in the Motor input section).
        ///< Optimal: This is the nameplate motor rated power for an optimally sized pump.
        double motorShaftPower; ///< Existing: This is the estimated motor shaft power for the existing motor. The estimate is based on measured electrical data and Pump's efficiency estimate for the specified motor size, speed, and class.
        ///< Optimal: This is the motor shaft power requirements for the optimal pump, based on the specified flow rate, head, and specific gravity values, along with the HI 1.3 achievable efficiency algorithms. If a belt drive is specified, associated losses are added to the pump shaft power to determine required motor power. For direct-driven pumps, the pump and motor shaft powers are the same.
        double pumpShaftPower; ///< Existing: This is the estimated pump shaft power for the existing motor. The estimate is the same as the motor shaft power (above) for direct-driven applications. For belt-driven applications, belt losses are deducted from the motor shaft power to determine pump shaft power.
        ///< Optimal: This is the shaft power requirements for the optimal pump, based on the specified flow rate, head, and specific gravity values, along with the HI 1.3 achievable efficiency algorithms.
        double motorEfficiency; ///< Existing: This is the estimated efficiency of the existing motor at the existing load.
        ///< Optimal: This is the estimated efficiency for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double motorPowerFactor; ///< Existing: This is the estimated power factor for the existing motor at the existing load. It is based on the measured electrical data and the motor performance characteristic curves for the specified motor.
        ///< Optimal: This is the estimated power factor for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power (also indicated above).
        double motorCurrent; ///< Existing: This is the estimated or measured current for the existing motor at the existing load.
        ///< Optimal: This is the estimated current for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double motorPower; ///< Existing: This is the estimated or measured electric power for the existing motor at the existing load.
        ///< Optimal: The estimated electric power for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double annualEnergy; ///< Existing: This is the annual energy consumption at the measured/estimated power level for the existing equipment when operated for the fraction of time indicated by the operating fraction.
        ///< Optimal: The annual energy consumption for an optimized pump driven by an energy-efficient motor, based on the estimated motor power and on the fraction of time the pump is operated indicated by the operating fraction.
        double annualCost; ///< Existing: This is the existing annual energy cost based on the product of the existing annual energy consumption and the unit operating cost (cents/kwhr) input.
        ///< Optimal: This is the annual energy cost based on the product of the optimal annual energy consumption and the unit operating cost (cents/kwhr) input.
        double loadFactor;
        double driveEfficiency;
        double estimatedFLA; ///< Existing: The full load amps are either specified (known) or estimated. This field will hold either one. The estimated full load amps are calculated from the motor voltage, hp, and speed.
    };

    /**
       * Gets the annual savings potential
       * @return double, annual savings potential in $/year
       */
    double getAnnualSavingsPotential()
    {
        return annualSavingsPotential;
    }

    /**
       * Gets the optimization rating
       * @return double, optimization rating as %
       */
    double getOptimizationRating() const
    {
        return optimizationRating;
    }

    Output calculateExisting();

    Output calculateModified();

private:
    // Out values
    Output existing, modified;
    double annualSavingsPotential = 0.0;
    double optimizationRating = 0.0;
    // In values
    Pump::Input pumpInput;
    Motor motor;
    Pump::FieldData fieldData;
    double operatingHours, unitCost;
};

#endif //TOOLS_SUITE_PUMPRESULT_H
