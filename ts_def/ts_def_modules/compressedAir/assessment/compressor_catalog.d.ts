/** Passive default compressor catalog record used by assessment workflows. */
export interface CompressorCatalogRecord {
    /** Sequential catalog record ID, dimensionless. */
    id: number;
    /** Compressor type identifier, dimensionless. */
    compressorTypeId: number;
    /** Compressor model name. */
    model: string;
    /** Rated motor size, units hp. */
    horsepower: number;
    /** Rated compressor capacity, units acfm. */
    ratedCapacityAcfm: number;
    /** Rated discharge pressure, units psig. */
    ratedPressurePsig: number;
    /** Maximum full-flow pressure, units psig. */
    maxFullFlowPressurePsig: number;
    /** Control type identifier, dimensionless. */
    controlTypeId: number;
    /** Unload point, units percent. */
    unloadPointPercent: number;
    /** Minimum unload sump pressure, units psig. */
    minUnloadSumpPressurePsig: number;
    /** Blowdown time, units seconds. */
    blowdownTimeSec: number;
    /** Unload steps, dimensionless count. */
    unloadSteps: number;
    /** Modulating pressure range, units psig. */
    modulatingPressureRangePsig: number;
    /** Full-load brake horsepower equivalent power, units kW. */
    fullLoadBhpPowerKw: number;
    /** Total package input power, units kW. */
    totalPackageInputPowerKw: number;
    /** Specific package power, units kW/acfm. */
    specificPackagePower: number;
    /** No-load fully modulating power fraction, dimensionless. */
    noLoadPowerFullyModulating: number;
    /** No-load unload power fraction, dimensionless. */
    noLoadPowerUnload: number;
    /** Maximum surge pressure, units psig. */
    maxSurgePressurePsig: number;
    /** Flow at maximum surge pressure, units acfm. */
    maxSurgePressureFlowAcfm: number;
    /** Minimum stonewall pressure, units psig. */
    minStonewallPressurePsig: number;
    /** Flow at minimum stonewall pressure, units acfm. */
    minStonewallPressureFlowAcfm: number;
    /** Design surge flow, units acfm. */
    designSurgeFlowAcfm: number;
    /** Design inlet temperature, units degF. */
    designInletTemperatureF: number;
    /** Design inlet pressure, units psia. */
    designInletPressurePsia: number;
    /** Full-load current, units A. */
    fullLoadAmps: number;
    /** Full-load efficiency, units percent. */
    fullLoadEfficiencyPercent: number;
}
