/**
 * @brief Compressor electricity parameters used when the electricity utility type is selected.
 * @details Compressor specific power characterizes electrical power required per unit
 *          compressed air flow, and compressor control adjustment captures part-load
 *          or variable-speed control behavior as a percentage factor.
 *
 * @var compressorControlAdjustment double, compressor control adjustment factor in percent.
 * @var compressorSpecificPower double, electrical power per unit flow rate in kW/(cfm).
 */
export interface CompressorElectricityData {
    compressorControlAdjustment: number;
    compressorSpecificPower: number;
}

/**
 * Factory function to load the Compressed Air Utils.
 */
export default function CompressedAirUtilsModule(): Promise<{
    CompressorElectricityData: CompressorElectricityData;
}>;

