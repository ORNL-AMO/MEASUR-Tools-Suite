#include "motorDriven/pump/pump_head.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Calculate pump head from a suction tank", "[pump_head]") {
    constexpr double kFlowRate = 2000.0;

    auto result = pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 115.0, 0.0,
                                                       1.0, 10.0, 124.0, 0.0, 1.0});
    CHECK(result.pump_head == Approx(22.9728655518));
    CHECK(result.differential_pressure_head == Approx(20.7972269883));
    CHECK(result.differential_elevation_head == Approx(0.0));
    CHECK(result.differential_velocity_head == Approx(1.0372994353));
    CHECK(result.estimated_suction_friction_head == Approx(0.1010396929));
    CHECK(result.estimated_discharge_friction_head == Approx(1.0372994353));

    REQUIRE(pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 0.0,
                                                 1.0, 10.0, 124.0, 0.0, 1.0})
                .pump_head == Approx(46.080895538862784));
    REQUIRE(pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                 1.0, 10.0, 124.0, 0.0, 1.0})
                .pump_head == Approx(41.080895538862784));

    result = pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                  0.5, 10.0, 124.0, 0.0, 1.0});
    CHECK(result.pump_head == Approx(41.0303756924));
    CHECK(result.differential_pressure_head == Approx(43.9052569754));
    CHECK(result.differential_elevation_head == Approx(-5.0));
    CHECK(result.differential_velocity_head == Approx(1.0372994353));
    CHECK(result.estimated_suction_friction_head == Approx(0.0505198464));
    CHECK(result.estimated_discharge_friction_head == Approx(1.0372994353));

    result = pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                  1.0, 15.0, 124.0, 0.0, 1.0});
    CHECK(result.pump_head == Approx(39.416093976));
    CHECK(result.differential_pressure_head == Approx(43.9052569754));
    CHECK(result.differential_elevation_head == Approx(-5.0));
    CHECK(result.differential_velocity_head == Approx(0.2048986539));
    CHECK(result.estimated_suction_friction_head == Approx(0.1010396929));
    CHECK(result.estimated_discharge_friction_head == Approx(0.2048986539));

    REQUIRE(pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                 1.0, 15.0, 124.0, 0.0, 1.0})
                .pump_head == Approx(39.41609397604601));
    REQUIRE(pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                 1.0, 15.0, 135.0, 0.0, 1.0})
                .pump_head == Approx(64.83492696179103));
    REQUIRE(pump_head::calculateFromSuctionTank({1.0, kFlowRate, 17.9, 105.0, 5.0,
                                                 1.0, 15.0, 135.0, 4.0, 0.1})
                .pump_head == Approx(68.6505181732944));
}

TEST_CASE("Calculate pump head from suction and discharge gauges", "[pump_head]") {
    constexpr double kFlowRate = 2000.0;

    auto result = pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 5.0, 5.0,
                                                        1.0, 15.0, 50.0, 1.0, 1.0});
    CHECK(result.pump_head == Approx(100.3959322495));
    CHECK(result.differential_pressure_head == Approx(103.9861349417));
    CHECK(result.differential_elevation_head == Approx(-4.0));
    CHECK(result.differential_velocity_head == Approx(0.103858961));
    CHECK(result.estimated_suction_friction_head == Approx(0.1010396929));
    CHECK(result.estimated_discharge_friction_head == Approx(0.2048986539));

    REQUIRE(pump_head::calculateFromSuctionGauge({0.8, kFlowRate, 17.9, 5.0, 5.0,
                                                  1.0, 15.0, 50.0, 1.0, 1.0})
                .pump_head == Approx(126.3924659849));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 5.0,
                                                  1.0, 15.0, 50.0, 1.0, 1.0})
                .pump_head == Approx(88.84191725593406));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                  1.0, 15.0, 50.0, 1.0, 1.0})
                .pump_head == Approx(78.84191725593406));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                  0.1, 15.0, 50.0, 1.0, 1.0})
                .pump_head == Approx(78.75098153232594));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                  0.1, 60.0, 50.0, 1.0, 1.0})
                .pump_head == Approx(78.34278499528914));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                  0.1, 60.0, 20.0, 1.0, 1.0})
                .pump_head == Approx(9.018695034166301));
    REQUIRE(pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                  0.1, 60.0, 20.0, 10.0, 1.0})
                .pump_head == Approx(18.0186950341663));

    result = pump_head::calculateFromSuctionGauge({1.0, kFlowRate, 17.9, 10.0, 15.0,
                                                   0.1, 60.0, 20.0, 10.0, 0.9});
    CHECK(result.pump_head == Approx(18.0186149956));
    CHECK(result.differential_pressure_head == Approx(23.108029987));
    CHECK(result.differential_elevation_head == Approx(-5.0));
    CHECK(result.differential_velocity_head == Approx(-0.1002393075));
    CHECK(result.estimated_suction_friction_head == Approx(0.0101039693));
    CHECK(result.estimated_discharge_friction_head == Approx(0.0007203468));
}
