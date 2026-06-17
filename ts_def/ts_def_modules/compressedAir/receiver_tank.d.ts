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
    tankSize: number;
    airPressureIn: number;
    airPressureOut: number;
}

/**
 * Result of the usable air capacity calculation.
 *
 * @property usableCapacity double, usable air storage capacity in scf.
 */
export interface ReceiverTankUsableCapacityResult {
    usableCapacity: number;
}

/**
 * Input parameters for the General sizing method.
 */
export interface ReceiverTankGeneralInput {
    airDemand: number;
    allowablePressureDrop: number;
    atmosphericPressure: number;
}

/**
 * Tank size result shared by multiple receiver tank sizing methods.
 */
export interface ReceiverTankSizeResult {
    tankSize: number;
}

/**
 * Input parameters for the Dedicated Storage sizing method.
 */
export interface ReceiverTankDedicatedStorageInput {
    lengthOfDemand: number;
    airFlowRequirement: number;
    atmosphericPressure: number;
    initialTankPressure: number;
    finalTankPressure: number;
}

/**
 * Input parameters for the Metered Storage sizing method.
 */
export interface ReceiverTankMeteredStorageInput {
    lengthOfDemand: number;
    airFlowRequirement: number;
    atmosphericPressure: number;
    initialTankPressure: number;
    finalTankPressure: number;
    meteredFlowControl: number;
}

/**
 * Result of the Metered Storage sizing calculation.
 */
export interface ReceiverTankMeteredStorageResult {
    tankSize: number;
    refillTime: number;
}

/**
 * Input parameters for the Bridging Compressor Reaction Delay sizing method.
 */
export interface ReceiverTankBridgingInput {
    distanceToCompressorRoom: number;
    speedOfAir: number;
    atmosphericPressure: number;
    airDemandCfm: number;
    allowablePressureDrop: number;
}

/**
 * Input parameters for the Compressor Cycle sizing method.
 */
export interface ReceiverTankCompressorCycleInput {
    loadTime: number;
    unloadTime: number;
    compressorCapacity: number;
    unloadPressure: number;
    fullLoadPressure: number;
    atmosphericPressure: number;
}

/**
 * Result of the Compressor Cycle sizing calculation.
 */
export interface ReceiverTankCompressorCycleResult {
    tankSize: number;
    effectiveCapacity: number;
    pressureChange: number;
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
