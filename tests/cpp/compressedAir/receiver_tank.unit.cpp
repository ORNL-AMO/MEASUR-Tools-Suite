#include "catch.hpp"

#include "compressedAir/receiver_tank.h"

using namespace Catch;
using namespace receiver_tank;

TEST_CASE("ReceiverTank - Usable Air Capacity", "[CompressedAir][ReceiverTank][UsableCapacity]") {
    CHECK(calculateUsableCapacity({660, 110, 100}).usable_capacity == Approx(60.0240096038));
    CHECK(calculateUsableCapacity({760, 110, 100}).usable_capacity == Approx(69.1185565135));
    CHECK(calculateUsableCapacity({760, 150, 100}).usable_capacity == Approx(345.5927825676));
    CHECK(calculateUsableCapacity({760, 150, 130}).usable_capacity == Approx(138.237113027));
}

TEST_CASE("ReceiverTank - General Size", "[CompressedAir][ReceiverTank][GeneralSize]") {
    CHECK(calculateGeneralSize({150, 3, 14.7}).tank_size == Approx(5497.8));
    CHECK(calculateGeneralSize({190, 3, 14.7}).tank_size == Approx(6963.88));
    CHECK(calculateGeneralSize({190, 8, 14.7}).tank_size == Approx(2611.455));
    CHECK(calculateGeneralSize({190, 8, 12.7}).tank_size == Approx(2256.155));
}

TEST_CASE("ReceiverTank - Dedicated Storage Size", "[CompressedAir][ReceiverTank][DedicatedStorageSize]") {
    CHECK(calculateDedicatedStorageSize({0.5, 100, 14.7, 110, 100}).tank_size == Approx(549.78));
    CHECK(calculateDedicatedStorageSize({1.5, 100, 14.7, 110, 100}).tank_size == Approx(1649.34));
    CHECK(calculateDedicatedStorageSize({1.5, 120, 14.7, 110, 100}).tank_size == Approx(1979.208));
    CHECK(calculateDedicatedStorageSize({1.5, 120, 11.7, 110, 100}).tank_size == Approx(1575.288));
    CHECK(calculateDedicatedStorageSize({1.5, 120, 11.7, 150, 100}).tank_size == Approx(315.0576));
    CHECK(calculateDedicatedStorageSize({1.5, 120, 11.7, 150, 120}).tank_size == Approx(525.096));
}

TEST_CASE("ReceiverTank - Metered Storage Size", "[CompressedAir][ReceiverTank][MeteredStorageSize]") {
    CHECK(calculateMeteredStorageSize({0.5, 900, 14.7, 100, 70, 45}).tank_size == Approx(1566.873));
    CHECK(calculateMeteredStorageSize({1.5, 900, 14.7, 100, 70, 45}).tank_size == Approx(4700.619));
    CHECK(calculateMeteredStorageSize({1.5, 800, 14.7, 100, 70, 45}).tank_size == Approx(4150.839));
    CHECK(calculateMeteredStorageSize({1.5, 800, 11.7, 100, 70, 45}).tank_size == Approx(3303.729));
    CHECK(calculateMeteredStorageSize({1.5, 800, 11.7, 120, 70, 45}).tank_size == Approx(1982.2374));
    CHECK(calculateMeteredStorageSize({1.5, 800, 11.7, 120, 90, 45}).tank_size == Approx(3303.729));
    CHECK(calculateMeteredStorageSize({1.5, 800, 11.7, 120, 90, 75}).tank_size == Approx(3172.455));
}

TEST_CASE("ReceiverTank - Metered Storage Refill Time", "[CompressedAir][ReceiverTank][MeteredStorageRefillTime]") {
    CHECK(calculateMeteredStorageSize({0.333, 640, 14.7, 97, 90, 300}).refill_time == Approx(22.642).margin(0.01));
}

TEST_CASE("ReceiverTank - Bridging Compressor Reaction Delay Size",
          "[CompressedAir][ReceiverTank][BridgingSize]") {
    CHECK(calculateBridgingSize({1000, 250, 14.7, 600, 2}).tank_size == Approx(2199.12));
    CHECK(calculateBridgingSize({1200, 250, 14.7, 600, 2}).tank_size == Approx(2638.944));
    CHECK(calculateBridgingSize({1200, 350, 14.7, 600, 2}).tank_size == Approx(1884.96));
    CHECK(calculateBridgingSize({1200, 350, 11.7, 600, 2}).tank_size == Approx(1500.2742857143));
    CHECK(calculateBridgingSize({1200, 350, 11.7, 800, 2}).tank_size == Approx(2000.3657142857));
    CHECK(calculateBridgingSize({1200, 350, 11.7, 800, 19}).tank_size == Approx(210.56481203));
}

TEST_CASE("ReceiverTank - Compressor Cycle Size", "[CompressedAir][ReceiverTank][CompressorCycleSize]") {
    // {load_time, unload_time, compressor_capacity, unload_pressure, full_load_pressure, atmospheric_pressure}
    {
        auto r = calculateCompressorCycleSize({15, 5, 100, 110, 100, 14.7});
        CHECK(r.tank_size           == Approx(68.7225));
        CHECK(r.effective_capacity  == Approx(75.0));
        CHECK(r.pressure_change     == Approx(10.0));
        CHECK(r.volume_cf           == Approx(9.1875));
    }
    {
        auto r = calculateCompressorCycleSize({20, 10, 200, 120, 100, 14.7});
        CHECK(r.tank_size           == Approx(122.1733333));
        CHECK(r.effective_capacity  == Approx(133.3333333));
        CHECK(r.pressure_change     == Approx(20.0));
        CHECK(r.volume_cf           == Approx(16.3333333));
    }
    {
        auto r = calculateCompressorCycleSize({10, 5, 150, 105, 100, 14.7});
        CHECK(r.tank_size           == Approx(183.26));
        CHECK(r.effective_capacity  == Approx(100.0));
        CHECK(r.pressure_change     == Approx(5.0));
        CHECK(r.volume_cf           == Approx(24.5));
    }
    {
        auto r = calculateCompressorCycleSize({10, 5, 150, 105, 100, 12.0});
        CHECK(r.tank_size           == Approx(149.6));
        CHECK(r.effective_capacity  == Approx(100.0));
        CHECK(r.pressure_change     == Approx(5.0));
        CHECK(r.volume_cf           == Approx(20.0));
    }
    {
        auto r = calculateCompressorCycleSize({25, 15, 300, 115, 95, 14.7});
        CHECK(r.tank_size           == Approx(257.709375));
        CHECK(r.effective_capacity  == Approx(187.5));
        CHECK(r.pressure_change     == Approx(20.0));
        CHECK(r.volume_cf           == Approx(34.453125));
    }
}
