
#include "databases/gas_flue_gas_material_data.h"

#include "catch.hpp"
#include "physics/gas_composition.h"
using namespace Catch;
using namespace gas_flue_gas_material_data;
using namespace gas_composition;

TEST_CASE("DefaultData - getGasFlueGasMaterials", "[databases]") {

    // Typical Natural Gas - US
    {
        auto outputs = get_default_gas_flue_gas_materials();
        CHECK(outputs.size() == 4);
        GasComposition expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        CHECK(expected.substance == outputs[0].substance);
        CHECK(expected.c2h6.composition_percent == outputs[0].c2h6);
        CHECK(expected.n2.composition_percent == outputs[0].n2);
        CHECK(expected.h2.composition_percent == outputs[0].h2);
        CHECK(expected.c3h8.composition_percent == outputs[0].c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == outputs[0].c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == outputs[0].h2o);
        CHECK(expected.co.composition_percent == outputs[0].co);
        CHECK(expected.co2.composition_percent == outputs[0].co2);
        CHECK(expected.so2.composition_percent == outputs[0].so2);
        CHECK(expected.o2.composition_percent == outputs[0].o2);
        CHECK(outputs[0].heating_value == Approx(22030.67089880065));
        CHECK(outputs[0].heating_value_volume == Approx(1032.445));
        CHECK(outputs[0].specific_gravity == Approx(0.6571206283343215));
    }

    {
        auto           output = get_default_gas_flue_gas_materials()[0];
        GasComposition expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        CHECK(expected.substance == output.substance);
        CHECK(expected.c2h6.composition_percent == output.c2h6);
        CHECK(expected.n2.composition_percent == output.n2);
        CHECK(expected.h2.composition_percent == output.h2);
        CHECK(expected.c3h8.composition_percent == output.c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == output.c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == output.h2o);
        CHECK(expected.co.composition_percent == output.co);
        CHECK(expected.co2.composition_percent == output.co2);
        CHECK(expected.so2.composition_percent == output.so2);
        CHECK(expected.o2.composition_percent == output.o2);
        CHECK(output.heating_value == Approx(22030.67089880065));
        CHECK(output.heating_value_volume == Approx(1032.445));
        CHECK(output.specific_gravity == Approx(0.6571206283343215));
    }

    // Coke Oven Gas
    {
        auto outputs = get_default_gas_flue_gas_materials();
        CHECK(outputs.size() == 4);
        GasComposition expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        CHECK(expected.substance == outputs[1].substance);
        CHECK(expected.c2h6.composition_percent == outputs[1].c2h6);
        CHECK(expected.n2.composition_percent == outputs[1].n2);
        CHECK(expected.h2.composition_percent == outputs[1].h2);
        CHECK(expected.c3h8.composition_percent == outputs[1].c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == outputs[1].c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == outputs[1].h2o);
        CHECK(expected.co.composition_percent == outputs[1].co);
        CHECK(expected.co2.composition_percent == outputs[1].co2);
        CHECK(expected.so2.composition_percent == outputs[1].so2);
        CHECK(expected.o2.composition_percent == outputs[1].o2);
        CHECK(outputs[1].heating_value == Approx(19185.932389233436));
        CHECK(outputs[1].heating_value_volume == Approx(610.52));
        CHECK(outputs[1].specific_gravity == Approx(0.44638781861292243));
    }

    {
        auto           output = get_default_gas_flue_gas_materials()[1];
        GasComposition expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        CHECK(expected.substance == output.substance);
        CHECK(expected.c2h6.composition_percent == output.c2h6);
        CHECK(expected.n2.composition_percent == output.n2);
        CHECK(expected.h2.composition_percent == output.h2);
        CHECK(expected.c3h8.composition_percent == output.c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == output.c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == output.h2o);
        CHECK(expected.co.composition_percent == output.co);
        CHECK(expected.co2.composition_percent == output.co2);
        CHECK(expected.so2.composition_percent == output.so2);
        CHECK(expected.o2.composition_percent == output.o2);
        CHECK(output.heating_value == Approx(19185.932389233436));
        CHECK(output.heating_value_volume == Approx(610.52));
        CHECK(output.specific_gravity == Approx(0.44638781861292243));
    }

    // Blast Furnace
    {
        auto outputs = get_default_gas_flue_gas_materials();
        CHECK(outputs.size() == 4);
        GasComposition expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        CHECK(expected.substance == outputs[2].substance);
        CHECK(expected.c2h6.composition_percent == outputs[2].c2h6);
        CHECK(expected.n2.composition_percent == outputs[2].n2);
        CHECK(expected.h2.composition_percent == outputs[2].h2);
        CHECK(expected.c3h8.composition_percent == outputs[2].c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == outputs[2].c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == outputs[2].h2o);
        CHECK(expected.co.composition_percent == outputs[2].co);
        CHECK(expected.co2.composition_percent == outputs[2].co2);
        CHECK(expected.so2.composition_percent == outputs[2].so2);
        CHECK(expected.o2.composition_percent == outputs[2].o2);
        CHECK(outputs[2].heating_value == Approx(1080.6848266529887));
        CHECK(outputs[2].heating_value_volume == Approx(83.605));
        CHECK(outputs[2].specific_gravity == Approx(1.0870540901007706));
    }

    {
        auto           output = get_default_gas_flue_gas_materials()[2];
        GasComposition expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        CHECK(expected.substance == output.substance);
        CHECK(expected.c2h6.composition_percent == output.c2h6);
        CHECK(expected.n2.composition_percent == output.n2);
        CHECK(expected.h2.composition_percent == output.h2);
        CHECK(expected.c3h8.composition_percent == output.c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == output.c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == output.h2o);
        CHECK(expected.co.composition_percent == output.co);
        CHECK(expected.co2.composition_percent == output.co2);
        CHECK(expected.so2.composition_percent == output.so2);
        CHECK(expected.o2.composition_percent == output.o2);
        CHECK(output.heating_value == Approx(1080.6848266529887));
        CHECK(output.heating_value_volume == Approx(83.605));
        CHECK(output.specific_gravity == Approx(1.0870540901007706));
    }

    // Hydrogen
    {
        auto outputs = get_default_gas_flue_gas_materials();
        CHECK(outputs.size() == 4);
        GasComposition expected("Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0);
        CHECK(expected.substance == outputs[3].substance);
        CHECK(expected.c2h6.composition_by_volume == outputs[3].c2h6);
        CHECK(expected.n2.composition_percent == outputs[3].n2);
        CHECK(expected.h2.composition_percent == outputs[3].h2);
        CHECK(expected.c3h8.composition_percent == outputs[3].c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == outputs[3].c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == outputs[3].h2o);
        CHECK(expected.co.composition_percent == outputs[3].co);
        CHECK(expected.co2.composition_percent == outputs[3].co2);
        CHECK(expected.so2.composition_percent == outputs[3].so2);
        CHECK(expected.o2.composition_percent == outputs[3].o2);
        CHECK(outputs[3].heating_value == Approx(61095.0));
        CHECK(outputs[3].heating_value_volume == Approx(325));
        CHECK(outputs[3].specific_gravity == Approx(0.0746887967));
    }

    {
        auto           output = get_default_gas_flue_gas_materials()[3];
        GasComposition expected("Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0);
        CHECK(expected.substance == output.substance);
        CHECK(expected.c2h6.composition_percent == output.c2h6);
        CHECK(expected.n2.composition_percent == output.n2);
        CHECK(expected.h2.composition_percent == output.h2);
        CHECK(expected.c3h8.composition_percent == output.c3h8);
        CHECK(expected.c4h10_cnh2n.composition_percent == output.c4h10_cnh2n);
        CHECK(expected.h2o.composition_percent == output.h2o);
        CHECK(expected.co.composition_percent == output.co);
        CHECK(expected.co2.composition_percent == output.co2);
        CHECK(expected.so2.composition_percent == output.so2);
        CHECK(expected.o2.composition_percent == output.o2);
        CHECK(output.heating_value == Approx(61095.0));
        CHECK(output.heating_value_volume == Approx(325));
        CHECK(output.specific_gravity == Approx(0.0746887967));
    }
};