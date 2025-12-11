#include "processHeat/losses/gas_flue_gas_material_heat_loss.h"

#include "physics/gas_composition.h"
using namespace gas_composition;

namespace gas_flue_gas_material_heat_loss {

double totalHeatLoss(double flue_gas_temperature, double excess_air_percentage, double combustion_air_temperature,
                     GasComposition& compositions, double fuel_temperature) {
    double                combustion_air_moisture = 60;
    double                excess_air              = 0;
    ProcessHeatProperties process_heat_properties = compositions.process_heat_properties(
        flue_gas_temperature, excess_air_percentage / 100, combustion_air_temperature, fuel_temperature, combustion_air_moisture, excess_air);
    return process_heat_properties.available_heat;
}

} // namespace gas_flue_gas_material_heat_loss
