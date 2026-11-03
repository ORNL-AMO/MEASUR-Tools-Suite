/**
 * Pump style classification used by pump/fan calculators.
 */
export enum PumpStyle {
    /** Unitless classification; preserved native enum value. */
    END_SUCTION_SLURRY = 0,
    /** Unitless classification; preserved native enum value. */
    END_SUCTION_SEWAGE = 1,
    /** Unitless classification; preserved native enum value. */
    END_SUCTION_STOCK = 2,
    /** Unitless classification; preserved native enum value. */
    END_SUCTION_SUBMERSIBLE_SEWAGE = 3,
    /** Unitless classification; preserved native enum value. */
    API_DOUBLE_SUCTION = 4,
    /** Unitless classification; preserved native enum value. */
    MULTISTAGE_BOILER_FEED = 5,
    /** Unitless classification; preserved native enum value. */
    END_SUCTION_ANSI_API = 6,
    /** Unitless classification; preserved native enum value. */
    AXIAL_FLOW = 7,
    /** Unitless classification; preserved native enum value. */
    DOUBLE_SUCTION = 8,
    /** Unitless classification; preserved native enum value. */
    VERTICAL_TURBINE = 9,
    /** Unitless classification; preserved native enum value. */
    LARGE_END_SUCTION = 10,
    /** Unitless classification; preserved native enum value. */
    SPECIFIED_OPTIMAL_EFFICIENCY = 11,
    /** Unitless classification; preserved native enum value. */
    POSITIVE_DISPLACEMENT = 12
}

/**
 * Pump specific speed mode.
 */
export enum SpecificSpeed {
    /** Unitless classification; preserved native enum value. */
    FIXED_SPEED = 0,
    /** Unitless classification; preserved native enum value. */
    NOT_FIXED_SPEED = 1
}

/** Shared runtime enums; values and names match Pump.h and existing consumers. */
export type PumpEnumsModule = {
    PumpStyle: typeof PumpStyle;
    SpecificSpeed: typeof SpecificSpeed;
};
