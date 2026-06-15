/**
 * Bio-Tiger Wastewater Treatment simulation.
 *
 * Simulates activated-sludge wastewater treatment performance and provides
 * process outputs with and without the full iteration calculations table.
 */

import { CalculationsTableV } from "../binding/registered_vectors";

/**
 * Iteration row of intermediate wastewater-treatment calculations.
 *
 * Result rows are produced by the internal solver and exposed through
 * {@link WasteWater_TreatmentOutput.calculationsTable}.
 */
export declare class CalculationsTable {
    Se: number;
    HeterBio: number;
    CellDeb: number;
    InterVes: number;
    MLVSS: number;
    MLSS: number;
    BiomassProd: number;
    SludgeProd: number;
    SolidProd: number;
    Effluent: number;
    IntentWaste: number;
    OxygenRqd: number;
    FlowMgd: number;
    NRemoved: number;
    NRemovedMgl: number;
    NitO2Dem: number;
    O2Reqd: number;
    EffNH3N: number;
    EffNo3N: number;
    TotalO2Rqd: number;
    WAS: number;
    EstimatedEff: number;
    EstimRas: number;
    FmRatio: number;
    Diff_MLSS: number;
    SRT: number;

    /** @returns Numeric array view of this row in model-defined order */
    getArray(): number[];

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WasteWater_Treatment.calculate}.
 *
 * @property TotalAverageDailyFlowRate double
 * @property VolumeInService double
 * @property InfluentBOD5Concentration double
 * @property InfluentBOD5MassLoading double
 * @property SecWWOxidNLoad double
 * @property SecWWTSSLoad double
 * @property FM_ratio double
 * @property SolidsRetentionTime double
 * @property MLSS double
 * @property MLVSS double
 * @property TSSSludgeProduction double
 * @property TSSInActivatedSludgeEffluent double
 * @property TotalOxygenRequirements double
 * @property TotalOxygenReqWDenit double
 * @property TotalOxygenSupplied double
 * @property MixingIntensityInReactor double
 * @property RASFlowRate double
 * @property RASRecyclePercentage double
 * @property WASFlowRate double
 * @property RASTSSConcentration double
 * @property TotalSludgeProduction double
 * @property ReactorDetentionTime double
 * @property VOLR double
 * @property EffluentCBOD5 double
 * @property EffluentTSS double
 * @property EffluentAmmonia_N double
 * @property EffluentNO3_N double
 * @property EffluentNO3_N_W_Denit double
 * @property AeEnergy double
 * @property AeCost double
 * @property FieldOTR double
 * @property calculationsTable {@link CalculationsTableV}
 */
export interface WasteWater_TreatmentOutput {
    TotalAverageDailyFlowRate: number;
    VolumeInService: number;
    InfluentBOD5Concentration: number;
    InfluentBOD5MassLoading: number;
    SecWWOxidNLoad: number;
    SecWWTSSLoad: number;
    FM_ratio: number;
    SolidsRetentionTime: number;
    MLSS: number;
    MLVSS: number;
    TSSSludgeProduction: number;
    TSSInActivatedSludgeEffluent: number;
    TotalOxygenRequirements: number;
    TotalOxygenReqWDenit: number;
    TotalOxygenSupplied: number;
    MixingIntensityInReactor: number;
    RASFlowRate: number;
    RASRecyclePercentage: number;
    WASFlowRate: number;
    RASTSSConcentration: number;
    TotalSludgeProduction: number;
    ReactorDetentionTime: number;
    VOLR: number;
    EffluentCBOD5: number;
    EffluentTSS: number;
    EffluentAmmonia_N: number;
    EffluentNO3_N: number;
    EffluentNO3_N_W_Denit: number;
    AeEnergy: number;
    AeCost: number;
    FieldOTR: number;
    calculationsTable: CalculationsTableV;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WasteWater_Treatment.calculateGivenSRT}.
 *
 * Same output as {@link WasteWater_TreatmentOutput} but without the
 * full calculations table.
 */
export interface WasteWater_TreatmentOutputWithoutTable {
    TotalAverageDailyFlowRate: number;
    VolumeInService: number;
    InfluentBOD5Concentration: number;
    InfluentBOD5MassLoading: number;
    SecWWOxidNLoad: number;
    SecWWTSSLoad: number;
    FM_ratio: number;
    SolidsRetentionTime: number;
    MLSS: number;
    MLVSS: number;
    TSSSludgeProduction: number;
    TSSInActivatedSludgeEffluent: number;
    TotalOxygenRequirements: number;
    TotalOxygenReqWDenit: number;
    TotalOxygenSupplied: number;
    MixingIntensityInReactor: number;
    RASFlowRate: number;
    RASRecyclePercentage: number;
    WASFlowRate: number;
    RASTSSConcentration: number;
    TotalSludgeProduction: number;
    ReactorDetentionTime: number;
    VOLR: number;
    EffluentCBOD5: number;
    EffluentTSS: number;
    EffluentAmmonia_N: number;
    EffluentNO3_N: number;
    EffluentNO3_N_W_Denit: number;
    AeEnergy: number;
    AeCost: number;
    FieldOTR: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Bio-Tiger wastewater treatment simulation calculator.
 */
export declare class WasteWater_Treatment {
    /**
     * Create a wastewater treatment simulation with process, aeration, and economic inputs.
     *
     * @param Temperature double
     * @param So double
     * @param Volume double
     * @param FlowRate double
     * @param InertVSS double
     * @param OxidizableN double
     * @param Biomass double
     * @param InfluentTSS double
     * @param InertInOrgTSS double
     * @param EffluentTSS double
     * @param RASTSS double
     * @param MLSSpar double
     * @param FractionBiomass double
     * @param BiomassYeild double
     * @param HalfSaturation double
     * @param MicrobialDecay double
     * @param MaxUtilizationRate double
     * @param MaxDays double
     * @param TimeIncrement double
     * @param OperatingDO double
     * @param Alpha double
     * @param Beta double
     * @param SOTR double
     * @param Aeration double
     * @param Elevation double
     * @param OperatingTime double
     * @param TypeAerators int
     * @param Speed double
     * @param EnergyCostUnit double
     * @param DefinedSRT double
     */
    constructor(
        Temperature: number,
        So: number,
        Volume: number,
        FlowRate: number,
        InertVSS: number,
        OxidizableN: number,
        Biomass: number,
        InfluentTSS: number,
        InertInOrgTSS: number,
        EffluentTSS: number,
        RASTSS: number,
        MLSSpar: number,
        FractionBiomass: number,
        BiomassYeild: number,
        HalfSaturation: number,
        MicrobialDecay: number,
        MaxUtilizationRate: number,
        MaxDays: number,
        TimeIncrement: number,
        OperatingDO: number,
        Alpha: number,
        Beta: number,
        SOTR: number,
        Aeration: number,
        Elevation: number,
        OperatingTime: number,
        TypeAerators: number,
        Speed: number,
        EnergyCostUnit: number,
        DefinedSRT: number
    );

    /**
     * Run the full simulation and return outputs including the iteration table.
     *
     * @returns {@link WasteWater_TreatmentOutput}
     */
    calculate(): WasteWater_TreatmentOutput;

    /**
     * Run the simulation at the defined solids retention time.
     *
     * @returns {@link WasteWater_TreatmentOutputWithoutTable}
     */
    calculateGivenSRT(): WasteWater_TreatmentOutputWithoutTable;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type WasteWaterModule = {
    CalculationsTable: typeof CalculationsTable;
    WasteWater_TreatmentOutput: WasteWater_TreatmentOutput;
    WasteWater_TreatmentOutputWithoutTable: WasteWater_TreatmentOutputWithoutTable;
    WasteWater_Treatment: typeof WasteWater_Treatment;
};
