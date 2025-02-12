/**
 * @file
 * @brief Function prototypes for the Fan result fields
 *
 * This contains the prototypes for the Fan results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing, modified and optimal results.
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_FANRESULT_H
#define TOOLS_SUITE_FANRESULT_H

#include "motorDriven/motor/MotorShaftPower.h"

namespace Fan {
    struct Input {
        Input(const double fanSpeed, const double airDensity, const Motor::Drive drive, double specifiedEfficiency)
                : fanSpeed(fanSpeed), airDensity(airDensity), drive(drive), specifiedEfficiency(specifiedEfficiency){}

        double fanSpeed, airDensity;
        Motor::Drive drive;
        double specifiedEfficiency;
    };

    struct FieldDataModified {
        /**
         * To be used for Modified and Optimal Fan results
         * @param measuredVoltage
         * @param measuredAmps
         * @param flowRate
         * @param inletPressure
         * @param outletPressure
         * @param compressibilityFactor
         */
        FieldDataModified(const double measuredVoltage, const double measuredAmps, const double flowRate, const double inletPressure,
                          const double outletPressure, const double compressibilityFactor, const double velocityPressure)
                : measuredVoltage(measuredVoltage), measuredAmps(measuredAmps), flowRate(flowRate),
                  inletPressure(inletPressure), outletPressure(outletPressure), compressibilityFactor(compressibilityFactor), velocityPressure(velocityPressure){}

        double measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, velocityPressure;
    };

    struct FieldDataBaseline: public FieldDataModified {
        /**
         * To be used for Baseline Fan results
         * @param measuredPower
         * @param measuredVoltage
         * @param measuredAmps
         * @param flowRate
         * @param inletPressure
         * @param outletPressure
         * @param compressibilityFactor
         * @param loadEstimationMethod
         */
        FieldDataBaseline(const double measuredPower, const double measuredVoltage, const double measuredAmps,
                          const double flowRate, const double inletPressure, const double outletPressure,
                          const double compressibilityFactor, Motor::LoadEstimationMethod loadEstimationMethod, const double velocityPressure)
                : FieldDataModified(measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, velocityPressure),
                  measuredPower(measuredPower), loadEstimationMethod(loadEstimationMethod){}

        double measuredPower;
        Motor::LoadEstimationMethod loadEstimationMethod;
    };
}

class FanResult
{
public:
    struct Output
    {
        Output(double fanEfficiency, const double motorRatedPower, const double motorShaftPower, const double fanShaftPower,
               double motorEfficiency, double motorPowerFactor, const double motorCurrent, const double motorPower,
               const double annualEnergy, double annualCost, const double fanEnergyIndex, const double loadFactor, double driveEfficiency, const double estimatedFLA = 0)
                : fanEfficiency(fanEfficiency), motorRatedPower(motorRatedPower), motorShaftPower(motorShaftPower),
                  fanShaftPower(fanShaftPower), motorEfficiency(motorEfficiency), motorPowerFactor(motorPowerFactor),
                  motorCurrent(motorCurrent), motorPower(motorPower), annualEnergy(annualEnergy), annualCost(annualCost),
                  fanEnergyIndex(fanEnergyIndex), loadFactor(loadFactor), driveEfficiency(driveEfficiency), estimatedFLA(estimatedFLA){}

        Output(const MotorShaftPower::Output output, double fanEfficiency, const double motorRatedPower,
               const double fanShaftPower, const double annualEnergy, double annualCost, const double fanEnergyIndex, const double loadFactor, double driveEfficiency,
               const double estimatedFLA = 0)
                : fanEfficiency(fanEfficiency), motorRatedPower(motorRatedPower), motorShaftPower(output.shaftPower),
                  fanShaftPower(fanShaftPower), motorEfficiency(output.efficiency), motorPowerFactor(output.powerFactor),
                  motorCurrent(output.current), motorPower(output.power), annualEnergy(annualEnergy), annualCost(annualCost),
                  fanEnergyIndex(fanEnergyIndex), loadFactor(loadFactor), driveEfficiency(driveEfficiency), estimatedFLA(estimatedFLA){}

        double fanEfficiency;
        const double motorRatedPower, motorShaftPower, fanShaftPower;
        double motorEfficiency, motorPowerFactor;
        const double motorCurrent, motorPower, annualEnergy;
        double annualCost;
        const double fanEnergyIndex, loadFactor;
        double driveEfficiency;
        const double estimatedFLA;

        // double fanEfficiency, motorEfficiency, motorPowerFactor;
        // const double motorRatedPower, motorShaftPower, fanShaftPower, motorCurrent;
        // const double motorPower, annualEnergy, annualCost, fanEnergyIndex;
        // const double loadFactor, driveEfficiency, estimatedFLA;
    };

    FanResult(Fan::Input fanInput, Motor motor, double operatingHours, double unitCost)
            : fanInput(fanInput), motor(motor), operatingHours(operatingHours), unitCost(unitCost){}

    /**
       * @param fanFieldData, Fan::FieldDataBaseline
       * @return FanResult::Output, the results of an existing fan system assessment
       */
    Output calculateExisting(Fan::FieldDataBaseline const fanFieldData);

    /**
       * @param fanFieldData, Fan::FieldDataModified
       * @param fanEfficiency, double
       * @return FanResult::Output, the results of a fan system assessment
       */
    Output calculateModified(Fan::FieldDataModified const fanFieldData, double fanEfficiency);

private:
    double annualSavingsPotential = 0;
    double optimizationRating = 0;
    // In values
    Fan::Input fanInput;
    Motor motor;
    double operatingHours, unitCost;
};

#endif //TOOLS_SUITE_FANRESULT_H
