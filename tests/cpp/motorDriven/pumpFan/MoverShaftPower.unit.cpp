#include "catch.hpp"
#include "motorDriven/pump/PumpData.h"
#include "motorDriven/pumpFan/MoverShaftPower.h"
#include <unordered_map>
#include <array>

TEST_CASE( "Pump shaft power", "[Pump][pump shaft power][drive]" ) {
	CHECK(MoverShaftPower(50, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(48.4814329723));
	CHECK(MoverShaftPower(100, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(97.0776282082));
	CHECK(MoverShaftPower(150, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(145.6804036099));
	CHECK(MoverShaftPower(200, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(194.2722411119));
	CHECK(MoverShaftPower(250, Motor::Drive::N_V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(242.8550331213));

	CHECK(MoverShaftPower(50, Motor::Drive::V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(47.8740061612));
	CHECK(MoverShaftPower(100, Motor::Drive::V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(95.9086794914));
	CHECK(MoverShaftPower(150, Motor::Drive::V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(143.9525650539));
	CHECK(MoverShaftPower(200, Motor::Drive::V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(191.981137556));
	CHECK(MoverShaftPower(250, Motor::Drive::V_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(239.9970463698));

	CHECK(MoverShaftPower(50, Motor::Drive::S_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(49.3925731889));
	CHECK(MoverShaftPower(100, Motor::Drive::S_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(98.8310512833));
	CHECK(MoverShaftPower(150, Motor::Drive::S_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(148.272161444));
	CHECK(MoverShaftPower(200, Motor::Drive::S_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(197.7088964447));
	CHECK(MoverShaftPower(250, Motor::Drive::S_BELT_DRIVE, 0).calculate().moverShaftPower == Approx(247.1420132485));

	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 1.00).calculate().moverShaftPower == Approx(50));
	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 0.98).calculate().moverShaftPower == Approx(49));
	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 0.96).calculate().moverShaftPower == Approx(48));
	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 0.94).calculate().moverShaftPower == Approx(47));
	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 0.92).calculate().moverShaftPower == Approx(46));
	CHECK(MoverShaftPower(50, Motor::Drive::SPECIFIED, 0.90).calculate().moverShaftPower == Approx(45));

	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 1.00).calculate().moverShaftPower == Approx(250));
	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 0.98).calculate().moverShaftPower == Approx(245));
	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 0.96).calculate().moverShaftPower == Approx(240));
	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 0.94).calculate().moverShaftPower == Approx(235));
	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 0.92).calculate().moverShaftPower == Approx(230));
	CHECK(MoverShaftPower(250, Motor::Drive::SPECIFIED, 0.90).calculate().moverShaftPower == Approx(225));
}