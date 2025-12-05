#include "processHeat/losses/energy_input_electric_arc_furnace.h"
#include "physics/constants.h"
namespace energy_input_electric_arc_furnace {

double totalChemicalEnergyInput(double natural_gas_heat_input, double coal_carbon_injection, double coal_heating_value,
                               double electrode_use, double electrode_heating_value, double other_fuels) {
    // All inputs in BTU/hr except coal/electrode (lb/hr, btu/lb)
    // Convert coal and electrode energy from (lb/hr * btu/lb) to MMBtu/hr
    double coal_heat_content      = (coal_heating_value * coal_carbon_injection)  / 1000000; // MMBtu/hr
    double electrode_heat_content = (electrode_use * electrode_heating_value) / 1000000;     // MMBtu/hr
    // Sum all sources and convert back to BTU/hr
    return (natural_gas_heat_input + coal_heat_content + electrode_heat_content + other_fuels) * 1000000; // BTU/hr
}

double totalHeatDelivered(double total_chemical_energy_input, double electricity_input) {
    using namespace physics::conversions;
    // electricity_input in kWh/hr, convert to MMBtu/hr
    double electricity_heat = (electricity_input * kKilowattToBtuPerHour) / 1000000; // MMBtu/hr
    // Sum and convert back to BTU/hr
    double total_chemical_energy_input_mmbtu = total_chemical_energy_input / 1000000; // MMBtu/hr
    return (total_chemical_energy_input_mmbtu + electricity_heat) * 1000000; // BTU/hr
}

} // namespace energy_input_electric_arc_furnace
