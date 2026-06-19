import { Drive } from "../motor/motorEnum";

/**
 * Pump/Fan helper calculations.
 *
 * Provides calculators for mover shaft power, specific speed correction,
 * and pump efficiency metrics.
 */

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
 * Result object returned by {@link MoverShaftPower.calculate}.
 *
 * @property moverShaftPower double, mover shaft power in hp
 * @property driveEfficiency Drive efficiency, dimensionless fraction.
 */
export declare class MoverShaftPowerOutput {
    /**
     * Constructor for MoverShaftPowerOutput
     * @param moverShaftPower Mover shaft power, units hp.
     * @param driveEfficiency Drive efficiency, dimensionless fraction.
     */
    constructor(moverShaftPower: number, driveEfficiency: number);

    /** Mover shaft power, units hp */
    moverShaftPower: number;
    /** Drive efficiency, dimensionless fraction. */
    driveEfficiency: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates pump mover shaft power from motor shaft power and drive type.
 */
export declare class MoverShaftPower {
    /**
     * @param motorShaftPower Motor shaft power, units hp.
     * @param drive Drive enum, drive type
     * @param specifiedEfficiency User-specified drive efficiency, dimensionless fraction.
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
     * @param specificSpeed Specific speed, units rpm*sqrt(gpm)/(ft^(3/4)).
     */
    constructor(style: PumpStyle, specificSpeed: number);

    /**
     * Calculates the optimal specific speed correction
     * @returns Optimal specific speed correction, units %.
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link PumpEfficiency.calculate}.
 *
 * @property average Achievable average pump efficiency, dimensionless fraction.
 * @property max Maximum pump efficiency, dimensionless fraction.
 */
export declare class PumpEfficiencyResults {
    /**
     * Constructor for PumpEfficiencyResults
     * @param average Achievable average pump efficiency, dimensionless fraction.
     * @param max Maximum pump efficiency, dimensionless fraction.
     */
    constructor(average: number, max: number);

    /** Achievable average pump efficiency, dimensionless fraction. */
    average: number;
    /** Maximum pump efficiency, dimensionless fraction. */
    max: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Calculates achievable and maximum pump efficiency values.
 */
export declare class PumpEfficiency {
    /**
     * @param style PumpStyle enum
     * @param pumpEfficiency Operating pump efficiency, dimensionless fraction.
     * @param rpm Pump speed, units rpm.
     * @param kinematicViscosity Fluid kinematic viscosity, units cSt.
     * @param stageCount Pump stage count.
     * @param flowRate Flow rate, units gpm.
     * @param head Pump head, units ft.
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
     * Calculates pump efficiency.
     * @returns {@link PumpEfficiencyResults} object containing average and maximum pump efficiency, dimensionless fractions.
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
