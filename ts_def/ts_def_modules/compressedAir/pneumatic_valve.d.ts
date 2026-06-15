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
    inletPressure: number;
    outletPressure: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result of the flow rate calculation (Cv = 1).
 *
 * @property flowRate double, air flow rate through a valve with Cv = 1 in scfm.
 */
export interface PneumaticValveFlowRateResult {
    flowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Input parameters for the valve flow coefficient (Cv) calculation.
 *
 * @property inletPressure double, inlet (upstream) absolute pressure in psia.
 * @property outletPressure double, outlet (downstream) absolute pressure in psia.
 * @property flowRate double, measured or required air flow rate in scfm.
 */
export interface PneumaticValveCvInput {
    inletPressure: number;
    outletPressure: number;
    flowRate: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result of the valve flow coefficient (Cv) calculation.
 *
 * @property flowCoefficient double, dimensionless valve flow coefficient (Cv).
 */
export interface PneumaticValveCvResult {
    flowCoefficient: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
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
    PneumaticValveFlowRateInput: PneumaticValveFlowRateInput;
    PneumaticValveFlowRateResult: PneumaticValveFlowRateResult;
    PneumaticValveCvInput: PneumaticValveCvInput;
    PneumaticValveCvResult: PneumaticValveCvResult;
};