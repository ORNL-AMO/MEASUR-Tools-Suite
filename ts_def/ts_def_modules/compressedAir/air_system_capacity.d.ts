import type { DoubleVector } from "../binding/registered_vectors";
import type { PipeData } from "./pipe_data";

/**
 * Compressed Air System Capacity
 *
 * Calculates total compressed air storage from pipe volume and receiver volume.
 */

/**
 * Input object for air system capacity calculations.
 */
export interface AirSystemCapacityInput {
    /** Pipe data constructed from pipe lengths; stored per-size pipe volumes, units ft3. */
    pipeLengths: PipeData;
    /** Receiver volumes, units gal. */
    receivers: DoubleVector;
}

/**
 * Output object for air system capacity calculations.
 *
 * `receiverCapacities` and `pipeLengths` are embind runtime objects returned
 * inside the value object; clean them up with `delete()` when finished.
 */
export interface AirSystemCapacityOutput {
    /** Total pipe volume, units ft3. */
    totalPipeVolume: number;
    /** Total receiver volume, units ft3. */
    totalReceiverVolume: number;
    /** Total compressed air system capacity, units ft3. */
    totalCapacityOfCompressedAirSystem: number;
    /** Receiver capacities converted from gallons, units ft3. */
    receiverCapacities: DoubleVector;
    /** Per-size pipe volumes, units ft3. */
    pipeLengths: PipeData;
}

/**
 * Calculates total compressed air system capacity from pipe and receiver data.
 * @param input Pipe and receiver input data.
 * @returns Total capacity output with pipe volume, receiver volume, and total system capacity, units ft3.
 */
export declare function calculateAirSystemCapacity(input: AirSystemCapacityInput): AirSystemCapacityOutput;

export type AirSystemCapacityModule = {
    calculateAirSystemCapacity: typeof calculateAirSystemCapacity;
};
