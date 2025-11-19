#include "processHeat/losses/fixture_heat_loss.h"

namespace fixture_heat_loss {

double totalHeatLoss(double specific_heat, double feed_rate, double initial_temperature, double final_temperature,
                     double correction_factor) {
    return feed_rate * specific_heat * (final_temperature - initial_temperature) * correction_factor;
}

} // namespace fixture_heat_loss
