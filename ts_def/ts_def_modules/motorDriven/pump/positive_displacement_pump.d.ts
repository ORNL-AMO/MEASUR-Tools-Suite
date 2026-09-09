/**
 * Positive displacement pump calculations.
 *
 * Calculates pump power and annual energy use from flow rate, differential
 * pressure, pump efficiency, and operating hours.
 */

/**
 * Result object returned by {@link PositiveDisplacementPump.calculate}.
 */
export declare class PositiveDisplacementPumpOutput {
    /**
     * Constructor for PositiveDisplacementPumpOutput.
     * @param power Pump power, units kW.
     * @param energy Annual energy use, units kWh/year.
     */
    constructor(power: number, energy: number);

    /** Pump power, units kW. */
    power: number;
    /** Annual energy use, units kWh/year. */
    energy: number;

    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

/**
 * Calculates positive displacement pump power and annual energy use.
 */
export declare class PositiveDisplacementPump {
    /**
     * @param flowRate Volumetric flow rate, units gpm.
     * @param differentialPressure Pump differential pressure, units psi.
     * @param pumpEfficiency Pump efficiency, dimensionless fraction.
     * @param operatingHours Annual operating hours, units hr/year.
     */
    constructor(
        flowRate: number,
        differentialPressure: number,
        pumpEfficiency: number,
        operatingHours: number
    );

    /**
     * Calculate pump power and annual energy use.
     * @returns {@link PositiveDisplacementPumpOutput}
     */
    calculate(): PositiveDisplacementPumpOutput;

    /** Frees the underlying resource; must be called when finished with the instance. */
    delete(): void;
}

export type PositiveDisplacementPumpModule = {
    PositiveDisplacementPump: typeof PositiveDisplacementPump;
    PositiveDisplacementPumpOutput: typeof PositiveDisplacementPumpOutput;
};
