import { Drive } from "../motor/motorEnum";

/**
 * Pump style classification used by pump/fan calculators.
 */
export enum PumpStyle {
    END_SUCTION_SLURRY = 0,
    END_SUCTION_SEWAGE = 1,
    END_SUCTION_STOCK = 2,
    END_SUCTION_SUBMERSIBLE_SEWAGE = 3,
    API_DOUBLE_SUCTION = 4,
    MULTISTAGE_BOILER_FEED = 5,
    END_SUCTION_ANSI_API = 6,
    AXIAL_FLOW = 7,
    DOUBLE_SUCTION = 8,
    VERTICAL_TURBINE = 9,
    LARGE_END_SUCTION = 10,
    SPECIFIED_OPTIMAL_EFFICIENCY = 11
}

/**
 * Pump specific speed mode.
 */
export enum SpecificSpeed {
    FIXED_SPEED = 0,
    NOT_FIXED_SPEED = 1
}

/**
 * Output of mover shaft power calculation.
 */
export declare class MoverShaftPowerOutput {
    /**
     * Constructor for MoverShaftPowerOutput
     * @param moverShaftPower double, motor shaft power in hp
     * @param driveEfficiency efficiency of the drive defined as a fraction, unitless
     */
    constructor(moverShaftPower: number, driveEfficiency: number);

    moverShaftPower: number;
    driveEfficiency: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates pump mover shaft power from motor shaft power and drive type.
 */
export declare class MoverShaftPower {
    /**
     * @param motorShaftPower double, motor shaft power in hp
     * @param drive Drive enum, drive type
     * @param specifiedEfficiency double, user-specified drive efficiency
     */
    constructor(motorShaftPower: number, drive: Drive, specifiedEfficiency: number);

    /**
     * Calculates the pump shaft power
     * @returns {@link MoverShaftPowerOutput} object containing the pump shaft power and drive efficiency
     */
    calculate(): MoverShaftPowerOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates optimal specific speed correction factor.
 */
export declare class OptimalSpecificSpeedCorrection {
    /**
     * @param style PumpStyle enum, type of pump speed from either fixed or not fixed.
     * @param specificSpeed double, specific speed in rpm*sqrt(gpm)/((ft/s)^(3/2))
     */
    constructor(style: PumpStyle, specificSpeed: number);

    /**
     * Calculates the optimal specific speed correction
     * @returns double, optimal specific speed correction as %
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Output of pump efficiency calculation.
 */
export declare class PumpEfficiencyResults {
    /**
     * Constructor for PumpEfficiencyResults
     * @param average
     * @param max
     */
    constructor(average: number, max: number);

    average: number;
    max: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates achievable/maximum pump efficiency values.
 */
export declare class PumpEfficiency {
    /**
     * @param style PumpStyle enum
     * @param pumpEfficiency double, operating pump efficiency
     * @param rpm double, pump speed in RPM
     * @param kinematicViscosity double, fluid kinematic viscosity
     * @param stageCount double, number of stages
     * @param flowRate double, flow rate in gpm
     * @param head double, pump head in ft
     */
    constructor(
        style: PumpStyle,
        pumpEfficiency: number,
        rpm: number,
        kinematicViscosity: number,
        stageCount: number,
        flowRate: number,
        head: number
    );

    /**
     * Calculates pump efficiency
     * @returns {@link PumpEfficiencyResults} object containing the average and maximum pump efficiency values
     */
    calculate(): PumpEfficiencyResults;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type PumpFanModule = {
    PumpStyle: typeof PumpStyle;
    SpecificSpeed: typeof SpecificSpeed;
    MoverShaftPower: typeof MoverShaftPower;
    MoverShaftPowerOutput: typeof MoverShaftPowerOutput;
    OptimalSpecificSpeedCorrection: typeof OptimalSpecificSpeedCorrection;
    PumpEfficiency: typeof PumpEfficiency;
    PumpEfficiencyResults: typeof PumpEfficiencyResults;
};
