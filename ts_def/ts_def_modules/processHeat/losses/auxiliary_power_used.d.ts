/**
 * Auxiliary Power Used calculations.
 *
 * Calculates the auxiliary power used by electrical systems (motors and other
 * auxiliary systems) associated with process heating equipment.
 *
 */

/**
 * Calculate auxiliary power used by electrical systems associated with process heating equipment.
 *
 * Computes the energy use of motors and other auxiliary systems using
 * electricity, based on electrical parameters and operating time.
 *
 * @param number_of_motor_phases Number of motor phases (unitless)
 * @param supply_voltage Supply voltage, units V (volts)
 * @param avg_current Average current, units A (amperes)
 * @param power_factor Power factor (unitless)
 * @param operating_time Operating time, units % (0-100)
 * @returns Auxiliary power used, units BTU/hr
 */
export function auxiliaryCalculatePowerUsed(
    number_of_motor_phases: number,
    supply_voltage: number,
    avg_current: number,
    power_factor: number,
    operating_time: number
): number;

export type AuxiliaryPowerUsedModule = {
    auxiliaryCalculatePowerUsed: typeof auxiliaryCalculatePowerUsed;
};
