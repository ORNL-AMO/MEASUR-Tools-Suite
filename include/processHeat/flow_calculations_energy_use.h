#pragma once

/**
 * @file flow_calculations_energy_use.h
 * @ingroup flow_calculations_energy_use_calculator
 * 
 * @copybrief flow_calculations_energy_use
 */


/** 
 * @ingroup flow_calculations_energy_use_calculator
 * @namespace flow_calculations_energy_use
 * @brief Flow calculations for energy use in fuel-fired furnaces.
 * 
 */
 
namespace flow_calculations_energy_use {

/**
 * @ingroup flow_calculations_energy_use_calculator
 * @struct FlowCalculationsEnergyUseResults
 * @brief Results of the flow calculations energy use.
 * @details Contains output values for flow rate, heat input, and total flow.
 */
struct FlowCalculationsEnergyUseResults {
    double flow_per_hour = 0; ///< Flow rate @unitb{SCF/hr}
    double heat_input    = 0; ///< Heat input @unitb{MMBtu}
    double total_flow    = 0; ///< Total flow @unitb{SCF}
};

/**
 * @ingroup flow_calculations_energy_use_calculator
 * @brief Calculates flow rate, heat input, and total flow for a fuel-fired furnace using orifice flow equations.
 * @details Implements standard orifice meter equations for combustion gas flow measurement. All parameters must be provided in U.S. customary units.
 *
 * @param[in] specific_gravity Specific gravity of gas (unitless)
 * @param[in] orifice_diameter Orifice diameter @unitb{in}
 * @param[in] inside_pipe_diameter Inside pipe diameter @unitb{in}
 * @param[in] discharge_coefficient Discharge coefficient (unitless)
 * @param[in] gas_heating_value Gas heating value @unitb{Btu/scf}
 * @param[in] gas_temperature Gas temperature @unitb{\degreeFahrenheit}
 * @param[in] gas_pressure Gas pressure @unitb{psig}
 * @param[in] orifice_pressure_drop Orifice pressure drop @unitb{in. W.C.}
 * @param[in] operating_time Operating time @unitb{hr}
 * @return FlowCalculationsEnergyUseResults struct with flow rate, heat input, and total flow.
 */
FlowCalculationsEnergyUseResults flowCalculationsEnergyUse(
    double specific_gravity,
    double orifice_diameter,
    double inside_pipe_diameter,
    double discharge_coefficient,
    double gas_heating_value,
    double gas_temperature,
    double gas_pressure,
    double orifice_pressure_drop,
    double operating_time
);

} // namespace flow_calculations_energy_use