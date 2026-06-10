/**
 * Input parameters for the orifice method compressed air leak calculation.
 *
 * @property operatingTime double, annual system operating time in hours.
 * @property airTemp double, compressed air temperature at the leak point in degrees Fahrenheit.
 * @property atmPressure double, local atmospheric (barometric) pressure in psia.
 * @property dischargeCoef double, orifice discharge coefficient (unitless).
 * @property diameter double, orifice (leak opening) diameter in inches.
 * @property supplyPressure double, compressed air supply pressure (gauge) in psig.
 * @property numOrifices int, number of identical orifice leak points.
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
 * Result of the orifice method leak flow rate and annual consumption calculation.
 *
 * @property standardDensity double, air density at standard atmospheric conditions in lb/ft^3.
 * @property sonicDensity double, air density at the isentropic sonic throat in lb/ft^3.
 * @property leakVelocity double, sonic air velocity at the orifice throat in ft/s.
 * @property leakRateLBMmin double, mass flow rate of leaked air through one orifice in lbm/min.
 * @property leakRateScfm double, volumetric flow rate of leaked air through one orifice in scfm.
 * @property leakRateEstimate double, total volumetric leak flow rate through all orifices in scfm.
 * @property annualConsumption double, estimated annual compressed air loss in kscf.
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
 * Estimates compressed air leak flow rate and annual consumption using the orifice method.
 * @details Applies isentropic choked-flow relations with pressure and leak geometry inputs.
 * @note Supply pressure is provided in psig and converted to absolute pressure internally.
 * @param input Input for orifice method calculation.
 * @returns OrificeMethodResult containing intermediate and final flow values.
 */
export function calculateOrificeMethod(input: OrificeMethodInput): OrificeMethodResult;

export type OrificeMethodModule = {
    calculateOrificeMethod: typeof calculateOrificeMethod;
    OrificeMethodInput: OrificeMethodInput;
    OrificeMethodResult: OrificeMethodResult;
};
