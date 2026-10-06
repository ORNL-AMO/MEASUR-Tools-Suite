/** Inputs for pump-head calculation from suction- and discharge-gauge measurements. */
export interface PumpHeadSuctionGaugeInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Volumetric flow rate, units gpm. */
    flowRate: number;
    /** Suction-pipe inside diameter, units in. */
    suctionPipeDiameter: number;
    /** Suction gauge pressure, units psig. */
    suctionGaugePressure: number;
    /** Suction-gauge elevation, units ft. */
    suctionGaugeElevation: number;
    /** Aggregate suction-line loss coefficient, dimensionless. */
    suctionLineLossCoefficients: number;
    /** Discharge-pipe inside diameter, units in. */
    dischargePipeDiameter: number;
    /** Discharge gauge pressure, units psig. */
    dischargeGaugePressure: number;
    /** Discharge-gauge elevation, units ft. */
    dischargeGaugeElevation: number;
    /** Aggregate discharge-line loss coefficient, dimensionless. */
    dischargeLineLossCoefficients: number;
}

/** Inputs for pump-head calculation with a pressurized suction tank. */
export interface PumpHeadSuctionTankInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Volumetric flow rate, units gpm. */
    flowRate: number;
    /** Suction-pipe inside diameter, units in. */
    suctionPipeDiameter: number;
    /** Suction-tank gas overpressure, units psig. */
    suctionTankGasOverPressure: number;
    /** Suction-tank fluid-surface elevation, units ft. */
    suctionTankFluidSurfaceElevation: number;
    /** Aggregate suction-line loss coefficient, dimensionless. */
    suctionLineLossCoefficients: number;
    /** Discharge-pipe inside diameter, units in. */
    dischargePipeDiameter: number;
    /** Discharge gauge pressure, units psig. */
    dischargeGaugePressure: number;
    /** Discharge-gauge elevation, units ft. */
    dischargeGaugeElevation: number;
    /** Aggregate discharge-line loss coefficient, dimensionless. */
    dischargeLineLossCoefficients: number;
}

/** Component heads and total operating pump head returned as a plain object. */
export interface PumpHeadResult {
    /** Discharge-minus-suction elevation head, units ft. */
    differentialElevationHead: number;
    /** Discharge-minus-suction pressure head, units ft. */
    differentialPressureHead: number;
    /** Discharge-minus-suction velocity head, units ft. */
    differentialVelocityHead: number;
    /** Estimated suction-line friction head, units ft. */
    estimatedSuctionFrictionHead: number;
    /** Estimated discharge-line friction head, units ft. */
    estimatedDischargeFrictionHead: number;
    /** Total operating pump head, units ft. */
    pumpHead: number;
}

/**
 * Calculates operating pump head from suction- and discharge-gauge measurements.
 * @param input Flow, pipe, pressure, elevation, and loss-coefficient inputs in U.S. customary units.
 * @returns Component heads and total operating pump head, units ft.
 */
export declare function calculatePumpHeadFromSuctionGauge(
    input: PumpHeadSuctionGaugeInput
): PumpHeadResult;

/**
 * Calculates operating pump head for a system supplied from a pressurized suction tank.
 * @param input Flow, pipe, tank, discharge, and loss-coefficient inputs in U.S. customary units.
 * @returns Component heads and total operating pump head, units ft.
 */
export declare function calculatePumpHeadFromSuctionTank(
    input: PumpHeadSuctionTankInput
): PumpHeadResult;

/** Runtime exports contributed by the pump-head binding. */
export type PumpHeadModule = {
    calculatePumpHeadFromSuctionGauge: typeof calculatePumpHeadFromSuctionGauge;
    calculatePumpHeadFromSuctionTank: typeof calculatePumpHeadFromSuctionTank;
};
