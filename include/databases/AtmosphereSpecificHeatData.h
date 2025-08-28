#pragma once

#include "default_data.h"

class Atmosphere;

std::vector<Atmosphere> DefaultData::get_default_atmosphere_specific_heat() {
    return {
        {"Nitrogen", 0.0185},        {"Hydrogen", 0.0182}, {"Exothermic Gas", 0.0185},
        {"Endothermic Gas", 0.0185}, {"Air", 0.0184},      {"Water Vapor", 0.0212},
    };
}
