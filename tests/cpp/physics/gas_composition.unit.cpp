#include "physics/gas_composition.h"

#include "catch.hpp"

using namespace Catch;
using namespace gas_composition;

TEST_CASE("Calculate Gas compositions", "[Gas Composition]") {
    GasComposition composition("unit test gas", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);

    CHECK(composition.excess_air_from_o2(0.005) == Approx(0.0231722095));
    CHECK(composition.excess_air_from_o2(0.03) == Approx(0.1552234415));
    CHECK(composition.excess_air_from_o2(0.07) == Approx(0.4519750365));

    CHECK(composition.o2_percentage_from_excess_air(0.0231722) == Approx(0.0049367284));
    CHECK(composition.o2_percentage_from_excess_air(0.1552234) == Approx(0.0294793974));
    CHECK(composition.o2_percentage_from_excess_air(0.451975) == Approx(0.0690024841));

    CHECK(composition.process_heat_properties(700, 0.0231722095, 125, 125, 60, 0).available_heat ==
          Approx(0.7831351536));
    CHECK(composition.process_heat_properties(700, 0.1552234415, 125, 125, 60, 0).available_heat ==
          Approx(0.5615301965));
    CHECK(composition.process_heat_properties(700, 0.09, 125, 125, 60, 0).available_heat == Approx(0.7264072116));

    composition = GasComposition("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
    CHECK(composition.heating_value == Approx(22030.67089880065));
    CHECK(composition.heating_value_volume == Approx(1032.445));
    CHECK(composition.specific_gravity == Approx(0.6571206283343215));

    composition = GasComposition("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
    CHECK(composition.heating_value == Approx(19185.932389233436));
    CHECK(composition.heating_value_volume == Approx(610.52));
    CHECK(composition.specific_gravity == Approx(0.44638781861292243));

    composition = GasComposition("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
    CHECK(composition.heating_value == Approx(1080.6848266529887));
    CHECK(composition.heating_value_volume == Approx(83.605));
    CHECK(composition.specific_gravity == Approx(1.0870540901007706));

    composition = GasComposition("Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0);
    CHECK(composition.heating_value == Approx(61095.0));
    CHECK(composition.heating_value_volume == Approx(325));
    CHECK(composition.specific_gravity == Approx(0.0746887967));

    composition = GasComposition("", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);
    CHECK(composition.heating_value == Approx(22630.345));
    CHECK(composition.specific_gravity == Approx(0.631782959));
    CHECK(composition.heating_value_volume == Approx(1019.6648));

    composition = GasComposition("", 93.9, 4.2, 1.0, 0, 0.3, 0.06, 0, 0, 0.5, 0, 0.01);
    CHECK(composition.heating_value == Approx(23030.1592092352));
    CHECK(composition.specific_gravity == Approx(0.6298888036));
    CHECK(composition.heating_value_volume == Approx(1034.57));

    composition = GasComposition("", 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    CHECK(composition.heating_value == Approx(23875));
    CHECK(composition.specific_gravity == Approx(0.5943242442));
    CHECK(composition.heating_value_volume == Approx(1012));

    composition = GasComposition("", 45, 45, 1, 1, 3, 2, 0, 1, 0, 0, 2);
    CHECK(composition.heating_value == Approx(21684.26));
    CHECK(composition.specific_gravity == Approx(0.9060143746));
    CHECK(composition.heating_value_volume == Approx(1400.8));

    composition = GasComposition("", 10, 55, 1, 10, 16, 2, 0, 1, 3, 0, 2);
    CHECK(composition.heating_value == Approx(20585.7766384286));
    CHECK(composition.specific_gravity == Approx(1.0774007113));
    CHECK(composition.heating_value_volume == Approx(1581.14));
}