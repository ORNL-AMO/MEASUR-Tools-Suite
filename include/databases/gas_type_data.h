
#pragma once
#include <string>
#include <vector>

/**
 * @namespace gas_type_data
 * @brief Contains default data for atmospheric gas types used in atmosphere heat loss calculations.
 */
namespace gas_type_data {

/**
 * @struct GasType
 * @brief Struct to hold default gas type data
 * @param gas_description Description of the gas type
 * @param specific_heat Specific heat in Btu/(scf*°F)
 */
struct GasType {
    std::string gas_description;
    double      specific_heat;
};

/**
 * @brief Returns a vector of default gas types.
 * @return std::vector<GasType> Default gas types
 */
inline std::vector<GasType> get_default_gas_types() {
    return {
        {"Nitrogen", 0.0185},
        {"Hydrogen", 0.0182},
        {"Exothermic Gas", 0.0185},
        {"Endothermic Gas", 0.0185},
        {"Air", 0.0184},
        {"Water Vapor", 0.0212}
    };
}

} // namespace gas_type_data
