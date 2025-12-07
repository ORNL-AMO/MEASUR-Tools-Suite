#include "processHeat/losses/exhaust_gas_heat_loss_electric_arc_furnace.h"
#include "physics/constants.h"

namespace exhaust_gas_heat_loss_electric_arc_furnace {

namespace {
constexpr double kCOHeatingValueBtuPerPercent = 321.0; // Btu per % CO
constexpr double kH2HeatingValueBtuPerPercent = 325.0; // Btu per % H2
constexpr double kCombustibleHeatingValueBtuPerPercent = 1020.0; // Btu per % combustibles
constexpr double kSensibleHeatFactor = 0.0225; // Btu per (°F above 60)
constexpr double kDustHeatFactor = 0.25; // Btu per dust loading per (°F above 60)
}

double totalHeatLoss(double off_gas_temp, double co_percent, double h2_percent, double combustible_gases_percent,
                        double volume_flow_rate, double dust_loading) {
    using namespace physics::us;
    using namespace physics::conversions;
    // Chemical heat from gas composition
    double co_heat      = co_percent * kCOHeatingValueBtuPerPercent / 100.0;
    double h2_heat      = h2_percent * kH2HeatingValueBtuPerPercent / 100.0;
    double combustibles = combustible_gases_percent * kCombustibleHeatingValueBtuPerPercent / 100.0;
    double chemical_heat = co_heat + h2_heat + combustibles;

    // Sensible heat and dust heat
    double sensible_heat = kSensibleHeatFactor * (off_gas_temp - kAmbientTemperatureF);
    double heat_in_dust  = dust_loading * kDustHeatFactor * (off_gas_temp - kAmbientTemperatureF);
    double total_heat_flue = chemical_heat + sensible_heat + heat_in_dust;

    // Correct volume flow rate for temperature
    double total_vfr = volume_flow_rate * kStandardGasTemperatureF / (460.0 + off_gas_temp);

    // Total heat loss (Btu/hr)
    double total_heat_loss = total_vfr * total_heat_flue * kMinutesPerHour;
    return total_heat_loss;
}

} // namespace exhaust_gas_heat_loss_electric_arc_furnace
