import { LineFrequency, MotorEfficiencyClass } from "./motorEnum";

/** Class representing motor data and specifications. */
export declare class MotorData {
    /**
     * Constructor for motor data.
     *
     * @param hp double, horsepower of the motor
     *
     * @param synchronousSpeed integer, synchronous speed of the motor in RPM
     *
     * @param poles integer, number of poles in the motor
     *
     * @param nominalEfficiency double, nominal efficiency of the motor as a fraction
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param nemaTable string, NEMA table reference for the motor
     *
     * @param enclosureType string, type of enclosure for the motor
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor
     *
     * @param voltageLimit integer, voltage limit for the motor
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

    /** Getter for motor data property ID. */
    getId(): number;
    /** Getter for motor data property HP. */
    getHp(): number;
    /** Getter for motor data property synchronous speed. */
    getSynchronousSpeed(): number;
    /** Getter for motor data property poles. */
    getPoles(): number;
    /** Getter for motor data property nominal efficiency. */
    getNominalEfficiency(): number;
    /** Getter for motor data property efficiency class. */
    getEfficiencyClass(): MotorEfficiencyClass;
    /** Getter for motor data property NEMA table. */
    getNemaTable(): string;
    /** Getter for motor data property enclosure type. */
    getEnclosureType(): string;
    /** Getter for motor data property line frequency. */
    getLineFrequency(): LineFrequency;
    /** Getter for motor data property voltage limit. */
    getVoltageLimit(): number;
    /** Getter for motor data property catalog. */
    getCatalog(): string;

    /** Setter for motor data property ID. */
    setId(value: number): void;
    /** Setter for motor data property HP. */
    setHp(value: number): void;
    /** Setter for motor data property synchronous speed. */
    setSynchronousSpeed(value: number): void;
    /** Setter for motor data property poles. */
    setPoles(value: number): void;
    /** Setter for motor data property nominal efficiency. */
    setNominalEfficiency(value: number): void;
    /** Setter for motor data property efficiency class. */
    setEfficiencyClass(value: MotorEfficiencyClass): void;
    /** Setter for motor data property NEMA table. */
    setNemaTable(value: string): void;
    /** Setter for motor data property enclosure type. */
    setEnclosureType(value: string): void;
    /** Setter for motor data property line frequency. */
    setLineFrequency(value: LineFrequency): void;
    /** Setter for motor data property voltage limit. */
    setVoltageLimit(value: number): void;
    /** Setter for motor data property catalog. */
    setCatalog(value: string): void;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Class for calculating motor efficiency based on various parameters. */
export declare class MotorEfficiency {
    /**
     * Constructor for motor efficiency.
     *
     * @param lineFrequency LineFrequency, classification of line frequency in Hz
     *
     * @param motorRpm double, RPM of motor
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of motor
     *
     * @param motorRatedPower double, rated power of motor in hp
     *
     */
    constructor(
        lineFrequency : LineFrequency,
        motorRpm: number,
        efficiencyClass: MotorEfficiencyClass,
        motorRatedPower: number
    );

    /**
     * Calculate the motor efficiency based on the input parameters.
     *
     * @param loadFactor double, load factor - unitless ratio
     *
     * @param specifiedEfficiency efficiency of SPECIFIED efficiency class motor as defined by fraction
     *
     * @returns double The calculated motor efficiency %.
     *
     */
    calculate(loadFactor : number, specifiedEfficiency : number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Class for estimating the full load amps (FLA) of a motor based on various parameters. */
export declare class EstimateFLA {
    /**
     * Constructor for estimating full load amps (FLA) of a motor.
     *
     * @param motorRatedPower double, rated power of the motor in hp
     *
     * @param motorRPM double, RPM of the motor
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor in Hz
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param specifiedEfficiency double, efficiency of SPECIFIED efficiency class motor defined as a fraction
     *
     * @param ratedVoltage double, rated voltage of the motor in volts
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
     * @returns double, The estimated full load amps (FLA).
     *
     */
    getEstimatedFLA(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Class representing a motor and its performance characteristics. */
export declare class Motor {
    /**
     * Constructor for the Motor class, which initializes the motor with various parameters.
     *
     * @param lineFrequency LineFrequency, line frequency classification of the motor in Hz
     *
     * @param motorRatedPower double, rated power of the motor in hp
     *
     * @param motorRpm double, RPM of the motor
     *
     * @param efficiencyClass MotorEfficiencyClass, efficiency class of the motor
     *
     * @param specifiedEfficiency double, specified % Efficiency of motor, unused unless efficiency class is SPECIFIED
     *
     * @param motorRatedVoltage double, motor nameplate design voltage in volts
     *
     * @param fullLoadAmps double, current at full load in amps
     *
     * @param sizeMargin double, size margin as defined in %
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

/** Class for calculating the motor current based on various parameters. */
export declare class MotorCurrent {
    /**
     * Constructor for calculating the motor current based on various parameters.
     *
     * @param motorRatedPower double, Rated power of motor in hp
     *
     * @param motorRPM double, RPM of motor.
     *
     * @param lineFrequency Motor::LineFrequency, classification of line Frequency of motor in Hz
     *
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor.
     * @param specifiedEfficiency double, Specified efficiency of motor when the efficiency class = SPECIFIED as %
     *
     * @param loadFactor double, load factor - unitless
     *
     * @param ratedVoltage double, Rated voltage of the motor in Volts
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
     * @param fullLoadAmps double, Current at full load in Amps
     *
     * @returns double, motor current in amps
     *
     */
    calculateCurrent(fullLoadAmps: number): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Class for calculating the motor power factor based on various parameters. */
export declare class MotorPowerFactor {
    /**
     * Constructor
     * @param motorRatedPower double, Rated Power of motor in hp
     *
     * @param loadFactor double, load factor - unitless
     *
     * @param motorCurrent double, current of motor in A
     *
     * @param motorEfficiency double, motor efficiency as %
     *
     * @param ratedVoltage double, rated voltage as V
     *
     */
    constructor(
        motorRatedPower: number,
        loadFactor: number,
        motorCurrent: number,
        motorEfficiency: number,
        ratedVoltage: number );

    /**
     * Calculates the motor power factor
     *
     * @returns double, power factor - unitless
     *
     */
    calculate(): number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Struct representing the output of motor performance calculations,
 *
 * Object contains the calculated current, efficiency, and powerfactor of the motor.
 *
 */
export declare class MotorPerformanceOutput {
    /**
     * Constructor for the MotorPerformanceOutput class, which initializes the output with various parameters.
     *
     * @param current
     *
     * @param efficiency
     *
     * @param powerFactor
     *
     */
    constructor(current: number, efficiency: number, powerFactor: number);

    current: number;
    efficiency: number;
    powerFactor: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/** Class for calculating the overall motor performance based on various parameters. */
export declare class MotorPerformance {
    /**
     * Constructor
     *
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     *
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     *
     * @param motorRatedPower double, rated power of motor in hp
     *
     * @param motorRpm double, RPM of motor
     *
     * @param specifiedEfficiency double, Specified efficiency of motor when the efficiency class = SPECIFIED as %
     *
     * @param loadFactor double, load factor - unitless
     *
     * @param ratedVoltage double, Rated voltage of the motor in Volts
     *
     * @param fullLoadAmps double, current at full load in Amps
     *
     */
    constructor(
        lineFrequency: LineFrequency,
        efficiencyClass: MotorEfficiencyClass,
        motorRatedPower: number,
        motorRpm: number,
        specifiedEfficiency: number,
        loadFactor: number,
        ratedVoltage: number,
        fullLoadAmps: number);

    /**
     * Calculates the overall motor performance based on the input parameters and returns a MotorPerformanceOutput object containing the calculated current, efficiency, and power factor.
     *
     * @returns MotorPerformanceOutput, an object containing the calculated current, efficiency, and power factor of the motor.
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
