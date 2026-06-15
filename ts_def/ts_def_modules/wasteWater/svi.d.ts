/**
 * Sludge Volume Index (SVI) calculations.
 *
 * Performs state-point analysis for activated sludge settling behavior and
 * returns clarifier loading metrics with graph data points.
 */

import { GraphDataV } from "../binding/registered_vectors";

/**
 * Enumeration selecting which SVI parameter is used as the known input.
 */
export enum SVIParameter {
    SVISN = 0,
    SVIGN = 1,
    SVIGS = 2,
    SVISS = 3,
    VoK = 4,
}

/**
 * Graph data point for solids concentration and solids flux.
 *
 * @property SolidsConcentration double
 * @property SolidsFlux double
 */
export declare class GraphDataPoint {
    /** Solids concentration value */
    SolidsConcentration: number;
    /** Solids flux value */
    SolidsFlux: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link SludgeVolumeIndex.calculate}.
 *
 * @property TotalAreaClarifier double, units m2
 * @property SurfaceOverflow double, units l/m2h
 * @property AppliedSolidsLoading double, units kf/m2h
 * @property RasConcentration double, units kg/L
 * @property UnderFlowRateX2 double, units g/L
 * @property UnderFlowRateY1 double, units kg/m2h
 * @property OverFlowRateX2 double, units g/L
 * @property OverFlowRateY2 double, units kg/m2h
 * @property StatePointX double
 * @property StatePointY double
 * @property GraphData {@link GraphDataV}, computed graph data points
 */
export interface SludgeVolumeIndexOutput {
    /** Total clarifier area, units m2 */
    TotalAreaClarifier: number;
    /** Surface overflow, units l/m2h */
    SurfaceOverflow: number;
    /** Applied solids loading, units kf/m2h */
    AppliedSolidsLoading: number;
    /** RAS concentration, units kg/L */
    RasConcentration: number;
    /** Underflow rate X2, units g/L */
    UnderFlowRateX2: number;
    /** Underflow rate Y1, units kg/m2h */
    UnderFlowRateY1: number;
    /** Overflow rate X2, units g/L */
    OverFlowRateX2: number;
    /** Overflow rate Y2, units kg/m2h */
    OverFlowRateY2: number;
    /** State point X */
    StatePointX: number;
    /** State point Y */
    StatePointY: number;
    /** Computed graph data points */
    GraphData: GraphDataV;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Sludge Volume Index calculator.
 */
export declare class SludgeVolumeIndex {
    /**
     * Create an SVI calculator using process and clarifier parameters.
     *
     * @param sviParameter {@link SVIParameter}
     * @param sviValue double, units L/g
     * @param numberOfClarifiers double
     * @param areaOfClarifier double, units m2
     * @param MLSS double, units kg/L
     * @param influentFlow double, units L/h
     * @param rasFlow double, units L/h
     * @param sludgeSettlingVelocity double, units m/h
     */
    constructor(
        sviParameter: SVIParameter,
        sviValue: number,
        numberOfClarifiers: number,
        areaOfClarifier: number,
        MLSS: number,
        influentFlow: number,
        rasFlow: number,
        sludgeSettlingVelocity: number
    );

    /**
     * Calculate sludge volume index results.
     *
     * @returns {@link SludgeVolumeIndexOutput}
     */
    calculate(): SludgeVolumeIndexOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type SviModule = {
    SVIParameter: typeof SVIParameter;
    GraphDataPoint: typeof GraphDataPoint;
    SludgeVolumeIndexOutput: SludgeVolumeIndexOutput;
    SludgeVolumeIndex: typeof SludgeVolumeIndex;
};
