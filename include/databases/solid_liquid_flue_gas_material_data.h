#pragma once
/**
 * @ingroup solid_liquid_flue_gas_material_data_database
 * @file solid_liquid_flue_gas_material_data.h
 * @brief Defines default solid/liquid flue gas material data for process heat calculations.
 */

#include <string>
#include <vector>

/**
 * @namespace solid_liquid_flue_gas_material_data
 * @brief Contains default solid/liquid flue gas material data.
 */
namespace solid_liquid_flue_gas_material_data {
/**
 * @struct SolidLiquidFlueGasMaterial
 * @brief Struct to hold default solid/liquid flue gas material data.
 */
struct SolidLiquidFlueGasMaterial {
    std::string substance; ///< Name of the material
    double      carbon;    ///< Carbon percent by mass
    double      hydrogen;  ///< Hydrogen percent by mass
    double      sulfur;    ///< Sulfur percent by mass
    double      oxygen;    ///< Oxygen percent by mass
    double      nitrogen;  ///< Nitrogen percent by mass
    double      moisture;  ///< Moisture percent by mass
    double      inert_ash;       ///< Ash percent by mass
};

/**
 * @brief Returns a vector of default solid/liquid flue gas materials.
 * @return std::vector<SolidLiquidFlueGasMaterial> Default solid/liquid flue gas materials
 */
inline std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials() {
    return {{"Typical Bituminous Coal - US", 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5},
            {"Typical Anthracite - US", 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8},
            {"Typical Lignite - US", 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8},
            {"Fuel Oil #2", 86.6, 12.8, 0.5, 0, 0, 0, 0.1},
            {"Fuel Oil #6", 87.1, 10.6, 2.1, 0.2, 0, 0, 0},
            {"Typical Wood", 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2}};
}
} // namespace solid_liquid_flue_gas_material_data
