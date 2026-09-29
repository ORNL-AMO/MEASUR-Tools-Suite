/**
 * Load Charge Material shared types.
 *
 * Define the thermic reaction type enumeration shared by all load/charge
 * material heat-required calculators (gas, liquid, solid).
 */

/**
 * Classification of the thermic reaction type for a load/charge material.
 */
export enum ThermicReactionType {
    ENDOTHERMIC = 0,
    EXOTHERMIC = 1,
    NONE = 2,
}

export type LoadChargeMaterialModule = {
    ThermicReactionType: typeof ThermicReactionType;
};
