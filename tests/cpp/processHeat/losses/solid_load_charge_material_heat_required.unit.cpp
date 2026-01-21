#include <processHeat/losses/load_charge_material.h>
#include <processHeat/losses/solid_load_charge_material_heat_required.h>

#include "catch.hpp"

using namespace Catch;
using namespace solid_load_charge_material_heat_required;
TEST_CASE("Calculate Total Heat for Charge Material - Solids", "[Total Heat][ChargeMaterial][Solids]") {
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.139957009792214, 117.15, 0.16,
                                  2550, 20000.0, 1.0, 0.0, 70, 1500.0, 212.0, 0.0, 0.0, 100.0, 0) == Approx(4185142.7752567500));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.247910198232625, 169.0,
                                  0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0,
                                  100.0, 0) == Approx(3872263.395872940));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0,
                                  0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0,
                                  100.0, 0) == Approx(3774263.395872940));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0,
                                  0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0, 0.0,
                                  0) == Approx(3774263.395872940));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.032959159, 28.5,
                                  0.0339144972534403, 1945.004, 100.0, 10, 0.0, 70.0, 1500.0, 212.0, 0.0, 100.0, 200.0,
                                  0) == Approx(33361.843802245));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.032959159, 28.5,
                                  0.0339144972534403, 1945.004, 100.0, 10, 0.0, 70.0, 1500.0, 212.0, 0.0, 100.0, 200.0,
                                  0) == Approx(15361.8438022450));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.150, 60.0, 0.481, 2900.0,
                                  10000.0, 0.1, 0.0, 70.0, 2200.0, 500.0, 0.0, 1.0, 100, 0) == Approx(3204310));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0,
                                  0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1300.0, 220.0, 100.0, 0.0,
                                  100.0, 0) == Approx(4675276));
    CHECK(totalHeatRequired(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0,
                                  0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1215.0, 220.0, 10.0, 0.0,
                                  100.0, 0) == Approx(2933199));
}