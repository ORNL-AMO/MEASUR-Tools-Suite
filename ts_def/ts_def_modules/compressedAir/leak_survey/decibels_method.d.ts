/**
 * @brief Input parameters for the decibels method compressed air leak calculation.
 * @details Two calibration reference points (A and B) define the interpolation grid.
 *          By convention, point A carries the lower decibel reference and point B the
 *          higher; the two reference pressures (`pressureA` and `pressureB`) have no
 *          required ordering.
 *
 * @var operatingTime double, annual system operating time in hours.
 * @var linePressure double, system line pressure at the leak location in psig.
 * @var decibels double, ultrasonic decibel level measured at the leak location in decibel.
 * @var decibelRatingA double, lower ultrasonic decibel reference rating for point A in decibel.
 * @var pressureA double, reference line pressure corresponding to point A in psig.
 * @var firstFlowA double, flow rate at point A in scfm.
 * @var secondFlowA double, flow rate at point A in scfm.
 * @var decibelRatingB double, upper ultrasonic decibel reference rating for point B in decibel.
 * @var pressureB double, reference line pressure corresponding to point B in psig.
 * @var firstFlowB double, flow rate for point B in scfm.
 * @var secondFlowB double, flow rate for point B in scfm.
 */
export interface DecibelsMethodInput {
    operatingTime: number;
    linePressure: number;
    decibels: number;
    decibelRatingA: number;
    pressureA: number;
    firstFlowA: number;
    secondFlowA: number;
    decibelRatingB: number;
    pressureB: number;
    firstFlowB: number;
    secondFlowB: number;
}

/**
 * @brief Result of the decibels method leak flow rate calculation.
 *
 * @var leakRateEstimate double, estimated compressed air leak flow rate in scfm.
 * @var annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface DecibelsMethodResult {
    leakRateEstimate: number;
    annualConsumption: number;
}

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the decibels method.
 * @details Uses bilinear interpolation across line pressure and ultrasonic decibel reference axes.
 * @note Reference pressures and decibel ratings should bracket measured values for best accuracy.
 * @param input Input for decibels method calculation.
 * @return DecibelsMethodResult containing `leakRateEstimate` [scfm] and `annualConsumption` [kscf].
 */
export function calculateDecibelsMethod(input: DecibelsMethodInput): DecibelsMethodResult;

/** Factory function to load the Decibels Method. */
export default function DecibelsMethodModule(): Promise<{
    calculateDecibelsMethod: typeof calculateDecibelsMethod;
}>;

