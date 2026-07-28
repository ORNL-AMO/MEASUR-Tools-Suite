/**
 * Pneumatic Valve Calculations
 *
 * Calculates flow rate for unit Cv valves and required valve flow coefficient
 * (Cv) from pressure and flow conditions.
 */

/**
 * Input parameters for the flow rate calculation (Cv = 1).
 *
 * @property inletPressure double, inlet (upstream) absolute pressure in psia.
 * @property outletPressure double, outlet (downstream) absolute pressure in psia.
 */
export interface PneumaticValveFlowRateInput {
    /** inlet (upstream) absolute pressure units psia. */
    inletPressure: number;
    /** outlet (downstream) absolute pressure units psia. */
    outletPressure: number;
}

/**
 * Result of the flow rate calculation (Cv = 1).
 *
 * @property flowRate double, air flow rate through a valve with Cv = 1 in scfm.
 */
export interface PneumaticValveFlowRateResult {
    /** air flow rate through a valve with Cv = 1 units scfm. */
    flowRate: number;
}

/**
 * Input parameters for the valve flow coefficient (Cv) calculation.
 *
 * @property inletPressure double, inlet (upstream) absolute pressure in psia.
 * @property outletPressure double, outlet (downstream) absolute pressure in psia.
 * @property flowRate double, measured or required air flow rate in scfm.
 */
export interface PneumaticValveCvInput {
    /** inlet (upstream) absolute pressure units psia. */
    inletPressure: number;
    /** outlet (downstream) absolute pressure units psia. */
    outletPressure: number;
    /** measured or required air flow rate units scfm. */
    flowRate: number;
}

/**
 * Result of the valve flow coefficient (Cv) calculation.
 *
 * @property flowCoefficient double, dimensionless valve flow coefficient (Cv).
 */
export interface PneumaticValveCvResult {
    /** dimensionless valve flow coefficient (Cv). */
    flowCoefficient: number;
}

/**
 * Calculates the air flow rate through a pneumatic valve with unit flow coefficient (Cv = 1).
 * @param input {@link PneumaticValveFlowRateInput}
 * @returns {@link PneumaticValveFlowRateResult} containing `flowRate` [scfm].
 */
export function calculatePneumaticValveFlowRate(
    input: PneumaticValveFlowRateInput
): PneumaticValveFlowRateResult;

/**
 * Calculates the valve flow coefficient (Cv) for a pneumatic valve.
 * @param input {@link PneumaticValveCvInput}
 * @returns {@link PneumaticValveCvResult} containing `flowCoefficient`.
 */
export function calculatePneumaticValveCv(
    input: PneumaticValveCvInput
): PneumaticValveCvResult;

export type PneumaticValveModule = {
    calculatePneumaticValveFlowRate: typeof calculatePneumaticValveFlowRate;
    calculatePneumaticValveCv: typeof calculatePneumaticValveCv;
};
