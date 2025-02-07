#include "catch.hpp"
#include "fans/FanResult.h"
#include "motorDriven/pump/PumpData.h"
#include <unordered_map>
#include <array>

TEST_CASE( "Fan Output existing", "[Fan results existing]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 600, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataBaseline fanFieldData = {460, 460, 660, 129691, -16.36, 1.1, 0.988, Motor::LoadEstimationMethod::POWER, 0};
	FanResult result = {fanInput, motor, 8760, 0.06};
	auto const output = result.calculateExisting(fanFieldData);

	CHECK(Approx(output.fanEfficiency) == 0.595398315);
	CHECK(Approx(output.motorRatedPower) == 600.0);
	CHECK(Approx(output.motorShaftPower) == 590.622186263);
	CHECK(Approx(output.fanShaftPower) == 590.622186263);
	CHECK(Approx(output.motorEfficiency) == 0.9578351108);
	CHECK(Approx(output.motorPowerFactor) == 0.8577466651);
	CHECK(Approx(output.motorCurrent) == 673.1011529439);
	CHECK(Approx(output.motorPower) == 460.0);
	CHECK(Approx(output.annualEnergy) == 4029.6);
	CHECK(Approx(output.annualCost) == 241.776);
	CHECK(Approx(output.estimatedFLA) == 683.2505707137);
	CHECK(Approx(output.fanEnergyIndex) == 0.9718906186);
}

TEST_CASE( "Fan Output modified", "[Fan results modified]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 600, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataModified fanFieldData = {460, 660, 129691, -16.36, 1.1, 0.988, 0};
	FanResult result = {fanInput, motor, 8760, 0.06};
	auto const output = result.calculateModified(fanFieldData, 0.595398315);

	CHECK(Approx(output.fanEfficiency) == 0.595398315);
	CHECK(Approx(output.motorRatedPower) == 600.0);
	CHECK(Approx(output.motorShaftPower) == 590.622186263);
	CHECK(Approx(output.fanShaftPower) == 590.622186263);
	CHECK(Approx(output.motorEfficiency) == 0.9578351072);
	CHECK(Approx(output.motorPowerFactor) == 0.8577480086);
	CHECK(Approx(output.motorCurrent) == 673.1003093353);
	CHECK(Approx(output.motorPower) == 460.0001440224);
	CHECK(Approx(output.annualEnergy) == 4029.6012616363);
	CHECK(Approx(output.annualCost) == 241.7760756982);
	CHECK(Approx(output.fanEnergyIndex) == 0.9718903143);
}
