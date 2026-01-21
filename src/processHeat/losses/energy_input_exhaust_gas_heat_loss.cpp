#include "processHeat/losses/energy_input_exhaust_gas_heat_loss.h"


#include "physics/constants.h"

namespace {
constexpr double kBaseHeatPercent     = 95.0;  // Base available heat percent (model-specific)
constexpr double kExhaustGasTempCoeff = 0.025; // Coefficient for exhaust gas temp in heat calculation (model-specific)
using physics::us::kAirCorrectionBase;
using physics::us::kSpecificHeatAirBase;
using physics::us::kSpecificHeatAirCoeff;
} // namespace

namespace energy_input_exhaust_gas_heat_loss {

double availableHeat(double excess_air, double combustion_air_temp, double exhaust_gas_temp, double total_heat_input) {
    // If total heat input is zero, available heat is 100%
    if (total_heat_input == 0.0) {
        return 100.0;
    }
    // Convert excess air percent to fraction
    double excess_air_frac = excess_air / 100.0;

    // Calculate base heat percent minus exhaust gas temperature effect
    double heat = kBaseHeatPercent - kExhaustGasTempCoeff * exhaust_gas_temp;

    // Calculate specific heat of air as a function of combustion air temperature
    double specific_heat_air = kSpecificHeatAirBase + kSpecificHeatAirCoeff * combustion_air_temp;

    // Air correction: accounts for excess air and exhaust gas temperature
    double air_correction = ((kAirCorrectionBase + specific_heat_air * exhaust_gas_temp) * excess_air_frac);

    // Combustion air correction: accounts for combustion air temperature and excess air
    double combustion_air_correction =
        (kAirCorrectionBase + specific_heat_air * combustion_air_temp) * (1.0 + excess_air_frac);

    return heat - air_correction + combustion_air_correction;
}

double heatDelivered(double available_heat, double total_heat_input) {
    // Heat delivered is total heat input multiplied by available heat percent
    return total_heat_input * available_heat / 100.0;
}

double totalHeatLoss(double heat_delivered, double available_heat) {
    // Exhaust gas losses are the fraction of heat delivered that is lost
    return heat_delivered * (100.0 - available_heat) / available_heat;
}

EnergyInputExhaustGasResult calculate(double excess_air, double combustion_air_temp, double exhaust_gas_temp,
                                             double total_heat_input) {
    double avail     = availableHeat(excess_air, combustion_air_temp, exhaust_gas_temp, total_heat_input);
    double delivered = heatDelivered(avail, total_heat_input);
    double losses    = totalHeatLoss(delivered, avail);
    return EnergyInputExhaustGasResult{avail, delivered, losses};
}

} // namespace energy_input_exhaust_gas_heat_loss
