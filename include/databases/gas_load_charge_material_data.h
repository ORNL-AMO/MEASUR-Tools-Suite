#pragma once
#include <string>
#include <vector>
/**
 * @ingroup gas_load_charge_material_data_database
 * @file gas_load_charge_material_data.h
 * @authors Mark Root
 *
 */
/**
 * @ingroup gas_load_charge_material_data_database
 * @namespace gas_load_charge_material_data
 * @copybrief gas_load_charge_material_data_database
 */
namespace gas_load_charge_material_data {

/**
 * @struct GasLoadChargeMaterial
 * @brief Struct to hold default gas load/charge material data
 */
struct GasLoadChargeMaterial {
    std::string substance; ///< Name of substance
    double specific_heat_vapor; ///< Specific Heat of Vapor in Btu/(lb*°F)
};

/**
 * @brief Returns a vector of default gas load/charge materials.
 * @return std::vector<GasLoadChargeMaterial> Default materials
 */
inline std::vector<GasLoadChargeMaterial> get_default_gas_load_charge_materials() {
    return {
        {"Water vapor - Near Atm. Pressure", 0.47},
        {"Steam - 50 PSIG, 400 degrees F", 0.4901},
        {"Steam - 150 PSIG, 500 degrees F", 0.5099},
        {"Steam - 600 PSIG, 700 degrees F", 0.5899},
        {"Air - Low Pressure", 0.245},
        {"Nitrogen - Low Pressure", 0.2501},
        {"Oxygen - Low Pressure", 0.23},
        {"Carbon Dioxide - Low Pressure", 0.24},
        {"Carbon Monoxide - Low Pressure", 0.2501},
        {"Hydrogen - Low Pressure", 3.45}
    };
}

} // namespace gas_load_charge_material_data
