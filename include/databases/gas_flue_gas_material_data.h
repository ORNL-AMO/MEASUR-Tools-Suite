#pragma once
/**
 * @ingroup gas_flue_gas_material_data_database
 * @file gas_flue_gas_material_data.h
 * @authors Mark Root, Gina Accawi
 * @brief Defines default flue gas material data for process heat calculations.
 */

#include <string>
#include <vector>

/**
 * @ingroup gas_flue_gas_material_data_database
 * @namespace gas_flue_gas_material_data
 * @brief Contains default flue gas material data and accessors.
 */
namespace gas_flue_gas_material_data {

/**
 * @struct GasFlueGasMaterial
 * @brief Struct to hold default flue gas material data.
 * @param substance Name of the flue gas material
 * @param ch4 Methane (CH4) percent by volume
 * @param c2h6 Ethane (C2H6) percent by volume
 * @param n2 Nitrogen (N2) percent by volume
 * @param h2 Hydrogen (H2) percent by volume
 * @param c3h8 Propane (C3H8) percent by volume
 * @param c4h10_cnh2n Butane/Paraffins (C4H10/CnH2n) percent by volume
 * @param h2o Water vapor (H2O) percent by volume
 * @param co Carbon monoxide (CO) percent by volume
 * @param co2 Carbon dioxide (CO2) percent by volume
 * @param so2 Sulfur dioxide (SO2) percent by volume
 * @param o2 Oxygen (O2) percent by volume
 * @param heating_value Heating value (Btu/SCF)
 * @param heating_value_volume Heating value (Btu/ft3)
 * @param specific_gravity Specific gravity (dimensionless)
 */
struct GasFlueGasMaterial {
  std::string substance;
  double ch4;
  double c2h6;
  double n2;
  double h2;
  double c3h8;
  double c4h10_cnh2n;
  double h2o;
  double co;
  double co2;
  double so2;
  double o2;
  double heating_value;
  double heating_value_volume;
  double specific_gravity;
};

/**
 * @brief Returns a vector of default flue gas materials.
 * @return std::vector<GasFlueGasMaterial> Default flue gas materials
 */
inline std::vector<GasFlueGasMaterial> get_default_gas_flue_gas_materials() {
  return {
    {"Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1, 22030.67089880065, 1032.445, 0.6571206283343215},
    {"Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6, 19185.932389233436, 610.52, 0.44638781861292243},
    {"Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0, 1080.6848266529887, 83.605, 1.0870540901007706},
    {"Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 61095.0, 325, 0.0746887967}
  };
}

} // namespace gas_flue_gas_material_data
