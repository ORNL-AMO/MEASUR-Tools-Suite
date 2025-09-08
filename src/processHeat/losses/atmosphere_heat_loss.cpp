#include "processHeat/losses/atmosphere_heat_loss.h"

namespace atmosphere_heat_loss {

double totalHeatLoss(double flow_rate, double specific_heat, double inlet_temperature, double outlet_temperature,
                     double correction_factor) {
    return flow_rate * specific_heat * (outlet_temperature - inlet_temperature) * correction_factor;
}

} // namespace atmosphere_heat_loss