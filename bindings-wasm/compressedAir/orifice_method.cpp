#include <emscripten/bind.h>

#include "compressedAir/orifice_method.h"

using namespace emscripten;
using namespace orifice_method;

EMSCRIPTEN_BINDINGS(orifice_method) {
    // ---- Orifice Method ----
    // calculateOrificeMethod(OrificeMethodInput) -> OrificeMethodResult
    //   operatingTime   [hr]    - annual system operating time
    //   airTemp         [°F]    - compressed air temperature at the leak point
    //   atmPressure     [psia]  - local atmospheric (barometric) pressure (default: 14.7)
    //   dischargeCoef   [-]     - orifice discharge coefficient (default: 1.0)
    //   diameter        [in]    - orifice (leak opening) diameter
    //   supplyPressure  [psig]  - compressed air supply pressure (gauge)
    //   numOrifices     [-]     - number of identical orifice leak points
    //   -> standardDensity   [lb/ft³]  - air density at standard atmospheric conditions
    //   -> sonicDensity      [lb/ft³]  - air density at the isentropic sonic throat
    //   -> leakVelocity      [ft/s]    - sonic air velocity at the orifice throat
    //   -> leakRateLBMmin    [lbm/min] - mass flow rate of leaked air per orifice
    //   -> leakRateScfm      [scfm]    - volumetric flow rate per orifice
    //   -> leakRateEstimate  [scfm]    - total leak flow rate for all orifices
    //   -> annualConsumption [kscf]    - estimated annual compressed air loss
    value_object<Input>("OrificeMethodInput")
        .field("operatingTime",  &Input::operating_time)
        .field("airTemp",        &Input::air_temp)
        .field("atmPressure",    &Input::atm_pressure)
        .field("dischargeCoef",  &Input::discharge_coef)
        .field("diameter",       &Input::diameter)
        .field("supplyPressure", &Input::supply_pressure)
        .field("numOrifices",    &Input::num_orifices);

    value_object<Result>("OrificeMethodResult")
        .field("standardDensity",   &Result::standard_density)
        .field("sonicDensity",      &Result::sonic_density)
        .field("leakVelocity",      &Result::leak_velocity)
        .field("leakRateLBMmin",    &Result::leak_rate_lbm_min)
        .field("leakRateScfm",      &Result::leak_rate_scfm)
        .field("leakRateEstimate",  &Result::leak_rate_estimate)
        .field("annualConsumption", &Result::annual_consumption);

    function("calculateOrificeMethod", &calculate);
}
