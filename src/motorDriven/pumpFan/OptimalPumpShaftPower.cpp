/**
 * @brief Contains the definition of functions of OptimalPumpShaftPower class.
 *      calculate(): Calculates the Optimal Pump ShaftPower
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "motorDriven/pumpFan/OptimalPumpShaftPower.h"

#include "motorDriven/pumpFan/fluid_power.h"

double OptimalPumpShaftPower::calculate() {
    if (isPump) {
        const double fluidPower = fluid_power::calculatePump({specificGravity, flowRate, head});
        return (fluidPower / efficiency) / 0.746;
    }
    const double fluidPower =
        fluid_power::calculateFan({flowRate, inletPressure, outletPressure, compressibilityFactor, velocityPressure});
    return (fluidPower / efficiency) / 0.746;
}
