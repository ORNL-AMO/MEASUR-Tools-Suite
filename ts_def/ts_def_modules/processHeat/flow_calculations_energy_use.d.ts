/**
 * Flow Calculations Energy Use Calculator.
 *
 * Calculates flow rate, heat input, and total flow for a fuel-fired furnace
 * using standard orifice meter equations for combustion gas flow measurement.
 * All parameters must be provided in U.S. customary units.
 */

/**
 * Results of the flow calculations energy use.
 *
 * @property flowPerHour Flow rate, units SCF/hr
 * @property heatInput Heat input, units MMBtu
 * @property totalFlow Total flow, units SCF
 */
export interface FlowCalculationsEnergyUseResults {
    /** Flow rate, units SCF/hr */
    flowPerHour: number;
    /** Heat input, units MMBtu */
    heatInput: number;
    /** Total flow, units SCF */
    totalFlow: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates flow rate, heat input, and total flow for a fuel-fired furnace
 * using standard orifice meter equations for combustion gas flow measurement.
 *
 * @param specific_gravity Specific gravity of gas, unitless
 * @param orifice_diameter Orifice diameter, units in
 * @param inside_pipe_diameter Inside pipe diameter, units in
 * @param discharge_coefficient Discharge coefficient, unitless
 * @param gas_heating_value Gas heating value, units BTU/scf
 * @param gas_temperature Gas temperature, units degF
 * @param gas_pressure Gas pressure, units psig
 * @param orifice_pressure_drop Orifice pressure drop, units in. W.C. (inches water column)
 * @param operating_time Operating time, units hr
 * @returns {@link FlowCalculationsEnergyUseResults} with flow rate, heat input, and total flow
 */
export function flowCalculationsEnergyUse(
    specific_gravity: number,
    orifice_diameter: number,
    inside_pipe_diameter: number,
    discharge_coefficient: number,
    gas_heating_value: number,
    gas_temperature: number,
    gas_pressure: number,
    orifice_pressure_drop: number,
    operating_time: number
): FlowCalculationsEnergyUseResults;

export type FlowCalculationsEnergyUseModule = {
    FlowCalculationsEnergyUseResults: FlowCalculationsEnergyUseResults;
    flowCalculationsEnergyUse: typeof flowCalculationsEnergyUse;
};
