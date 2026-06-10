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
 * @property idCompType integer
 * @property model string
 * @property hp double, watt
 * @property ratedCapacity double, scf/min
 * @property ratedPressure double, lb/in2
 * @property maxFllFlowPressure double, lb/in2
 * @property idControlType integer
 * @property unloadPoint double, lb/in2
 * @property minULSumpPressure double, lb/in2
 * @property blowdownTime double, minute
 * @property unloadSteps double, %
 * @property modulatingPressRange double, lb/in2
 * @property powerFLBHP double, kW
 * @property totPackageInputPower double, kW
 * @property specPackagePower double, kW
 * @property noLoadPowerFM double, kW
 * @property noLoadPowerUL double, kW
 * @property maxSurgePressure double, lb/in2
 * @property maxPressSurgeFlow double, lb/in2
 * @property minStonewallPressure double, lb/in2
 * @property minPressStonewallFlow double, lb/in2
 * @property designSurgeFlow double, lb/in2
 * @property designInTemp double, F
 * @property designInPressure double, lb/in2
 * @property ampsFL double
 * @property effFL double, %
 */
export declare class CompressorsData {
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

    setID(id: number): void;
    ID(): number;
    idCompType(): number;
    model(): string;
    hp(): number;
    ratedCapacity(): number;
    ratedPressure(): number;
    maxFullFlowPressure(): number;
    idControlType(): number;
    unloadPoint(): number;
    minULSumpPressure(): number;
    blowdownTime(): number;
    unloadSteps(): number;
    modulatingPressRange(): number;
    powerFLBHP(): number;
    totPackageInputPower(): number;
    specPackagePower(): number;
    noLoadPowerFM(): number;
    noLoadPowerUL(): number;
    maxSurgePressure(): number;
    maxPressSurgeFlow(): number;
    minStonewallPressure(): number;
    minPressStonewallFlow(): number;
    designSurgeFlow(): number;
    designInTemp(): number;
    designInPressure(): number;
    ampsFL(): number;
    effFL(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Standard compressor calculation output.
 * @param kW_Calc double
 * @param C_Calc double
 * @param PerkW double
 * @param C_Per double
 *      Units for power kW and Capacity acfm
 */
export declare class CompressorsOutput {
    kW_Calc: number;
    C_Calc: number;
    PerkW: number;
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
    kW_Calc: number;
    C_Calc: number;
    PerkW: number;
    C_Per: number;
    C_blow: number;
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
    C_lkred: number;
    C_usage_lkred: number;
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
    C_af_red: number;
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
    P_fl_rpred: number;
    kW_fl_rpadj: number;
    C_usage_rpred: number;
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
    kW_fl_adj: number;
    C_usage_adj: number;
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
    kW_savings: number;
    kWh_savings: number;
    cost_savings: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Centrifugal compressor model with load/unload control. */
export declare class Compressors_Centrifugal_LoadUnload {
    /**
     * @param kWFl double, kW
     * @param CFl  double, acfm
     * @param kWNl kW_nl double, kW
     */
    constructor(kWFl: number, CFl: number, kWNl: number);

    /**
     * @param perkW double
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     *
     * @param c double Capacity
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double Power Factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity array of doubles Capacity at full load, max and min
     * @param dischargePressure array of doubles DischargePressure at full load, max and min
     * @param pFl double
     * @param pMax double, not required for this control type
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    C_fl_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Centrifugal compressor model with modulation/unload control. */
export declare class Compressors_Centrifugal_ModulationUnload {
    /**
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param kWNl double, kW
     * @param CMax double, acfm
     * @param kWUl double, kW
     * @param CUl double, acfm
     */
    constructor(kWFl: number, CFl: number, kWNl: number, CMax: number, kWUl: number, CUl: number);

    /**
     * @param perkW
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double Power Factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity array of doubles Capacity at full load, max and min
     * @param dischargePressure array of doubles DischargePressure at full load, max and min
     * @param pFl double
     * @param pMax double
     *      Units for power kW and Capacity acfm
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    C_fl_Adjusted: number;
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
     * @param perkW double
     * @param blowPer double
     * @returns CompressorsOutputBlowOff
     */
    calculateFromPerkW_BlowOff(perkW: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param cPer double, units percentage / fraction
     * @returns CompressorsOutputBlowOff
     */
    calculateFromPerC_BlowOff(cPer: number): CompressorsOutputBlowOff;

    /**
     * @param kW double, units kW
     * @param blowPer double, units percentage / fraction
     * @returns CompressorsOutputBlowOff
     */
    calculateFromkWMeasured_BlowOff(kW: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param c double, capacity units acfm
     * @returns CompressorsOutputBlowOff
     */
    calculateFromCMeasured_BlowOff(c: number): CompressorsOutputBlowOff;

    /**
     * @param v Voltage double
     * @param i Current double, amps
     * @param pf Power Factor double, percentage / fraction
     * @param blowPer double, percentage / fraction
     */
    calculateFromVIPFMeasured_BlowOff(v: number, i: number, pf: number, blowPer: number): CompressorsOutputBlowOff;

    /**
     * @param capacity array of doubles Capacity at full load, max and min
     * @param dischargePressure array of doubles DischargePressure at full load, max and min
     * @param pFl double
     * @param pMax double, not required for this control type
     *      Units for power kW and Capacity acfm
     */
    AdjustDischargePressure(capacity: number[], dischargePressure: number[], pFl: number, pMax: number): void;

    C_fl_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for modulation without unload control. */
export declare class Compressors_ModulationWOUnload {
    /**
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param kWNl double, kW
     */
    constructor(kWFl: number, CFl: number, kWNl: number);

    /**
     * @param perkW double
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v Voltage double
     * @param i Current double
     * @param pf Power Factor double
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     *
     * @param capacity double
     * @param fullLoadBhp double
     * @param polyExponent double
     * @param pRatedDischarge double
     * @param pRatedIn double
     * @param eff double
     * @param pFl double
     * @param pMax double
     * @param pIn double
     * @param presAdj double
     * @param pAtm double
     *      Units for power kW and Capacity acfm
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

    C_fl_Adjusted: number;
    C_max_Adjusted: number;
    kW_fl_Adjusted: number;
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for start/stop control. */
export declare class Compressors_StartStop {
    /**
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param kWPerMax double, percent
     * @param kWPerFl double, percent
     */
    constructor(kWFl: number, CFl: number, kWPerMax: number, kWPerFl: number);

    /**
     * @param perkW double
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double Power Factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     *
     * @param capacity double
     * @param fullLoadBhp double
     * @param polyExponent double
     * @param pRatedDischarge double
     * @param pRatedIn double
     * @param eff double
     * @param pFl double
     * @param pMax double
     * @param pIn double
     * @param presAdj double
     * @param pAtm double
     *      Units for power kW and Capacity acfm
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

    C_fl_Adjusted: number;
    C_max_Adjusted: number;
    kW_fl_Adjusted: number;
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for load/unload and related controls. */
export declare class Compressors_LoadUnload {
    /**
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param CStorage double, ft3
     * @param kWMax double, kW
     * @param PFl double, psig
     * @param PMax double, psig
     * @param PMod double, psig
     * @param lfUl double, decimal
     * @param PAtm double, psia
     * @param compType CompressorType
     * @param lubricantType Lubricant
     * @param cntrlType ControlType
     * @param kWNl double, kW
     * @param perCUl double, %
     * @param tBlowdown double, sec
     * @param PSumpUl double, psig
     * @param noLoadPowerFM double, decimal
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
     * @param perkW double, %
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double, %
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double, kW
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double, acfm
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double Power Factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity double, acfm
     * @param fullLoadBhp double, hp
     * @param polyExponent double
     * @param pRatedDischarge double, psig
     * @param pRatedIn double, psig
     * @param eff double, %
     * @param pFl double, psig
     * @param pMax double, psig
     * @param pIn double, psig
     * @param presAdj double, psig
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

    C_fl_Adjusted: number;
    C_max_Adjusted: number;
    kW_fl_Adjusted: number;
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Variable-frequency-drive compressor model. */
export declare class Compressor_VFD {
    /**
     * @param fullLoadPower double
     * @param midTurndownPower double
     * @param turndownPower double
     * @param noLoadPower double
     * @param capacityFullFload double
     * @param midTurndownAirflow double
     * @param turndownAirflow double
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
     * @param perkW double
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double power factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Compressor model for modulation with unload control. */
export declare class Compressors_ModulationWithUnload extends Compressors_LoadUnload {
    /**
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param CStorage double, ft3
     * @param kWMax double, kW
     * @param kWNl double, kW
     * @param PFl double, psig
     * @param PMax double, psig
     * @param PMod double, psig
     * @param PAtm double, psia
     * @param perCUl double, %
     * @param cntrlType ControlType
     * @param tBlowdown double, sec
     * @param PSumpUl double, psig
     * @param noLoadPowerFM double, decimal
     * @param kWUl double, kW
     * @param PUl double, psig
     * @param CUl double, acfm
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
     * @param kWFl double, kW
     * @param CFl double, acfm
     * @param CStorage double, ft3
     * @param kWMax double, kW
     * @param kWNl double, kW
     * @param PFl double, psig
     * @param PMax double, psig
     * @param PMod double, psig
     * @param PAtm double, psia
     * @param perCUl double, %
     * @param cntrlType ControlType
     * @param tBlowdown double, sec
     * @param PSumpUl double, psig
     * @param noLoadPowerFM double, decimal
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
     * @param perkW double
     * @returns CompressorsOutput
     */
    calculateFromPerkW(perkW: number): CompressorsOutput;

    /**
     * @param cPer double
     * @returns CompressorsOutput
     */
    calculateFromPerC(cPer: number): CompressorsOutput;

    /**
     * @param kW double
     * @returns CompressorsOutput
     */
    calculateFromkWMeasured(kW: number): CompressorsOutput;

    /**
     * @param c double
     * @returns CompressorsOutput
     */
    calculateFromCMeasured(c: number): CompressorsOutput;

    /**
     * @param v double Voltage
     * @param i double Current
     * @param pf double double Power Factor
     * @returns CompressorsOutput
     */
    calculateFromVIPFMeasured(v: number, i: number, pf: number): CompressorsOutput;

    /**
     * @param capacity double, acfm
     * @param fullLoadBhp double, hp
     * @param polyExponent double
     * @param pRatedDischarge double, psig
     * @param pRatedIn double, psig
     * @param eff double, %
     * @param pFl double, psig
     * @param pMax double, psig
     * @param pIn double, psig
     * @param presAdj double, psig
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

    C_fl_Adjusted: number;
    C_max_Adjusted: number;
    kW_fl_Adjusted: number;
    kW_max_Adjusted: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates reduced air usage from leak reduction.
 * @property CFl double, units acfm
 * @property CUsage double, units acfm
 * @property CLk double, units acfm
 * @property perCLkred double percentage / fraction
 */
export function ReduceAirLeaks(
    CFl: number,
    CUsage: number,
    CLk: number,
    perCLkred: number
): ReduceAirLeaksOutput;

/**
 * Calculates reduced air usage from end-use efficiency improvements.
 * @property CFl double, units acfm
 * @property CUsage double, units acfm
 * @property CAvgafRed double, units acfm
 */
export function ImproveEndUseEfficiency(
    CFl: number,
    CUsage: number,
    CAvgafRed: number
): ImproveEndUseEfficiencyOutput;

/**
 * Calculates adjusted usage and power when system pressure is reduced.
 * @property CFl double, units acfm
 * @property CUsage double, units acfm
 * @property PFl double, units psig
 * @property kWFl double, units kW
 * @property PRpred double, units psig
 * @property PAlt double, units psig
 * @property PAtm double, units psia
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
 * @property CFl double, units acfm
 * @property CUsage double, units acfm
 * @property PFl double, units psig
 * @property kWFl double, units kW
 * @property PFlAdj double, units psig
 * @property PAlt double, units psig
 * @property PAtm double, units psia
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
 * @property operatingHours double
 * @property costPerkWh double, units /kWh
 * @property kWFlRated double, units kW
 * @property PFlRated double, units psig
 * @property dischargePresBaseline double, units psig
 * @property dischargePresMod double, units psig
 * @property PAlt double, units psig
 * @property PAtm double, units psig
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
 * @property kWFlRated double, units kW
 * @property PFlRated double, units psig
 * @property PDischarge double, units psig
 * @property PAlt double, units psig
 * @property PAtm double, units psia
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
