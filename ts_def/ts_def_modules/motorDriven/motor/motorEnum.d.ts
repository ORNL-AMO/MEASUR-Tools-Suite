/**
 * Motor Enumerations
 *
 * Enumerations used by motor, pump, and fan motor-driven calculations.
 */

/**
 * Enumeration representing the motor drive type.
 */
export enum Drive {
    DIRECT_DRIVE =0,
    V_BELT_DRIVE =1,
    N_V_BELT_DRIVE =2,
    S_BELT_DRIVE =3,
    SPECIFIED =4
}

/**
 * Enumeration representing line frequency.
 */
export enum LineFrequency {
    FREQ60 =0,
    FREQ50 =1
}

/**
 * Enumeration representing the motor load estimation method.
 */
export enum LoadEstimationMethod {
    POWER =0,
    CURRENT =1
}

/**
 * Enumeration representing the motor efficiency, dimensionless class.
 */
export enum MotorEfficiencyClass {
    STANDARD =0,
    ENERGY_EFFICIENT =1,
    PREMIUM =2,
    SPECIFIED =3
}

export type MotorEnumModule = {
    Drive: typeof Drive;
    LineFrequency: typeof LineFrequency;
    LoadEstimationMethod: typeof LoadEstimationMethod;
    MotorEfficiencyClass: typeof MotorEfficiencyClass;
};
