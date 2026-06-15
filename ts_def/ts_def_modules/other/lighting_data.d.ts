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
     * @param lampsPerFixture double, number of lamps per fixture
     * @param lampWattage double, lamp wattage in W
     * @param lampOutput double, lamp luminous output in lumens
     * @param lampLife double, rated lamp life in hours
     * @param lampCRI double, Color Rendering Index
     * @param coefficientOfUtilization double, coefficient of utilization as decimal
     * @param ballastFactor ballast factor (unitless)
     * @param lumenDegradationFactor lumen degradation factor (unitless)
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
     * @param id double, sequential ID of this lighting record
     */
    setID(id: number): void;

    /**
     * Gets the sequential record ID.
     *
     * @returns double, sequential ID
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
     * Gets number of lamps per fixture.
     * @returns double, lamps per fixture
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
     * Gets lamp Color Rendering Index (CRI).
     * @returns double, lamp CRI
     */
    lampCRI(): number;

    /**
     * Gets coefficient of utilization.
     * @returns double, coefficient of utilization as decimal
     */
    coefficientOfUtilization(): number;

    /**
     * Gets ballast factor.
     * @returns double, ballast factor
     */
    ballastFactor(): number;

    /**
     * Gets lumen degradation factor.
     * @returns double, lumen degradation factor
     */
    lumenDegradationFactor(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type LightingDataModule = {
    LightingData: typeof LightingData;
};
