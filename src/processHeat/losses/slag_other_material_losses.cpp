#include "processHeat/losses/slag_other_material_losses.h"

double SlagOtherMaterialLosses::getHeatLoss() {
    this->totalHeat = weight * specificHeat * (outletTemperature - inletTemperature);
    this->totalHeat *= correctionFactor;
    return this->totalHeat;
}