/**
 * Solid/Liquid Fuel Flue Gas Material calculations.
 *
 * Calculates total heat loss, excess air, flue gas O2, heating value, and
 * stoichiometric air for solid or liquid fuel combustion, based on the fuel
 * elemental composition (percent by mass).
 *
 */

/**
 * Calculate total heat loss for solid/liquid fuel flue gas.
 *
 * @param flue_gas_temperature Flue gas temperature, units degF
 * @param excess_air Excess air as fraction (e.g. 0.09 for 9%), unitless
 * @param combustion_air_temperature Combustion air temperature, units degF
 * @param fuel_temperature Fuel temperature, units degF
 * @param moisture_in_air_combustion Moisture in combustion air, units %
 * @param ash_discharge_temperature Ash discharge temperature, units degF
 * @param unburned_carbon_in_ash Unburned carbon in ash as fraction, unitless
 * @param carbon Percent carbon in fuel, units %
 * @param hydrogen Percent hydrogen in fuel, units %
 * @param sulphur Percent sulphur in fuel, units %
 * @param inert_ash Percent inert ash in fuel, units %
 * @param o2 Percent oxygen in fuel, units %
 * @param moisture Percent moisture in fuel, units %
 * @param nitrogen Percent nitrogen in fuel, units %
 * @param ambient_air_temp_f Ambient air temperature, units degF (default: 60)
 * @returns Total heat loss, units BTU/hr
 */
export function solidLiquidFlueGasMaterialTotalHeatLoss(
    flue_gas_temperature: number,
    excess_air: number,
    combustion_air_temperature: number,
    fuel_temperature: number,
    moisture_in_air_combustion: number,
    ash_discharge_temperature: number,
    unburned_carbon_in_ash: number,
    carbon: number,
    hydrogen: number,
    sulphur: number,
    inert_ash: number,
    o2: number,
    moisture: number,
    nitrogen: number,
    ambient_air_temp_f?: number
): number;

/**
 * Calculate excess air percentage from flue gas O2 using an
 * iterative algorithm.
 *
 * @param flue_gas_o2 O2 percentage in flue gas, units %
 * @param carbon Percent carbon in fuel, units %
 * @param hydrogen Percent hydrogen in fuel, units %
 * @param sulphur Percent sulphur in fuel, units %
 * @param inert_ash Percent inert ash in fuel, units %
 * @param o2 Percent oxygen in fuel, units %
 * @param moisture Percent moisture in fuel, units %
 * @param nitrogen Percent nitrogen in fuel, units %
 * @param moisture_in_air_combustion Percent moisture in combustion air, units %
 * @returns Calculated excess air, units %
 */
export function calculateExcessAirFromFlueGasO2(
    flue_gas_o2: number,
    carbon: number,
    hydrogen: number,
    sulphur: number,
    inert_ash: number,
    o2: number,
    moisture: number,
    nitrogen: number,
    moisture_in_air_combustion: number
): number;

/**
 * Calculate flue gas O2 fraction from excess air and fuel composition.
 *
 * @param excess_air Excess air as fraction (e.g. 0.09 for 9%), unitless
 * @param carbon Percent carbon in fuel, units %
 * @param hydrogen Percent hydrogen in fuel, units %
 * @param sulphur Percent sulphur in fuel, units %
 * @param inert_ash Percent inert ash in fuel, units %
 * @param o2 Percent oxygen in fuel, units %
 * @param moisture Percent moisture in fuel, units %
 * @param nitrogen Percent nitrogen in fuel, units %
 * @param moisture_in_air_combustion Percent moisture in combustion air, units %
 * @returns Calculated O2 fraction in flue gas, unitless
 */
export function calculateFlueGasO2(
    excess_air: number,
    carbon: number,
    hydrogen: number,
    sulphur: number,
    inert_ash: number,
    o2: number,
    moisture: number,
    nitrogen: number,
    moisture_in_air_combustion: number
): number;

/**
 * Calculate fuel heating value from elemental composition.
 *
 * @param carbon Percent carbon in fuel, units %
 * @param hydrogen Percent hydrogen in fuel, units %
 * @param sulphur Percent sulphur in fuel, units %
 * @param inert_ash Percent inert ash in fuel, units %
 * @param o2 Percent oxygen in fuel, units %
 * @param moisture Percent moisture in fuel, units %
 * @param nitrogen Percent nitrogen in fuel, units %
 * @returns Heating value of the fuel, units BTU/lb
 */
export function calculateHeatingValueFuel(
    carbon: number,
    hydrogen: number,
    sulphur: number,
    inert_ash: number,
    o2: number,
    moisture: number,
    nitrogen: number
): number;

/**
 * Calculate stoichiometric air required for complete combustion of the
 * given fuel composition (percent by mass).
 *
 * @param carbon Percent carbon in fuel, units %
 * @param hydrogen Percent hydrogen in fuel, units %
 * @param sulphur Percent sulphur in fuel, units %
 * @param inert_ash Percent inert ash in fuel, units %
 * @param o2 Percent oxygen in fuel, units %
 * @param moisture Percent moisture in fuel, units %
 * @param nitrogen Percent nitrogen in fuel, units %
 * @returns Stoichiometric air required, units lb air/lb fuel
 */
export function calculateStoichiometricAir(
    carbon: number,
    hydrogen: number,
    sulphur: number,
    inert_ash: number,
    o2: number,
    moisture: number,
    nitrogen: number
): number;

export type SolidLiquidFlueGasMaterialModule = {
    solidLiquidFlueGasMaterialTotalHeatLoss: typeof solidLiquidFlueGasMaterialTotalHeatLoss;
    calculateExcessAirFromFlueGasO2: typeof calculateExcessAirFromFlueGasO2;
    calculateFlueGasO2: typeof calculateFlueGasO2;
    calculateHeatingValueFuel: typeof calculateHeatingValueFuel;
    calculateStoichiometricAir: typeof calculateStoichiometricAir;
};
