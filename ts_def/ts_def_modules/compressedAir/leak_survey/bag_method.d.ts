/**
 * Leak Survey - Bag Method
 *
 * Estimates compressed air leak flow and annual consumption using a timed
 * bag-fill field measurement.
 */

/**
 * Input parameters for the bag method compressed air leak calculation.
 *
 * @property operatingTime double, annual system operating time in hours.
 * @property bagFillTime double, time for the measurement bag to fill with leaked air in seconds.
 * @property bagVolume double, pre-measured volume of the measurement bag in cubic feet.
 */
export interface BagMethodInput {
    operatingTime: number;
    bagFillTime: number;
    bagVolume: number;
}

/**
 * Result of the bag method leak flow rate calculation.
 *
 * @property flowRate double, measured compressed air leak flow rate in scfm.
 * @property annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface BagMethodResult {
    flowRate: number;
    annualConsumption: number;
}

/**
 * Estimates compressed air leak flow rate and annual consumption using the bag method.
 * @details The leak flow rate is the bag volume divided by the fill time (converted to minutes).
 *          Annual consumption scales by operating hours and converts to kiloscf.
 * @param input {@link BagMethodInput} parameters for bag method calculation.
 * @returns {@link BagMethodResult} containing `flowRate` [scfm] and `annualConsumption` [kscf].
 */
export function calculateBagMethod(input: BagMethodInput): BagMethodResult;

export type BagMethodModule = {
    calculateBagMethod: typeof calculateBagMethod;
};
