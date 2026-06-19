/**
 * Compressor Performance Calculations
 *
 * Provides compressor performance models, control-type calculations, and
 * compressed-air reduction and savings helper functions.
 */

/**
 * Compressor type used in compressor calculation models.
 */
export enum CompressorType {
    Centrifugal = 0,
    Screw = 1,
    Reciprocating = 2
}

/**
 * Compressor control strategy used in compressor calculation models.
 */
export enum ControlType {
    LoadUnload = 0,
    ModulationUnload = 1,
    BlowOff = 2,
    ModulationWOUnload = 3,
    StartStop = 4,
    VariableDisplacementUnload = 5,
    MultiStepUnloading = 6,
    VFD = 7
}

/**
 * Compressor stage configuration.
 */
export enum Stage {
    Single = 0,
    Two = 1,
    Multiple = 2
}

/**
 * Lubrication type used for compressor calculations.
 */
export enum Lubricant {
    Injected = 0,
    Free = 1,
    None = 2
}

/**
 * Modulation mode used by supported control types.
 */
export enum Modulation {
    Throttle = 0,
    VariableDisplacement = 1
}

/**
 * Input interpretation mode used by compressor calculation methods.
 */
export enum ComputeFrom {
    PercentagePower = 0,
    PercentageCapacity = 1,
    PowerMeasured = 2,
    CapacityMeasured = 3,
    PowerFactor = 4
}

/**
 * Data record for one default compressor entry.
 * @property idCompType Compressor type identifier, unitless enum value.
 * @property model string
 * @property hp Compressor rated power, units hp.
 * @property ratedCapacity Rated capacity, units scfm.
 * @property ratedPressure Rated pressure, units psig.
 * @property maxFllFlowPressure Maximum full-flow pressure, units psig.
 * @property idControlType Control type identifier, unitless enum value.
 * @property unloadPoint Unload point pressure, units psig.
 * @property minULSumpPressure Minimum unload sump pressure, units psig.
 * @property blowdownTime Blowdown time, units min.
 * @property unloadSteps Unload steps, units %.
 * @property modulatingPressRange Modulating pressure range, units psi.
 * @property powerFLBHP Full-load brake horsepower, units hp.
 * @property totPackageInputPower Total package input power, units kW.
 * @property specPackagePower Specific package power, units kW/100 acfm.
 * @property noLoadPowerFM No-load power for full modulation, units kW.
 * @property noLoadPowerUL No-load power for unload control, units kW.
 * @property maxSurgePressure Maximum surge pressure, units psig.
 * @property maxPressSurgeFlow Maximum pressure surge flow, units acfm.
 * @property minStonewallPressure Minimum stonewall pressure, units psig.
 * @property minPressStonewallFlow Minimum pressure stonewall flow, units acfm.
 * @property designSurgeFlow Design surge flow, units acfm.
 * @property designInTemp Design inlet temperature, units degF.
 * @property designInPressure Design inlet pressure, units psia.
 * @property ampsFL Full-load current, units A.
 * @property effFL Full-load efficiency, units %.
 */
export declare class CompressorsData {
    /**
     * @param idCompType Compressor type identifier, unitless enum value.
     * @param model Compressor model name.
     * @param hp Compressor rated power, units hp.
     * @param ratedCapacity Rated capacity, units scfm.
     * @param ratedPressure Rated pressure, units psig.
     * @param maxFllFlowPressure Maximum full-flow pressure, units psig.
     * @param idControlType Control type identifier, unitless enum value.
     * @param unloadPoint Unload point pressure, units psig.
     * @param minULSumpPressure Minimum unload sump pressure, units psig.
     * @param blowdownTime Blowdown time, units min.
     * @param unloadSteps Unload steps, units %.
     * @param modulatingPressRange Modulating pressure range, units psi.
     * @param powerFLBHP Full-load brake horsepower, units hp.
     * @param totPackageInputPower Total package input power, units kW.
     * @param specPackagePower Specific package power, units kW/100 acfm.
     * @param noLoadPowerFM No-load power for full modulation, units kW.
     * @param noLoadPowerUL No-load power for unload control, units kW.
     * @param maxSurgePressure Maximum surge pressure, units psig.
     * @param maxPressSurgeFlow Maximum pressure surge flow, units acfm.
     * @param minStonewallPressure Minimum stonewall pressure, units psig.
     * @param minPressStonewallFlow Minimum pressure stonewall flow, units acfm.
     * @param designSurgeFlow Design surge flow, units acfm.
     * @param designInTemp Design inlet temperature, units degF.
     * @param designInPressure Design inlet pressure, units psia.
     * @param ampsFL Full-load current, units A.
     * @param effFL Full-load efficiency, units %.
     */
    constructor(
        idCompType: number,
        model: string,
        hp: number,
        ratedCapacity: number,
        ratedPressure: number,
        maxFllFlowPressure: number,
        idControlType: number,
        unloadPoint: number,
        minULSumpPressure: number,
        blowdownTime: number,
        unloadSteps: number,
        modulatingPressRange: number,
        powerFLBHP: number,
        totPackageInputPower: number,
        specPackagePower: number,
        noLoadPowerFM: number,
        noLoadPowerUL: number,
        maxSurgePressure: number,
        maxPressSurgeFlow: number,
        minStonewallPressure: number,
        minPressStonewallFlow: number,
        designSurgeFlow: number,
        designInTemp: number,
        designInPressure: number,
        ampsFL: number,
        effFL: number
    );

    /** @param id Sequential compressor record ID, unitless identifier. */
    setID(id: number): void;
    /** @returns Sequential compressor record ID, unitless identifier. */
    ID(): number;
    /** @returns Compressor type identifier, unitless enum value. */
    idCompType(): number;
    model(): string;
    /** @returns Compressor rated power, units hp. */
    hp(): number;
    /** @returns Rated capacity, units scfm. */
    ratedCapacity(): number;
    /** @returns Rated pressure, units psig. */
    ratedPressure(): number;
    /** @returns Maximum full-flow pressure, units psig. */
    maxFullFlowPressure(): number;
    /** @returns Control type identifier, unitless enum value. */
    idControlType(): number;
    /** @returns Unload point pressure, units psig. */
    unloadPoint(): number;
    /** @returns Minimum unload sump pressure, units psig. */
    minULSumpPressure(): number;
    /** @returns Blowdown time, units min. */
    blowdownTime(): number;
    /** @returns Unload steps, units %. */
    unloadSteps(): number;
    /** @returns Modulating pressure range, units psi. */
    modulatingPressRange(): number;
    /** @returns Full-load brake horsepower, units hp. */
    powerFLBHP(): number;
    /** @returns Total package input power, units kW. */
    totPackageInputPower(): number;
    /** @returns Specific package power, units kW/100 acfm. */
    specPackagePower(): number;
    /** @returns No-load power for full modulation, units kW. */
    noLoadPowerFM(): number;
    /** @returns No-load power for unload control, units kW. */
    noLoadPowerUL(): number;
    /** @returns Maximum surge pressure, units psig. */
    maxSurgePressure(): number;
    /** @returns Maximum pressure surge flow, units acfm. */
    maxPressSurgeFlow(): number;
    /** @returns Minimum stonewall pressure, units psig. */
    minStonewallPressure(): number;
    /** @returns Minimum pressure stonewall flow, units acfm. */
    minPressStonewallFlow(): number;
    /** @returns Design surge flow, units acfm. */
    designSurgeFlow(): number;
    /** @returns Design inlet temperature, units degF. */
    designInTemp(): number;
    /** @returns Design inlet pressure, units psia. */
    designInPressure(): number;
    /** @returns Full-load current, units A. */
    ampsFL(): number;
    /** @returns Full-load efficiency, units %. */
    effFL(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Standard compressor calculation output.
 * @property kW_Calc Calculated compressor power, units kW.
 * @property C_Calc Calculated compressor capacity, units acfm.
 * @property PerkW Compressor power percentage, dimensionless percent or fraction.
 * @property C_Per Compressor capacity percentage, dimensionless percent or fraction.
 */
export declare class CompressorsOutput {
    /** Calculated compressor power, units kW. */
    kW_Calc: number;
    /** Calculated compressor capacity, units acfm. */
    C_Calc: number;
    /** Compressor power percentage, dimensionless percent or fraction. */
    PerkW: number;
    /** Compressor capacity percentage, dimensionless percent or fraction. */
    C_Per: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Compressor calculation output for blow-off control.
 * @param kW_Calc double, units kW
 * @property C_Calc double, units acfm
 * @property PerkW double, units percentage / fraction
 * @property C_Per double, units percentage / fraction
 * @property C_blow double, units acfm
 * @property blowPer double, units percentage / fraction
 */
export declare class CompressorsOutputBlowOff {
    /** Compressor power, units kW. */
    kW_Calc: number;
    /** Compressor capacity, units acfm. */
    C_Calc: number;
    /** Compressor percentage value, dimensionless percent or fraction. */
    PerkW: number;
    /** Compressor percentage value, dimensionless percent or fraction. */
    C_Per: number;
    /** Compressor capacity, units acfm. */
    C_blow: number;
    /** Compressor percentage value, dimensionless percent or fraction. */
    blowPer: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output for air leak reduction calculation.
 * @property C_lkred double, units acfm
 * @property C_usage_lkred double, units acfm
 * @property PerC_lkred double percentage / fraction
 */
export declare class ReduceAirLeaksOutput {
    /** Compressor capacity, units acfm. */
    C_lkred: number;
    /** Compressor capacity, units acfm. */
    C_usage_lkred: number;
    /** PerC_lkred, dimensionless percent / fraction. */
    PerC_lkred: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output for end-use efficiency improvement calculation.
 * @property C_af_red double, units acfm
 * @property CPer_af_red double percentage / fraction
 */
export declare class ImproveEndUseEfficiencyOutput {
    /** Compressor capacity, units acfm. */
    C_af_red: number;
    /** CPer_af_red, dimensionless percent / fraction. */
    CPer_af_red: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output for system air pressure reduction calculation.
 * @property P_fl_rpred double, units psig
 * @property kW_fl_rpadj double, units kW
 * @property C_usage_rpred double, units acfm
 * @property PerC_rpred double percentage / fraction
 */
export declare class ReduceSystemAirPressureOutput {
    /** Compressor pressure, units psig. */
    P_fl_rpred: number;
    /** Compressor power, units kW. */
    kW_fl_rpadj: number;
    /** Compressor capacity, units acfm. */
    C_usage_rpred: number;
    /** PerC_rpred, dimensionless percent / fraction. */
    PerC_rpred: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output for cascading set-point adjustment calculation.
 * @property kW_fl_adj double, units kW
 * @property C_usage_adj double, units acfm
 * @property PerC_adj double percentage / fraction
 */
export declare class AdjustCascadingSetPointOutput {
    /** Compressor power, units kW. */
    kW_fl_adj: number;
    /** Compressor capacity, units acfm. */
    C_usage_adj: number;
    /** PerC_adj, dimensionless percent / fraction. */
    PerC_adj: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output for pressure reduction savings calculation.
 * @property kW_savings double, units kW
 * @property kWh_savings double, units kWh
 * @property cost_savings double, units currency $$$
 */
export declare class PressureReductionSavingOutput {
    /** Compressor power, units kW. */
    kW_savings: number;
    /** Annual energy savings, units kWh/year. */
    kWh_savings: number;
    /** Annual cost savings, units $/year. */
    cost_savings: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Centrifugal compressor model with load/unload control. */
export declare class Compressors_Centrifugal_LoadUnload {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param kWNl No-load power, units kW.
     */
    constructor(kWFl: number, CFl: number, kWNl: number);

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     *
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity Capacity at full load, maximum, and minimum, units acfm.
     * @param dischargePressure Discharge pressure at full load, maximum, and minimum, units psig.
     * @param pFl Full-load pressure, units psig.
     * @param pMax Maximum pressure, units psig; not required for this control type.
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Centrifugal compressor model with modulation/unload control. */
export declare class Compressors_Centrifugal_ModulationUnload {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param kWNl No-load power, units kW.
     * @param CMax Maximum capacity, units acfm.
     * @param kWUl Unload power, units kW.
     * @param CUl Unload capacity, units acfm.
     */
    constructor(kWFl: number, CFl: number, kWNl: number, CMax: number, kWUl: number, CUl: number);

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity Capacity at full load, maximum, and minimum, units acfm.
     * @param dischargePressure Discharge pressure at full load, maximum, and minimum, units psig.
     * @param pFl Full-load pressure, units psig.
     * @param pMax Maximum pressure, units psig.
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;
    /** Adjusted maximum compressor capacity, units acfm. */
    C_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Centrifugal compressor model with blow-off control. */
export declare class Compressors_Centrifugal_BlowOff {
    /**
     * @param kWFl double, units kW
     * @param CFl double, units acfm
     * @param kWBlow double, units kW
     * @param CBlow double, units acfm
     *
     */
    constructor(kWFl: number, CFl: number, kWBlow: number, CBlow: number);

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @param blowPer Blow-off percentage, dimensionless percent or fraction.
     * @returns CompressorsOutputBlowOff
     */
    calculateFromPerkW_BlowOff(perkW: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutputBlowOff
     */
    calculateFromPerC_BlowOff(cPer: number): CompressorsOutputBlowOff;

    /**
     * @param kW Measured compressor power, units kW.
     * @param blowPer Blow-off percentage, dimensionless percent or fraction.
     * @returns CompressorsOutputBlowOff
     */
    calculateFromkWMeasured_BlowOff(kW: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutputBlowOff
     */
    calculateFromCMeasured_BlowOff(c: number): CompressorsOutputBlowOff;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @param blowPer Blow-off percentage, dimensionless percent or fraction.
     */
    calculateFromVIPFMeasured_BlowOff(v: number, i: number, pf: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param capacity Capacity at full load, maximum, and minimum, units acfm.
     * @param dischargePressure Discharge pressure at full load, maximum, and minimum, units psig.
     * @param pFl Full-load pressure, units psig.
     * @param pMax Maximum pressure, units psig; not required for this control type.
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for modulation without unload control. */
export declare class Compressors_ModulationWOUnload {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param kWNl No-load power, units kW.
     */
    constructor(kWFl: number, CFl: number, kWNl: number);

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     *
     * @param capacity Compressor capacity, units acfm.
     * @param fullLoadBhp Full-load brake horsepower, units hp.
     * @param polyExponent Polytropic exponent, dimensionless.
     * @param pRatedDischarge Rated discharge pressure, units psig.
     * @param pRatedIn Rated inlet pressure, units psig.
     * @param eff Compressor efficiency, units %.
     * @param pFl Full-load pressure, units psig.
     * @param pMax Maximum pressure, units psig.
     * @param pIn Inlet pressure, units psig.
     * @param presAdj Whether pressure adjustment is enabled.
     * @param pAtm Atmospheric pressure, units psia.
     */
    Pressure_InletCorrection(
        capacity: number,
        fullLoadBhp: number,
        polyExponent: number,
        pRatedDischarge: number,
        pRatedIn: number,
        eff: number,
        pFl: number,
        pMax: number,
        pIn: number,
        presAdj: boolean,
        pAtm: number
    ): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;
    /** Adjusted maximum compressor capacity, units acfm. */
    C_max_Adjusted: number;
    /** Adjusted full-load compressor power, units kW. */
    kW_fl_Adjusted: number;
    /** Adjusted maximum compressor power, units kW. */
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for start/stop control. */
export declare class Compressors_StartStop {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param kWPerMax Maximum power percentage, units %.
     * @param kWPerFl Full-load power percentage, units %.
     */
    constructor(kWFl: number, CFl: number, kWPerMax: number, kWPerFl: number);

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     *
     * @param capacity Compressor capacity, units acfm.
     * @param fullLoadBhp Full-load brake horsepower, units hp.
     * @param polyExponent Polytropic exponent, dimensionless.
     * @param pRatedDischarge Rated discharge pressure, units psig.
     * @param pRatedIn Rated inlet pressure, units psig.
     * @param eff Compressor efficiency, units %.
     * @param pFl Full-load pressure, units psig.
     * @param pMax Maximum pressure, units psig.
     * @param pIn Inlet pressure, units psig.
     * @param presAdj Whether pressure adjustment is enabled.
     * @param pAtm Atmospheric pressure, units psia.
     */
    Pressure_InletCorrection(
        capacity: number,
        fullLoadBhp: number,
        polyExponent: number,
        pRatedDischarge: number,
        pRatedIn: number,
        eff: number,
        pFl: number,
        pMax: number,
        pIn: number,
        presAdj: boolean,
        pAtm: number
    ): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;
    /** Adjusted maximum compressor capacity, units acfm. */
    C_max_Adjusted: number;
    /** Adjusted full-load compressor power, units kW. */
    kW_fl_Adjusted: number;
    /** Adjusted maximum compressor power, units kW. */
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for load/unload and related controls. */
export declare class Compressors_LoadUnload {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param CStorage Receiver storage capacity, units ft3.
     * @param kWMax Maximum power, units kW.
     * @param PFl Full-load pressure, units psig.
     * @param PMax Maximum pressure, units psig.
     * @param PMod Modulating pressure, units psig.
     * @param lfUl Unload load factor, dimensionless fraction.
     * @param PAtm Atmospheric pressure, units psia.
     * @param compType CompressorType
     * @param lubricantType Lubricant
     * @param cntrlType ControlType
     * @param kWNl No-load power, units kW.
     * @param perCUl Unload capacity percentage, units %.
     * @param tBlowdown Blowdown time, units sec.
     * @param PSumpUl Unload sump pressure, units psig.
     * @param noLoadPowerFM No-load power fraction for full modulation, dimensionless.
     */
    constructor(
        kWFl: number,
        CFl: number,
        CStorage: number,
        kWMax: number,
        PFl: number,
        PMax: number,
        PMod: number,
        lfUl: number,
        PAtm: number,
        compType: CompressorType,
        lubricantType: Lubricant,
        cntrlType: ControlType,
        kWNl: number,
        perCUl: number,
        tBlowdown: number,
        PSumpUl: number,
        noLoadPowerFM: number
    );

    /**
     * @param perkW Compressor power percentage, units %.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, units %.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity double, acfm
     * @param fullLoadBhp double, hp
     * @param polyExponent Polytropic exponent, dimensionless.
     * @param pRatedDischarge double, psig
     * @param pRatedIn double, psig
     * @param eff Compressor efficiency, units %.
     * @param pFl double, psig
     * @param pMax double, psig
     * @param pIn double, psig
     * @param presAdj Whether pressure adjustment is enabled.
     * @param pAtm double, psia
     */
    Pressure_InletCorrection(
        capacity: number,
        fullLoadBhp: number,
        polyExponent: number,
        pRatedDischarge: number,
        pRatedIn: number,
        eff: number,
        pFl: number,
        pMax: number,
        pIn: number,
        presAdj: boolean,
        pAtm: number
    ): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;
    /** Adjusted maximum compressor capacity, units acfm. */
    C_max_Adjusted: number;
    /** Adjusted full-load compressor power, units kW. */
    kW_fl_Adjusted: number;
    /** Adjusted maximum compressor power, units kW. */
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Variable-frequency-drive compressor model. */
export declare class Compressor_VFD {
    /**
     * @param fullLoadPower Full-load power, units kW.
     * @param midTurndownPower Mid-turndown power, units kW.
     * @param turndownPower Turndown power, units kW.
     * @param noLoadPower No-load power, units kW.
     * @param capacityFullFload Full-load capacity, units acfm.
     * @param midTurndownAirflow Mid-turndown airflow, units acfm.
     * @param turndownAirflow Turndown airflow, units acfm.
     */
    constructor(
        fullLoadPower: number,
        midTurndownPower: number,
        turndownPower: number,
        noLoadPower: number,
        capacityFullFload: number,
        midTurndownAirflow: number,
        turndownAirflow: number
    );

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for modulation with unload control. */
export declare class Compressors_ModulationWithUnload {
    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param CStorage Receiver storage capacity, units ft3.
     * @param kWMax Maximum power, units kW.
     * @param kWNl No-load power, units kW.
     * @param PFl Full-load pressure, units psig.
     * @param PMax Maximum pressure, units psig.
     * @param PMod Modulating pressure, units psig.
     * @param PAtm Atmospheric pressure, units psia.
     * @param perCUl Unload capacity percentage, units %.
     * @param cntrlType ControlType
     * @param tBlowdown Blowdown time, units sec.
     * @param PSumpUl Unload sump pressure, units psig.
     * @param noLoadPowerFM No-load power fraction for full modulation, dimensionless.
     * @param kWUl Unload power, units kW.
     * @param PUl Unload pressure, units psig.
     * @param CUl Unload capacity, units acfm.
     */
    constructor(
        kWFl: number,
        CFl: number,
        CStorage: number,
        kWMax: number,
        kWNl: number,
        PFl: number,
        PMax: number,
        PMod: number,
        PAtm: number,
        perCUl: number,
        cntrlType: ControlType,
        tBlowdown: number,
        PSumpUl: number,
        noLoadPowerFM: number,
        kWUl: number,
        PUl: number,
        CUl: number
    );

    /**
     * @param kWFl Full-load power, units kW.
     * @param CFl Full-load capacity, units acfm.
     * @param CStorage Receiver storage capacity, units ft3.
     * @param kWMax Maximum power, units kW.
     * @param kWNl No-load power, units kW.
     * @param PFl Full-load pressure, units psig.
     * @param PMax Maximum pressure, units psig.
     * @param PMod Modulating pressure, units psig.
     * @param PAtm Atmospheric pressure, units psia.
     * @param perCUl Unload capacity percentage, units %.
     * @param cntrlType ControlType
     * @param tBlowdown Blowdown time, units sec.
     * @param PSumpUl Unload sump pressure, units psig.
     * @param noLoadPowerFM No-load power fraction for full modulation, dimensionless.
     */
    constructor(
        kWFl: number,
        CFl: number,
        CStorage: number,
        kWMax: number,
        kWNl: number,
        PFl: number,
        PMax: number,
        PMod: number,
        PAtm: number,
        perCUl: number,
        cntrlType: ControlType,
        tBlowdown: number,
        PSumpUl: number,
        noLoadPowerFM: number
    );

    /**
     * @param perkW Compressor power percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer Compressor capacity percentage, dimensionless percent or fraction.
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW Measured compressor power, units kW.
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c Measured compressor capacity, units acfm.
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Measured voltage, units V.
     * @param i Measured current, units A.
     * @param pf Power factor, dimensionless.
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity double, acfm
     * @param fullLoadBhp double, hp
     * @param polyExponent Polytropic exponent, dimensionless.
     * @param pRatedDischarge double, psig
     * @param pRatedIn double, psig
     * @param eff Compressor efficiency, units %.
     * @param pFl double, psig
     * @param pMax double, psig
     * @param pIn double, psig
     * @param presAdj Whether pressure adjustment is enabled.
     * @param pAtm double, psia
     */
    Pressure_InletCorrection(
        capacity: number,
        fullLoadBhp: number,
        polyExponent: number,
        pRatedDischarge: number,
        pRatedIn: number,
        eff: number,
        pFl: number,
        pMax: number,
        pIn: number,
        presAdj: boolean,
        pAtm: number
    ): void;

    /** Adjusted full-load compressor capacity, units acfm. */
    C_fl_Adjusted: number;
    /** Adjusted maximum compressor capacity, units acfm. */
    C_max_Adjusted: number;
    /** Adjusted full-load compressor power, units kW. */
    kW_fl_Adjusted: number;
    /** Adjusted maximum compressor power, units kW. */
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates reduced air usage from leak reduction.
 * @param CFl Full-load capacity, units acfm.
 * @param CUsage Current air usage, units acfm.
 * @param CLk Leak air usage, units acfm.
 * @param perCLkred Leak reduction percentage, dimensionless percent or fraction.
 * @returns ReduceAirLeaksOutput
 */
export function ReduceAirLeaks(
    CFl: number,
    CUsage: number,
    CLk: number,
    perCLkred: number
): ReduceAirLeaksOutput;

/**
 * Calculates reduced air usage from end-use efficiency improvements.
 * @param CFl Full-load capacity, units acfm.
 * @param CUsage Current air usage, units acfm.
 * @param CAvgafRed Average air flow reduction, units acfm.
 * @returns ImproveEndUseEfficiencyOutput
 */
export function ImproveEndUseEfficiency(
    CFl: number,
    CUsage: number,
    CAvgafRed: number
): ImproveEndUseEfficiencyOutput;

/**
 * Calculates adjusted usage and power when system pressure is reduced.
 * @param CFl Full-load capacity, units acfm.
 * @param CUsage Current air usage, units acfm.
 * @param PFl Full-load pressure, units psig.
 * @param kWFl Full-load power, units kW.
 * @param PRpred Reduced system pressure, units psig.
 * @param PAlt Site elevation pressure adjustment, units psig.
 * @param PAtm Atmospheric pressure, units psia.
 * @returns ReduceSystemAirPressureOutput
 */
export function ReduceSystemAirPressure(
    CFl: number,
    CUsage: number,
    PFl: number,
    kWFl: number,
    PRpred: number,
    PAlt?: number,
    PAtm?: number
): ReduceSystemAirPressureOutput;

/**
 * Calculates adjusted usage and power for cascading set-point changes.
 * @param CFl Full-load capacity, units acfm.
 * @param CUsage Current air usage, units acfm.
 * @param PFl Full-load pressure, units psig.
 * @param kWFl Full-load power, units kW.
 * @param PFlAdj Adjusted full-load pressure, units psig.
 * @param PAlt Site elevation pressure adjustment, units psig.
 * @param PAtm Atmospheric pressure, units psia.
 * @returns AdjustCascadingSetPointOutput
 */
export function AdjustCascadingSetPoint(
    CFl: number,
    CUsage: number,
    PFl: number,
    kWFl: number,
    PFlAdj: number,
    PAlt?: number,
    PAtm?: number
): AdjustCascadingSetPointOutput;

/**
 * Calculates kW, energy, and cost savings from discharge pressure reduction.
 * @param operatingHours Annual operating hours, units hr/year.
 * @param costPerkWh Electricity unit cost, units $/kWh.
 * @param kWFlRated Rated full-load power, units kW.
 * @param PFlRated Rated full-load pressure, units psig.
 * @param dischargePresBaseline Baseline discharge pressure, units psig.
 * @param dischargePresMod Modified discharge pressure, units psig.
 * @param PAlt Site elevation pressure adjustment, units psig.
 * @param PAtm Atmospheric pressure, units psia.
 * @returns PressureReductionSavingOutput
 */
export function PressureReductionSaving(
    operatingHours: number,
    costPerkWh: number,
    kWFlRated: number,
    PFlRated: number,
    dischargePresBaseline: number,
    dischargePresMod: number,
    PAlt?: number,
    PAtm?: number
): PressureReductionSavingOutput;

/**
 * Calculates adjusted full-load compressor power for a discharge pressure.
 * @param kWFlRated Rated full-load power, units kW.
 * @param PFlRated Rated full-load pressure, units psig.
 * @param PDischarge Discharge pressure, units psig.
 * @param PAlt Site elevation pressure adjustment, units psig.
 * @param PAtm Atmospheric pressure, units psia.
 * @returns Adjusted full-load compressor power, units kW.
 */
export function kWAdjusted(
    kWFlRated: number,
    PFlRated: number,
    PDischarge: number,
    PAlt?: number,
    PAtm?: number
): number;

export type CompressorsCalcModule = {
    CompressorType: typeof CompressorType;
    ControlType: typeof ControlType;
    Stage: typeof Stage;
    Lubricant: typeof Lubricant;
    Modulation: typeof Modulation;
    ComputeFrom: typeof ComputeFrom;
    CompressorsData: typeof CompressorsData;
    CompressorsOutput: typeof CompressorsOutput;
    CompressorsOutputBlowOff: typeof CompressorsOutputBlowOff;
    ReduceAirLeaksOutput: typeof ReduceAirLeaksOutput;
    ImproveEndUseEfficiencyOutput: typeof ImproveEndUseEfficiencyOutput;
    ReduceSystemAirPressureOutput: typeof ReduceSystemAirPressureOutput;
    AdjustCascadingSetPointOutput: typeof AdjustCascadingSetPointOutput;
    PressureReductionSavingOutput: typeof PressureReductionSavingOutput;
    Compressors_Centrifugal_LoadUnload: typeof Compressors_Centrifugal_LoadUnload;
    Compressors_Centrifugal_ModulationUnload: typeof Compressors_Centrifugal_ModulationUnload;
    Compressors_Centrifugal_BlowOff: typeof Compressors_Centrifugal_BlowOff;
    Compressors_ModulationWOUnload: typeof Compressors_ModulationWOUnload;
    Compressors_StartStop: typeof Compressors_StartStop;
    Compressors_LoadUnload: typeof Compressors_LoadUnload;
    Compressor_VFD: typeof Compressor_VFD;
    Compressors_ModulationWithUnload: typeof Compressors_ModulationWithUnload;

    ReduceAirLeaks: typeof ReduceAirLeaks;
    ImproveEndUseEfficiency: typeof ImproveEndUseEfficiency;
    ReduceSystemAirPressure: typeof ReduceSystemAirPressure;
    AdjustCascadingSetPoint: typeof AdjustCascadingSetPoint;
    PressureReductionSaving: typeof PressureReductionSaving;
    kWAdjusted: typeof kWAdjusted;

    AdjustDischargePressureLoadUnload: typeof Compressors_Centrifugal_LoadUnload.prototype.AdjustDischargePressure;
    AdjustDischargePressureModulationUnload: typeof Compressors_Centrifugal_ModulationUnload.prototype.AdjustDischargePressure;
    AdjustDischargePressureBlowOff: typeof Compressors_Centrifugal_BlowOff.prototype.AdjustDischargePressure;
};
