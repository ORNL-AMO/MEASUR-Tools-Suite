/** Stateless pump and fan calculations of power delivered to the fluid, in kW. */

/** Complete pump hydraulic-duty data; plain object requiring no delete(). */
export interface PumpFluidPowerInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Liquid volumetric flow, units US gpm. */
    flowRate: number;
    /** Pump head in feet of the pumped fluid, units ft. */
    head: number;
}

/** Complete fan operating-duty data; plain object requiring no delete(). */
export interface FanFluidPowerInput {
    /** Gas volumetric flow, units cfm. */
    flowRate: number;
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
 * Calculates power delivered to the liquid, excluding pump, drive and motor losses.
 * Retains the 3961.38 divisor and 0.746 hp-to-kW conversion. All fields are required.
 * No validation, defaults or clamping are applied; signed and nonfinite results are retained.
 * @param input Complete hydraulic-duty data, with units documented per field; not modified.
 * @returns Fluid power, units kW. The plain input and numeric result require no delete().
 */
export declare function calculatePumpFluidPower(input: PumpFluidPowerInput): number;

/**
 * Calculates power delivered to the gas, excluding fan, drive and motor losses.
 * Uses outlet minus inlet minus velocity pressure, the supplied compressibility correction,
 * the 6362 divisor and 0.746 hp-to-kW conversion. All five fields are required, including
 * velocityPressure. No validation, defaults or clamping are applied; signed and nonfinite
 * results are retained.
 * @param input Complete fan-duty data, with units documented per field; not modified.
 * @returns Fluid power, units kW. The plain input and numeric result require no delete().
 */
export declare function calculateFanFluidPower(input: FanFluidPowerInput): number;

/** Runtime functions contributed by the fluid-power binding. */
export type FluidPowerModule = {
    calculatePumpFluidPower: typeof calculatePumpFluidPower;
    calculateFanFluidPower: typeof calculateFanFluidPower;
};
