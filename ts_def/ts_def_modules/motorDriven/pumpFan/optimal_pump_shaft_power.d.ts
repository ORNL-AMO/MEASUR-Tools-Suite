/** Stateless pump and fan shaft-power calculations at a supplied efficiency; no optimization is performed. */

/** Complete pump duty and supplied efficiency; plain object requiring no delete(). */
export interface OptimalPumpShaftPowerInput {
    /** Liquid volumetric flow, units US gpm. */
    flowRate: number;
    /** Pump head in feet of the pumped fluid, units ft. */
    head: number;
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Supplied pump efficiency, dimensionless fraction (0.80 means 80%), not percentage points. */
    pumpEfficiency: number;
}

/** Complete fan duty and supplied efficiency; plain object requiring no delete(). */
export interface OptimalFanShaftPowerInput {
    /** Gas volumetric flow, units cfm. */
    flowRate: number;
    /** Inlet gauge pressure, units inches of water column. */
    inletPressure: number;
    /** Outlet gauge pressure, units inches of water column. */
    outletPressure: number;
    /** Supplied fan compressibility correction, dimensionless. */
    compressibilityFactor: number;
    /** Supplied fan efficiency, dimensionless fraction (0.80 means 80%), not percentage points. */
    fanEfficiency: number;
    /** Velocity pressure subtracted from the pressure rise, units inches of water column. */
    velocityPressure: number;
}

/**
 * Calculates pump shaft input required at the supplied duty and efficiency.
 * Divides fluid power in kW by the efficiency fraction, then by 0.746 kW/hp. All fields are required.
 * No validation, defaults or clamping are applied; signed and nonfinite results are retained.
 * @param input Complete duty and efficiency data, with units documented per field; not modified.
 * @returns Required pump shaft power, units hp, excluding motor and drive losses.
 * The plain input and numeric result require no delete().
 */
export declare function calculateOptimalPumpShaftPower(input: OptimalPumpShaftPowerInput): number;

/**
 * Calculates fan shaft input required at the supplied duty and efficiency.
 * Uses outlet minus inlet minus velocity pressure and the supplied compressibility correction.
 * Divides fluid power in kW by the efficiency fraction, then by 0.746 kW/hp.
 * All fields are required, including velocityPressure. No validation, defaults or clamping are applied;
 * signed and nonfinite results are retained.
 * @param input Complete duty and efficiency data, with units documented per field; not modified.
 * @returns Required fan shaft power, units hp, excluding motor and drive losses.
 * The plain input and numeric result require no delete().
 */
export declare function calculateOptimalFanShaftPower(input: OptimalFanShaftPowerInput): number;

/** Runtime functions contributed by the optimal-shaft-power binding. */
export type OptimalPumpShaftPowerModule = {
    calculateOptimalPumpShaftPower: typeof calculateOptimalPumpShaftPower;
    calculateOptimalFanShaftPower: typeof calculateOptimalFanShaftPower;
};
