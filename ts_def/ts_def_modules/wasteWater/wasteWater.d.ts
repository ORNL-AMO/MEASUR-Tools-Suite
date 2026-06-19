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
    /** Effluent soluble BOD concentration, units mg/L. */
    Se: number;
    /** Heterotrophic biomass concentration, units mg/L. */
    HeterBio: number;
    /** Cell debris concentration, units mg/L. */
    CellDeb: number;
    /** Inert volatile suspended solids concentration, units mg/L. */
    InterVes: number;
    /** Mixed liquor volatile suspended solids concentration, units mg/L. */
    MLVSS: number;
    /** Mixed liquor suspended solids concentration, units mg/L. */
    MLSS: number;
    /** Biomass production, units lb/day. */
    BiomassProd: number;
    /** Volatile sludge production, units lb/day. */
    SludgeProd: number;
    /** Total solids production, units lb/day. */
    SolidProd: number;
    /** TSS in activated sludge effluent, units lb/day. */
    Effluent: number;
    /** Intentional waste sludge production, units lb/day. */
    IntentWaste: number;
    /** Carbonaceous oxygen requirement, units lb/day. */
    OxygenRqd: number;
    /** Waste activated sludge flow, units MGD. */
    FlowMgd: number;
    /** Nitrogen removed, units lb/day. */
    NRemoved: number;
    /** Nitrogen removed concentration, units mg/L. */
    NRemovedMgl: number;
    /** Nitrification oxygen demand, units lb/day. */
    NitO2Dem: number;
    /** Total oxygen required before denitrification credit, units lb/day. */
    O2Reqd: number;
    /** Effluent ammonia nitrogen concentration, units mg/L. */
    EffNH3N: number;
    /** Effluent nitrate nitrogen concentration, units mg/L. */
    EffNo3N: number;
    /** Total oxygen required with denitrification credit, units lb/day. */
    TotalO2Rqd: number;
    /** Waste activated sludge flow, units MGD. */
    WAS: number;
    /** Estimated effluent CBOD5 concentration, units mg/L. */
    EstimatedEff: number;
    /** Estimated return activated sludge flow, units MGD. */
    EstimRas: number;
    /** Food-to-microorganism ratio, dimensionless. */
    FmRatio: number;
    /** Squared difference from target MLSS, units (mg/L)^2. */
    Diff_MLSS: number;
    /** Solids retention time, units days. */
    SRT: number;

    /** @returns Numeric array view of this row in model-defined order */
    getArray(): number[];

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link WasteWater_Treatment.calculate}.
 *
 * @property TotalAverageDailyFlowRate Total average daily flow rate, units MGD.
 * @property VolumeInService Aeration basin volume in service, units million gallons.
 * @property InfluentBOD5Concentration Influent BOD5 concentration, units mg/L.
 * @property InfluentBOD5MassLoading Influent BOD5 mass loading, units lb/day.
 * @property SecWWOxidNLoad Secondary wastewater oxidizable nitrogen load, units lb/day.
 * @property SecWWTSSLoad Secondary wastewater TSS load, units lb/day.
 * @property FM_ratio Food-to-microorganism ratio, dimensionless.
 * @property SolidsRetentionTime Selected solids retention time, units days.
 * @property MLSS Mixed liquor suspended solids concentration, units mg/L.
 * @property MLVSS Mixed liquor volatile suspended solids concentration, units mg/L.
 * @property TSSSludgeProduction TSS sludge production, units lb/day.
 * @property TSSInActivatedSludgeEffluent TSS in activated sludge effluent, units lb/day.
 * @property TotalOxygenRequirements Total oxygen requirements before denitrification credit, units lb/day.
 * @property TotalOxygenReqWDenit Total oxygen requirements with denitrification credit, units lb/day.
 * @property TotalOxygenSupplied Total oxygen supplied by aeration, units lb/day.
 * @property MixingIntensityInReactor Mixing intensity in reactor, units hp/MG.
 * @property RASFlowRate Return activated sludge flow rate, units MGD.
 * @property RASRecyclePercentage Return activated sludge recycle percentage, units %.
 * @property WASFlowRate Waste activated sludge flow rate, units MGD.
 * @property RASTSSConcentration Return activated sludge TSS concentration, units mg/L.
 * @property TotalSludgeProduction Total sludge production, units lb/day.
 * @property ReactorDetentionTime Reactor detention time, units hr.
 * @property VOLR Volumetric organic loading rate, units lb BOD/day/1000 ft3.
 * @property EffluentCBOD5 Effluent CBOD5 concentration, units mg/L.
 * @property EffluentTSS Effluent TSS concentration, units mg/L.
 * @property EffluentAmmonia_N Effluent ammonia nitrogen concentration, units mg/L.
 * @property EffluentNO3_N Effluent nitrate nitrogen concentration, units mg/L.
 * @property EffluentNO3_N_W_Denit Effluent nitrate nitrogen with denitrification, units mg/L.
 * @property AeEnergy Aerator energy use, units kWh/month.
 * @property AeCost Aerator energy cost, units $/month.
 * @property FieldOTR Field oxygen transfer rate, units lb O2/hr.
 * @property calculationsTable {@link CalculationsTableV}
 */
export interface WasteWater_TreatmentOutput {
    /** Total average daily flow rate, units MGD. */
    TotalAverageDailyFlowRate: number;
    /** Aeration basin volume in service, units million gallons. */
    VolumeInService: number;
    /** Influent BOD5 concentration, units mg/L. */
    InfluentBOD5Concentration: number;
    /** Influent BOD5 mass loading, units lb/day. */
    InfluentBOD5MassLoading: number;
    /** Secondary wastewater oxidizable nitrogen load, units lb/day. */
    SecWWOxidNLoad: number;
    /** Secondary wastewater TSS load, units lb/day. */
    SecWWTSSLoad: number;
    /** Food-to-microorganism ratio, dimensionless. */
    FM_ratio: number;
    /** Selected solids retention time, units days. */
    SolidsRetentionTime: number;
    /** Mixed liquor suspended solids concentration, units mg/L. */
    MLSS: number;
    /** Mixed liquor volatile suspended solids concentration, units mg/L. */
    MLVSS: number;
    /** TSS sludge production, units lb/day. */
    TSSSludgeProduction: number;
    /** TSS in activated sludge effluent, units lb/day. */
    TSSInActivatedSludgeEffluent: number;
    /** Total oxygen requirements before denitrification credit, units lb/day. */
    TotalOxygenRequirements: number;
    /** Total oxygen requirements with denitrification credit, units lb/day. */
    TotalOxygenReqWDenit: number;
    /** Total oxygen supplied by aeration, units lb/day. */
    TotalOxygenSupplied: number;
    /** Mixing intensity in reactor, units hp/MG. */
    MixingIntensityInReactor: number;
    /** Return activated sludge flow rate, units MGD. */
    RASFlowRate: number;
    /** Return activated sludge recycle percentage, units %. */
    RASRecyclePercentage: number;
    /** Waste activated sludge flow rate, units MGD. */
    WASFlowRate: number;
    /** Return activated sludge TSS concentration, units mg/L. */
    RASTSSConcentration: number;
    /** Total sludge production, units lb/day. */
    TotalSludgeProduction: number;
    /** Reactor detention time, units hr. */
    ReactorDetentionTime: number;
    /** Volumetric organic loading rate, units lb BOD/day/1000 ft3. */
    VOLR: number;
    /** Effluent CBOD5 concentration, units mg/L. */
    EffluentCBOD5: number;
    /** Effluent TSS concentration, units mg/L. */
    EffluentTSS: number;
    /** Effluent ammonia nitrogen concentration, units mg/L. */
    EffluentAmmonia_N: number;
    /** Effluent nitrate nitrogen concentration, units mg/L. */
    EffluentNO3_N: number;
    /** Effluent nitrate nitrogen with denitrification, units mg/L. */
    EffluentNO3_N_W_Denit: number;
    /** Aerator energy use, units kWh/month. */
    AeEnergy: number;
    /** Aerator energy cost, units $/month. */
    AeCost: number;
    /** Field oxygen transfer rate, units lb O2/hr. */
    FieldOTR: number;
    /** CalculationsTableV. */
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
    /** Total average daily flow rate, units MGD. */
    TotalAverageDailyFlowRate: number;
    /** Aeration basin volume in service, units million gallons. */
    VolumeInService: number;
    /** Influent BOD5 concentration, units mg/L. */
    InfluentBOD5Concentration: number;
    /** Influent BOD5 mass loading, units lb/day. */
    InfluentBOD5MassLoading: number;
    /** Secondary wastewater oxidizable nitrogen load, units lb/day. */
    SecWWOxidNLoad: number;
    /** Secondary wastewater TSS load, units lb/day. */
    SecWWTSSLoad: number;
    /** Food-to-microorganism ratio, dimensionless. */
    FM_ratio: number;
    /** Selected solids retention time, units days. */
    SolidsRetentionTime: number;
    /** Mixed liquor suspended solids concentration, units mg/L. */
    MLSS: number;
    /** Mixed liquor volatile suspended solids concentration, units mg/L. */
    MLVSS: number;
    /** TSS sludge production, units lb/day. */
    TSSSludgeProduction: number;
    /** TSS in activated sludge effluent, units lb/day. */
    TSSInActivatedSludgeEffluent: number;
    /** Total oxygen requirements before denitrification credit, units lb/day. */
    TotalOxygenRequirements: number;
    /** Total oxygen requirements with denitrification credit, units lb/day. */
    TotalOxygenReqWDenit: number;
    /** Total oxygen supplied by aeration, units lb/day. */
    TotalOxygenSupplied: number;
    /** Mixing intensity in reactor, units hp/MG. */
    MixingIntensityInReactor: number;
    /** Return activated sludge flow rate, units MGD. */
    RASFlowRate: number;
    /** Return activated sludge recycle percentage, units %. */
    RASRecyclePercentage: number;
    /** Waste activated sludge flow rate, units MGD. */
    WASFlowRate: number;
    /** Return activated sludge TSS concentration, units mg/L. */
    RASTSSConcentration: number;
    /** Total sludge production, units lb/day. */
    TotalSludgeProduction: number;
    /** Reactor detention time, units hr. */
    ReactorDetentionTime: number;
    /** Volumetric organic loading rate, units lb BOD/day/1000 ft3. */
    VOLR: number;
    /** Effluent CBOD5 concentration, units mg/L. */
    EffluentCBOD5: number;
    /** Effluent TSS concentration, units mg/L. */
    EffluentTSS: number;
    /** Effluent ammonia nitrogen concentration, units mg/L. */
    EffluentAmmonia_N: number;
    /** Effluent nitrate nitrogen concentration, units mg/L. */
    EffluentNO3_N: number;
    /** Effluent nitrate nitrogen with denitrification, units mg/L. */
    EffluentNO3_N_W_Denit: number;
    /** Aerator energy use, units kWh/month. */
    AeEnergy: number;
    /** Aerator energy cost, units $/month. */
    AeCost: number;
    /** Field oxygen transfer rate, units lb O2/hr. */
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
     * @param Temperature Wastewater temperature, units degC.
     * @param So Influent soluble BOD concentration, units mg/L.
     * @param Volume Aeration basin volume, units million gallons.
     * @param FlowRate Average daily flow rate, units MGD.
     * @param InertVSS Inert volatile suspended solids concentration, units mg/L.
     * @param OxidizableN Oxidizable nitrogen concentration, units mg/L.
     * @param Biomass Biomass fraction, dimensionless.
     * @param InfluentTSS Influent total suspended solids concentration, units mg/L.
     * @param InertInOrgTSS Inert inorganic TSS concentration, units mg/L.
     * @param EffluentTSS Target effluent TSS concentration, units mg/L.
     * @param RASTSS Return activated sludge TSS concentration, units mg/L.
     * @param MLSSpar Mixed liquor suspended solids target, units mg/L.
     * @param FractionBiomass Biomass fraction in volatile solids, dimensionless.
     * @param BiomassYeild Biomass yield coefficient, dimensionless.
     * @param HalfSaturation Half-saturation coefficient, units mg/L.
     * @param MicrobialDecay Microbial decay coefficient, units 1/day.
     * @param MaxUtilizationRate Maximum substrate utilization rate, units 1/day.
     * @param MaxDays Maximum solids retention time, units days.
     * @param TimeIncrement Solver time increment, units days.
     * @param OperatingDO Operating dissolved oxygen concentration, units mg/L.
     * @param Alpha Alpha correction factor, dimensionless.
     * @param Beta Beta correction factor, dimensionless.
     * @param SOTR Standard oxygen transfer rate, units lb O2/hr.
     * @param Aeration Aeration power, units hp.
     * @param Elevation Site elevation, units ft.
     * @param OperatingTime Aerator operating time, units hr/day.
     * @param TypeAerators Aerator type selector, unitless enum value.
     * @param Speed Aerator speed, units %.
     * @param EnergyCostUnit Energy cost, units $/kWh.
     * @param DefinedSRT User-defined solids retention time, units days.
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
