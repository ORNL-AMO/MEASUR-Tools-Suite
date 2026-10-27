/** Default compressor catalog record used by assessment workflows. A value of -9999 means unavailable or not applicable. */
export interface CompressorCatalogRecord {
    /** Sequential catalog record ID, dimensionless. */
    id: number;
    /** Catalog compressor-family ID: 1 single-stage injected screw, 2 two-stage injected screw, 3 two-stage lubricant-free screw, 4 single-stage reciprocating, 5 two-stage reciprocating, 6 multiple-stage centrifugal. */
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
    /** Catalog control-family ID: 1 modulation, 2 modulation/unload, 3 variable displacement/unload, 4 load/unload, 5 multi-step unloading, 6 start/stop, 7-10 centrifugal blow-off/unloading variants, 11 VFD. */
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
    /** Full-load shaft power, units bhp. */
    fullLoadBrakeHorsepower: number;
    /** @deprecated Use fullLoadBrakeHorsepower. This compatibility alias also contains bhp, despite its name. */
    fullLoadBhpPowerKw: number;
    /** Total package input power, units kW. */
    totalPackageInputPowerKw: number;
    /** Specific package power, units kW/100 acfm. */
    specificPackagePower: number;
    /** No-load fully modulating power, units percent. */
    noLoadPowerFullyModulating: number;
    /** No-load unload power, units percent. */
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
