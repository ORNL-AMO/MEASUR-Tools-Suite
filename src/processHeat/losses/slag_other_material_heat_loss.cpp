#include "processHeat/losses/slag_other_material_heat_loss.h"

namespace slag_other_material_heat_loss {
double totalHeatLoss(double weight, double inlet_temperature, double outlet_temperature, double specific_heat,
                     double correction_factor) {
    return weight * specific_heat * (outlet_temperature - inlet_temperature) * correction_factor;
}

} // namespace slag_other_material_heat_loss