#include <emscripten/bind.h>

#include "compressedAir/operating_cost.h"

using namespace emscripten;
using namespace operating_cost;

EMSCRIPTEN_BINDINGS(operating_cost) {
    // ---- Operating Cost ----
    // calculateOperatingCost(OperatingCostInput) -> OperatingCostResult
    //   motorBhp              [bhp]     - full-load motor brake horsepower
    //   bhpUnloaded           [%]       - percentage of full-load BHP consumed when unloaded
    //   annualOperatingHours  [h]       - total compressor operating hours per year
    //   runTimeLoaded         [%]       - percentage of operating time the compressor runs loaded
    //   efficiencyLoaded      [%]       - motor efficiency in the loaded condition
    //   efficiencyUnloaded    [%]       - motor efficiency in the unloaded condition
    //   costOfElectricity     [$/kWh]   - electricity unit cost
    //   -> runTimeUnloaded    [%]       - percentage of operating time the compressor runs unloaded
    //   -> costForLoaded      [$/yr]    - annual electricity cost in the loaded condition
    //   -> costForUnloaded    [$/yr]    - annual electricity cost in the unloaded condition
    //   -> totalAnnualCost    [$/yr]    - total annual electricity cost
    value_object<Input>("OperatingCostInput")
        .field("motorBhp", &Input::motor_bhp)
        .field("bhpUnloaded", &Input::bhp_unloaded)
        .field("annualOperatingHours", &Input::annual_operating_hours)
        .field("runTimeLoaded", &Input::run_time_loaded)
        .field("efficiencyLoaded", &Input::efficiency_loaded)
        .field("efficiencyUnloaded", &Input::efficiency_unloaded)
        .field("costOfElectricity", &Input::cost_of_electricity);

    value_object<Result>("OperatingCostResult")
        .field("runTimeUnloaded", &Result::run_time_unloaded)
        .field("costForLoaded", &Result::cost_for_loaded)
        .field("costForUnloaded", &Result::cost_for_unloaded)
        .field("totalAnnualCost", &Result::total_annual_cost);

    function("calculateOperatingCost", &calculateOperatingCost);
}
