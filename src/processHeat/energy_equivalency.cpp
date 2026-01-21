#include "processHeat/energy_equivalency.h"
#include "physics/constants.h"

namespace energy_equivalency {

double calculateElectricalEquivalentHeatInput(
    double fuel_fired_heat_input,
    double fuel_fired_efficiency,
    double electrically_heated_efficiency
) {
    using namespace physics::conversions;
    double energy_use_mmbtu = (fuel_fired_heat_input * fuel_fired_efficiency) / electrically_heated_efficiency;
    return mmbtuPerHrToKW(energy_use_mmbtu);
}

double calculateFuelFiredEquivalentHeatInput(
    double electrical_heat_input,
    double electrically_heated_efficiency,
    double fuel_fired_efficiency
) {
    using namespace physics::conversions;
    double energy_use_kw = (electrical_heat_input * electrically_heated_efficiency) / fuel_fired_efficiency;
    return kWToMMBtuPerHr(energy_use_kw);
}

} // namespace energy_equivalency