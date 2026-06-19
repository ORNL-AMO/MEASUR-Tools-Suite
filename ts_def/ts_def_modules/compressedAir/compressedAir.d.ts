import { DoubleVector } from "../binding/registered_vectors";

/**
 * Compressed Air Core Calculations
 *
 * Provides compressed air system capacity and velocity calculations based on
 * pipe size data, system pressure, and receiver volumes.
 */

/**
 * Pipe data for compressed air calculators.
 * @details Holds values by nominal pipe size. This type is used by air system
 *          capacity and air velocity calculations. Constructor inputs are pipe
 *          lengths, units ft. Stored values are context-specific: the
 *          AirSystemCapacity result contains pipe volumes, units ft3, while
 *          AirVelocity returns velocity by pipe size, units ft/s.
 */
export declare class PipeData {
    /**
     * @param oneHalf Nominal 1/2 in pipe length, units ft.
     * @param threeFourths Nominal 3/4 in pipe length, units ft.
     * @param one Nominal 1 in pipe length, units ft.
     * @param oneAndOneFourth Nominal 1-1/4 in pipe length, units ft.
     * @param oneAndOneHalf Nominal 1-1/2 in pipe length, units ft.
     * @param two Nominal 2 in pipe length, units ft.
     * @param twoAndOneHalf Nominal 2-1/2 in pipe length, units ft.
     * @param three Nominal 3 in pipe length, units ft.
     * @param threeAndOneHalf Nominal 3-1/2 in pipe length, units ft.
     * @param four Nominal 4 in pipe length, units ft.
     * @param five Nominal 5 in pipe length, units ft.
     * @param six Nominal 6 in pipe length, units ft.
     * @param eight Nominal 8 in pipe length, units ft.
     * @param ten Nominal 10 in pipe length, units ft.
     * @param twelve Nominal 12 in pipe length, units ft.
     * @param fourteen Nominal 14 in pipe length, units ft.
     * @param sixteen Nominal 16 in pipe length, units ft.
     * @param eighteen Nominal 18 in pipe length, units ft.
     * @param twenty Nominal 20 in pipe length, units ft.
     * @param twentyFour Nominal 24 in pipe length, units ft.
     */
    constructor(
        oneHalf: number,
        threeFourths: number,
        one: number,
        oneAndOneFourth: number,
        oneAndOneHalf: number,
        two: number,
        twoAndOneHalf: number,
        three: number,
        threeAndOneHalf: number,
        four: number,
        five: number,
        six: number,
        eight: number,
        ten: number,
        twelve: number,
        fourteen: number,
        sixteen: number,
        eighteen: number,
        twenty: number,
        twentyFour: number
    );

    /** Value for nominal 1/2 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    oneHalf: number;
    /** Value for nominal 3/4 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    threeFourths: number;
    /** Value for nominal 1 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    one: number;
    /** Value for nominal 1-1/4 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    oneAndOneFourth: number;
    /** Value for nominal 1-1/2 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    oneAndOneHalf: number;
    /** Value for nominal 2 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    two: number;
    /** Value for nominal 2-1/2 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    twoAndOneHalf: number;
    /** Value for nominal 3 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    three: number;
    /** Value for nominal 3-1/2 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    threeAndOneHalf: number;
    /** Value for nominal 4 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    four: number;
    /** Value for nominal 5 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    five: number;
    /** Value for nominal 6 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    six: number;
    /** Value for nominal 8 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    eight: number;
    /** Value for nominal 10 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    ten: number;
    /** Value for nominal 12 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    twelve: number;
    /** Value for nominal 14 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    fourteen: number;
    /** Value for nominal 16 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    sixteen: number;
    /** Value for nominal 18 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    eighteen: number;
    /** Value for nominal 20 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    twenty: number;
    /** Value for nominal 24 in pipe; units ft3 for capacity results or ft/s for velocity results. */
    twentyFour: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output object for air system capacity calculations.
 *
 * @property totalPipeVolume double, total pipe volume.
 * @property totalReceiverVolume double, total receiver volume.
 * @property totalCapacityOfCompressedAirSystem double, total compressed air system capacity.
 * @property receiverCapacities number[], receiver capacities.
 * @property pipeLengths {@link PipeData}, per-size pipe values.
 */
export declare class AirSystemCapacityOutput {
    /**
     * @param totalPipeVolume Total pipe volume, units ft3.
     * @param receiverCapacities Receiver capacities converted from gallons, units ft3.
     * @param totalReceiverVolume Total receiver volume, units ft3.
     * @param totalCapacityOfCompressedAirSystem Total compressed air system capacity, units ft3.
     * @param pipeLengths Per-size pipe volumes, units ft3.
     */
    constructor(
        totalPipeVolume: number,
        receiverCapacities: DoubleVector,
        totalReceiverVolume: number,
        totalCapacityOfCompressedAirSystem: number,
        pipeLengths: PipeData
    );

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

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates total compressed air system capacity from pipe and receiver data.
 */
export declare class AirSystemCapacity {
    /**
     * @param pipeLengths Pipe lengths by nominal pipe size, units ft.
     * @param receivers Receiver volumes, units gal.
     */
    constructor(pipeLengths: PipeData, receivers: DoubleVector);

    /**
     * @returns {@link AirSystemCapacityOutput} object containing total pipe volume, total receiver volume, total compressed air system capacity, and per-size pipe values.
    */
    calculate(): AirSystemCapacityOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates compressed air velocity through different piping sizes.
 */
export declare class AirVelocity {
    /**
     * @param airFlow double, volumetric flow rate in scfm.
     * @param pipePressure double, pipe pressure in psig.
     * @param atmosphericPressure double, atmospheric pressure in psia.
     */
    constructor(airFlow: number, pipePressure: number, atmosphericPressure: number);

    /**
     * @returns {@link PipeData} object containing air velocity values for different pipe sizes.
    */
    calculate(): PipeData;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type CompressedAirModule = {
    PipeData: typeof PipeData;
    AirSystemCapacity: typeof AirSystemCapacity;
    AirSystemCapacityOutput: typeof AirSystemCapacityOutput;
    AirVelocity: typeof AirVelocity;
};
