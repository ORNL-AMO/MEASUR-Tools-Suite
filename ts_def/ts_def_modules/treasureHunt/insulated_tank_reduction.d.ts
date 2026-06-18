/**
 * Insulated Tank Heat Loss calculations.
 *
 * Provides a function-based API for estimating heat loss and annual energy
 * cost for a hot vertical cylindrical tank, with or without thermal insulation.
 * Air properties are evaluated at the ambient temperature using fourth-order
 * polynomial fits to tabulated U.S. customary air data.
 */

// ---------------------------------------------------------------------------
// Input / Output value objects
// ---------------------------------------------------------------------------

/**
 * Input parameters for the insulated tank heat loss calculation.
 *
 * Temperatures are in degrees Rankine. Geometry (height, diameter,
 * thickness) is in feet. Thermal conductivities are in BTU/(hr.ft.degF).
 * System efficiency is a fraction (0-1). Set `insulationThickness <= 0` to
 * compute heat loss for a bare (uninsulated) tank.
 *
 * @property operatingHours number, annual operating hours, units hours/year
 * @property tankHeight number, tank lateral height, units ft
 * @property tankDiameter number, tank inner diameter, units ft
 * @property tankThickness number, tank wall thickness, units ft
 * @property tankEmissivity number, emissivity of the bare tank outer surface (0-1)
 * @property tankConductivity number, thermal conductivity of the tank wall material, units BTU/(hr.ft.degF)
 * @property tankTemperature number, temperature of the tank fluid (inner surface), units Rankine
 * @property ambientTemperature number, ambient air temperature, units Rankine
 * @property systemEfficiency number, heating system efficiency (0-1)
 * @property insulationThickness number, insulation layer thickness; set <= 0 for bare tank, units ft
 * @property insulationConductivity number, thermal conductivity of the insulation material, units BTU/(hr.ft.degF)
 * @property jacketEmissivity number, emissivity of the insulation jacket outer surface (0-1)
 * @property surfaceTemperature number, outer surface temperature (jacket or bare tank outer wall), units Rankine
 */
export interface InsulatedTankInput {
    /** Annual operating hours, units hours/year */
    operatingHours: number;
    /** Tank lateral height, units ft */
    tankHeight: number;
    /** Tank inner diameter, units ft */
    tankDiameter: number;
    /** Tank wall thickness, units ft */
    tankThickness: number;
    /** Emissivity of the bare tank outer surface (0-1) */
    tankEmissivity: number;
    /** Thermal conductivity of the tank wall material, units BTU/(hr.ft.degF) */
    tankConductivity: number;
    /** Temperature of the tank fluid (inner surface), units Rankine */
    tankTemperature: number;
    /** Ambient air temperature, units Rankine */
    ambientTemperature: number;
    /** Heating system efficiency (0-1) */
    systemEfficiency: number;
    /** Insulation layer thickness; set <= 0 for bare tank, units ft */
    insulationThickness: number;
    /** Thermal conductivity of the insulation material, units BTU/(hr.ft.degF) */
    insulationConductivity: number;
    /** Emissivity of the insulation jacket outer surface (0-1) */
    jacketEmissivity: number;
    /** Outer surface temperature (jacket or bare tank outer wall), units Rankine */
    surfaceTemperature: number;
}

/**
 * Result object returned by {@link insulatedTankReduction} and heat-loss helper functions.
 *
 * @property heatLoss number, instantaneous heat loss (scaled), units BTU/hr per 10^5
 * @property annualHeatLoss number, annual heat loss (scaled, efficiency-adjusted), units BTU per 10^6
 */
export interface InsulatedTankOutput {
    /** Instantaneous heat loss (scaled), units BTU/hr per 10^5 */
    heatLoss: number;
    /** Annual heat loss (scaled, efficiency-adjusted), units BTU per 10^6 */
    annualHeatLoss: number;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate heat loss and annual heat loss for a tank.
 *
 * Dispatches to {@link insulatedTankHeatLoss} or {@link bareTankHeatLoss}
 * based on whether `insulationThickness` is positive.
 *
 * @param input {@link InsulatedTankInput} with tank geometry, material properties,
 *   operating conditions, and insulation parameters.
 * @returns {@link InsulatedTankOutput} with heat loss and annual heat loss.
 */
export function insulatedTankReduction(input: InsulatedTankInput): InsulatedTankOutput;

/**
 * Calculate heat loss for a tank wrapped in insulation.
 *
 * Air properties are evaluated at the ambient temperature. The outer surface
 * temperature (insulation jacket) drives the Rayleigh number and radiation term.
 *
 * @param input {@link InsulatedTankInput} describing the insulated tank system.
 * @returns {@link InsulatedTankOutput} with heat loss and annual heat loss.
 */
export function insulatedTankHeatLoss(input: InsulatedTankInput): InsulatedTankOutput;

/**
 * Calculate heat loss for an uninsulated (bare) tank.
 *
 * Air properties are evaluated at the ambient temperature. The tank fluid
 * temperature is used as the surface temperature driving the Rayleigh number
 * and radiation term.
 *
 * @param input {@link InsulatedTankInput} describing the bare tank system
 *   (`insulationThickness` and `insulationConductivity` are ignored).
 * @returns {@link InsulatedTankOutput} with heat loss and annual heat loss.
 */
export function bareTankHeatLoss(input: InsulatedTankInput): InsulatedTankOutput;

/**
 * Compute the Rayleigh number for natural convection along a vertical
 * cylinder in U.S. customary units.
 *
 * @param thermal_expansion Volumetric thermal expansion coefficient of air (1/T_ambient), units 1/Rankine.
 * @param surface_temperature Outer surface temperature, units Rankine.
 * @param ambient_temperature Ambient air temperature, units Rankine.
 * @param diameter Tank inner diameter, units ft.
 * @param kin_viscosity Kinematic viscosity of air, units sqft/s.
 * @param thermal_diffusivity Thermal diffusivity of air, units sqft/s.
 * @returns Dimensionless Rayleigh number.
 */
export function insulatedTankRayleighNumber(
    thermal_expansion: number,
    surface_temperature: number,
    ambient_temperature: number,
    diameter: number,
    kin_viscosity: number,
    thermal_diffusivity: number
): number;

/**
 * Compute the natural convection heat transfer coefficient for a vertical
 * cylinder using the Ra^(1/3) empirical correlation.
 *
 * @param rayleigh Rayleigh number (dimensionless).
 * @param conductivity Thermal conductivity of air, units BTU/(hr.ft.degF).
 * @param diameter Tank outer diameter, units ft.
 * @returns Natural convection heat transfer coefficient, units BTU/(hr.sqft.degF).
 */
export function insulatedTankNaturalConvectionCoeff(
    rayleigh: number,
    conductivity: number,
    diameter: number
): number;

export type InsulatedTankReductionModule = {
    insulatedTankReduction: typeof insulatedTankReduction;
    insulatedTankHeatLoss: typeof insulatedTankHeatLoss;
    bareTankHeatLoss: typeof bareTankHeatLoss;
    insulatedTankRayleighNumber: typeof insulatedTankRayleighNumber;
    insulatedTankNaturalConvectionCoeff: typeof insulatedTankNaturalConvectionCoeff;
};
