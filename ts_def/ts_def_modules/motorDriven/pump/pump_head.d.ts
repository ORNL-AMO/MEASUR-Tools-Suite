/**
 * Inputs for pump-head calculation from suction- and discharge-gauge measurements.
 * Gauge elevations refer to the centers of the gauges from a common datum and must correspond
 * to the supplied pressure readings. For a reading corrected to another reference elevation,
 * use that elevation instead.
 */
export interface PumpHeadSuctionGaugeInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Volumetric flow rate, units gpm. */
    flowRate: number;
    /** Pipe inside diameter at the suction pressure-measurement location, units in. */
    suctionPipeDiameter: number;
    /** Suction gauge pressure, units psig. */
    suctionGaugePressure: number;
    /** Elevation of the suction gauge center or corrected pressure reference from the common datum, units ft. */
    suctionGaugeElevation: number;
    /** Aggregate suction-line loss coefficient, dimensionless. */
    suctionLineLossCoefficients: number;
    /** Pipe inside diameter at the discharge pressure-measurement location, units in. */
    dischargePipeDiameter: number;
    /** Discharge gauge pressure, units psig. */
    dischargeGaugePressure: number;
    /** Elevation of the discharge gauge center or corrected pressure reference from the common datum, units ft. */
    dischargeGaugeElevation: number;
    /** Aggregate discharge-line loss coefficient, dimensionless. */
    dischargeLineLossCoefficients: number;
}

/**
 * Inputs for pump-head calculation with a pressurized suction tank.
 * The suction elevation refers to the tank fluid surface. Discharge elevation refers to the
 * gauge center, or the reference elevation to which the pressure reading has been corrected,
 * measured from the same datum.
 */
export interface PumpHeadSuctionTankInput {
    /** Fluid specific gravity, dimensionless. */
    specificGravity: number;
    /** Volumetric flow rate, units gpm. */
    flowRate: number;
    /** Suction-pipe inside diameter used as the reference for suction-line losses, units in. */
    suctionPipeDiameter: number;
    /** Suction-tank gas overpressure, units psig. */
    suctionTankGasOverPressure: number;
    /** Suction-tank fluid-surface elevation from the common datum, units ft. */
    suctionTankFluidSurfaceElevation: number;
    /** Aggregate suction-line loss coefficient, dimensionless. */
    suctionLineLossCoefficients: number;
    /** Pipe inside diameter at the discharge pressure-measurement location, units in. */
    dischargePipeDiameter: number;
    /** Discharge gauge pressure, units psig. */
    dischargeGaugePressure: number;
    /** Elevation of the discharge gauge center or corrected pressure reference from the common datum, units ft. */
    dischargeGaugeElevation: number;
    /** Aggregate discharge-line loss coefficient, dimensionless. */
    dischargeLineLossCoefficients: number;
}

/** Component heads and pump head returned as a plain object. */
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
    /** Pump head, units ft. */
    pumpHead: number;
}

/**
 * Calculates pump head from suction- and discharge-gauge measurements.
 * @param input Flow, pipe, pressure, elevation, and loss-coefficient inputs in U.S. customary units.
 * @returns Component heads and pump head, units ft.
 */
export declare function calculatePumpHeadFromSuctionGauge(
    input: PumpHeadSuctionGaugeInput
): PumpHeadResult;

/**
 * Calculates pump head for a system supplied from a pressurized suction tank.
 * @param input Flow, pipe, tank, discharge, and loss-coefficient inputs in U.S. customary units.
 * @returns Component heads and pump head, units ft.
 */
export declare function calculatePumpHeadFromSuctionTank(
    input: PumpHeadSuctionTankInput
): PumpHeadResult;

/** Runtime exports contributed by the pump-head binding. */
export type PumpHeadModule = {
    calculatePumpHeadFromSuctionGauge: typeof calculatePumpHeadFromSuctionGauge;
    calculatePumpHeadFromSuctionTank: typeof calculatePumpHeadFromSuctionTank;
};
