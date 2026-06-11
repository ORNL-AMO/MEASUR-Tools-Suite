/**
 * Pipe data for compressed air calculators.
 * @details Holds values by nominal pipe size. This type is used by air system
 *          capacity and air velocity calculations.
 */
export declare class PipeData {
    /**
     * @param oneHalf double, nominal 1/2 in pipe value.
     * @param threeFourths double, nominal 3/4 in pipe value.
     * @param one double, nominal 1 in pipe value.
     * @param oneAndOneFourth double, nominal 1-1/4 in pipe value.
     * @param oneAndOneHalf double, nominal 1-1/2 in pipe value.
     * @param two double, nominal 2 in pipe value.
     * @param twoAndOneHalf double, nominal 2-1/2 in pipe value.
     * @param three double, nominal 3 in pipe value.
     * @param threeAndOneHalf double, nominal 3-1/2 in pipe value.
     * @param four double, nominal 4 in pipe value.
     * @param five double, nominal 5 in pipe value.
     * @param six double, nominal 6 in pipe value.
     * @param eight double, nominal 8 in pipe value.
     * @param ten double, nominal 10 in pipe value.
     * @param twelve double, nominal 12 in pipe value.
     * @param fourteen double, nominal 14 in pipe value.
     * @param sixteen double, nominal 16 in pipe value.
     * @param eighteen double, nominal 18 in pipe value.
     * @param twenty double, nominal 20 in pipe value.
     * @param twentyFour double, nominal 24 in pipe value.
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

    oneHalf: number;
    threeFourths: number;
    one: number;
    oneAndOneFourth: number;
    oneAndOneHalf: number;
    two: number;
    twoAndOneHalf: number;
    three: number;
    threeAndOneHalf: number;
    four: number;
    five: number;
    six: number;
    eight: number;
    ten: number;
    twelve: number;
    fourteen: number;
    sixteen: number;
    eighteen: number;
    twenty: number;
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
    constructor(
        totalPipeVolume: number,
        receiverCapacities: number[],
        totalReceiverVolume: number,
        totalCapacityOfCompressedAirSystem: number,
        pipeLengths: PipeData
    );

    totalPipeVolume: number;
    totalReceiverVolume: number;
    totalCapacityOfCompressedAirSystem: number;
    receiverCapacities: number[];
    pipeLengths: PipeData;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates total compressed air system capacity from pipe and receiver data.
 */
export declare class AirSystemCapacity {
    /**
     * @param pipeLengths PipeData, object containing values for different pipe sizes.
     * @param receivers number[], vector of receiver volumes.
     */
    constructor(pipeLengths: PipeData, receivers: number[]);

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
