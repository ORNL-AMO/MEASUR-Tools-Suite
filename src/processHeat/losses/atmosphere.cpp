#include "processHeat/losses/atmosphere.h"

double Atmosphere::getTotalHeat() {
    // return the total net heat for the example case
    totalHeat = flowRate * specificHeat * (outletTemperature - inletTemperature) * correctionFactor;
    return totalHeat;
}
