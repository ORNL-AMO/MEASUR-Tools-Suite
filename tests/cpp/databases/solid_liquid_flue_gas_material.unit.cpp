
#include "catch.hpp"
#include "databases/solid_liquid_flue_gas_material_data.h"
using namespace Catch;
using namespace solid_liquid_flue_gas_material_data;

TEST_CASE("solid_liquid_flue_gas_material_data", "[databases]") {

    // Typical Bituminous Coal - US
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Typical Bituminous Coal - US", 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5};
        CHECK(expected.substance == outputs[0].substance);
        CHECK(expected.carbon == outputs[0].carbon);
        CHECK(expected.hydrogen == outputs[0].hydrogen);
        CHECK(expected.oxygen == outputs[0].oxygen);
        CHECK(expected.moisture == outputs[0].moisture);
        CHECK(expected.nitrogen == outputs[0].nitrogen);
        CHECK(expected.inert_ash == outputs[0].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[0];
        SolidLiquidFlueGasMaterial expected = {"Typical Bituminous Coal - US", 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }

    // Typical Anthracite - US
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Typical Anthracite - US", 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8};
        CHECK(expected.substance == outputs[1].substance);
        CHECK(expected.carbon == outputs[1].carbon);
        CHECK(expected.hydrogen == outputs[1].hydrogen);
        CHECK(expected.oxygen == outputs[1].oxygen);
        CHECK(expected.moisture == outputs[1].moisture);
        CHECK(expected.nitrogen == outputs[1].nitrogen);
        CHECK(expected.inert_ash == outputs[1].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[1];
        SolidLiquidFlueGasMaterial expected = {"Typical Anthracite - US", 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }

    // Typical Lignite - US
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Typical Lignite - US", 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8};
        CHECK(expected.substance == outputs[2].substance);
        CHECK(expected.carbon == outputs[2].carbon);
        CHECK(expected.hydrogen == outputs[2].hydrogen);
        CHECK(expected.oxygen == outputs[2].oxygen);
        CHECK(expected.moisture == outputs[2].moisture);
        CHECK(expected.nitrogen == outputs[2].nitrogen);
        CHECK(expected.inert_ash == outputs[2].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[2];
        SolidLiquidFlueGasMaterial expected = {"Typical Lignite - US", 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }

    // Fuel Oil #2
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Fuel Oil #2", 86.6, 12.8, 0.5, 0, 0, 0, 0.1};
        CHECK(expected.substance == outputs[3].substance);
        CHECK(expected.carbon == outputs[3].carbon);
        CHECK(expected.hydrogen == outputs[3].hydrogen);
        CHECK(expected.oxygen == outputs[3].oxygen);
        CHECK(expected.moisture == outputs[3].moisture);
        CHECK(expected.nitrogen == outputs[3].nitrogen);
        CHECK(expected.inert_ash == outputs[3].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[3];
        SolidLiquidFlueGasMaterial expected = {"Fuel Oil #2", 86.6, 12.8, 0.5, 0, 0, 0, 0.1};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }

    // Fuel Oil #6
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Fuel Oil #6", 87.1, 10.6, 2.1, 0.2, 0, 0, 0};
        CHECK(expected.substance == outputs[4].substance);
        CHECK(expected.carbon == outputs[4].carbon);
        CHECK(expected.hydrogen == outputs[4].hydrogen);
        CHECK(expected.oxygen == outputs[4].oxygen);
        CHECK(expected.moisture == outputs[4].moisture);
        CHECK(expected.nitrogen == outputs[4].nitrogen);
        CHECK(expected.inert_ash == outputs[4].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[4];
        SolidLiquidFlueGasMaterial expected = {"Fuel Oil #6", 87.1, 10.6, 2.1, 0.2, 0, 0, 0};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }

    // Typical Wood
    {
        auto const outputs = get_default_solid_liquid_flue_gas_materials();
        CHECK(outputs.size() == 6);
        SolidLiquidFlueGasMaterial expected = {"Typical Wood", 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2};
        CHECK(expected.substance == outputs[5].substance);
        CHECK(expected.carbon == outputs[5].carbon);
        CHECK(expected.hydrogen == outputs[5].hydrogen);
        CHECK(expected.oxygen == outputs[5].oxygen);
        CHECK(expected.moisture == outputs[5].moisture);
        CHECK(expected.nitrogen == outputs[5].nitrogen);
        CHECK(expected.inert_ash == outputs[5].inert_ash);
    }

    {
        auto const output   = get_default_solid_liquid_flue_gas_materials()[5];
        SolidLiquidFlueGasMaterial expected = {"Typical Wood", 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2};
        CHECK(expected.substance == output.substance);
        CHECK(expected.carbon == output.carbon);
        CHECK(expected.hydrogen == output.hydrogen);
        CHECK(expected.oxygen == output.oxygen);
        CHECK(expected.moisture == output.moisture);
        CHECK(expected.nitrogen == output.nitrogen);
        CHECK(expected.inert_ash == output.inert_ash);
    }
}