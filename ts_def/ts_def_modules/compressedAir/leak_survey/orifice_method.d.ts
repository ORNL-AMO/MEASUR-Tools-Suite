/**
 * @brief Input parameters for the orifice method compressed air leak calculation.
 *
 * @var operatingTime double, annual system operating time in hours.
 * @var airTemp double, compressed air temperature at the leak point in degrees Fahrenheit.
 * @var atmPressure double, local atmospheric (barometric) pressure in psia.
 * @var dischargeCoef double, orifice discharge coefficient (unitless).
 * @var diameter double, orifice (leak opening) diameter in inches.
 * @var supplyPressure double, compressed air supply pressure (gauge) in psig.
 * @var numOrifices int, number of identical orifice leak points.
 */
export interface OrificeMethodInput {
    operatingTime: number;
    airTemp: number;
    atmPressure: number;
    dischargeCoef: number;
    diameter: number;
    supplyPressure: number;
    numOrifices: number;
}

/**
 * @brief Result of the orifice method leak flow rate and annual consumption calculation.
 *
 * @var standardDensity double, air density at standard atmospheric conditions in lb/ft^3.
 * @var sonicDensity double, air density at the isentropic sonic throat in lb/ft^3.
 * @var leakVelocity double, sonic air velocity at the orifice throat in ft/s.
 * @var leakRateLBMmin double, mass flow rate of leaked air through one orifice in lbm/min.
 * @var leakRateScfm double, volumetric flow rate of leaked air through one orifice in scfm.
 * @var leakRateEstimate double, total volumetric leak flow rate through all orifices in scfm.
 * @var annualConsumption double, estimated annual compressed air loss in kscf.
 */
export interface OrificeMethodResult {
    standardDensity: number;
    sonicDensity: number;
    leakVelocity: number;
    leakRateLBMmin: number;
    leakRateScfm: number;
    leakRateEstimate: number;
    annualConsumption: number;
}

/**
 * @brief Estimates compressed air leak flow rate and annual consumption using the orifice method.
 * @details Applies isentropic choked-flow relations with pressure and leak geometry inputs.
 * @note Supply pressure is provided in psig and converted to absolute pressure internally.
 * @param input Input for orifice method calculation.
 * @return OrificeMethodResult containing intermediate and final flow values.
 */
export function calculateOrificeMethod(input: OrificeMethodInput): OrificeMethodResult;

/** Factory function to load the Orifice Method. */
export default function OrificeMethodModule(): Promise<{
    calculateOrificeMethod: typeof calculateOrificeMethod;
}>;

