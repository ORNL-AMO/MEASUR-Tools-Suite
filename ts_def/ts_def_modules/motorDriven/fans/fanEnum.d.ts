/**
 * Fan Enumerations
 *
 * Enumerations used by fan performance, base gas density, and fan-curve
 * calculations.
 */

/**
 * Enumeration representing gas type used by base gas density calculations.
 */
export enum GasType {
    AIR = 0,
    STANDARDAIR = 1,
    OTHERGAS = 2
}

/**
 * Enumeration representing base gas density input mode.
 */
export enum BaseGasDensityInputType {
    DewPoint = 0,
    RelativeHumidity = 1,
    WetBulbTemp = 2
}

/**
 * Enumeration representing fan type for optimal efficiency calculations.
 */
export enum FanType {
    AirfoilSISW = 0,
    BackwardCurvedSISW = 1,
    RadialSISW = 2,
    RadialTipSISW = 3,
    BackwardInclinedSISW = 4,
    AirfoilDIDW = 5,
    BackwardCurvedDIDW = 6,
    BackwardInclinedDIDW = 7,
    VaneAxial = 8,
    AirHandling = 9,
    MaterialHandling = 10,
    LongShavings = 11
}

/**
 * Enumeration representing fan curve data calculation mode.
 */
export enum FanCurveDataCalculationType {
    BaseCurve = 0,
    RatedPoint = 1,
    BaseOperatingPoint = 2
}

/**
 * Enumeration representing fan pressure curve type.
 */
export enum FanCurveType {
    FanStaticPressure = 0,
    FanTotalPressure = 1,
    StaticPressureRise = 2
}

export type FanEnumModule = {
    GasType: typeof GasType;
    BaseGasDensityInputType: typeof BaseGasDensityInputType;
    FanType: typeof FanType;
    FanCurveDataCalculationType: typeof FanCurveDataCalculationType;
    FanCurveType: typeof FanCurveType;
};
