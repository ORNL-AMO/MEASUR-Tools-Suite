/**
 * Receiver Tank Calculations
 *
 * Provides compressed air receiver tank sizing and usable-capacity calculations
 * for common sizing methods.
 */

/**
 * Input parameters for the usable air capacity calculation.
 *
 * @property tankSize double, tank volume in gallons.
 * @property airPressureIn double, inlet (charging) pressure in psia.
 * @property airPressureOut double, outlet (cut-out) pressure in psia.
 */
export interface ReceiverTankUsableCapacityInput {
    /** tank volume units gal. */
    tankSize: number;
    /** inlet (charging) pressure units psia. */
    airPressureIn: number;
    /** outlet (cut-out) pressure units psia. */
    airPressureOut: number;
}

/**
 * Result of the usable air capacity calculation.
 *
 * @property usableCapacity double, usable air storage capacity in scf.
 */
export interface ReceiverTankUsableCapacityResult {
    /** usable air storage capacity units scf. */
    usableCapacity: number;
}

/**
 * Input parameters for the General sizing method.
 */
export interface ReceiverTankGeneralInput {
    /** Air demand drawn from the tank, units ft3. */
    airDemand: number;
    /** Tolerable pressure drop across the tank, units psi. */
    allowablePressureDrop: number;
    /** Local atmospheric pressure, units psia. */
    atmosphericPressure: number;
}

/**
 * Tank size result shared by multiple receiver tank sizing methods.
 */
export interface ReceiverTankSizeResult {
    /** Required receiver tank size, units gal. */
    tankSize: number;
}

/**
 * Input parameters for the Dedicated Storage sizing method.
 */
export interface ReceiverTankDedicatedStorageInput {
    /** Duration of the air demand event, units min. */
    lengthOfDemand: number;
    /** Required air flow during the demand event, units cfm. */
    airFlowRequirement: number;
    /** Local atmospheric pressure, units psia. */
    atmosphericPressure: number;
    /** Tank pressure before releasing air, units psia. */
    initialTankPressure: number;
    /** Tank pressure after releasing air, units psia. */
    finalTankPressure: number;
}

/**
 * Input parameters for the Metered Storage sizing method.
 */
export interface ReceiverTankMeteredStorageInput {
    /** Duration of the air demand event, units min. */
    lengthOfDemand: number;
    /** Required air flow during the demand event, units cfm. */
    airFlowRequirement: number;
    /** Local atmospheric pressure, units psia. */
    atmosphericPressure: number;
    /** Tank pressure before releasing air, units psia. */
    initialTankPressure: number;
    /** Tank pressure after releasing air, units psia. */
    finalTankPressure: number;
    /** Metering valve flow rate, units cfm. */
    meteredFlowControl: number;
}

/**
 * Result of the Metered Storage sizing calculation.
 */
export interface ReceiverTankMeteredStorageResult {
    /** Required receiver tank size, units gal. */
    tankSize: number;
    /** Time to refill the tank after a demand event, units s. */
    refillTime: number;
}

/**
 * Input parameters for the Bridging Compressor Reaction Delay sizing method.
 */
export interface ReceiverTankBridgingInput {
    /** Distance from demand event to compressor room, units ft. */
    distanceToCompressorRoom: number;
    /** Speed of compressed air in distribution piping, units ft/s. */
    speedOfAir: number;
    /** Local atmospheric pressure, units psia. */
    atmosphericPressure: number;
    /** Air demand at the event location, units cfm. */
    airDemandCfm: number;
    /** Tolerable pressure drop at the event, units psi. */
    allowablePressureDrop: number;
}

/**
 * Input parameters for the Compressor Cycle sizing method.
 */
export interface ReceiverTankCompressorCycleInput {
    /** Compressor loaded time per cycle, units min. */
    loadTime: number;
    /** Compressor unloaded time per cycle, units min. */
    unloadTime: number;
    /** Rated compressor output at full load, units cfm. */
    compressorCapacity: number;
    /** Pressure at which the compressor unloads, units psia. */
    unloadPressure: number;
    /** Pressure at which the compressor fully loads, units psia. */
    fullLoadPressure: number;
    /** Local atmospheric pressure, units psia. */
    atmosphericPressure: number;
}

/**
 * Result of the Compressor Cycle sizing calculation.
 */
export interface ReceiverTankCompressorCycleResult {
    /** Required receiver tank size, units gal. */
    tankSize: number;
    /** Effective net compressor capacity over a full cycle, units cfm. */
    effectiveCapacity: number;
    /** Pressure band width, units psi. */
    pressureChange: number;
    /** Required storage volume, units ft3. */
    volumeCf: number;
}

/**
 * Calculates the usable air capacity of a receiver tank.
 * @param input {@link ReceiverTankUsableCapacityInput} object containing the tank size and pressure conditions.
 * @returns {@link ReceiverTankUsableCapacityResult} object containing the usable air storage capacity in scf.
 * @remarks This calculation is based on the ideal gas law and assumes standard conditions for temperature and humidity.
*/
export function calculateReceiverTankUsableCapacity(
    input: ReceiverTankUsableCapacityInput
): ReceiverTankUsableCapacityResult;

/**
 * Calculates receiver tank size using the General method.
 * @param input {@link ReceiverTankGeneralInput} object containing the air demand, allowable pressure drop, and atmospheric pressure.
 * @returns {@link ReceiverTankSizeResult} object containing the calculated tank size in gallons.
 * @remarks The General method provides a basic sizing approach based on the air demand and pressure conditions, without accounting for specific system dynamics or control strategies.
*/
export function calculateReceiverTankGeneralSize(input: ReceiverTankGeneralInput): ReceiverTankSizeResult;

/**
 * Calculates receiver tank size using the Dedicated Storage method.
 * @param input {@link ReceiverTankDedicatedStorageInput} object containing the length of demand, air flow requirement, atmospheric pressure, and initial and final tank pressures.
 * @returns {@link ReceiverTankSizeResult} object containing the calculated tank size in gallons.
 * @remarks The Dedicated Storage method is designed for applications with a specific length of demand and flow requirement, providing a more tailored sizing approach compared to the General method.
*/
export function calculateReceiverTankDedicatedStorageSize(
    input: ReceiverTankDedicatedStorageInput
): ReceiverTankSizeResult;

/**
 * Calculates receiver tank size and refill time using the Metered Storage method.
 * @param input {@link ReceiverTankMeteredStorageInput} object containing the length of demand, air flow requirement, atmospheric pressure, initial and final tank pressures, and metered flow control setting.
 * @returns {@link ReceiverTankMeteredStorageResult} object containing the calculated tank size in gallons and the refill time in seconds.
 * @remarks The Metered Storage method accounts for a metered flow control strategy, which can help optimize tank size and refill time based on the specific demand profile and control settings of the system.
*/
export function calculateReceiverTankMeteredStorageSize(
    input: ReceiverTankMeteredStorageInput
): ReceiverTankMeteredStorageResult;

/**
 * Calculates receiver tank size using the Bridging Compressor Reaction Delay method.
 * @param input {@link ReceiverTankBridgingInput} object containing the distance to the compressor room, speed of air, atmospheric pressure, air demand in cfm, and allowable pressure drop.
 * @returns {@link ReceiverTankSizeResult} object containing the calculated tank size in gallons.
 * @remarks The Bridging method is designed to account for the delay in compressor reaction time due to the distance between the receiver tank and compressor room, providing a sizing approach that helps ensure sufficient air supply during transient demand conditions.
*/
export function calculateReceiverTankBridgingSize(input: ReceiverTankBridgingInput): ReceiverTankSizeResult;

/**
 * Calculates receiver tank size from compressor duty cycle and pressure band.
 * @param input {@link ReceiverTankCompressorCycleInput} object containing the load time, unload time, compressor capacity, unload pressure, full load pressure, and atmospheric pressure.
 * @returns {@link ReceiverTankCompressorCycleResult} object containing the calculated tank size in gallons, effective capacity in scf, pressure change in psi, and volume in cubic feet.
 * @remarks The Compressor Cycle method provides a sizing approach based on the compressor's duty cycle and pressure band, helping to ensure that the receiver tank can effectively buffer the compressor's operation and maintain stable pressure during load changes.
*/
export function calculateReceiverTankCompressorCycleSize(
    input: ReceiverTankCompressorCycleInput
): ReceiverTankCompressorCycleResult;

export type ReceiverTankModule = {
    calculateReceiverTankUsableCapacity: typeof calculateReceiverTankUsableCapacity;
    calculateReceiverTankGeneralSize: typeof calculateReceiverTankGeneralSize;
    calculateReceiverTankDedicatedStorageSize: typeof calculateReceiverTankDedicatedStorageSize;
    calculateReceiverTankMeteredStorageSize: typeof calculateReceiverTankMeteredStorageSize;
    calculateReceiverTankBridgingSize: typeof calculateReceiverTankBridgingSize;
    calculateReceiverTankCompressorCycleSize: typeof calculateReceiverTankCompressorCycleSize;
};
