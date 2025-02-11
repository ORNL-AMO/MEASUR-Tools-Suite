#include "catch.hpp"
#include "motorDriven/pump/PumpData.h"
#include "motorDriven/pump/PumpResult.h"
#include "motorDriven/motor/EstimateFLA.h"
#include <unordered_map>
#include <array>

TEST_CASE( "PumpResults Premium existing", "[PumpResults]" ) {
	double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_hours = 8760, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::PREMIUM);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

	auto const & ex = pumpResult.calculateExisting();

	CHECK(ex.pumpEfficiency * 100 == Approx(78.555319445));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(103.385910304));
	CHECK(ex.pumpShaftPower == Approx(103.385910304));
	CHECK(ex.motorEfficiency * 100 == Approx(96.4073613585));
	CHECK(ex.motorPowerFactor * 100 == Approx(75.3340317395));
	CHECK(ex.motorCurrent == Approx(127.7311762599));
	CHECK(ex.motorPower == Approx(80));
	CHECK(ex.annualEnergy == Approx(700.8));
	CHECK(ex.annualCost * 1000.0 == Approx(35040));
	CHECK(pumpResult.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(pumpResult.getOptimizationRating() == Approx(0));

}

TEST_CASE( "PumpResults existing and modified", "[PumpResults]" ) {
	double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = .95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_hours = 8760, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();

	CHECK(ex.pumpEfficiency * 100 == Approx(80.2620381));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(101.18747791246317));
	CHECK(ex.pumpShaftPower == Approx(101.18747791246317));
	CHECK(ex.motorEfficiency * 100 == Approx(94.35732315337191));
	CHECK(ex.motorPowerFactor * 100 == Approx(76.45602656178534));
	CHECK(ex.motorCurrent == Approx(125.85671685040634));
	CHECK(ex.motorPower == Approx(80));
	CHECK(ex.annualEnergy == Approx(700.8));
	CHECK(ex.annualCost * 1000.0 == Approx(35040));

	CHECK(mod.pumpEfficiency * 100 == Approx(80));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(101.5189151255));
	CHECK(mod.pumpShaftPower == Approx(101.5189151255));
	CHECK(mod.motorEfficiency * 100 == Approx(94.3652462131));
	CHECK(mod.motorPowerFactor * 100 == Approx(76.2584456388));
	CHECK(mod.motorCurrent == Approx(126.5852583329));
	CHECK(mod.motorPower == Approx(80.2551564807));
	CHECK(mod.annualEnergy == Approx(703.0351707712));
	CHECK(mod.annualCost * 1000.0 == Approx(35151.7585385623));

	CHECK(pumpResult.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(pumpResult.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PumpResults - existing changed voltage", "[PumpResults]" ) {
	double pumpEfficiency = 0.382, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
	double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
	double motor_rated_fla = 83, margin = 0.15, operating_hours = 8760, cost_kw_hour = 0.039, flow_rate = 2800;
	double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
	double specified_efficiency = 1.0;
	Pump::Style style1(Pump::Style::END_SUCTION_STOCK);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::STANDARD);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
	auto const & ex = pumpResult.calculateExisting();
	CHECK(ex.pumpEfficiency * 100 == Approx(21.4684857877));
	CHECK(ex.motorRatedPower == Approx(350));
	CHECK(ex.motorShaftPower == Approx(338.9835681041));
	CHECK(ex.pumpShaftPower == Approx(338.9835681041));
	CHECK(ex.motorEfficiency * 100 == Approx(94.518008321));
	CHECK(ex.motorPowerFactor * 100 == Approx(83.4292940632));
	CHECK(ex.motorCurrent == Approx(80.5));
	CHECK(ex.motorPower == Approx(267.548741554));
	CHECK(ex.annualEnergy == Approx(2343.7));
	CHECK(ex.annualCost * 1000.0 == Approx(91405.352064809));
}

TEST_CASE( "PumpResults - mod changed voltage", "[PumpResults]" ) {
	double pumpEfficiency = 0.204, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1;
	double stages = 1.0, motor_rated_power = 30, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 230;
	double motor_rated_fla = 71, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 500;
	double head = 60, motor_field_power = 30, motor_field_current = 80.5, motor_field_voltage = 236;
	double specified_efficiency = 1.0;
	Pump::Style style1(Pump::Style::END_SUCTION_STOCK);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);
	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();
	CHECK(ex.pumpEfficiency * 100 == Approx(20.4308309532));
	CHECK(ex.motorShaftPower == Approx(37.06710939));
	CHECK(ex.pumpShaftPower == Approx(37.06710939));
	CHECK(ex.motorEfficiency * 100 == Approx(92.1735453498));
	CHECK(ex.motorPowerFactor * 100 == Approx(86.9792780871));
	CHECK(ex.motorCurrent == Approx(84.3786991404));
	CHECK(ex.motorPower == Approx(30.0));
	CHECK(mod.pumpEfficiency * 100 == Approx(20.4));
	CHECK(mod.motorShaftPower == Approx(37.1231296996));
	CHECK(mod.pumpShaftPower == Approx(37.1231296996));
	CHECK(mod.motorEfficiency * 100 == Approx(92.164816187));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.4617844857));
	CHECK(mod.motorCurrent == Approx(85.0201337882));
	CHECK(mod.motorPower == Approx(30.0482102275));
}

TEST_CASE( "PumpResults - specified drive", "[PumpResults]" ) {
	double pumpEfficiency = 0.382, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
	double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
	double motor_rated_fla = 83, margin = 0.15, operating_hours = 8760, cost_kw_hour = 0.039, flow_rate = 2800;
	double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
	double specified_efficiency = 0.95;
	Pump::Style style1(Pump::Style::END_SUCTION_STOCK);
	Motor::Drive drive1(Motor::Drive::SPECIFIED); //SPEC
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::STANDARD);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
	auto const & ex = pumpResult.calculateExisting();
	CHECK(ex.pumpEfficiency * 100 == Approx(22.5984060923));
	CHECK(ex.motorRatedPower == Approx(350));
	CHECK(ex.motorShaftPower == Approx(338.9835681041));
	CHECK(ex.pumpShaftPower == Approx(322.0343896989));
	CHECK(ex.motorEfficiency * 100 == Approx(94.518008321));
	CHECK(ex.motorPowerFactor * 100 == Approx(83.4292940632));
	CHECK(ex.motorCurrent == Approx(80.5));
	CHECK(ex.motorPower == Approx(267.548741554));
	CHECK(ex.annualEnergy == Approx(2343.7269760207537));
	CHECK(ex.annualCost * 1000.0 == Approx(91405.352064809));
}

TEST_CASE( "PumpResults - existing and modified", "[PumpResults]" ) {
	double pumpEfficiency = 0.382, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = .95, motor_rated_voltage = 460;
	double motor_rated_fla = 227.29, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 277.0, motor_field_power = 150.0, motor_field_current = 125.857, motor_field_voltage = 480;
	double specified_efficiency = 1.0;
	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);
	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();
	CHECK(ex.pumpEfficiency * 100 == Approx(38.1094253534));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(191.1541214642));
	CHECK(ex.pumpShaftPower == Approx(183.4851259332));
	CHECK(ex.motorEfficiency * 100 == Approx(95.0673164082));
	CHECK(ex.motorPowerFactor * 100 == Approx(86.3561411197));
	CHECK(ex.motorCurrent == Approx(208.9277690995));
	CHECK(ex.motorPower == Approx(150.0));
	CHECK(ex.annualEnergy == Approx(1314.0));
	CHECK(ex.annualCost * 1000.0 == Approx(78840));
	CHECK(mod.pumpEfficiency * 100 == Approx(38.2));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(190.7010275392));
	CHECK(mod.pumpShaftPower == Approx(183.0500709481));
	CHECK(mod.motorEfficiency * 100 == Approx(95.0700964487));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.8975146434));
	CHECK(mod.motorCurrent == Approx(207.128014213));
	CHECK(mod.motorPower == Approx(149.6401247588));
	CHECK(mod.annualEnergy == Approx(1310.8474928874));
	CHECK(mod.annualCost * 1000.0 == Approx(78650.8495732458));
}

TEST_CASE( "PumpResults2 v-belt type", "[PumpResults]" ) {
	double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(200.507050278));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(95.6211069257));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.7354953183));
	CHECK(mod.motorCurrent == Approx(226.3599309627));
	CHECK(mod.motorPower == Approx(156.4281376282));
	CHECK(mod.annualEnergy == Approx(1370.3104856228));
	CHECK(mod.annualCost * 1000.0 == Approx(82218.6291373691));

	CHECK(pumpResult.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(pumpResult.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PumpResults notched v belt", "[PumpResults]" ) {
	double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::N_V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(198.2102452363));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(95.6417064886));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.6915209945));
	CHECK(mod.motorCurrent == Approx(223.8322217984));
	CHECK(mod.motorPower == Approx(154.6029182589));
	CHECK(mod.annualEnergy == Approx(1354.3215639476));
	CHECK(mod.annualCost * 1000.0 == Approx(81259.2938368578));

	CHECK(pumpResult.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(pumpResult.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PumpResults sync belt", "[PumpResults]" ) {
	double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::S_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PumpResult pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

	auto const & ex = pumpResult.calculateExisting();
	auto const & mod = pumpResult.calculateModified();

	CHECK(mod.motorShaftPower == Approx(194.767));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorPower == Approx(151.8722277599));
}

TEST_CASE( "EstimateFLA", "[EstimateFLA]" ) {
	auto unitTestNumber = 0; // unit test number 0 indexed
	const std::array<std::array<double, 6>, 9> expected = {
			{
					{{18.8775576, 23.6212730421, 34.0613092325, 46.5048449789, 60.381474681, 75.5372248259}},
					{{48.6495840124, 63.249248253, 96.1954123714, 132.4400532659, 172.6294043084, 215.9593847898}},
					{{49.55811480809, 56.11300070569, 78.49438625307, 102.84658002297, 129.16907799852, 159.7821494841}},
					{{28.6566235624, 39.6191308792, 61.8010643593, 86.8044256422, 113.8781958, 142.6893793376}},
					{{53.3464740091, 75.2070177891, 119.291789, 167.65708225, 219.981424828, 275.6367253}},
					{{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
					{{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
					{{88.3024614572, 116.2594022102, 179.8542042707, 249.6685871227, 326.1945449939, 408.0693757874}},
					{{494.2117767987, 618.953071161, 849.5097896611, 1130.1225205859, 1439.4257134111, 1780.5696074895}}
			}
	};

	auto const compare = [&unitTestNumber, &expected](const std::array<double, 6> & results) {
		for (unsigned int i = 0; i < results.size(); i++) {
		// for (auto i = 0; i < results.size(); i++) {
			INFO("index is " + std::to_string(i) + " and the unit test number is " + std::to_string(unitTestNumber));
			CHECK(expected.at(unitTestNumber).at(i) == Approx(results[i]));
		}
		unitTestNumber++;
	};

	// test voltages
	compare(EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(150, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());

	compare(EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .965, 100).calculate());
	compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .985, 110).calculate());

	compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 98.5, 110).calculate());
	compare(EstimateFLA(290, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 93.5, 110).calculate());
	compare(EstimateFLA(1200, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 65.5, 210).calculate());

	// test FLA
	auto t = EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(277.7547835326));

	t = EstimateFLA(150, 2400, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 110);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(707.6948056564));

	t = EstimateFLA(75, 2000, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 110);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(348.9439377969));

	t = EstimateFLA(175, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 220);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(460.3700518143));

	t = EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .80, 220);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(312.5479443728)); //311.3720600292

	t = EstimateFLA(125, 1900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .90, 220); // 120 -> 125, 
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(302.2156478756)); //291.0633925033

	t = EstimateFLA(90, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 120);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(432.5925070407));

	t = EstimateFLA(150, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .55, 600); // 90 -> 600
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(218.1935995715)); //1457.2693184418

	t = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .94, 460);
	t.calculate();
	CHECK(t.getEstimatedFLA() == Approx(228.3902237064));

	t = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, .95, 460);
	t.calculate();
	CHECK(t.getEstimatedFLA() == Approx(227.288340026));
}
