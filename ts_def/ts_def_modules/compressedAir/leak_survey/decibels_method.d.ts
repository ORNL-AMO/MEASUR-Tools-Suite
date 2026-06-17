/**
 * Leak Survey - Decibels Method
 *
 * Estimates compressed air leak rate and annual consumption from ultrasonic
 * decibel readings and calibration points.
 */

/**
 * Input parameters for the decibels method compressed air leak calculation.
 * @details Two calibration reference points (A and B) define the interpolation grid.
 *          By convention, point A carries the lower decibel reference and point B the
 *          higher; the two reference pressures (`pressureA` and `pressureB`) have no
 *          required ordering.
 *
 * @property operatingTime double, annual system operating time in hours.
 * @property linePressure double, system line pressure at the leak location in psig.
 * @property decibels double, ultrasonic decibel level measured at the leak location in decibel.
 * @property decibelRatingA double, lower ultrasonic decibel reference rating for point A in decibel.
 * @property pressureA double, reference line pressure corresponding to point A in psig.
 * @property firstFlowA double, flow rate at point A in scfm.
 * @property secondFlowA double, flow rate at point A in scfm.
 * @property decibelRatingB double, upper ultrasonic decibel reference rating for point B in decibel.
 * @property pressureB double, reference line pressure corresponding to point B in psig.
 * @property firstFlowB double, flow rate for point B in scfm.
 * @property secondFlowB double, flow rate for point B in scfm.
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
 * Result of the decibels method leak flow rate calculation.
 *
 * @property leakRateEstimate double, estimated compressed air leak flow rate in scfm.
 * @property annualConsumption double, estimated annual air loss from the leak in kscf.
 */
export interface DecibelsMethodResult {
    leakRateEstimate: number;
    annualConsumption: number;
}

/**
 * Estimates compressed air leak flow rate and annual consumption using the decibels method.
 * @details Uses bilinear interpolation across line pressure and ultrasonic decibel reference axes.
 * @note Reference pressures and decibel ratings should bracket measured values for best accuracy.
 * @param input {@link DecibelsMethodInput} for decibels method calculation.
 * @returns {@link DecibelsMethodResult} containing `leakRateEstimate` [scfm] and `annualConsumption` [kscf].
 */
export function calculateDecibelsMethod(input: DecibelsMethodInput): DecibelsMethodResult;

export type DecibelsMethodModule = {
    calculateDecibelsMethod: typeof calculateDecibelsMethod;
};
