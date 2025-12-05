#pragma once

/**
 * @ingroup slag_other_material_heat_loss_calculator
 * @file slag_other_material_heat_loss.h
 * @authors Gina Accawi, Mark Root
 *
 * @copybrief slag_other_material_heat_loss
 */

/**
 * @ingroup slag_other_material_heat_loss_calculator
 * @namespace slag_other_material_heat_loss
 * @copybrief slag_other_material_heat_loss_calculator
 */
namespace slag_other_material_heat_loss {

/**
 * @ingroup slag_other_material_heat_loss_calculator
 * @brief Calculates the total heat required for slag or other material losses.
 * @details This function computes the heat loss caused by heating slag or other combustion byproducts within the
 * furnace. Assumes majority of slag is silicon and specific heat does not change with temperature. For glass structures
 * in slag, output may change significantly.
 * @param[in] weight Weight discharged @unitb{\pound}
 * @param[in] inlet_temperature Inlet temperature of charged materials @unitb{\degreeFahrenheit}
 * @param[in] outlet_temperature Outlet temperature @unitb{\degreeFahrenheit}
 * @param[in] specific_heat Specific heat of material @unitb{\btu\per\pound\degreeFahrenheit}
 * @param[in] correction_factor Correction factor @unitb{\unitless}
 * @return Total heat loss @unitb{\btu}
 * @see
 * - slag_other_material_heat_loss_formula
 */
double totalHeatLoss(double weight, double inlet_temperature, double outlet_temperature, double specific_heat,
                     double correction_factor);

} // namespace slag_other_material_heat_loss
