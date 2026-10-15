#include "motorDriven/pumpFan/MoverEfficiency.h"

#include "motorDriven/pumpFan/fluid_power.h"

double MoverEfficiency::calculate() {
    if (isPump) {
        double const fluidPower   = fluid_power::calculatePump({specificGravity, flowRate, head});
        double const fluidPowerHp = fluidPower / 0.746; // convert to hp
        return fluidPowerHp / moverShaftPower;
    }

    double const fluidPower =
        fluid_power::calculateFan({flowRate, inletPressure, outletPressure, compressibilityFactor, velocityPressure});
    double const fluidPowerHp = fluidPower / 0.746; // convert to hp
    return fluidPowerHp / moverShaftPower;
}
