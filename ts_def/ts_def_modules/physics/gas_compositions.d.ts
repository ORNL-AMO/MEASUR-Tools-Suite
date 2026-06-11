/**
 * Gas Composition calculations for process heat.
 *
 * Represents a fuel gas mixture and its derived thermodynamic properties.
 * Supports excess-air / O₂ conversions for flue-gas analysis.
 */

/**
 * Represents a fuel gas mixture and its properties for process heat calculations.
 * Stores the composition and calculated properties for a fuel gas mixture,
 * including constituent gases and derived values.
 *
 * Constructs a {@link GasCompositions} instance representing a named fuel gas mixture.
 *
 * All percentage parameters are expressed as percent by volume (% vol).
 *
 * @property heatingValue   Heating value of the fuel gas mixture, units BTU/SCF
 * @property heatingValueVolume Heating value of the fuel gas mixture, units BTU/ft³
 * @property specificGravity Specific gravity of the fuel gas mixture (unitless)
 */
export declare class GasCompositions {
    /**
     * @param substance Name of the fuel gas mixture
     * @param ch4_percent Methane (CH4) percent by volume, units %
     * @param c2h6_percent Ethane (C2H6) percent by volume, units %
     * @param n2_percent Nitrogen (N2) percent by volume, units %
     * @param h2_percent Hydrogen (H2) percent by volume, units %
     * @param c3h8_percent Propane (C3H8) percent by volume, units %
     * @param c4h10_cnh2n_percent Butane/Paraffins (C4H10/CnH2n) percent by volume, units %
     * @param h2o_percent Water vapor (H2O) percent by volume, units %
     * @param co_percent Carbon monoxide (CO) percent by volume, units %
     * @param co2_percent Carbon dioxide (CO2) percent by volume, units %
     * @param so2_percent Sulphur dioxide (SO2) percent by volume, units %
     * @param o2_percent Oxygen (O2) percent by volume, units %
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

    /** Heating value of the fuel gas mixture, units BTU/SCF */
    heatingValue: number;
    /** Heating value of the fuel gas mixture, units BTU/ft³ */
    heatingValueVolume: number;
    /** Specific gravity of the fuel gas mixture (unitless) */
    specificGravity: number;

    /**
     * Calculates excess air percentage from flue gas oxygen percentage.
     *
     * @param flue_gas_o2_percentage Oxygen percentage in flue gas, units %
     * @returns Excess air percentage, units %
     */
    calculateExcessAir(flue_gas_o2_percentage: number): number;

    /**
     * Calculates flue gas oxygen percentage from excess air percentage.
     *
     * @param excess_air Excess air percentage, units %
     * @returns Oxygen percentage in flue gas, units %
     */
    calculateO2(excess_air: number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type GasCompositionsModule = {
    GasCompositions: typeof GasCompositions;
};
