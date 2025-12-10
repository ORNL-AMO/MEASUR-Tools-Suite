#include "databases/default_data.h"

#include "catch.hpp"

using namespace Catch;

#include "databases/GasFlueGasMaterialData.h"
#include "databases/MotorData.h"
#include "databases/SolidLiquidFlueGasMaterialData.h"
#include "databases/compressors_type1_data.h"
#include "databases/compressors_type1_GT_100kW_data.h"
#include "databases/compressors_type2_data.h"
#include "databases/compressors_type3_data.h"
#include "databases/compressors_type4_data.h"
#include "databases/compressors_type5_data.h"
#include "databases/compressors_type6_data.h"
#include "databases/lighting_data.h"
#include <compressedAir/compressors_data.h>
#include <other/lighting_data.h>
#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"


TEST_CASE("DefaultData - getGasFlueGasMaterials", "[databases]") {
    auto defaultData = DefaultData();

    // Typical Natural Gas - US
    {
        auto outputs = defaultData.getGasFlueGasMaterials();
        CHECK(outputs.size() == 4);
        GasCompositions expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(1);
        CHECK(expected.getID() == outputs[0].getID());
        CHECK(expected.getSubstance() == outputs[0].getSubstance());
        CHECK(expected.getGasByVol("C2H6") == outputs[0].getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == outputs[0].getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == outputs[0].getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == outputs[0].getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == outputs[0].getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == outputs[0].getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == outputs[0].getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == outputs[0].getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == outputs[0].getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == outputs[0].getGasByVol("O2"));
        CHECK(outputs[0].getHeatingValue() == Approx(22030.67089880065));
        CHECK(outputs[0].getHeatingValueVolume() == Approx(1032.445));
        CHECK(outputs[0].getSpecificGravity() == Approx(0.6571206283343215));
    }

    {
        auto            output = defaultData.getGasFlueGasMaterials()[0];
        GasCompositions expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(1);
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getGasByVol("C2H6") == output.getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == output.getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == output.getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == output.getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == output.getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == output.getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == output.getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == output.getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == output.getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == output.getGasByVol("O2"));
        CHECK(output.getHeatingValue() == Approx(22030.67089880065));
        CHECK(output.getHeatingValueVolume() == Approx(1032.445));
        CHECK(output.getSpecificGravity() == Approx(0.6571206283343215));
    }

    // Coke Oven Gas
    {
        auto outputs = defaultData.getGasFlueGasMaterials();
        CHECK(outputs.size() == 4);
        GasCompositions expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        expected.setID(2);
        CHECK(expected.getID() == outputs[1].getID());
        CHECK(expected.getSubstance() == outputs[1].getSubstance());
        CHECK(expected.getGasByVol("C2H6") == outputs[1].getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == outputs[1].getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == outputs[1].getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == outputs[1].getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == outputs[1].getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == outputs[1].getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == outputs[1].getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == outputs[1].getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == outputs[1].getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == outputs[1].getGasByVol("O2"));
        CHECK(outputs[1].getHeatingValue() == Approx(19185.932389233436));
        CHECK(outputs[1].getHeatingValueVolume() == Approx(610.52));
        CHECK(outputs[1].getSpecificGravity() == Approx(0.44638781861292243));
    }

    {
        auto            output = defaultData.getGasFlueGasMaterials()[1];
        GasCompositions expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        expected.setID(2);
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getGasByVol("C2H6") == output.getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == output.getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == output.getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == output.getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == output.getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == output.getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == output.getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == output.getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == output.getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == output.getGasByVol("O2"));
        CHECK(output.getHeatingValue() == Approx(19185.932389233436));
        CHECK(output.getHeatingValueVolume() == Approx(610.52));
        CHECK(output.getSpecificGravity() == Approx(0.44638781861292243));
    }

    // Blast Furnace
    {
        auto outputs = defaultData.getGasFlueGasMaterials();
        CHECK(outputs.size() == 4);
        GasCompositions expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        expected.setID(3);
        CHECK(expected.getID() == outputs[2].getID());
        CHECK(expected.getSubstance() == outputs[2].getSubstance());
        CHECK(expected.getGasByVol("C2H6") == outputs[2].getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == outputs[2].getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == outputs[2].getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == outputs[2].getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == outputs[2].getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == outputs[2].getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == outputs[2].getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == outputs[2].getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == outputs[2].getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == outputs[2].getGasByVol("O2"));
        CHECK(outputs[2].getHeatingValue() == 1080.6848266529887);
        CHECK(outputs[2].getHeatingValueVolume() == 83.605);
        CHECK(outputs[2].getSpecificGravity() == 1.0870540901007706);
    }

    {
        auto            output = defaultData.getGasFlueGasMaterials()[2];
        GasCompositions expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        expected.setID(3);
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getGasByVol("C2H6") == output.getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == output.getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == output.getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == output.getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == output.getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == output.getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == output.getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == output.getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == output.getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == output.getGasByVol("O2"));
        CHECK(output.getHeatingValue() == 1080.6848266529887);
        CHECK(output.getHeatingValueVolume() == 83.605);
        CHECK(output.getSpecificGravity() == 1.0870540901007706);
    }

    // Hydrogen
    {
        auto outputs = defaultData.getGasFlueGasMaterials();
        CHECK(outputs.size() == 4);
        GasCompositions expected("Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0);
        expected.setID(4);
        CHECK(expected.getID() == outputs[3].getID());
        CHECK(expected.getSubstance() == outputs[3].getSubstance());
        CHECK(expected.getGasByVol("C2H6") == outputs[3].getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == outputs[3].getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == outputs[3].getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == outputs[3].getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == outputs[3].getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == outputs[3].getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == outputs[3].getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == outputs[3].getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == outputs[3].getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == outputs[3].getGasByVol("O2"));
        CHECK(outputs[3].getHeatingValue() == 61095.0);
        CHECK(outputs[3].getHeatingValueVolume() == 325);
        CHECK(outputs[3].getSpecificGravity() == 0.0746887967);
    }

    {
        auto            output = defaultData.getGasFlueGasMaterials()[3];
        GasCompositions expected("Hydrogen", 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0);
        expected.setID(4);
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getGasByVol("C2H6") == output.getGasByVol("C2H6"));
        CHECK(expected.getGasByVol("N2") == output.getGasByVol("N2"));
        CHECK(expected.getGasByVol("H2") == output.getGasByVol("H2"));
        CHECK(expected.getGasByVol("C3H8") == output.getGasByVol("C3H8"));
        CHECK(expected.getGasByVol("C4H10_CnH2n") == output.getGasByVol("C4H10_CnH2n"));
        CHECK(expected.getGasByVol("H2O") == output.getGasByVol("H2O"));
        CHECK(expected.getGasByVol("CO") == output.getGasByVol("CO"));
        CHECK(expected.getGasByVol("CO2") == output.getGasByVol("CO2"));
        CHECK(expected.getGasByVol("SO2") == output.getGasByVol("SO2"));
        CHECK(expected.getGasByVol("O2") == output.getGasByVol("O2"));
        CHECK(output.getHeatingValue() == 61095.0);
        CHECK(output.getHeatingValueVolume() == 325);
        CHECK(output.getSpecificGravity() == .0746887967);
    }
}

TEST_CASE("DefaultData - getSolidLiquidFlueGasMaterials", "[databases]") {
    auto defaultData = DefaultData();

    // Typical Bituminous Coal - US
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setSubstance("Typical Bituminous Coal - US");
        expected.setID(1);
        CHECK(expected.getID() == outputs[0].getID());
        CHECK(expected.getSubstance() == outputs[0].getSubstance());
        CHECK(expected.getCarbon() == outputs[0].getCarbon());
        CHECK(expected.getHydrogen() == outputs[0].getHydrogen());
        CHECK(expected.getSulphur() == outputs[0].getSulphur());
        CHECK(expected.getInertAsh() == outputs[0].getInertAsh());
        CHECK(expected.getO2() == outputs[0].getO2());
        CHECK(expected.getMoisture() == outputs[0].getMoisture());
        CHECK(expected.getNitrogen() == outputs[0].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[0];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setID(1);
        expected.setSubstance("Typical Bituminous Coal - US");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }

    // Typical Anthracite - US
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8);
        expected.setSubstance("Typical Anthracite - US");
        expected.setID(2);
        CHECK(expected.getID() == outputs[1].getID());
        CHECK(expected.getSubstance() == outputs[1].getSubstance());
        CHECK(expected.getCarbon() == outputs[1].getCarbon());
        CHECK(expected.getHydrogen() == outputs[1].getHydrogen());
        CHECK(expected.getSulphur() == outputs[1].getSulphur());
        CHECK(expected.getInertAsh() == outputs[1].getInertAsh());
        CHECK(expected.getO2() == outputs[1].getO2());
        CHECK(expected.getMoisture() == outputs[1].getMoisture());
        CHECK(expected.getNitrogen() == outputs[1].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[1];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8);
        expected.setID(2);
        expected.setSubstance("Typical Anthracite - US");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }

    // Typical Lignite - US
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8);
        expected.setSubstance("Typical Lignite - US");
        expected.setID(3);
        CHECK(expected.getID() == outputs[2].getID());
        CHECK(expected.getSubstance() == outputs[2].getSubstance());
        CHECK(expected.getCarbon() == outputs[2].getCarbon());
        CHECK(expected.getHydrogen() == outputs[2].getHydrogen());
        CHECK(expected.getSulphur() == outputs[2].getSulphur());
        CHECK(expected.getInertAsh() == outputs[2].getInertAsh());
        CHECK(expected.getO2() == outputs[2].getO2());
        CHECK(expected.getMoisture() == outputs[2].getMoisture());
        CHECK(expected.getNitrogen() == outputs[2].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[2];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8);
        expected.setID(3);
        expected.setSubstance("Typical Lignite - US");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }

    // Fuel Oil #2
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 86.6, 12.8, 0.5, 0, 0, 0, 0.1);
        expected.setSubstance("Fuel Oil #2");
        expected.setID(4);
        CHECK(expected.getID() == outputs[3].getID());
        CHECK(expected.getSubstance() == outputs[3].getSubstance());
        CHECK(expected.getCarbon() == outputs[3].getCarbon());
        CHECK(expected.getHydrogen() == outputs[3].getHydrogen());
        CHECK(expected.getSulphur() == outputs[3].getSulphur());
        CHECK(expected.getInertAsh() == outputs[3].getInertAsh());
        CHECK(expected.getO2() == outputs[3].getO2());
        CHECK(expected.getMoisture() == outputs[3].getMoisture());
        CHECK(expected.getNitrogen() == outputs[3].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[3];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 86.6, 12.8, 0.5, 0, 0, 0, 0.1);
        expected.setID(4);
        expected.setSubstance("Fuel Oil #2");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }

    // Fuel Oil #6
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 87.1, 10.6, 2.1, 0.2, 0, 0, 0);
        expected.setSubstance("Fuel Oil #6");
        expected.setID(5);
        CHECK(expected.getID() == outputs[4].getID());
        CHECK(expected.getSubstance() == outputs[4].getSubstance());
        CHECK(expected.getCarbon() == outputs[4].getCarbon());
        CHECK(expected.getHydrogen() == outputs[4].getHydrogen());
        CHECK(expected.getSulphur() == outputs[4].getSulphur());
        CHECK(expected.getInertAsh() == outputs[4].getInertAsh());
        CHECK(expected.getO2() == outputs[4].getO2());
        CHECK(expected.getMoisture() == outputs[4].getMoisture());
        CHECK(expected.getNitrogen() == outputs[4].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[4];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 87.1, 10.6, 2.1, 0.2, 0, 0, 0);
        expected.setID(5);
        expected.setSubstance("Fuel Oil #6");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }

    // Typical Wood
    {
        auto const outputs = defaultData.getSolidLiquidFlueGasMaterials();
        CHECK(outputs.size() == 6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2);
        expected.setSubstance("Typical Wood");
        expected.setID(6);
        CHECK(expected.getID() == outputs[5].getID());
        CHECK(expected.getSubstance() == outputs[5].getSubstance());
        CHECK(expected.getCarbon() == outputs[5].getCarbon());
        CHECK(expected.getHydrogen() == outputs[5].getHydrogen());
        CHECK(expected.getSulphur() == outputs[5].getSulphur());
        CHECK(expected.getInertAsh() == outputs[5].getInertAsh());
        CHECK(expected.getO2() == outputs[5].getO2());
        CHECK(expected.getMoisture() == outputs[5].getMoisture());
        CHECK(expected.getNitrogen() == outputs[5].getNitrogen());
    }

    {
        auto const output   = defaultData.getSolidLiquidFlueGasMaterials()[5];
        auto       expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2);
        expected.setID(6);
        expected.setSubstance("Typical Wood");
        CHECK(expected.getID() == output.getID());
        CHECK(expected.getSubstance() == output.getSubstance());
        CHECK(expected.getCarbon() == output.getCarbon());
        CHECK(expected.getHydrogen() == output.getHydrogen());
        CHECK(expected.getSulphur() == output.getSulphur());
        CHECK(expected.getInertAsh() == output.getInertAsh());
        CHECK(expected.getO2() == output.getO2());
        CHECK(expected.getMoisture() == output.getMoisture());
        CHECK(expected.getNitrogen() == output.getNitrogen());
    }
}

TEST_CASE("DefaultData - getMotorData", "[databases]") {
    auto defaultData = DefaultData();

    {
        auto const outputs = defaultData.getMotorData();
        CHECK(outputs.size() == 954);
    }
}

TEST_CASE( "DefaultData CompressorType1 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType1Data();

    {
        CHECK( outputs.size() == 308 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("5 hp/3.7 kW" == outputFirstCD.model());
        CHECK(85 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("125 hp/90 kW" == outputLastCD.model());
        CHECK(92.40000153 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType1_GT100kW - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType1_GT100kWData();

    {
        CHECK( outputs.size() == 317 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("150 hp/110 kW" == outputFirstCD.model());
        CHECK(93 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("500 hp/375 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType2 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType2Data();

    {
        CHECK( outputs.size() == 225 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("100 hp/75 kW" == outputFirstCD.model());
        CHECK(91.69999695 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("600 hp/450 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType3 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType3Data();

    {
        CHECK( outputs.size() == 180 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("50 hp/37 kW" == outputFirstCD.model());
        CHECK(91.69999695 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("500 hp/375 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType4 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType4Data();

    {
        CHECK( outputs.size() == 294 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("5 hp/3.7 kW" == outputFirstCD.model());
        CHECK(85 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("350 hp/260 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType5 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType5Data();

    {
        CHECK( outputs.size() == 301 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("5 hp/3.7 kW" == outputFirstCD.model());
        CHECK(85 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("400 hp/300 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData CompressorType6 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType6Data();

    {
        CHECK( outputs.size() == 5 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.ID());
        CHECK("example centrifugal/0 kW" == outputFirstCD.model());
        CHECK(94.5 == outputFirstCD.effFL());

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.ID());
        CHECK("example centrifugal/0 kW" == outputLastCD.model());
        CHECK(94.5 == outputLastCD.effFL());
    }
}

TEST_CASE( "DefaultData - getLightingData", "[databases]" ) {
    auto const outputs = DefaultData().getLightingData();

    {
        CHECK( outputs.size() == 74 );
    }

    {
        auto const& outputFirstLS = outputs[0];
        CHECK(1 == outputFirstLS.ID());
        CHECK("Metal Halide" == outputFirstLS.category());
        CHECK("175-W Metal Halide" == outputFirstLS.type());
        CHECK(0.8333 == outputFirstLS.lumenDegradationFactor());

        auto length = (int)outputs.size();
        auto const& outputLastLS = outputs[length - 1];
        CHECK(length == outputLastLS.ID());
        CHECK("LED Troffers" == outputLastLS.category());
        CHECK("4L 2 Foot LED" == outputLastLS.type());
        CHECK(1 == outputLastLS.lumenDegradationFactor());
    }
}
