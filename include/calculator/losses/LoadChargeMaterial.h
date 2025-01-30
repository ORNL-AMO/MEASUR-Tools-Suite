#ifndef TOOLS_SUITE_LOADCHARGEMATERIAL_H
#define TOOLS_SUITE_LOADCHARGEMATERIAL_H

/**
 * Load Charge Material class
 * Used to describe the reaction type (endothermic or exothermic)
 */
namespace LoadChargeMaterial {
    ///Classifications of thermic reaction type
    enum class ThermicReactionType {
        ENDOTHERMIC,
        EXOTHERMIC,
        NONE
    };
}

#endif //TOOLS_SUITE_LOADCHARGEMATERIAL_H
