#include <emscripten/bind.h>
#include "processHeat/flow_calculations_energy_use.h"

using namespace emscripten;
using namespace flow_calculations_energy_use;

EMSCRIPTEN_BINDINGS(flow_calculations_energy_use_module) {
    value_object<FlowCalculationsEnergyUseResults>("FlowCalculationsEnergyUseResults")
        .field("flowPerHour", &FlowCalculationsEnergyUseResults::flow_per_hour)
        .field("heatInput", &FlowCalculationsEnergyUseResults::heat_input)
        .field("totalFlow", &FlowCalculationsEnergyUseResults::total_flow);

    // Parameters for flowCalculationsEnergyUse:
    //   specific_gravity (unitless)
    //   orifice_diameter (in)
    //   inside_pipe_diameter (in)
    //   discharge_coefficient (unitless)
    //   gas_heating_value (Btu/scf)
    //   gas_temperature (°F)
    //   gas_pressure (psig)
    //   orifice_pressure_drop (in. W.C.)
    //   operating_time (hr)
    function("flowCalculationsEnergyUse", &flowCalculationsEnergyUse);
}
