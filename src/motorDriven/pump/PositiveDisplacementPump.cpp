#include "motorDriven/pump/PositiveDisplacementPump.h"
#include "physics/constants.h"

PositiveDisplacementPump::Output PositiveDisplacementPump::calculate() const {
    const double power = flowRate * differentialPressure / (physics::conversions::kPumpGpmPsiPerHp * pumpEfficiency) *
                         physics::conversions::kBhpToKw;
    const double energy = power * operatingHours;

    return {power, energy};
}
