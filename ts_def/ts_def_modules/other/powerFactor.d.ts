/**
 * Power Factor (pf) Calculations - Power Triangle
 *
 * Calculates Apparent Power S, Real Power P, Reactive Power Q,
 * Phase Angle, Power Factor pf, and Capacitance based on two known inputs.
 *
 * Input combination must include two known parameters:
 *   1. Apparent Power + Real Power | Reactive Power | Phase Angle | Power Factor
 *   2. Real Power    + Reactive Power | Phase Angle | Power Factor
 *   3. Reactive Power + Phase Angle | Power Factor
 */

/**
 * Enumeration representing which two input parameters are provided to the calculation.
 *
 * Order of the enum values mirrors the order of `input1` and `input2` in {@link PowerFactor.calculate}.
 * For example, `ApparentPower_RealPower` means `input1` is Apparent Power and `input2` is Real Power.
 */
export enum PowerFactorModeType {
    ApparentPower_RealPower = 0,
    ApparentPower_ReactivePower = 1,
    ApparentPower_PhaseAngle = 2,
    ApparentPower_PowerFactor = 3,
    RealPower_ReactivePower = 4,
    RealPower_PhaseAngle = 5,
    RealPower_PowerFactor = 6,
    ReactivePower_PhaseAngle = 7,
    ReactivePower_PowerFactor = 8,
}

/**
 * Result object returned by {@link PowerFactor.calculate}.
 *
 * @property realPower double, units kW
 * @property reactivePower double, units kVAr
 * @property apparentPower double, units kVA
 * @property powerFactor double, units % as decimal value (0 - 1)
 * @property phaseAngle double, units deg
 * @property realDemand double, units kW
 * @property demandPenalty double, units kW
 * @property proposedReactivePower double, units kVAr - reactive power required to reach the target power factor
 * @property proposedCapacitance double, units kVAr - capacitance required to correct to the target power factor
 */
export interface PowerFactorOutput {
    /** Real Power P, units kW */
    realPower: number;
    /** Reactive Power Q, units kVAr */
    reactivePower: number;
    /** Apparent Power S, units kVA */
    apparentPower: number;
    /** Power Factor pf, units % as decimal value (0 - 1) */
    powerFactor: number;
    /** Phase Angle, units deg */
    phaseAngle: number;
    /** Real Demand, units kW */
    realDemand: number;
    /** Demand Penalty, units kW */
    demandPenalty: number;
    /** Proposed Reactive Power needed to reach target power factor, units kVAr */
    proposedReactivePower: number;
    /** Proposed Capacitance needed to reach target power factor, units kVAr */
    proposedCapacitance: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Power Factor calculator.
 *
 * Computes all power-triangle quantities (P, Q, S, Angle, pf) and the capacitance
 * correction required to reach a target power factor, given any two known
 * power-triangle parameters.
 */
export declare class PowerFactor {
    /** Default constructor - no arguments required. */
    constructor();

    /**
     * Perform power factor calculations.
     *
     * @param mode {@link PowerFactorModeType} - selects which two input parameters are supplied.
     * @param input1 double - first known parameter (see mode for interpretation):
     *   - Apparent Power: units kVA
     *   - Real Power: units kW
     *   - Reactive Power: units kVAr
     * @param input2 double - second known parameter (see mode for interpretation):
     *   - Real Power: units kW
     *   - Reactive Power: units kVAr
     *   - Phase Angle: units deg
     *   - Power Factor: units % as decimal value (0 - 1)
     * @param inputPowerFactor double, Minimum Required / Target Power Factor as decimal (default 0.95)
     * @returns {@link PowerFactorOutput}
     */
    calculate(
        mode: PowerFactorModeType,
        input1: number,
        input2: number,
        inputPowerFactor?: number
    ): PowerFactorOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type PowerFactorModule = {
    PowerFactorModeType: typeof PowerFactorModeType;
    PowerFactorOutput: PowerFactorOutput;
    PowerFactor: typeof PowerFactor;
};
