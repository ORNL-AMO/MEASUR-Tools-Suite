#include <emscripten/bind.h>
#include "processHeat/losses/energy_input_exhaust_gas_heat_loss.h"

using namespace emscripten;
using namespace energy_input_exhaust_gas_heat_loss;

// energyInputExhaustGasLosses
EMSCRIPTEN_BINDINGS(energy_input_exhaust_gas_heat_loss) {
    // Parameters for EnergyInputExhaustGasResult:
    //   available_heat (%), heat_delivered (Btu/hr), exhaust_gas_losses (Btu/hr)
    value_object<EnergyInputExhaustGasResult>("EnergyInputExhaustGasLossesResult")
        .field("available_heat", &EnergyInputExhaustGasResult::available_heat)
        .field("heat_delivered", &EnergyInputExhaustGasResult::heat_delivered)
        .field("exhaust_gas_losses", &EnergyInputExhaustGasResult::exhaust_gas_losses);

    // Parameters for energyInputExhaustGasLossesCalculate:
    //   excess_air (%), combustion_air_temp (°F), exhaust_gas_temp (°F), total_heat_input (Btu/hr)
    function("energyInputExhaustGasHeatLossCalculate", &calculate);
    // parameters for availableHeat:
    //    excess_air (%), combustion_air_temp (°F), exhaust_gas_temp (°F), total_heat_input (Btu/hr)
    function("energyInputAvailableHeat", &availableHeat);
    // parameters for heatDelivered:
    //   available_heat (%), total_heat_input (Btu/hr)
    function("energyInputHeatDelivered", &heatDelivered);
    // parameters for totalHeatLoss:
    //   heat_delivered (Btu/hr), available_heat (%)
    function("energyInputTotalHeatLoss", &totalHeatLoss);
}