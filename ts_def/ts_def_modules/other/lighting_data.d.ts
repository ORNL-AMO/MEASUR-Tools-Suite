/**
 * Lighting default data.
 *
 * Defines a single default lighting fixture record used by lighting
 * calculations and default dataset retrieval.
 */
export declare class LightingData {
    /**
     * Creates a lighting default data record.
     *
     * The ID is initialized to 0; use {@link setID} to assign a sequential ID.
     *
     * @param category string, fixture category
     * @param type string, fixture type
     * @param lampsPerFixture double, lamp count per fixture, count
     * @param lampWattage double, lamp wattage in W
     * @param lampOutput double, lamp luminous output in lumens
     * @param lampLife double, rated lamp life in hours
     * @param lampCRI double, color rendering index, unitless
     * @param coefficientOfUtilization double, coefficient of utilization, dimensionless decimal
     * @param ballastFactor ballast factor, dimensionless (unitless)
     * @param lumenDegradationFactor lumen degradation factor, dimensionless (unitless)
     */
    constructor(
        category: string,
        type: string,
        lampsPerFixture: number,
        lampWattage: number,
        lampOutput: number,
        lampLife: number,
        lampCRI: number,
        coefficientOfUtilization: number,
        ballastFactor: number,
        lumenDegradationFactor: number
    );

    /**
     * Sets the sequential record ID.
     *
     * @param id Sequential ID of this lighting record, unitless identifier.
     */
    setID(id: number): void;

    /**
     * Gets the sequential record ID.
     *
     * @returns Sequential ID, unitless identifier.
     */
    ID(): number;

    /**
     * Gets fixture category.
     * @returns string, fixture category
     */
    category(): string;

    /**
     * Gets fixture type.
     * @returns string, fixture type
     */
    type(): string;

    /**
     * Gets lamp count per fixture, count.
     * @returns Lamps per fixture, count.
     */
    lampsPerFixture(): number;

    /**
     * Gets lamp wattage.
     * @returns double, lamp wattage in W
     */
    lampWattage(): number;

    /**
     * Gets lamp luminous output.
     * @returns double, lamp output in lumens
     */
    lampOutput(): number;

    /**
     * Gets rated lamp life.
     * @returns double, lamp life in hours
     */
    lampLife(): number;

    /**
     * Gets lamp color rendering index, unitless (CRI).
     * @returns Lamp color rendering index, unitless.
     */
    lampCRI(): number;

    /**
     * Gets coefficient of utilization.
     * @returns double, coefficient of utilization, dimensionless decimal
     */
    coefficientOfUtilization(): number;

    /**
     * Gets ballast factor, dimensionless.
     * @returns double, ballast factor, dimensionless
     */
    ballastFactor(): number;

    /**
     * Gets lumen degradation factor, dimensionless.
     * @returns double, lumen degradation factor, dimensionless
     */
    lumenDegradationFactor(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type LightingDataModule = {
    LightingData: typeof LightingData;
};
