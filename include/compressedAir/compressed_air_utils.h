#pragma once

namespace compressed_air_utils {

/**
 * @struct CompressorElectricityData
 * @brief Compressor electricity parameters used when the electricity utility type is selected.
 * @details The compressor specific power characterizes the electrical power required to sustain
 * one standard cubic foot per minute of compressed air flow. The control adjustment factor
 * accounts for part-load or variable-speed control efficiency and is expressed as a percentage
 * (0–100); it is divided by 100 and multiplied by the specific power before converting
 * consumption to electrical energy use.
 */
struct CompressorElectricityData {
    double compressor_control_adjustment = 0.0; ///< Compressor control adjustment factor @unitb{\percent}
    double compressor_specific_power     = 0.0; ///< Electrical power per unit flow rate @unitb{\kilo\watt\per(\cubic\foot\per\minute)}
};

} // namespace compressed_air_utils
