#include "databases/default_data.h"

#include "catch.hpp"

using namespace Catch;

#include "databases/MotorData.h"
#include "databases/compressors_type1_data.h"
#include "databases/compressors_type1_GT_100kW_data.h"
#include "databases/compressors_type2_data.h"
#include "databases/compressors_type3_data.h"
#include "databases/compressors_type4_data.h"
#include "databases/compressors_type5_data.h"
#include "databases/compressors_type6_data.h"
#include "databases/lighting_data.h"
#include <compressedAir/assessment/compressor_catalog.h>
#include <other/lighting_data.h>
#include "motorDriven/motor/MotorData.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"

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
        CHECK(1 == outputFirstCD.id);
        CHECK("5 hp/3.7 kW" == outputFirstCD.model);
        CHECK(85 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("125 hp/90 kW" == outputLastCD.model);
        CHECK(92.40000153 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType1_GT100kW - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType1_GT100kWData();

    {
        CHECK( outputs.size() == 317 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("150 hp/110 kW" == outputFirstCD.model);
        CHECK(93 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("500 hp/375 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType2 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType2Data();

    {
        CHECK( outputs.size() == 225 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("100 hp/75 kW" == outputFirstCD.model);
        CHECK(91.69999695 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("600 hp/450 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType3 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType3Data();

    {
        CHECK( outputs.size() == 180 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("50 hp/37 kW" == outputFirstCD.model);
        CHECK(91.69999695 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("500 hp/375 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType4 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType4Data();

    {
        CHECK( outputs.size() == 294 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("5 hp/3.7 kW" == outputFirstCD.model);
        CHECK(85 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("350 hp/260 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType5 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType5Data();

    {
        CHECK( outputs.size() == 301 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("5 hp/3.7 kW" == outputFirstCD.model);
        CHECK(85 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("400 hp/300 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
    }
}

TEST_CASE( "DefaultData CompressorType6 - getCompressorData", "[databases]" ) {
    auto const outputs = DefaultData().getCompressorType6Data();

    {
        CHECK( outputs.size() == 5 );
    }

    {
        auto const& outputFirstCD = outputs[0];
        CHECK(1 == outputFirstCD.id);
        CHECK("example centrifugal/0 kW" == outputFirstCD.model);
        CHECK(94.5 == outputFirstCD.fullLoadEfficiencyPercent);

        auto length = (int)outputs.size();
        auto const& outputLastCD = outputs[length - 1];
        CHECK(length == outputLastCD.id);
        CHECK("example centrifugal/0 kW" == outputLastCD.model);
        CHECK(94.5 == outputLastCD.fullLoadEfficiencyPercent);
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
