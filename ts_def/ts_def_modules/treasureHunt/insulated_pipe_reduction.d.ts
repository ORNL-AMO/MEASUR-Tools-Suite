/**
 * Insulated Pipe Heat Loss calculations.
 *
 * Provides a function-based API for estimating heat loss per unit length and annual heat loss
 * from a hot pipe, with or without insulation. The iterative solver converges on the surface
 * temperature and interface temperature using heat transfer correlations for forced and free
 * convection and radiation. Air properties are computed from fourth-order polynomial fits to
 * tabulated data.
 */

// ---------------------------------------------------------------------------
// Input / Output value objects
// ---------------------------------------------------------------------------

/**
 * Input parameters for the insulated pipe heat loss calculation.
 *
 * All temperatures are in Kelvin and all lengths are in meters. The material coefficient
 * arrays must each contain exactly 5 values representing polynomial fit coefficients
 * (order 4 down to order 0) for thermal conductivity as a function of temperature.
 *
 * @property operatingHours number, annual operating hours, units hours/year
 * @property pipeLength number, total pipe length, units m
 * @property pipeDiameter number, outer pipe diameter, units m
 * @property pipeThickness number, pipe wall thickness, units m
 * @property pipeTemperature number, pipe inner surface (fluid) temperature, units K
 * @property ambientTemperature number, ambient air temperature, units K
 * @property windVelocity number, wind velocity across the pipe, units m/s
 * @property systemEfficiency number, heating system efficiency (dimensionless, 0-1)
 * @property insulationThickness number, insulation thickness; set <= 0 for uninsulated pipe, units m
 * @property pipeEmissivity number, emissivity of the bare pipe outer surface (dimensionless, 0-1)
 * @property jacketEmissivity number, emissivity of the insulation jacket outer surface (dimensionless, 0-1)
 * @property pipeMaterialCoefficients number[], 4th-order polynomial fit coefficients for pipe thermal conductivity
 * @property insulationMaterialCoefficients number[], 4th-order polynomial fit coefficients for insulation thermal conductivity
 */
export interface InsulatedPipeInput {
    /** Annual operating hours, units hours/year */
    operatingHours: number;
    /** Total pipe length, units m */
    pipeLength: number;
    /** Outer pipe diameter, units m */
    pipeDiameter: number;
    /** Pipe wall thickness, units m */
    pipeThickness: number;
    /** Pipe inner surface (fluid) temperature, units K */
    pipeTemperature: number;
    /** Ambient air temperature, units K */
    ambientTemperature: number;
    /** Wind velocity across the pipe, units m/s */
    windVelocity: number;
    /** Heating system efficiency (dimensionless, 0-1) */
    systemEfficiency: number;
    /** Insulation thickness; set <= 0 for uninsulated (bare) pipe, units m */
    insulationThickness: number;
    /** Emissivity of the bare pipe outer surface (dimensionless, 0-1) */
    pipeEmissivity: number;
    /** Emissivity of the insulation jacket outer surface (dimensionless, 0-1) */
    jacketEmissivity: number;
    /** 4th-order polynomial fit coefficients (5 values, order 4 -> 0) for pipe thermal conductivity, units W/(m.K) */
    pipeMaterialCoefficients: number[];
    /** 4th-order polynomial fit coefficients (5 values, order 4 -> 0) for insulation thermal conductivity, units W/(m.K) */
    insulationMaterialCoefficients: number[];

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

/**
 * Result object returned by {@link insulatedPipeReduction} and heat-loss helper functions.
 *
 * @property heatLossPerLength number, converged heat loss per unit length, units W/m
 * @property annualHeatLoss number, annual heat loss for the full pipe, units Wh/year
 */
export interface InsulatedPipeOutput {
    /** Converged heat loss per unit length, units W/m */
    heatLossPerLength: number;
    /** Annual heat loss for the full pipe, units Wh/year */
    annualHeatLoss: number;

    /** Frees the underlying resource; must be called when finished with the instance */
    delete(): void;
}

// ---------------------------------------------------------------------------
// Calculator functions
// ---------------------------------------------------------------------------

/**
 * Calculate heat loss per unit length and annual heat loss for a pipe.
 *
 * Dispatches to {@link insulatedPipeHeatLoss} or {@link bareInsulatedPipeHeatLoss} based on
 * whether insulation thickness is positive. The iterative solver (max 30 iterations) converges
 * when the change in heat loss per unit length is less than 0.0001 W/m.
 *
 * @param input {@link InsulatedPipeInput} with all pipe and insulation geometry, material
 *   properties, and environmental conditions.
 * @returns {@link InsulatedPipeOutput} with heat loss per unit length (W/m) and annual heat loss (Wh/year).
 */
export function insulatedPipeReduction(input: InsulatedPipeInput): InsulatedPipeOutput;

/**
 * Calculate heat loss per unit length for a pipe with insulation.
 *
 * Iteratively solves for surface temperature and pipe-insulation interface temperature using
 * forced and free convection and radiation on the insulation jacket outer surface.
 *
 * @param input {@link InsulatedPipeInput} describing the insulated pipe system.
 * @returns {@link InsulatedPipeOutput} with heat loss per unit length (W/m) and annual heat loss (Wh/year).
 */
export function insulatedPipeHeatLoss(input: InsulatedPipeInput): InsulatedPipeOutput;

/**
 * Calculate heat loss per unit length for an uninsulated (bare) pipe.
 *
 * Iteratively solves for surface temperature using convection and radiation directly on the bare
 * pipe outer surface. No insulation resistance is included. The `insulationThickness` field of
 * the input is ignored.
 *
 * @param input {@link InsulatedPipeInput} describing the bare pipe system.
 * @returns {@link InsulatedPipeOutput} with heat loss per unit length (W/m) and annual heat loss (Wh/year).
 */
export function bareInsulatedPipeHeatLoss(input: InsulatedPipeInput): InsulatedPipeOutput;

/**
 * Compute the thermal resistance of a cylindrical shell.
 *
 * @param diameter_a Outer diameter of the shell, units m.
 * @param diameter_b Outer diameter used in the logarithm (numerator), units m.
 * @param diameter_c Inner diameter used in the logarithm (denominator), units m.
 * @param thermal_conductivity Thermal conductivity of the shell material, units W/(m.K).
 * @returns Thermal resistance per unit length, units (m.K)/W.
 */
export function insulatedPipeThermalResistance(
    diameter_a: number,
    diameter_b: number,
    diameter_c: number,
    thermal_conductivity: number
): number;

/**
 * Compute the Reynolds number for external cross-flow over a cylinder.
 *
 * @param diameter Outer diameter of the cylinder, units m.
 * @param wind_velocity Free-stream wind velocity, units m/s.
 * @param kinematic_viscosity Kinematic viscosity of air at the film temperature, units sqm/s.
 * @returns Dimensionless Reynolds number.
 */
export function insulatedPipeReynoldsNumber(
    diameter: number,
    wind_velocity: number,
    kinematic_viscosity: number
): number;

/**
 * Compute the Rayleigh number for natural convection from a horizontal cylinder.
 *
 * @param expansion_coefficient Volumetric thermal expansion coefficient of air, units 1/K.
 * @param surface_temperature Outer surface temperature, units K.
 * @param ambient_temperature Ambient air temperature, units K.
 * @param diameter Outer diameter of the cylinder, units m.
 * @param kinematic_viscosity Kinematic viscosity of air at the film temperature, units sqm/s.
 * @param alpha Thermal diffusivity of air at the film temperature, units sqm/s.
 * @returns Dimensionless Rayleigh number.
 */
export function insulatedPipeRayleighNumber(
    expansion_coefficient: number,
    surface_temperature: number,
    ambient_temperature: number,
    diameter: number,
    kinematic_viscosity: number,
    alpha: number
): number;

/**
 * Combine forced and free convection Nusselt numbers using the Churchill-Bernstein
 * fourth-power sum rule: Nu = (Nu_forced^4 + Nu_free^4)^(1/4).
 *
 * @param nusselt_forced Forced-convection Nusselt number (dimensionless).
 * @param nusselt_free Free-convection Nusselt number (dimensionless).
 * @returns Combined Nusselt number (dimensionless).
 */
export function insulatedPipeNusseltNumber(
    nusselt_forced: number,
    nusselt_free: number
): number;

/**
 * Compute the forced-convection Nusselt number for external flow over a cylinder
 * using the Churchill-Bernstein correlation.
 *
 * @param reynolds Reynolds number (dimensionless).
 * @param prandtl Prandtl number of air at film temperature (dimensionless).
 * @returns Forced-convection Nusselt number (dimensionless).
 */
export function insulatedPipeNusseltForcedConvection(
    reynolds: number,
    prandtl: number
): number;

/**
 * Compute the free-convection Nusselt number for a horizontal cylinder using the
 * Churchill-Chu correlation.
 *
 * @param rayleigh Rayleigh number (dimensionless).
 * @param prandtl Prandtl number of air at film temperature (dimensionless).
 * @returns Free-convection Nusselt number (dimensionless).
 */
export function insulatedPipeNusseltFreeConvection(
    rayleigh: number,
    prandtl: number
): number;

/**
 * Compute the linearized radiative heat transfer coefficient.
 *
 * @param emissivity Surface emissivity (dimensionless, 0-1).
 * @param surface_temperature Outer surface temperature, units K.
 * @param ambient_temperature Ambient air temperature, units K.
 * @returns Radiative heat transfer coefficient, units W/(sqm.K).
 */
export function insulatedPipeRadiativeHeatTransferCoeff(
    emissivity: number,
    surface_temperature: number,
    ambient_temperature: number
): number;

/**
 * Compute the convective heat transfer coefficient from a Nusselt number.
 *
 * @param nusselt Combined Nusselt number (dimensionless).
 * @param air_conductivity Thermal conductivity of air at film temperature, units W/(m.K).
 * @param diameter Outer diameter of the surface, units m.
 * @returns Convective heat transfer coefficient, units W/(sqm.K).
 */
export function insulatedPipeConvectiveHeatTransferCoeff(
    nusselt: number,
    air_conductivity: number,
    diameter: number
): number;

export type InsulatedPipeReductionModule = {
    InsulatedPipeInput: InsulatedPipeInput;
    InsulatedPipeOutput: InsulatedPipeOutput;
    insulatedPipeReduction: typeof insulatedPipeReduction;
    insulatedPipeHeatLoss: typeof insulatedPipeHeatLoss;
    bareInsulatedPipeHeatLoss: typeof bareInsulatedPipeHeatLoss;
    insulatedPipeThermalResistance: typeof insulatedPipeThermalResistance;
    insulatedPipeReynoldsNumber: typeof insulatedPipeReynoldsNumber;
    insulatedPipeRayleighNumber: typeof insulatedPipeRayleighNumber;
    insulatedPipeNusseltNumber: typeof insulatedPipeNusseltNumber;
    insulatedPipeNusseltForcedConvection: typeof insulatedPipeNusseltForcedConvection;
    insulatedPipeNusseltFreeConvection: typeof insulatedPipeNusseltFreeConvection;
    insulatedPipeRadiativeHeatTransferCoeff: typeof insulatedPipeRadiativeHeatTransferCoeff;
    insulatedPipeConvectiveHeatTransferCoeff: typeof insulatedPipeConvectiveHeatTransferCoeff;
};
