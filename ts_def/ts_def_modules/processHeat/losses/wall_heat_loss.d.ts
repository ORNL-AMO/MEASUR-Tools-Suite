/**
 * Wall Heat Loss calculations.
 *
 * Calculates total, convective, and radiative heat loss from a furnace wall
 * to the ambient environment. Combines Stefan-Boltzmann radiative losses and
 * empirical convective correlations accounting for surface shape, wind speed,
 * and temperature difference.
 *
 */

/**
 * Calculate total heat loss from a wall to ambient (convective + radiative).
 *
 * @param surface_area Total exterior surface area of the wall, units sqft
 * @param ambient_temperature Ambient temperature on the exterior of the wall, units degF
 * @param surface_temperature Average surface temperature on the exterior of the wall, units degF
 * @param wind_speed Average wind speed on the exterior of the wall, units mph
 * @param surface_emissivity Surface emissivity of the wall, unitless
 * @param shape_factor Shape factor corresponding to the wall's surface configuration, unitless
 * @param correction_factor Correction factor for the wall heat loss calculations, unitless
 * @returns Total heat loss, units BTU/hr
 */
export function wallTotalHeatLoss(
    surface_area: number,
    ambient_temperature: number,
    surface_temperature: number,
    wind_speed: number,
    surface_emissivity: number,
    shape_factor: number,
    correction_factor: number
): number;

/**
 * Calculate convective heat loss from the wall to ambient.
 *
 * Uses an empirical correlation accounting for surface shape/orientation,
 * temperature difference, mean temperature, and wind speed.
 *
 * @param shape_factor Shape factor corresponding to the wall's surface configuration, unitless
 * @param wind_speed Average wind speed on the exterior of the wall, units mph
 * @param surface_area Total exterior surface area of the wall, units sqft
 * @param surface_temperature Average surface temperature on the exterior of the wall, units degF
 * @param ambient_temperature Ambient temperature on the exterior of the wall, units degF
 * @returns Convective heat loss, units BTU/hr
 */
export function wallConvectiveHeatLoss(
    shape_factor: number,
    wind_speed: number,
    surface_area: number,
    surface_temperature: number,
    ambient_temperature: number
): number;

/**
 * Calculate radiative heat loss from the wall to ambient.
 *
 * Uses the Stefan-Boltzmann law based on the fourth power of absolute
 * temperatures of the surface and ambient, surface area, and surface emissivity.
 *
 * @param surface_emissivity Surface emissivity of the wall, unitless
 * @param surface_area Total exterior surface area of the wall, units sqft
 * @param surface_temperature Average surface temperature on the exterior of the wall, units degF
 * @param ambient_temperature Ambient temperature on the exterior of the wall, units degF
 * @returns Radiative heat loss, units BTU/hr
 */
export function wallRadiativeHeatLoss(
    surface_emissivity: number,
    surface_area: number,
    surface_temperature: number,
    ambient_temperature: number
): number;

export type WallHeatLossModule = {
    wallTotalHeatLoss: typeof wallTotalHeatLoss;
    wallConvectiveHeatLoss: typeof wallConvectiveHeatLoss;
    wallRadiativeHeatLoss: typeof wallRadiativeHeatLoss;
};
