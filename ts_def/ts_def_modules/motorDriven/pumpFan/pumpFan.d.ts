/**
 * Pump/Fan helper calculations.
 *
 * Provides the remaining legacy pump efficiency calculator.
 */

import type { PumpStyle } from "../pump/pump_enums";

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
    PumpEfficiency: typeof PumpEfficiency;
    PumpEfficiencyResults: typeof PumpEfficiencyResults;
};
