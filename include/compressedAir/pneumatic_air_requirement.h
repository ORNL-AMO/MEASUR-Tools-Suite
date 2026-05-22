#pragma once

/**
 * @ingroup pneumatic_air_requirement_calculator
 * @file pneumatic_air_requirement.h
 * @brief Declarations for pneumatic cylinder air consumption calculations.
 * @details Provides functions to compute the air volume consumed per minute by a
 *          pneumatic cylinder for both single-acting and double-acting piston
 *          configurations. All calculations use U.S. customary units.
 * @see @ref pneumatic_air_requirement_calculator for formula derivations and symbol definitions.
 */

#include "physics/constants.h"

/**
 * @ingroup pneumatic_air_requirement_calculator
 * @namespace pneumatic_air_requirement
 * @brief Pneumatic cylinder air consumption calculations for single-acting and double-acting pistons.
 * @details This namespace provides two calculation modes for sizing the compressed air
 *          supply to a pneumatic cylinder:
 *
 * - **Single-Acting** – the compressed air acts on one side of the piston only (the
 *   return stroke is spring- or gravity-driven). Air is consumed only during the
 *   power stroke.
 * - **Double-Acting** – compressed air acts alternately on both sides of the piston.
 *   Air is consumed on both strokes, but the rod side has a slightly smaller effective
 *   area due to the piston rod occupying part of the bore.
 *
 * Both calculations determine the cylinder's volumetric air intake per minute (at the
 * cylinder inlet conditions), then multiply by the compression ratio to express the
 * result in standard cubic feet per minute — the free-air equivalent that the
 * compressor must supply.
 *
 * @see @ref pneumatic_air_requirement_calculator
 */
namespace pneumatic_air_requirement {

// ============================================================
//  Single-Acting Piston
// ============================================================

/**
 * @ingroup pneumatic_air_requirement_calculator
 * @struct SingleActingInput
 * @brief Input parameters for the single-acting piston air requirement calculation.
 */
struct SingleActingInput {
    double cylinder_diameter = 0.0; ///< Inner bore diameter of the cylinder @unitb{\inch}
    double cylinder_stroke   = 0.0; ///< Piston travel distance per stroke @unitb{\inch}
    double air_pressure      = 0.0; ///< Operating gauge pressure at the cylinder inlet @unitb{\psi}
    double cycles_per_min    = 0.0; ///< Number of complete cycles (two strokes) per minute @unitb{\per\minute}
};

// ============================================================
//  Double-Acting Piston
// ============================================================

/**
 * @ingroup pneumatic_air_requirement_calculator
 * @struct DoubleActingInput
 * @brief Input parameters for the double-acting piston air requirement calculation.
 */
struct DoubleActingInput {
    double cylinder_diameter  = 0.0; ///< Inner bore diameter of the cylinder @unitb{\inch}
    double cylinder_stroke    = 0.0; ///< Piston travel distance per stroke @unitb{\inch}
    double piston_rod_diameter = 0.0; ///< Diameter of the piston rod @unitb{\inch}
    double air_pressure       = 0.0; ///< Operating gauge pressure at the cylinder inlet @unitb{\psi}
    double cycles_per_min     = 0.0; ///< Number of complete cycles (two strokes) per minute @unitb{\per\minute}
};

// ============================================================
//  Shared Result
// ============================================================

/**
 * @ingroup pneumatic_air_requirement_calculator
 * @struct AirRequirementResult
 * @brief Result of a pneumatic cylinder air requirement calculation.
 */
struct AirRequirementResult {
    double volume_air_intake_piston          = 0.0; ///< Cylinder air intake volume per minute at cylinder conditions @unitb{\cubicFoot\per\minute}
    double compression_ratio                 = 0.0; ///< Ratio of absolute working pressure to atmospheric pressure @unitb{\unitless}
    double air_requirement_pneumatic_cylinder = 0.0; ///< Free-air equivalent consumption (scfm) @unitb{\standardCubicFeetPerMinute}
};

// ============================================================
//  Calculation Functions
// ============================================================

/**
 * @brief Calculates the air requirement for a single-acting pneumatic cylinder.
 * @details A single-acting cylinder consumes compressed air on the power stroke only.
 *          The piston cross-sectional area is computed from the bore diameter using
 *          @math{\pi/4 \cdot D^2}, and the swept volume per cycle is converted from
 *          cubic inches to cubic feet. The compression ratio scales the cylinder-inlet
 *          volume to the free-air equivalent that the compressor must deliver.
 *
 * **Cylinder Air Intake Volume:**
 * @formula{pneumatic-air-requirement-single-acting-volume;
 *   Q_{cyl} = \frac{\frac{\pi}{4} \cdot D^2 \cdot L \cdot n}{k_{in^3}}
 * }
 *
 * **Compression Ratio:**
 * @formula{pneumatic-air-requirement-compression-ratio;
 *   r_c = \frac{P_{gauge} + P_{atm}}{P_{atm}}
 * }
 *
 * **Free-Air Requirement:**
 * @formula{pneumatic-air-requirement-single-acting-scfm;
 *   Q_{free} = Q_{cyl} \cdot r_c
 * }
 *
 * where:
 * @symtable
 * @symrow{Q_{cyl}; Cylinder air intake volume per minute at cylinder conditions; \cubicFoot\per\minute}
 * @symrow{Q_{free}; Free-air equivalent consumption (scfm); \standardCubicFeetPerMinute}
 * @symrow{D; Inner bore diameter of the cylinder; \inch}
 * @symrow{L; Piston stroke length; \inch}
 * @symrow{n; Number of complete cycles per minute; \per\minute}
 * @symrow{k_{in^3}; Cubic inches per cubic foot (1728); \inch\cubed\per\cubicFoot}
 * @symrow{r_c; Compression ratio (absolute working pressure / atmospheric pressure); \unitless}
 * @symrow{P_{gauge}; Operating gauge pressure at the cylinder inlet; \psi}
 * @symrow{P_{atm}; Atmospheric pressure (14.7 psia); \psi}
 * @endsymtable
 *
 * @note @math{P_{atm}} is 14.7 psia at sea level (see @ref physics::us::kAtmosphericPressurePsi).
 *       @math{k_{in^3} = 1728} is the exact number of cubic inches in one cubic foot
 *       (see @ref physics::conversions::kFt3ToIn3).
 *       The factor @math{\pi/4 \approx 0.7854} gives the circular cross-sectional area of
 *       the bore in square inches when the diameter is in inches.
 *
 * @param[in] input  SingleActingInput
 * @return AirRequirementResult containing the cylinder intake volume (cfm), compression ratio,
 *         and free-air requirement (scfm).
 */
AirRequirementResult calculateSingleActing(const SingleActingInput& input);

/**
 * @brief Calculates the air requirement for a double-acting pneumatic cylinder.
 * @details A double-acting cylinder consumes compressed air on both the forward and
 *          return strokes. The forward stroke acts on the full bore area; the return
 *          stroke acts on the annular area between the bore and the piston rod. The
 *          net air intake is the sum of both swept volumes expressed in cubic feet per
 *          minute, and the compression ratio converts this to the free-air equivalent.
 *
 * **Combined Cylinder Air Intake Volume (forward + return strokes):**
 * @formula{pneumatic-air-requirement-double-acting-volume;
 *   Q_{cyl} = \frac{2 \cdot k_{in^3} \cdot Q_{sa} - \frac{\pi}{4} \cdot d_r^2 \cdot L \cdot n}{k_{in^3}}
 * }
 *
 * where @math{Q_{sa}} is the single-acting intake volume computed with the same bore,
 * stroke, and cycle rate. Equivalently:
 *
 * @formula{pneumatic-air-requirement-double-acting-expanded;
 *   Q_{cyl} = \frac{\frac{\pi}{4} \cdot (2 D^2 - d_r^2) \cdot L \cdot n}{k_{in^3}}
 * }
 *
 * **Compression Ratio** and **Free-Air Requirement** are the same as for the
 * single-acting case (see above).
 *
 * where:
 * @symtable
 * @symrow{Q_{cyl}; Combined cylinder air intake volume per minute; \cubicFoot\per\minute}
 * @symrow{Q_{sa}; Single-acting intake volume (bore stroke, no rod); \cubicFoot\per\minute}
 * @symrow{D; Inner bore diameter of the cylinder; \inch}
 * @symrow{d_r; Piston rod diameter; \inch}
 * @symrow{L; Piston stroke length; \inch}
 * @symrow{n; Number of complete cycles per minute; \per\minute}
 * @symrow{k_{in^3}; Cubic inches per cubic foot (1728); \inch\cubed\per\cubicFoot}
 * @symrow{r_c; Compression ratio; \unitless}
 * @symrow{P_{gauge}; Operating gauge pressure; \psi}
 * @symrow{P_{atm}; Atmospheric pressure (14.7 psia); \psi}
 * @endsymtable
 *
 * @note The factor @math{2 k_{in^3} \cdot Q_{sa}} recovers the bore swept volume in
 *       cubic inches before subtracting the rod cross-section contribution. The result
 *       is then divided by @math{k_{in^3}} to return to cubic feet per minute.
 *
 * @param[in] input  DoubleActingInput
 * @return AirRequirementResult containing the cylinder intake volume (cfm), compression ratio,
 *         and free-air requirement (scfm).
 */
AirRequirementResult calculateDoubleActing(const DoubleActingInput& input);

} // namespace pneumatic_air_requirement
