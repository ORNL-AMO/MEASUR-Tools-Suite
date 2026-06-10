/**
 * Gas type used by base gas density calculations.
 */
export enum GasType {
    AIR = 0,
    STANDARDAIR = 1,
    OTHERGAS = 2
}

/**
 * Input mode used by base gas density calculations.
 */
export enum BaseGasDensityInputType {
    DewPoint = 0,
    RelativeHumidity = 1,
    WetBulbTemp = 2
}

/**
 * Fan type used by optimal fan efficiency calculations.
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
 * Calculation mode for fan curve data.
 */
export enum FanCurveDataCalculationType {
    BaseCurve = 0,
    RatedPoint = 1,
    BaseOperatingPoint = 2
}

/**
 * Fan pressure curve type.
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
