/** Stateless three-phase motor real electrical input power calculation. */

/**
 * Calculates real electrical input power for balanced sinusoidal three-phase conditions.
 * Uses the supplied voltage directly without efficiency adjustments or input validation.
 * Signed and out-of-range inputs retain their arithmetic result; no clamping is performed.
 *
 * @param ratedVoltage RMS line-to-line motor voltage, units V. Use the voltage appropriate
 * to the operating point, which may differ from the nameplate rating; physically nonnegative.
 * @param motorCurrent RMS motor line current, units A; physically nonnegative.
 * @param powerFactor Real-to-apparent power ratio, dimensionless fraction, physically 0-1.
 * @returns Real electrical input power, units kW; distinct from motor shaft power.
 * The scalar inputs and result require no delete() calls.
 */
export declare function calculateMotorPower(ratedVoltage: number, motorCurrent: number, powerFactor: number): number;

/** Runtime function contributed by the motor-power binding. */
export type MotorPowerModule = {
    calculateMotorPower: typeof calculateMotorPower;
};
