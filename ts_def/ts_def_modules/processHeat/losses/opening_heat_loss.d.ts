/**
 * Opening Heat Loss calculations.
 *
 * Calculates radiative heat loss from process heating equipment openings to
 * the surroundings. Provides functions for rectangular and circular openings,
 * as well as view factor calculations for both shapes. Calculation assumes
 * radiative losses only and does not account for convection or conduction.
 *
 */

/**
 * Calculate total radiative heat loss for a rectangular (quad) opening.
 *
 * @param emissivity Emissivity of the opening surface, unitless
 * @param length Length of opening, units in
 * @param width Height of opening, units in
 * @param ambientTemperature Ambient temperature, units degF
 * @param insideTemperature Inside temperature, units degF
 * @param percentTimeOpen Percentage of time the opening is open, units %
 * @param viewFactor View factor for radiative heat transfer, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function openingTotalHeatLossQuad(
    emissivity: number,
    length: number,
    width: number,
    ambientTemperature: number,
    insideTemperature: number,
    percentTimeOpen: number,
    viewFactor: number
): number;

/**
 * Calculate total radiative heat loss for a circular opening.
 *
 * @param emissivity Emissivity of the opening surface, unitless
 * @param diameter Diameter of opening, units in
 * @param ambientTemperature Ambient temperature, units degF
 * @param insideTemperature Inside temperature, units degF
 * @param percentTimeOpen Percentage of time the opening is open, units %
 * @param viewFactor View factor for radiative heat transfer, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function openingTotalHeatLossCircular(
    emissivity: number,
    diameter: number,
    ambientTemperature: number,
    insideTemperature: number,
    percentTimeOpen: number,
    viewFactor: number
): number;

/**
 * Calculate the view factor for a circular opening.
 *
 * @param thickness Process heating equipment wall thickness, units in
 * @param diameter Diameter of opening, units in
 * @returns View factor for radiative heat transfer, unitless
 */
export function calculateViewFactorCircular(
    thickness: number,
    diameter: number
): number;

/**
 * Calculate the view factor for a rectangular (quad) opening.
 *
 * @param thickness Process heating equipment wall thickness, units in
 * @param length Length of opening, units in
 * @param height Height of opening, units in
 * @returns View factor for radiative heat transfer, unitless
 */
export function calculateViewFactorQuad(
    thickness: number,
    length: number,
    height: number
): number;

export type OpeningHeatLossModule = {
    openingTotalHeatLossQuad: typeof openingTotalHeatLossQuad;
    openingTotalHeatLossCircular: typeof openingTotalHeatLossCircular;
    calculateViewFactorCircular: typeof calculateViewFactorCircular;
    calculateViewFactorQuad: typeof calculateViewFactorQuad;
};
