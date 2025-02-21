/**
 * @file
 * @brief Implementations of Pneumatic Valve of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PNEUMATICVALVE_H
#define TOOLS_SUITE_PNEUMATICVALVE_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class PneumaticValve {
public:
    /**
     * Constructor for PneumaticValve - Can be used for finding flow rate for a pipe with flow coefficient Cv = 1
     * @param inletPressure double, psi
     * @param outletPressure double, psi
     */
    PneumaticValve(double inletPressure, double outletPressure)
            : inletPressure(inletPressure), outletPressure(outletPressure),
              flowRate(0.6875 * std::sqrt(inletPressure - outletPressure) * std::sqrt(inletPressure + outletPressure)),
              flowRateKnown(false)
    {}

    /**
     * Constructor for PneumaticValve - used for finding the flow coefficient (Cv) when the flow rate is known
     * @param inletPressure double, psi
     * @param outletPressure double, psi
     * @param flowRate double, scfm
     */
    PneumaticValve(double inletPressure, double outletPressure, double flowRate)
            : inletPressure(inletPressure), outletPressure(outletPressure), flowRate(flowRate), flowRateKnown(true)
    {}

    /**
     * @return flowRate or flow coefficient depending on which constructor was used
     */
    double calculate() {
        if (!flowRateKnown) {
            return flowRate;
        }
        return flowRate / (0.6875 * std::sqrt(inletPressure - outletPressure) * std::sqrt(inletPressure + outletPressure));
    }

private:
    double inletPressure, outletPressure, flowRate;
    bool flowRateKnown;
};

#endif
