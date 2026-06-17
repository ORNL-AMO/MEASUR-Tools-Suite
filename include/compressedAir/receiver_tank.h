#pragma once

/**
 * @ingroup receiver_tank_calculator
 * @file receiver_tank.h
 * @brief Declarations for compressed air receiver tank sizing and capacity calculations.
 * @details Provides functions to size receiver tanks using four established
 *          engineering methods and to calculate the usable air storage capacity of an
 *          existing tank. All calculations use U.S. customary units.
 * @see @ref receiver_tank_calculator for formula derivations and symbol definitions.
 */

#include "physics/constants.h"

/**
 * @ingroup receiver_tank_calculator
 * @namespace receiver_tank
 * @brief Compressed air receiver tank sizing and usable capacity calculations.
 * @details This namespace provides four sizing methods and one capacity method:
 *
 * - **Usable Capacity** – determines how many standard cubic feet of air are
 *   actually available between two operating pressures.
 * - **General** – sizes a tank to satisfy a known air demand over an allowable
 *   pressure drop.
 * - **Dedicated Storage** – sizes a tank that must supply a sustained flow for a
 *   defined duration from stored pressure.
 * - **Metered Storage** – sizes a tank and calculates refill time when flow is
 *   throttled through a metering (needle) valve.
 * - **Bridging Compressor Reaction Delay** – sizes a tank that bridges the
 *   compressor reaction time for a demand event located at a known distance from
 *   the compressor room.
 * - **Compressor Cycle** – sizes a tank based on the compressor's duty cycle
 *   (load/unload times and rated capacity) and the operating pressure band.
 *
 * @see @ref receiver_tank_calculator
 */
namespace receiver_tank {

/// @brief U.S. customary conversion: gallons per cubic foot @unitb{\gallon\per\cubicFoot}
inline constexpr double kGallonsPerCubicFoot = 7.48;

/// @brief U.S. customary conversion: cubic feet per gallon @unitb{\cubicFoot\per\gallon}
inline constexpr double kCubicFeetPerGallon = 0.133681;

// ============================================================
//  Usable Air Capacity
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct UsableCapacityInput
 * @brief Input parameters for the usable air capacity calculation.
 */
struct UsableCapacityInput {
    double tank_size       = 0.0; ///< Tank volume @unitb{\gallon}
    double air_pressure_in  = 0.0; ///< Inlet (charging) pressure @unitb{\psi}
    double air_pressure_out = 0.0; ///< Outlet (cut-out) pressure @unitb{\psi}
};

/**
 * @ingroup receiver_tank_calculator
 * @struct UsableCapacityResult
 * @brief Result of the usable air capacity calculation.
 */
struct UsableCapacityResult {
    double usable_capacity = 0.0; ///< Usable air storage capacity @unitb{\scf}
};

/**
 * @brief Calculates the usable air capacity of a receiver tank.
 * @details Converts the tank volume to cubic feet and scales by the available
 *          pressure differential relative to atmospheric pressure:
 *
 * @formula{receiver-tank-usable-capacity;
 *   V_{usable} = \frac{V_{tank}}{k_{gal}} \cdot \frac{P_{in} - P_{out}}{P_{atm}}
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{usable}; Usable air storage capacity; \scf}
 * @symrow{V_{tank}; Tank volume; \gallon}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @symrow{P_{in}; Charging (inlet) pressure; \psi}
 * @symrow{P_{out}; Cut-out (outlet) pressure; \psi}
 * @symrow{P_{atm}; Atmospheric pressure (14.7 psia); \psi}
 * @endsymtable
 *
 * @note The 7.48 gal/ft³ factor is the standard US customary volumetric conversion.
 *       @math{P_{atm}} is 14.7 psia at sea level (see @ref physics::us::kAtmosphericPressurePsi).
 *
 * @param[in] input  UsableCapacityInput
 * @return UsableCapacityResult containing the usable capacity in scf.
 */
UsableCapacityResult calculateUsableCapacity(const UsableCapacityInput& input);

// ============================================================
//  General Method
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct GeneralInput
 * @brief Input parameters for the General sizing method.
 */
struct GeneralInput {
    double air_demand              = 0.0; ///< Air demand drawn from the tank @unitb{\cubicFoot}
    double allowable_pressure_drop = 0.0; ///< Tolerable pressure drop across the tank @unitb{\psi}
    double atmospheric_pressure    = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psi}
};

/**
 * @ingroup receiver_tank_calculator
 * @struct SizeResult
 * @brief Tank size result shared by the General, Dedicated Storage, and Bridging methods.
 */
struct SizeResult {
    double tank_size = 0.0; ///< Required receiver tank size @unitb{\gallon}
};

/**
 * @brief Calculates receiver tank size using the General method.
 * @details Sizes a receiver tank to deliver a known air demand while limiting
 *          the pressure drop to the specified allowable value:
 *
 * @formula{receiver-tank-general-size;
 *   V_{tank} = Q_{demand} \cdot \frac{P_{atm}}{\Delta P} \cdot k_{gal}
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{tank}; Required receiver tank size; \gallon}
 * @symrow{Q_{demand}; Air demand drawn from the tank; \cubicFoot}
 * @symrow{P_{atm}; Atmospheric pressure; \psi}
 * @symrow{\Delta P; Allowable pressure drop; \psi}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @endsymtable
 *
 * @note Use this method when the required tank size must be calculated from a
 *       known air demand and a pressure drop budget.
 *
 * @param[in] input  GeneralInput
 * @return SizeResult containing the required tank size in gallons.
 */
SizeResult calculateGeneralSize(const GeneralInput& input);

// ============================================================
//  Dedicated Storage Method
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct DedicatedStorageInput
 * @brief Input parameters for the Dedicated Storage sizing method.
 */
struct DedicatedStorageInput {
    double length_of_demand      = 0.0; ///< Duration of the air demand event @unitb{\minute}
    double air_flow_requirement  = 0.0; ///< Required air flow during the demand event @unitb{\cubicFoot\per\minute}
    double atmospheric_pressure  = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psi}
    double initial_tank_pressure = 0.0; ///< Tank pressure before releasing air @unitb{\psi}
    double final_tank_pressure   = 0.0; ///< Tank pressure after releasing air @unitb{\psi}
};

/**
 * @brief Calculates receiver tank size using the Dedicated Storage method.
 * @details Sizes a tank that must deliver a sustained air flow for a defined
 *          duration, drawing down from an initial to a final operating pressure:
 *
 * @formula{receiver-tank-dedicated-storage-size;
 *   V_{tank} = \frac{k_{gal} \cdot t_{demand} \cdot Q_{flow} \cdot P_{atm}}{P_1 - P_2}
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{tank}; Required receiver tank size; \gallon}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @symrow{t_{demand}; Duration of the air demand event; \minute}
 * @symrow{Q_{flow}; Required air flow rate; \cubicFoot\per\minute}
 * @symrow{P_{atm}; Atmospheric pressure; \psi}
 * @symrow{P_1; Initial tank pressure; \psi}
 * @symrow{P_2; Final tank pressure; \psi}
 * @endsymtable
 *
 * @note Use this method when a receiver must independently supply a process for
 *       a measured time period from stored compressed air.
 *
 * @param[in] input  DedicatedStorageInput
 * @return SizeResult containing the required tank size in gallons.
 */
SizeResult calculateDedicatedStorageSize(const DedicatedStorageInput& input);

// ============================================================
//  Metered Storage Method
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct MeteredStorageInput
 * @brief Input parameters for the Metered Storage sizing method.
 */
struct MeteredStorageInput {
    double length_of_demand       = 0.0; ///< Duration of the air demand event @unitb{\minute}
    double air_flow_requirement   = 0.0; ///< Required air flow during the demand event @unitb{\cubicFoot\per\minute}
    double atmospheric_pressure   = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psi}
    double initial_tank_pressure  = 0.0; ///< Tank pressure before releasing air @unitb{\psi}
    double final_tank_pressure    = 0.0; ///< Tank pressure after releasing air @unitb{\psi}
    double metered_flow_control   = 0.0; ///< Metering valve (needle valve) flow rate @unitb{\cubicFoot\per\minute}
};

/**
 * @ingroup receiver_tank_calculator
 * @struct MeteredStorageResult
 * @brief Result of the Metered Storage sizing calculation.
 */
struct MeteredStorageResult {
    double tank_size   = 0.0; ///< Required receiver tank size @unitb{\gallon}
    double refill_time = 0.0; ///< Time to refill the tank after a demand event @unitb{\second}
};

/**
 * @brief Calculates receiver tank size and refill time using the Metered Storage method.
 * @details The demand event draws air at @math{Q_{flow}} while the metering valve
 *          supplies air at the controlled rate @math{Q_{metered}}. Only the
 *          net demand @math{(Q_{flow} - Q_{metered})} depletes the stored volume.
 *
 * **Tank Size:**
 * @formula{receiver-tank-metered-storage-size;
 *   V_{tank} = \frac{k_{gal} \cdot t_{demand} \cdot (Q_{flow} - Q_{metered}) \cdot P_{atm}}{P_1 - P_2}
 * }
 *
 * **Refill Time:**
 * @formula{receiver-tank-metered-storage-refill;
 *   T_{refill} = \frac{60 \cdot V_{cf} \cdot (P_1 - P_2)}{Q_{metered} \cdot P_{atm}}
 * }
 *
 * where @math{V_{cf} = V_{tank} \cdot k_{cf}} is the tank volume in cubic feet, and:
 * @symtable
 * @symrow{V_{tank}; Required receiver tank size; \gallon}
 * @symrow{V_{cf}; Tank volume in cubic feet; \cubicFoot}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @symrow{k_{cf}; Cubic feet per gallon (0.133681); \cubicFoot\per\gallon}
 * @symrow{t_{demand}; Duration of the air demand event; \minute}
 * @symrow{Q_{flow}; Required air flow rate; \cubicFoot\per\minute}
 * @symrow{Q_{metered}; Metering valve flow rate; \cubicFoot\per\minute}
 * @symrow{P_{atm}; Atmospheric pressure; \psi}
 * @symrow{P_1; Initial tank pressure; \psi}
 * @symrow{P_2; Final tank pressure; \psi}
 * @symrow{T_{refill}; Tank refill time; \second}
 * @symrow{60; Seconds per minute conversion; \second\per\minute}
 * @endsymtable
 *
 * @note The factor of 60 in the refill formula converts the computed duration
 *       (in minutes, since @math{Q_{metered}} is in cfm) to seconds.
 *
 * @param[in] input  MeteredStorageInput
 * @return MeteredStorageResult containing tank size in gallons and refill time in seconds.
 */
MeteredStorageResult calculateMeteredStorageSize(const MeteredStorageInput& input);

// ============================================================
//  Bridging Compressor Reaction Delay Method
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct BridgingInput
 * @brief Input parameters for the Bridging Compressor Reaction Delay sizing method.
 */
struct BridgingInput {
    double distance_to_compressor_room = 0.0; ///< Distance from demand event to compressor room @unitb{\foot}
    double speed_of_air                = 0.0; ///< Speed of compressed air in the distribution piping @unitb{\foot\per\second}
    double atmospheric_pressure        = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psi}
    double air_demand_cfm              = 0.0; ///< Air demand at the event location @unitb{\cubicFoot\per\minute}
    double allowable_pressure_drop     = 0.0; ///< Tolerable pressure drop at the event @unitb{\psi}
};

/**
 * @brief Calculates receiver tank size using the Bridging Compressor Reaction Delay method.
 * @details Sizes a tank that must supply air for the time it takes the pressure
 *          signal to travel from the demand event back to the compressor room and
 *          for the compressor to respond. The transit time is:
 *          @math{t_{transit} = d_{pipe} / v_{air}} (seconds).
 *
 * @formula{receiver-tank-bridging-size;
 *   V_{tank} = \frac{d_{pipe}}{v_{air}} \cdot \frac{Q_{demand}}{60} \cdot \frac{P_{atm}}{\Delta P} \cdot k_{gal}
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{tank}; Required receiver tank size; \gallon}
 * @symrow{d_{pipe}; Distance from demand event to compressor room; \foot}
 * @symrow{v_{air}; Speed of air in the distribution piping; \foot\per\second}
 * @symrow{Q_{demand}; Air demand at the event location; \cubicFoot\per\minute}
 * @symrow{60; Minutes-to-seconds conversion; \second\per\minute}
 * @symrow{P_{atm}; Atmospheric pressure; \psi}
 * @symrow{\Delta P; Allowable pressure drop; \psi}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @endsymtable
 *
 * @note @math{d_{pipe} / v_{air}} is the signal transit time in seconds.
 *       Dividing @math{Q_{demand}} by 60 converts cfm to ft³/s so that the
 *       product gives a volume in ft³, which is then converted to gallons.
 *
 * @param[in] input  BridgingInput
 * @return SizeResult containing the required tank size in gallons.
 */
SizeResult calculateBridgingSize(const BridgingInput& input);

// ============================================================
//  Compressor Cycle Method
// ============================================================

/**
 * @ingroup receiver_tank_calculator
 * @struct CompressorCycleInput
 * @brief Input parameters for the Compressor Cycle sizing method.
 */
struct CompressorCycleInput {
    double load_time            = 0.0; ///< Compressor loaded time per cycle @unitb{\minute}
    double unload_time          = 0.0; ///< Compressor unloaded time per cycle @unitb{\minute}
    double compressor_capacity  = 0.0; ///< Rated compressor output at full load @unitb{\cubicFoot\per\minute}
    double unload_pressure      = 0.0; ///< Pressure at which the compressor unloads @unitb{\psi}
    double full_load_pressure   = 0.0; ///< Pressure at which the compressor fully loads @unitb{\psi}
    double atmospheric_pressure = physics::us::kAtmosphericPressurePsi; ///< Local atmospheric pressure @unitb{\psi}
};

/**
 * @ingroup receiver_tank_calculator
 * @struct CompressorCycleResult
 * @brief Result of the Compressor Cycle sizing calculation.
 */
struct CompressorCycleResult {
    double tank_size           = 0.0; ///< Required receiver tank size (liquid storage volume) @unitb{\gallon}
    double effective_capacity  = 0.0; ///< Effective net compressor capacity over a full cycle @unitb{\cubicFoot\per\minute}
    double pressure_change     = 0.0; ///< Pressure band width (@math{P_{unload} - P_{load}}) @unitb{\psi}
    double volume_cf           = 0.0; ///< Required storage volume (area storage volume) @unitb{\cubicFoot}
};

/**
 * @brief Calculates receiver tank size from the compressor duty cycle and pressure band.
 * @details Sizes a receiver tank so that the compressor can run at its natural load/unload
 *          cycle without short-cycling. The effective net capacity is the fraction of the
 *          compressor's rated output actually consumed during a cycle, and the required
 *          storage volume is the amount of air that must be stored during the unloaded
 *          interval to keep system pressure within the operating band.
 *
 * @formula{receiver-tank-compressor-cycle-size;
 *   V_{required} = \frac{Q_{comp} \cdot t_{load} \cdot t_{unload} \cdot P_{atm}}
 *                       {60 \cdot (t_{load} + t_{unload}) \cdot (P_{unload} - P_{load})} \cdot k_{gal}
 * }
 *
 * where:
 * @symtable
 * @symrow{V_{required}; Required receiver tank size; \gallon}
 * @symrow{Q_{comp}; Rated compressor capacity at full load; \cubicFoot\per\minute}
 * @symrow{t_{load}; Compressor loaded time per cycle; \minute}
 * @symrow{t_{unload}; Compressor unloaded time per cycle; \minute}
 * @symrow{P_{atm}; Atmospheric pressure; \psi}
 * @symrow{P_{unload}; Compressor unload pressure; \psi}
 * @symrow{P_{load}; Compressor full-load pressure; \psi}
 * @symrow{60; Seconds per minute conversion; \second\per\minute}
 * @symrow{k_{gal}; Gallons per cubic foot (7.48); \gallon\per\cubicFoot}
 * @endsymtable
 *
 * @note The numerator factor @math{Q_{comp} \cdot t_{load} / (t_{load} + t_{unload})} is the
 *       effective net capacity — the average flow the compressor delivers over a full cycle.
 *       Multiplying by @math{t_{unload}} converts that rate to the volume (ft³) that must be
 *       buffered during the unloaded phase.
 *
 * @param[in] input  CompressorCycleInput
 * @return CompressorCycleResult containing the required tank size in gallons together with
 *         the intermediate results: effective capacity (cfm), pressure change (psi), and
 *         area storage volume (ft³).
 */
CompressorCycleResult calculateCompressorCycleSize(const CompressorCycleInput& input);

} // namespace receiver_tank
