#include <emscripten/bind.h>

#include "compressedAir/pneumatic_air_requirement.h"

using namespace emscripten;
using namespace pneumatic_air_requirement;

EMSCRIPTEN_BINDINGS(pneumatic_air_requirement) {
    // ---- Single-Acting Piston ----
    // calculatePneumaticAirRequirementSingleActing(PneumaticAirRequirementSingleActingInput)
    //     -> PneumaticAirRequirementResult
    //   cylinderDiameter  [in]    - inner bore diameter of the cylinder
    //   cylinderStroke    [in]    - piston travel distance per stroke
    //   airPressure       [psi]   - operating gauge pressure at the cylinder inlet
    //   cyclesPerMin      [1/min] - number of complete cycles per minute
    //   -> volumeAirIntakePiston           [cfm]  - cylinder air intake volume at cylinder conditions
    //   -> compressionRatio                [-]    - absolute working pressure / atmospheric pressure
    //   -> airRequirementPneumaticCylinder [scfm] - free-air equivalent consumption
    value_object<SingleActingInput>("PneumaticAirRequirementSingleActingInput")
        .field("cylinderDiameter", &SingleActingInput::cylinder_diameter)
        .field("cylinderStroke",   &SingleActingInput::cylinder_stroke)
        .field("airPressure",      &SingleActingInput::air_pressure)
        .field("cyclesPerMin",     &SingleActingInput::cycles_per_min);

    value_object<AirRequirementResult>("PneumaticAirRequirementResult")
        .field("volumeAirIntakePiston",           &AirRequirementResult::volume_air_intake_piston)
        .field("compressionRatio",                &AirRequirementResult::compression_ratio)
        .field("airRequirementPneumaticCylinder", &AirRequirementResult::air_requirement_pneumatic_cylinder);

    function("calculatePneumaticAirRequirementSingleActing", &calculateSingleActing);

    // ---- Double-Acting Piston ----
    // calculatePneumaticAirRequirementDoubleActing(PneumaticAirRequirementDoubleActingInput)
    //     -> PneumaticAirRequirementResult
    //   cylinderDiameter   [in]    - inner bore diameter of the cylinder
    //   cylinderStroke     [in]    - piston travel distance per stroke
    //   pistonRodDiameter  [in]    - diameter of the piston rod
    //   airPressure        [psi]   - operating gauge pressure at the cylinder inlet
    //   cyclesPerMin       [1/min] - number of complete cycles per minute
    //   -> volumeAirIntakePiston           [cfm]  - combined cylinder air intake (both strokes)
    //   -> compressionRatio                [-]    - absolute working pressure / atmospheric pressure
    //   -> airRequirementPneumaticCylinder [scfm] - free-air equivalent consumption
    value_object<DoubleActingInput>("PneumaticAirRequirementDoubleActingInput")
        .field("cylinderDiameter",  &DoubleActingInput::cylinder_diameter)
        .field("cylinderStroke",    &DoubleActingInput::cylinder_stroke)
        .field("pistonRodDiameter", &DoubleActingInput::piston_rod_diameter)
        .field("airPressure",       &DoubleActingInput::air_pressure)
        .field("cyclesPerMin",      &DoubleActingInput::cycles_per_min);

    function("calculatePneumaticAirRequirementDoubleActing", &calculateDoubleActing);
}
