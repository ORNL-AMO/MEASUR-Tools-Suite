#include "processHeat/losses/gas_cooling_heat_loss.h"

namespace gas_cooling_heat_loss {

double totalHeatLoss(double flow_rate, double initial_temperature, double final_temperature, double specific_heat, double correction_factor, double gas_density) {
    // 60 = conversion of SCFM (ft³/min) to SCFH (ft³/hr)
    return (flow_rate * 60.0 * gas_density) * specific_heat *
           (final_temperature - initial_temperature) * correction_factor;
}

} // namespace gas_cooling_heat_loss