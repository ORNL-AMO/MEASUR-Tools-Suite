/** Stateless calculation of pump/fan shaft input after motor-drive losses. */
import type { Drive } from "../motor/motorEnum";

/** Complete required drive data; a plain object requiring no delete(). */
export interface MoverShaftPowerInput {
    /** Mechanical motor shaft output, units hp. */
    motorShaftPower: number;
    /** Existing runtime Drive enum selecting direct, belt or specified drive efficiency. */
    drive: Drive;
    /** Supplied drive efficiency, dimensionless fraction (0.95 means 95%); used only for SPECIFIED. */
    specifiedEfficiency: number;
}

/** Delivered shaft power and drive efficiency; a plain object requiring no delete(). */
export interface MoverShaftPowerResult {
    /** Mechanical input at the pump/fan shaft, units hp. */
    moverShaftPower: number;
    /** Fraction of motor shaft output delivered through the drive, dimensionless. */
    driveEfficiency: number;
}

/**
 * Calculates pump/fan shaft input from motor shaft output and drive losses.
 * All fields are required. Direct drive has efficiency 1; SPECIFIED uses the supplied fraction;
 * belt drives use the retained power-dependent loss curves. No validation, defaults or clamping
 * are applied; signed and nonfinite results are retained, including NaN belt efficiency at zero power.
 * @param input Complete drive data, with units documented per field; not modified.
 * @returns Delivered shaft power in hp and drive efficiency as a dimensionless fraction.
 * Plain input/result objects require no delete().
 */
export declare function calculateMoverShaftPower(input: MoverShaftPowerInput): MoverShaftPowerResult;

/** Runtime function contributed by the mover-shaft-power binding. */
export type MoverShaftPowerModule = {
    calculateMoverShaftPower: typeof calculateMoverShaftPower;
};
