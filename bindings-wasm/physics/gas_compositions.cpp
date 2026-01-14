#include <emscripten/bind.h>

#include "physics/gas_composition.h"

using namespace emscripten;
using namespace gas_composition;

EMSCRIPTEN_BINDINGS(gas_composition) {

    // Parameters for GasComposition constructor:
    //   substance (string)
    //   ch4_percent (CH4, methane, % by volume)
    //   c2h6_percent (C2H6, ethane, % by volume)
    //   n2_percent (N2, nitrogen, % by volume)
    //   h2_percent (H2, hydrogen, % by volume)
    //   c3h8_percent (C3H8, propane, % by volume)
    //   c4h10_cnh2n_percent (C4H10/CnH2n, butane/paraffins, % by volume)
    //   h2o_percent (H2O, water vapor, % by volume)
    //   co_percent (CO, carbon monoxide, % by volume)
    //   co2_percent (CO2, carbon dioxide, % by volume)
    //   so2_percent (SO2, sulphur dioxide, % by volume)
    //   o2_percent (O2, oxygen, % by volume)
    class_<GasComposition>("GasCompositions")
        .constructor<std::string, double, double, double, double, double, double, double, double, double, double,
                     double>()
        .property("heatingValue", &GasComposition::heating_value)
        .property("heatingValueVolume", &GasComposition::heating_value_volume)
        .property("specificGravity", &GasComposition::specific_gravity)
        .function("calculateExcessAir", &GasComposition::excessAirFromO2)
        .function("calculateO2", &GasComposition::o2PercentageFromExcessAir);

    register_vector<GasComposition>("GasCompositionsV");
}