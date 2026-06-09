/**
 * @brief Input parameters for the bag method compressed air leak calculation.
 *
 * @var operatingTime double, annual system operating time in hours.
 * @var bagFillTime double, time for the measurement bag to fill with leaked air in seconds.
 * @var bagVolume double, pre-measured volume of the measurement bag in cubic feet.
 */
export interface BagMethodInput {
    operatingTime: number;
    bagFillTime: number;
    bagVolume: number;
}

/**
 * @brief Result of the bag method leak flow rate calculation.
 *
 * @var flowRate double, measured compressed air leak flow rate in scfm.
 * @var annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface BagMethodResult {
    flowRate: number;
    annualConsumption: number;
}

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the bag method.
 * @details The leak flow rate is the bag volume divided by the fill time (converted to minutes).
 *          Annual consumption scales by operating hours and converts to kiloscf.
 * @param input Input parameters for bag method calculation.
 * @return BagMethodResult containing `flowRate` [scfm] and `annualConsumption` [kscf].
 */
export function calculateBagMethod(input: BagMethodInput): BagMethodResult;

/** Factory function to load the Bag Method. */
export default function BagMethodModule(): Promise<{
    calculateBagMethod: typeof calculateBagMethod;
}>;

