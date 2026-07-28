/**
 * O2 Enrichment calculations.
 *
 * Calculates available heat, fuel consumption, and fuel savings for a
 * fuel-fired furnace when switching from standard air to O2-enriched
 * combustion air.
 */

/**
 * Result object returned by {@link calculateO2Enrichment}.
 *
 * @property excessAir Excess air (fraction)
 * @property excessAirEnriched Excess air with O2 enrichment (fraction)
 * @property heatInput Heat input, units %
 * @property heatInputEnriched Heat input with O2 enrichment, units %
 * @property airSpecificHeat Air specific heat, units BTU/(lb.degF)
 * @property enrichedAirSpecificHeat Enriched air specific heat, units BTU/(lb.degF)
 * @property airCorrection Air correction, units %
 * @property enrichedAirCorrection Enriched air correction, units BTU
 * @property combustionAirCorrection Combustion air correction, units %
 * @property combustionAirCorrectionEnriched Combustion air correction with O2 enrichment, units %
 * @property stdAvailableHeat Standard available heat (fraction)
 * @property stdAvailableHeatEnriched Standard available heat with O2 enrichment (fraction)
 * @property availableHeat Available heat (fraction)
 * @property availableHeatEnriched Available heat with O2 enrichment (fraction)
 * @property fuelConsumptionEnriched Fuel consumption with O2 enrichment, units MMBtu/hr
 * @property fuelSavingsEnriched Fuel savings with O2 enrichment, units %
 */
export interface O2EnrichmentResults {
    /** Excess air, fraction */
    excessAir: number;
    /** Excess air with O2 enrichment, fraction */
    excessAirEnriched: number;
    /** Heat input, units % */
    heatInput: number;
    /** Heat input with O2 enrichment, units % */
    heatInputEnriched: number;
    /** Air specific heat, units BTU/(lb.degF) */
    airSpecificHeat: number;
    /** Enriched air specific heat, units BTU/(lb.degF) */
    enrichedAirSpecificHeat: number;
    /** Air correction, units % */
    airCorrection: number;
    /** Enriched air correction, units BTU */
    enrichedAirCorrection: number;
    /** Combustion air correction, units % */
    combustionAirCorrection: number;
    /** Combustion air correction with O2 enrichment, units % */
    combustionAirCorrectionEnriched: number;
    /** Standard available heat, fraction */
    stdAvailableHeat: number;
    /** Standard available heat with O2 enrichment, fraction */
    stdAvailableHeatEnriched: number;
    /** Available heat, fraction */
    availableHeat: number;
    /** Available heat with O2 enrichment, fraction */
    availableHeatEnriched: number;
    /** Fuel consumption with O2 enrichment, units MMBtu/hr */
    fuelConsumptionEnriched: number;
    /** Fuel savings with O2 enrichment, units % */
    fuelSavingsEnriched: number;
}

/**
 * Calculate O2 enrichment results for a fuel-fired furnace.
 *
 * Uses process and enrichment parameters to estimate available heat,
 * fuel consumption, and fuel savings from O2 enrichment.
 *
 * @param o2_comb_air O2 in combustion air, units %
 * @param o2_comb_air_enriched O2 in enriched combustion air, units %
 * @param flue_gas_temp Flue gas temperature, units degF
 * @param flue_gas_temp_enriched Flue gas temperature with O2 enrichment, units degF
 * @param o2_flue_gas O2 in flue gas, units %
 * @param o2_flue_gas_enriched O2 in flue gas with O2 enrichment, units %
 * @param comb_air_temp Combustion air preheat temperature, units degF
 * @param comb_air_temp_enriched Combustion air preheat temperature with O2 enrichment, units degF
 * @param fuel_consumption Fuel consumption, units MMBtu/hr
 * @returns {@link O2EnrichmentResults}
 */
export function calculateO2Enrichment(
    o2_comb_air: number,
    o2_comb_air_enriched: number,
    flue_gas_temp: number,
    flue_gas_temp_enriched: number,
    o2_flue_gas: number,
    o2_flue_gas_enriched: number,
    comb_air_temp: number,
    comb_air_temp_enriched: number,
    fuel_consumption: number
): O2EnrichmentResults;

export type O2EnrichmentModule = {
    calculateO2Enrichment: typeof calculateO2Enrichment;
};
