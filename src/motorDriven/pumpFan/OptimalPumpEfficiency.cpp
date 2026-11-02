#include "motorDriven/pumpFan/OptimalPumpEfficiency.h"

#include <cmath>

#include "motorDriven/pump/optimal_pre_pump_efficiency.h"
#include "motorDriven/pumpFan/OptimalSpecificSpeed.h"
#include "motorDriven/pumpFan/OptimalSpecificSpeedCorrection.h"

double OptimalPumpEfficiency::calculate() {

    prePumpEfficiency = optimal_pre_pump_efficiency::calculate({style, flowRate});
    /*
     * You may have individual functions for each also.
     */
    /*
     * Viscosity Correction Factor
     */
    double parameterB = 26.6 * (std::pow(kinematicViscosity, 0.5) * std::pow(head, 0.0625)) /
                        (std::pow(flowRate, 0.375) * std::pow(rpm, 0.25));
    double viscosityCorrectionFactor = std::fmin(1, (std::pow(parameterB, -(0.0547 * std::pow(parameterB, 0.69)))));
    /*
     * Speed Correction
     */
    OptimalSpecificSpeed           optimalSpecificSpeed(rpm, flowRate, head, stageCount);
    double                         specificSpeed = optimalSpecificSpeed.calculate();
    OptimalSpecificSpeedCorrection optimalSpecificSpeedCorrection(style, specificSpeed);
    double                         speedCorrection = optimalSpecificSpeedCorrection.calculate();

    /*
     * Optimal Efficiency
     */
    prePumpEfficiency = prePumpEfficiency / 100;
    optimalEfficiency = prePumpEfficiency * viscosityCorrectionFactor - speedCorrection;
    return optimalEfficiency;
}
