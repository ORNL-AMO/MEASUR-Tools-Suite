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

/** Calculates the usable air capacity of a receiver tank. */
export function calculateReceiverTankUsableCapacity(
    input: ReceiverTankUsableCapacityInput
): ReceiverTankUsableCapacityResult;

/** Calculates receiver tank size using the General method. */
export function calculateReceiverTankGeneralSize(input: ReceiverTankGeneralInput): ReceiverTankSizeResult;

/** Calculates receiver tank size using the Dedicated Storage method. */
export function calculateReceiverTankDedicatedStorageSize(
    input: ReceiverTankDedicatedStorageInput
): ReceiverTankSizeResult;

/** Calculates receiver tank size and refill time using the Metered Storage method. */
export function calculateReceiverTankMeteredStorageSize(
    input: ReceiverTankMeteredStorageInput
): ReceiverTankMeteredStorageResult;

/** Calculates receiver tank size using the Bridging Compressor Reaction Delay method. */
export function calculateReceiverTankBridgingSize(input: ReceiverTankBridgingInput): ReceiverTankSizeResult;

/** Calculates receiver tank size from compressor duty cycle and pressure band. */
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
    ReceiverTankUsableCapacityInput: ReceiverTankUsableCapacityInput;
    ReceiverTankUsableCapacityResult: ReceiverTankUsableCapacityResult;
    ReceiverTankGeneralInput: ReceiverTankGeneralInput;
    ReceiverTankSizeResult: ReceiverTankSizeResult;
    ReceiverTankDedicatedStorageInput: ReceiverTankDedicatedStorageInput;
    ReceiverTankMeteredStorageInput: ReceiverTankMeteredStorageInput;
    ReceiverTankMeteredStorageResult: ReceiverTankMeteredStorageResult;
    ReceiverTankBridgingInput: ReceiverTankBridgingInput;
    ReceiverTankCompressorCycleInput: ReceiverTankCompressorCycleInput;
    ReceiverTankCompressorCycleResult: ReceiverTankCompressorCycleResult;
};
