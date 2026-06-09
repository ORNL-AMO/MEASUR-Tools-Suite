/**
 * @brief Data structure for a lighting default data record.
 *
 * Represents a single entry in the lighting default data set, containing
 * fixture category, lamp type, photometric, and electrical characteristics.
 */
export class LightingData {
    /**
     * Constructs a Lighting's data record with the specified parameters.
     * The data ID is initialized to 0; use {@link setID} to assign a sequential ID.
     *
     * @param category lighting system category (unitless)
     * @param type lighting system type (unitless)
     * @param lampsPerFixture number of lamps per fixture (unitless)
     * @param lampWattage lamp wattage in watts (W)
     * @param lampOutput lamp luminous output in lumens (lm)
     * @param lampLife lamp rated life in hours (h)
     * @param lampCRI lamp Color Rendering Index (unitless)
     * @param coefficientOfUtilization coefficient of utilization as a percentage (%)
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
     * Sets the sequential ID of the lighting default data record.
     * Used for default data initialization by assigning a sequential data ID.
     *
     * @param id sequential ID of the lighting default data record
     */
    setID(id: number): void;

    /**
     * Gets the sequential ID of the lighting default data record.
     *
     * @returns sequential ID of the lighting default data record
     */
    ID(): number;

    /**
     * Gets the category of the lighting system.
     *
     * @returns category of the lighting system
     */
    category(): string;

    /**
     * Gets the type of the lighting system.
     *
     * @returns type of the lighting system
     */
    type(): string;

    /**
     * Gets the number of lamps per fixture of the lighting system.
     *
     * @returns number of lamps per fixture (unitless)
     */
    lampsPerFixture(): number;

    /**
     * Gets the lamp wattage of the lighting system.
     *
     * @returns lamp wattage in watts (W)
     */
    lampWattage(): number;

    /**
     * Gets the lamp luminous output of the lighting system.
     *
     * @returns lamp output in lumens (lm)
     */
    lampOutput(): number;

    /**
     * Gets the rated lamp life of the lighting system.
     *
     * @returns lamp life in hours (h)
     */
    lampLife(): number;

    /**
     * Gets the lamp Color Rendering Index (CRI) of the lighting system.
     *
     * @returns lamp CRI (unitless)
     */
    lampCRI(): number;

    /**
     * Gets the coefficient of utilization of the lighting system.
     *
     * @returns coefficient of utilization as a percentage (%)
     */
    coefficientOfUtilization(): number;

    /**
     * Gets the ballast factor of the lighting system.
     *
     * @returns ballast factor (unitless)
     */
    ballastFactor(): number;

    /**
     * Gets the lumen degradation factor of the lighting system.
     *
     * @returns lumen degradation factor (unitless)
     */
    lumenDegradationFactor(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Factory function to load the Lighting Data module. */
export default function LightingDataModule(): Promise<{
    LightingData: typeof LightingData;
}>;

