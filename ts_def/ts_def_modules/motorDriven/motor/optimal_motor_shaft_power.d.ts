/** Stateless motor shaft output required to supply a pump/fan shaft duty. */
import type { Drive } from "./motorEnum";

/** Complete required drive data; a plain object requiring no delete(). */
export interface OptimalMotorShaftPowerInput {
    /** Required mechanical input at the pump/fan shaft, units hp. */
    moverShaftPower: number;
    /** Existing runtime Drive enum selecting direct, belt or specified drive efficiency. */
    drive: Drive;
    /** Supplied drive efficiency, dimensionless fraction (0.95 means 95%); used only for SPECIFIED. */
    specifiedEfficiency: number;
}

/** Required motor shaft output and drive efficiency; a plain object requiring no delete(). */
export interface OptimalMotorShaftPowerResult {
    /** Mechanical motor shaft output required before the drive, units hp. */
    motorShaftPower: number;
    /** Fraction of motor shaft output delivered to the mover, dimensionless. */
    driveEfficiency: number;
}

/**
 * Calculates motor shaft output required to supply a pump or fan through the selected drive.
 * All fields are required. Direct drive has efficiency 1; SPECIFIED divides power by the supplied
 * fraction; belts add retained empirical losses evaluated at mover power. No validation, defaults
 * or clamping are applied; signed/nonfinite arithmetic is retained. Belt efficiency is finite at
 * zero mover power. This performs no equipment optimization and is not an exact inverse of the
 * forward calculateMoverShaftPower belt model, which uses a different empirical curve.
 * @param input Complete drive data, with units documented per field; not modified.
 * @returns Required motor shaft output in hp and drive efficiency as a dimensionless fraction.
 * Plain input/result objects require no delete().
 */
export declare function calculateOptimalMotorShaftPower(input: OptimalMotorShaftPowerInput): OptimalMotorShaftPowerResult;

/** Runtime function contributed by the optimal motor shaft power binding. */
export type OptimalMotorShaftPowerModule = {
    calculateOptimalMotorShaftPower: typeof calculateOptimalMotorShaftPower;
};
