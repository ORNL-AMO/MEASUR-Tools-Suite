#include <emscripten/bind.h>

#include "compressedAir/pneumatic_valve.h"

using namespace emscripten;
using namespace pneumatic_valve;

EMSCRIPTEN_BINDINGS(pneumatic_valve) {
    // ---- Flow Rate (Cv = 1) ----
    // calculatePneumaticValveFlowRate(PneumaticValveFlowRateInput) -> PneumaticValveFlowRateResult
    //   inletPressure   [psia]  - inlet (upstream) absolute pressure
    //   outletPressure  [psia]  - outlet (downstream) absolute pressure
    //   -> flowRate [scfm] - air flow rate for a valve with Cv = 1
    value_object<FlowRateInput>("PneumaticValveFlowRateInput")
        .field("inletPressure", &FlowRateInput::inlet_pressure)
        .field("outletPressure", &FlowRateInput::outlet_pressure);

    value_object<FlowRateResult>("PneumaticValveFlowRateResult")
        .field("flowRate", &FlowRateResult::flow_rate);

    function("calculatePneumaticValveFlowRate", &calculateFlowRate);

    // ---- Flow Coefficient (Cv) ----
    // calculatePneumaticValveCv(PneumaticValveCvInput) -> PneumaticValveCvResult
    //   inletPressure   [psia]  - inlet (upstream) absolute pressure
    //   outletPressure  [psia]  - outlet (downstream) absolute pressure
    //   flowRate        [scfm]  - measured or required air flow rate
    //   -> flowCoefficient [-]  - dimensionless valve flow coefficient (Cv)
    value_object<CvInput>("PneumaticValveCvInput")
        .field("inletPressure", &CvInput::inlet_pressure)
        .field("outletPressure", &CvInput::outlet_pressure)
        .field("flowRate", &CvInput::flow_rate);

    value_object<CvResult>("PneumaticValveCvResult")
        .field("flowCoefficient", &CvResult::flow_coefficient);

    function("calculatePneumaticValveCv", &calculateCv);
}
