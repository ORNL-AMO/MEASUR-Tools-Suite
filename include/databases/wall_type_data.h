
#pragma once
#include <string>
#include <vector>

/**
 * @namespace wall_type_data
 * @brief Contains default data for wall types used in wall heat loss calculations.
 */
namespace wall_type_data {

/**
 * @struct WallType
 * @brief Struct to hold default wall type data
 * @param wall_description Description of the wall type
 * @param shape_factor Shape factor associated with the wall type (unitless)
 */
struct WallType {
    std::string wall_description;
    double      shape_factor;
};

/**
 * @brief Returns a vector of default wall types.
 * @return std::vector<WallType> Default wall types
 */
inline std::vector<WallType> get_default_wall_types() {
    return {
        {"Horizontal cylinders", 1.016},
        {"Longer vertical cylinders", 1.235},
        {"Vertical plates", 1.394},
        {"Horizontal plate facing up, warmer than air", 1.79},
        {"Horizontal plate facing down, warmer than air", 0.89},
        {"Horizontal plate facing up, cooler than air", 0.89},
        {"Horizontal plate facing down, cooler than air", 1.79}
    };
}

} // namespace wall_type_data
