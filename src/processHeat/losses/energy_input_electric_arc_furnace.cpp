#include "processHeat/losses/energy_input_electric_arc_furnace.h"

#include "physics/constants.h"
namespace energy_input_electric_arc_furnace {

double totalChemicalEnergyInput(double natural_gas_heat_input, double coal_carbon_injection, double coal_heating_value,
                                double electrode_use, double electrode_heating_value, double other_fuels) {
    // Units: natural_gas_heat_input (MMBtu/hr), other_fuels (MMBtu/hr), coal_carbon_injection (lb/hr),
    // coal_heating_value (btu/lb), electrode_use (lb/hr), electrode_heating_value (btu/lb) Convert coal and electrode
    // energy from (lb/hr * btu/lb) to BTU/hr
    double coal_heat_content      = (coal_heating_value * coal_carbon_injection); // BTU/hr
    double electrode_heat_content = (electrode_use * electrode_heating_value);    // BTU/hr
    // convert MMBtu to BTU/hr
    double natural_gas_heat_input_btu = natural_gas_heat_input * 1000000;                                 // BTU/hr
    double other_fuels_btu            = other_fuels * 1000000;                                            // BTU/hr
    return (natural_gas_heat_input_btu + coal_heat_content + electrode_heat_content + other_fuels_btu); // BTU/hr
}

double totalHeatDelivered(double total_chemical_energy_input, double electricity_input) {
    using namespace physics::conversions;
    // electricity_input in kWh/hr, convert to BTU/hr
    double electricity_heat = (electricity_input * kKilowattToBtuPerHour);
    // Sum and convert back to BTU/hr
    double total_chemical_energy_input_mmbtu = total_chemical_energy_input;
    return (total_chemical_energy_input_mmbtu + electricity_heat); // BTU/hr
}

} // namespace energy_input_electric_arc_furnace
