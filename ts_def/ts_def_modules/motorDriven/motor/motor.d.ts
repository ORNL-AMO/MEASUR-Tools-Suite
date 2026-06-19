import { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/**
 * Motor calculations and data models.
 *
 * Provides motor data records and calculators for efficiency, current,
 * power factor, and overall motor performance.
 */

/**
 * Motor default data record.
 */
export declare class MotorData {
    /**
     * Constructor for motor data.
     *
     * @param hp Motor power, units hp.
     *
     * @param synchronousSpeed Motor synchronous speed, units rpm.
     *
     * @param poles Motor pole count.
     *
     * @param nominalEfficiency Nominal motor efficiency, dimensionless fraction.
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param nemaTable string, NEMA table reference for the motor
     *
     * @param enclosureType string, type of enclosure for the motor
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor
     *
     * @param voltageLimit Voltage limit selector, unitless enum value.
     *
     * @param catalog string, catalog reference for the motor
     */
    constructor(
        hp: number,
        synchronousSpeed: number,
        poles: number,
        nominalEfficiency: number,
        efficiencyClass: MotorEfficiencyClass,
        nemaTable: string,
        enclosureType: string,
        lineFrequency: LineFrequency,
        voltageLimit: number,
        catalog: string );

    /** @returns Motor data record ID, unitless identifier. */
    getId(): number;
    /** @returns Motor power, units hp. */
    getHp(): number;
    /** @returns Motor synchronous speed, units rpm. */
    getSynchronousSpeed(): number;
    /** @returns Motor pole count. */
    getPoles(): number;
    /** @returns Nominal motor efficiency, dimensionless fraction. */
    getNominalEfficiency(): number;
    /** Getter for motor data property efficiency class. */
    getEfficiencyClass(): MotorEfficiencyClass;
    /** Getter for motor data property NEMA table. */
    getNemaTable(): string;
    /** Getter for motor data property enclosure type. */
    getEnclosureType(): string;
    /** Getter for motor data property line frequency. */
    getLineFrequency(): LineFrequency;
    /** @returns Voltage limit selector, unitless enum value. */
    getVoltageLimit(): number;
    /** Getter for motor data property catalog. */
    getCatalog(): string;

    /** @param value Motor data record ID, unitless identifier. */
    setId(value: number): void;
    /** @param value Motor power, units hp. */
    setHp(value: number): void;
    /** @param value Motor synchronous speed, units rpm. */
    setSynchronousSpeed(value: number): void;
    /** @param value Motor pole count. */
    setPoles(value: number): void;
    /** @param value Nominal motor efficiency, dimensionless fraction. */
    setNominalEfficiency(value: number): void;
    /** Setter for motor data property efficiency class. */
    setEfficiencyClass(value: MotorEfficiencyClass): void;
    /** Setter for motor data property NEMA table. */
    setNemaTable(value: string): void;
    /** Setter for motor data property enclosure type. */
    setEnclosureType(value: string): void;
    /** Setter for motor data property line frequency. */
    setLineFrequency(value: LineFrequency): void;
    /** @param value Voltage limit selector, unitless enum value. */
    setVoltageLimit(value: number): void;
    /** Setter for motor data property catalog. */
    setCatalog(value: string): void;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Motor efficiency calculator.
 */
export declare class MotorEfficiency {
    /**
     * Constructor for motor efficiency.
     *
     * @param lineFrequency LineFrequency, classification of line frequency in Hz
     *
     * @param motorRpm Motor speed, units rpm.
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of motor
     *
     * @param motorRatedPower Rated motor power, units hp.
     *
     */
    constructor(
        lineFrequency : LineFrequency,
        motorRpm: number,
        efficiencyClass: MotorEfficiencyClass,
        motorRatedPower: number
    );

    /**
     * Calculate motor efficiency based on the input parameters.
     *
     * @param loadFactor Load factor, dimensionless fraction.
     *
     * @param specifiedEfficiency Specified motor efficiency, dimensionless fraction.
     *
     * @returns Calculated motor efficiency, dimensionless fraction.
     *
     */
    calculate(loadFactor : number, specifiedEfficiency : number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Full-load current (FLA) estimator.
 */
export declare class EstimateFLA {
    /**
     * Constructor for estimating full load amps (FLA) of a motor.
     *
     * @param motorRatedPower Rated motor power, units hp.
     *
     * @param motorRPM Motor speed, units rpm.
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor in Hz
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param specifiedEfficiency Specified motor efficiency, dimensionless fraction.
     *
     * @param ratedVoltage Rated motor voltage, units V.
     *
     */
    constructor(
        motorRatedPower: number,
        motorRPM: number,
        lineFrequency: LineFrequency,
        efficiencyClass: MotorEfficiencyClass,
        specifiedEfficiency: number,
        ratedVoltage: number
        );

    /**
     * Method to calculate the estimated full load amps (FLA) of the motor.
     *
     * @returns Estimated full-load current, units A.
     *
     */
    getEstimatedFLA(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Motor model.
 */
export declare class Motor {
    /**
     * Constructor for the Motor class, which initializes the motor with various parameters.
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor in Hz
     *
     * @param motorRatedPower Rated motor power, units hp.
     *
     * @param motorRpm Motor speed, units rpm.
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param specifiedEfficiency Specified motor efficiency, dimensionless fraction.
     *
     * @param motorRatedVoltage Motor nameplate voltage, units V.
     *
     * @param fullLoadAmps Full-load current, units A.
     *
     * @param sizeMargin Size margin, units %.
     *
     */
    constructor(
        lineFrequency: LineFrequency,
        motorRatedPower: number,
        motorRpm: number,
        efficiencyClass: MotorEfficiencyClass,
        specifiedEfficiency: number,
        motorRatedVoltage: number,
        fullLoadAmps: number,
        sizeMargin: number );

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Motor current calculator.
 */
export declare class MotorCurrent {
    /**
     * Constructor for calculating the motor current based on various parameters.
     *
     * @param motorRatedPower Rated motor power, units hp.
     *
     * @param motorRPM Motor speed, units rpm.
     *
     * @param lineFrequency Motor::LineFrequency, classification of line Frequency of motor in Hz
     *
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor.
     * @param specifiedEfficiency Specified motor efficiency, dimensionless fraction.
     *
     * @param loadFactor Load factor, dimensionless fraction.
     *
     * @param ratedVoltage Rated motor voltage, units V.
     *
     */
    constructor(
        motorRatedPower: number,
        motorRPM: number,
        lineFrequency: LineFrequency,
        efficiencyClass: MotorEfficiencyClass,
        specifiedEfficiency: number,
        loadFactor: number,
        ratedVoltage: number );

    /**
     * calculates the motor current at a given load factor.
     *
     * @param fullLoadAmps Full-load current, units A.
     *
     * @returns Motor current, units A.
     *
     */
    calculateCurrent(fullLoadAmps: number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Motor power factor calculator.
 */
export declare class MotorPowerFactor {
    /**
     * Constructor
     * @param motorRatedPower Rated motor power, units hp.
     *
     * @param loadFactor Load factor, dimensionless fraction.
     *
     * @param motorCurrent Motor current, units A.
     *
     * @param motorEfficiency Motor efficiency, dimensionless fraction.
     *
     * @param ratedVoltage Rated motor voltage, units V.
     *
     */
    constructor(
        motorRatedPower: number,
        loadFactor: number,
        motorCurrent: number,
        motorEfficiency: number,
        ratedVoltage: number );

    /**
     * Calculates the motor power factor.
     *
     * @returns Motor power factor, dimensionless.
     *
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link MotorPerformance.calculate}.
 *
 * @property current Motor current, units A.
 * @property efficiency Motor efficiency, dimensionless fraction.
 * @property powerFactor Motor power factor, dimensionless.
 */
export declare class MotorPerformanceOutput {
    /**
     * Constructor for the MotorPerformanceOutput class, which initializes the output with various parameters.
     *
     * @param current Motor current, units A.
     *
     * @param efficiency Motor efficiency, dimensionless fraction.
     *
     * @param powerFactor Motor power factor, dimensionless.
     *
     */
    constructor(current: number, efficiency: number, powerFactor: number);

    /** motor current units A. */
    current: number;
    /** Motor efficiency, dimensionless fraction. */
    efficiency: number;
    /** Motor power factor, dimensionless. */
    powerFactor: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Motor performance calculator.
 */
export declare class MotorPerformance {
    /**
     * Constructor
     *
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     *
     * @param motorRpm Motor speed, units rpm.
     *
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     *
     * @param motorRatedPower Rated motor power, units hp.
     *
     * @param specifiedEfficiency Specified motor efficiency, dimensionless fraction.
     *
     * @param loadFactor Load factor, dimensionless fraction.
     *
     * @param ratedVoltage Rated motor voltage, units V.
     *
     * @param fullLoadAmps Full-load current, units A.
     *
     */
    constructor(
        lineFrequency: LineFrequency,
        motorRpm: number,
        efficiencyClass: MotorEfficiencyClass,
        motorRatedPower: number,
        specifiedEfficiency: number,
        loadFactor: number,
        ratedVoltage: number,
        fullLoadAmps: number);

    /**
     * Calculates the overall motor performance based on the input parameters and returns a MotorPerformanceOutput object containing the calculated current, efficiency, and power factor, dimensionless.
     *
     * @returns {@link MotorPerformanceOutput}, an object containing the calculated current, efficiency, and power factor, dimensionless of the motor.
     *
     */
    calculate(): MotorPerformanceOutput;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

export type MotorModule = {
    MotorData: typeof MotorData;
    MotorEfficiency: typeof MotorEfficiency;
    EstimateFLA: typeof EstimateFLA;
    Motor: typeof Motor;
    MotorCurrent: typeof MotorCurrent;
    MotorPowerFactor: typeof MotorPowerFactor;
    MotorPerformanceOutput: typeof MotorPerformanceOutput;
    MotorPerformance: typeof MotorPerformance;
};
