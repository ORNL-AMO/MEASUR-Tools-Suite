/**
 * Compressor electricity parameters used when the electricity utility type is selected.
 * @details Compressor specific power characterizes electrical power required per unit
 *          compressed air flow, and compressor control adjustment captures part-load
 *          or variable-speed control behavior as a percentage factor.
 *
 * @property compressorControlAdjustment double, compressor control adjustment factor in percent.
 * @property compressorSpecificPower double, electrical power per unit flow rate in kW/(cfm).
 */
export interface CompressorElectricityData {
    compressorControlAdjustment: number;
    compressorSpecificPower: number;
}

export type CompressedAirUtilsModule = {
    CompressorElectricityData: CompressorElectricityData;
};
