/**
 * Leak Survey - Orifice Method
 *
 * Estimates compressed air leak flow and annual consumption using orifice
 * choked-flow relations.
 */

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
    /** annual system operating time in hours. */
    operatingTime: number;
    /** compressed air temperature at the leak point in degrees Fahrenheit. */
    airTemp: number;
    /** local atmospheric (barometric) pressure units psia. */
    atmPressure: number;
    /** orifice discharge coefficient (unitless). */
    dischargeCoef: number;
    /** orifice (leak opening) diameter in inches. */
    diameter: number;
    /** compressed air supply pressure (gauge) units psig. */
    supplyPressure: number;
    /** Number of identical orifice leak points, count. */
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
    /** air density at standard atmospheric conditions in lb/ft^3. */
    standardDensity: number;
    /** air density at the isentropic sonic throat in lb/ft^3. */
    sonicDensity: number;
    /** sonic air velocity at the orifice throat in ft/s. */
    leakVelocity: number;
    /** mass flow rate of leaked air through one orifice in lbm/min. */
    leakRateLBMmin: number;
    /** volumetric flow rate of leaked air through one orifice units scfm. */
    leakRateScfm: number;
    /** total volumetric leak flow rate through all orifices units scfm. */
    leakRateEstimate: number;
    /** estimated annual compressed air loss units kscf. */
    annualConsumption: number;
}

/**
 * Estimates compressed air leak flow rate and annual consumption using the orifice method.
 * @details Applies isentropic choked-flow relations with pressure and leak geometry inputs.
 * @note Supply pressure is provided in psig and converted to absolute pressure internally.
 * @param input {@link OrificeMethodInput} for orifice method calculation.
 * @returns {@link OrificeMethodResult} containing intermediate and final flow values.
 */
export function calculateOrificeMethod(input: OrificeMethodInput): OrificeMethodResult;

export type OrificeMethodModule = {
    calculateOrificeMethod: typeof calculateOrificeMethod;
};
