
#pragma once
#include "physics/gas_composition.h"
/**
 * @ingroup air_water_cooling_using_flue_calculator
 * @file air_water_cooling_using_flue.h
 *
 * @copybrief air_water_cooling_using_flue
 */

/**
 * @ingroup air_water_cooling_using_flue_calculator
 * @namespace air_water_cooling_using_flue
 * @brief Air/water cooling using flue gas calculations for condensing heat exchangers.
 */
namespace air_water_cooling_using_flue {

/**
 * @ingroup air_water_cooling_using_flue_calculator
 * @struct AirWaterCoolingUsingFlueResults
 * @brief Results of the air/water cooling using flue calculation.
 * @details Contains all output values from the air/water cooling using flue calculation.
 */
struct AirWaterCoolingUsingFlueResults {
    double excess_air = 0;                   ///< Excess air fraction @unitb{\unitless}
    double flow_flue_gas = 0;                ///< Flue gas flow @unitb{\pound\per\hour}
    double specific_heat = 0;                ///< Specific heat @unitb{\btu\per\pound\degreeFahrenheit}
    double fraction_condensed = 0;           ///< Fraction of water vapor condensed @unitb{\unitless}
    double available_heat_fraction = 0;      ///< Fraction of heat available (sensible only) @unitb{\unitless}
    double total_available_heat_fraction = 0;///< Fraction of heat available (sensible + latent) @unitb{\unitless}
    double latent_heat_fraction = 0;         ///< Fraction of heat available due to latent heat @unitb{\unitless}
    double latent_heat_recovery = 0;         ///< Latent heat recovered @unitb{\mega\btu\per\hour}
    double sensible_heat_recovery = 0;       ///< Sensible heat recovered @unitb{\mega\btu\per\hour}
};

/**
 * @ingroup air_water_cooling_using_flue_calculator
 * @brief Calculates heat recovery using flue gas and condensing heat exchanger.
 * @details Uses gas composition and process parameters to estimate heat recovery, available heat, and latent heat effects.
 *
 * @param gas_compositions GasComposition object with fuel properties
 * @param heat_input Heat input @unitb{\mega\btu\per\hour}
 * @param temp_flue_gas_in Flue gas inlet temperature @unitb{\degreeFahrenheit}
 * @param temp_flue_gas_out Flue gas outlet temperature @unitb{\degreeFahrenheit}
 * @param temp_comb_air Combustion air temperature @unitb{\degreeFahrenheit}
 * @param fuel_temp Fuel temperature @unitb{\degreeFahrenheit}
 * @param perc_o2 Percent O2 in flue gas (fraction)
 * @param ambient_air_temp Ambient air temperature @unitb{\degreeFahrenheit} (default: 60)
 * @param moist_comb_air Moisture in combustion air (fraction, default: 0)
 * @return AirWaterCoolingUsingFlueResults struct with all calculated outputs.
 */
AirWaterCoolingUsingFlueResults airWaterCoolingUsingFlue(
    const gas_composition::GasComposition& gas_compositions,
    double heat_input,
    double temp_flue_gas_in,
    double temp_flue_gas_out,
    double temp_comb_air,
    double fuel_temp,
    double perc_o2,
    double ambient_air_temp = 60,
    double moist_comb_air = 0
);

} // namespace air_water_cooling_using_flue
