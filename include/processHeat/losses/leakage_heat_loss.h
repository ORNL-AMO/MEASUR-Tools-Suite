#pragma once


/**
 * @ingroup leakage_heat_loss_calculator
 * @file leakage_heat_loss.h
 * @authors Gina Accawi
 *
 * @copybrief leakage_heat_loss
 */

/**
 * @ingroup leakage_heat_loss_calculator
 * @namespace leakage_heat_loss
 * @brief Calculator for total energy loss for gas leakages.
 * @details Computes the heat loss caused by gases leaving the furnace via openings other than the flue. This calculator should only be used if the furnace is operating at a positive pressure.
 */
namespace leakage_heat_loss {

/**
 * @ingroup leakage_heat_loss_calculator
 * @brief Calculates the total heat loss from hot gas leakage.
 * @details This function computes the heat loss caused by gases leaking from the furnace. The calculation uses:
 * @param[in] draft_pressure Furnace draft pressure @unitb{\inchWaterColumn}
 * @param[in] opening_area Opening area @unitb{\foot\squared}
 * @param[in] leakage_gas_temperature Temperature of leaking gases @unitb{\degreeFahrenheit}
 * @param[in] ambient_temperature Ambient temperature @unitb{\degreeFahrenheit}
 * @param[in] coefficient_discharge Coefficient of discharge or flow coefficient @unitb{\unitless}
 * @param[in] specific_gravity Specific gravity @unitb{\unitless}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu\per\hour}
 */
double totalHeatLoss(double draft_pressure, double opening_area, double leakage_gas_temperature, double ambient_temperature,
                     double coefficient_discharge, double specific_gravity, double correction_factor);

} // namespace leakage_heat_loss
