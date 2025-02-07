/**
 * @file
 * @brief Contains the implementation of the fixture losses total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "processHeat/losses/FixtureLosses.h"

double FixtureLosses::getHeatLoss() {
    heatLoss = feedRate * specificHeat * (finalTemperature - initialTemperature) * correctionFactor;
    return heatLoss;
}