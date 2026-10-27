/** Stateless pump and fan calculations of the fraction of shaft power delivered to the fluid. */

/** Complete pump duty and shaft-power data; plain object requiring no delete(). */
export interface PumpMoverEfficiencyInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Liquid volumetric flow, units US gpm. */
    flowRate: number;
    /** Pump head in feet of the pumped fluid, units ft. */
    head: number;
    /** Power supplied at the pump shaft, units hp. */
    moverShaftPower: number;
}

/** Complete fan duty and shaft-power data; plain object requiring no delete(). */
export interface FanMoverEfficiencyInput {
    /** Gas volumetric flow, units cfm. */
    flowRate: number;
    /** Power supplied at the fan shaft, units hp. */
    moverShaftPower: number;
    /** Inlet gauge pressure, units inches of water column. */
    inletPressure: number;
    /** Outlet gauge pressure, units inches of water column. */
    outletPressure: number;
    /** Supplied fan compressibility correction, dimensionless. */
    compressibilityFactor: number;
    /** Velocity pressure subtracted from the pressure rise, units inches of water column. */
    velocityPressure: number;
}

/**
 * Calculates the fraction of pump shaft input delivered to the liquid.
 * Divides fluid power in kW by 0.746, then by shaft power in hp. All fields are required.
 * No validation, defaults or clamping are applied; above-one, signed and nonfinite results are retained.
 * @param input Complete duty and shaft-power data, with units documented per field; not modified.
 * @returns Mover efficiency, dimensionless fraction (0.75 means 75%), not percentage points.
 * The plain input and numeric result require no delete().
 */
export declare function calculatePumpMoverEfficiency(input: PumpMoverEfficiencyInput): number;

/**
 * Calculates the fraction of fan shaft input delivered to the gas.
 * Uses outlet minus inlet minus velocity pressure and the supplied compressibility correction.
 * Divides fluid power in kW by 0.746, then by shaft power in hp. All fields are required,
 * including velocityPressure. No validation, defaults or clamping are applied;
 * above-one, signed and nonfinite results are retained.
 * @param input Complete duty and shaft-power data, with units documented per field; not modified.
 * @returns Mover efficiency, dimensionless fraction (0.75 means 75%), not percentage points.
 * The plain input and numeric result require no delete().
 */
export declare function calculateFanMoverEfficiency(input: FanMoverEfficiencyInput): number;

/** Runtime functions contributed by the mover-efficiency binding. */
export type MoverEfficiencyModule = {
    calculatePumpMoverEfficiency: typeof calculatePumpMoverEfficiency;
    calculateFanMoverEfficiency: typeof calculateFanMoverEfficiency;
};
