/**
 * Gas Composition Calculations
 *
 * Represents a fuel gas mixture and its derived thermodynamic properties.
 * Supports excess-air and flue-gas oxygen conversion calculations.
 */

/**
 * Fuel gas composition model and calculator.
 *
 * Stores mixture composition and derived properties used for process heat
 * calculations.
 *
 * @property heatingValue double, heating value of the fuel gas mixture, units Btu/SCF
 * @property heatingValueVolume double, heating value of the fuel gas mixture, units Btu/ft3
 * @property specificGravity double, specific gravity of the fuel gas mixture (unitless)
 */
export declare class GasCompositions {
    /**
     * Creates a fuel gas composition.
     *
     * All composition values are percent by volume.
     *
     * @param substance string, name of the fuel gas mixture
     * @param ch4_percent double, methane (CH4), units %
     * @param c2h6_percent double, ethane (C2H6), units %
     * @param n2_percent double, nitrogen (N2), units %
     * @param h2_percent double, hydrogen (H2), units %
     * @param c3h8_percent double, propane (C3H8), units %
     * @param c4h10_cnh2n_percent double, butane/paraffins (C4H10/CnH2n), units %
     * @param h2o_percent double, water vapor (H2O), units %
     * @param co_percent double, carbon monoxide (CO), units %
     * @param co2_percent double, carbon dioxide (CO2), units %
     * @param so2_percent double, sulfur dioxide (SO2), units %
     * @param o2_percent double, oxygen (O2), units %
     */
    constructor(
        substance: string,
        ch4_percent: number,
        c2h6_percent: number,
        n2_percent: number,
        h2_percent: number,
        c3h8_percent: number,
        c4h10_cnh2n_percent: number,
        h2o_percent: number,
        co_percent: number,
        co2_percent: number,
        so2_percent: number,
        o2_percent: number
    );

    /** Heating value of the fuel gas mixture, units Btu/SCF */
    heatingValue: number;
    /** Heating value of the fuel gas mixture, units Btu/ft3 */
    heatingValueVolume: number;
    /** Specific gravity of the fuel gas mixture, unitless */
    specificGravity: number;

    /**
     * Calculates excess air from flue gas oxygen.
     *
     * @param flue_gas_o2_percentage double, oxygen percentage in flue gas, units %
     * @returns double, excess air percentage, units %
     */
    calculateExcessAir(flue_gas_o2_percentage: number): number;

    /**
     * Calculates flue gas oxygen from excess air.
     *
     * @param excess_air double, excess air percentage, units %
     * @returns double, oxygen percentage in flue gas, units %
     */
    calculateO2(excess_air: number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type GasCompositionsModule = {
    GasCompositions: typeof GasCompositions;
};
