#include "catch.hpp"
#include "motorDriven/pump/PumpData.h"
#include "motorDriven/pumpFan/PumpShaftPower.h"
#include <unordered_map>
#include <array>

TEST_CASE( "Pump shaft power", "[Pump][pump shaft power][drive]" ) {
	CHECK(PumpShaftPower(50, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(48.4814329723));
	CHECK(PumpShaftPower(100, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(97.0776282082));
	CHECK(PumpShaftPower(150, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(145.6804036099));
	CHECK(PumpShaftPower(200, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(194.2722411119));
	CHECK(PumpShaftPower(250, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(242.8550331213));

	CHECK(PumpShaftPower(50, Motor::Drive::V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(47.8740061612));
	CHECK(PumpShaftPower(100, Motor::Drive::V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(95.9086794914));
	CHECK(PumpShaftPower(150, Motor::Drive::V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(143.9525650539));
	CHECK(PumpShaftPower(200, Motor::Drive::V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(191.981137556));
	CHECK(PumpShaftPower(250, Motor::Drive::V_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(239.9970463698));

	CHECK(PumpShaftPower(50, Motor::Drive::S_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(49.3925731889));
	CHECK(PumpShaftPower(100, Motor::Drive::S_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(98.8310512833));
	CHECK(PumpShaftPower(150, Motor::Drive::S_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(148.272161444));
	CHECK(PumpShaftPower(200, Motor::Drive::S_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(197.7088964447));
	CHECK(PumpShaftPower(250, Motor::Drive::S_BELT_DRIVE, 0).calculate().pumpShaftPower == Approx(247.1420132485));

	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 1.00).calculate().pumpShaftPower == Approx(50));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.98).calculate().pumpShaftPower == Approx(49));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.96).calculate().pumpShaftPower == Approx(48));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.94).calculate().pumpShaftPower == Approx(47));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.92).calculate().pumpShaftPower == Approx(46));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.90).calculate().pumpShaftPower == Approx(45));

	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 1.00).calculate().pumpShaftPower == Approx(250));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.98).calculate().pumpShaftPower == Approx(245));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.96).calculate().pumpShaftPower == Approx(240));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.94).calculate().pumpShaftPower == Approx(235));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.92).calculate().pumpShaftPower == Approx(230));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.90).calculate().pumpShaftPower == Approx(225));
}