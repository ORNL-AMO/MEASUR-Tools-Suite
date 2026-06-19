import type { PipeData } from "./pipe_data";

/**
 * Compressed Air Velocity
 *
 * Calculates compressed air velocity through standard nominal pipe sizes.
 */

/**
 * Input object for air velocity calculations.
 */
export interface AirVelocityInput {
    /** Volumetric free-air flow rate, units scfm. */
    airFlow: number;
    /** Pipe gauge pressure, units psig. */
    pipePressure: number;
    /** Atmospheric absolute pressure, units psia. */
    atmosphericPressure: number;
}

/**
 * Calculates compressed air velocity through different piping sizes.
 * @param input Airflow and pressure input data.
 * @returns `PipeData` containing air velocity values by nominal pipe size, units ft/s.
 */
export declare function calculateAirVelocity(input: AirVelocityInput): PipeData;

export type AirVelocityModule = {
    calculateAirVelocity: typeof calculateAirVelocity;
};
