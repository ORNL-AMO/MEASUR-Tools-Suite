#include "processHeat/losses/water_cooling_heat_loss.h"

#include <cmath>

#include "physics/constants.h"
namespace water_cooling_heat_loss {
double totalHeatLoss(double flowRate, double initialTemperature, double outletTemperature, double correctionFactor) {
    using namespace physics::conversions;
    using namespace physics::si;

    double avg_temp            = (initialTemperature + outletTemperature) / 2.0;
    double avg_temp_in_celsius = fahrenheitToCelsius(avg_temp);

    // Constants for water density calculation (Tanaka et al., 2001)
    constexpr double kTanakaA          = 288.9414;
    constexpr double kTanakaB          = 508929.2;
    constexpr double kTanakaC          = 68.12963;
    constexpr double kTanakaD          = 3.9863;

    double numerator    = avg_temp_in_celsius + kTanakaA;
    double denominator  = kTanakaB * (avg_temp_in_celsius + kTanakaC);
    double temp_diff_sq = std::pow(avg_temp_in_celsius - kTanakaD, 2);

    double water_density = kWaterDensityBase * (1.0 - (numerator / denominator) * temp_diff_sq);

    double water_density_in_lb_gal = water_density * kKgPerM3ToLbPerGal;
    double temperatureRise         = outletTemperature - initialTemperature;
    // Total heat loss calculation
    //60 = conversion of GPM -> GPH
    return flowRate * 60 * water_density_in_lb_gal * temperatureRise * correctionFactor;
}
} // namespace water_cooling_heat_loss