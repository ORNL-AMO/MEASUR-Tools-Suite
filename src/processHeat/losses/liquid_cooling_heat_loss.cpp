#include "processHeat/losses/liquid_cooling_heat_loss.h"

namespace liquid_cooling_heat_loss {

double totalHeatLoss(double flow_rate, double density, double initial_temperature, double outlet_temperature, double specific_heat, double correction_factor) {
    //60 = conversion of GPM -> GPH
    return (flow_rate * 60.0 * density) * specific_heat *
           (outlet_temperature - initial_temperature) * correction_factor;
}
}