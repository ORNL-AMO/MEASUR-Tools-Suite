/**
 * @file
 * @brief Contains the implementation of the fixture losses total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "processHeat/losses/fixture_heat_loss.h"

double FixtureLosses::getHeatLoss() {
    heatLoss = feedRate * specificHeat * (finalTemperature - initialTemperature) * correctionFactor;
    return heatLoss;
}
