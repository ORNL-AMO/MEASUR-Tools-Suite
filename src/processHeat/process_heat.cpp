
#include "processHeat/process_heat.h"

namespace process_heat {

double calculateExcessAir(double o2_flue_gas) {
    constexpr double kStoichAirFactor = 8.52381;
    constexpr double kO2FlueGasFactor = 9.52381;
    return kStoichAirFactor * o2_flue_gas / (2.0 - kO2FlueGasFactor * o2_flue_gas);
}
} // namespace process_heat