/** Enumeration: Type of motor drive system. */
export enum Drive {
    DIRECT_DRIVE =0,
    V_BELT_DRIVE =1,
    N_V_BELT_DRIVE =2,
    S_BELT_DRIVE =3,
    SPECIFIED =4
}

/** Enumeration: Line frequency in Hz. */
export enum LineFrequency {
    FREQ60 =0,
    FREQ50 =1
}

/** Enumeration: Method for estimating motor load. */
export enum LoadEstimationMethod {
    POWER =0,
    CURRENT =1
}

/** Enumeration: Efficiency class of the motor. */
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
