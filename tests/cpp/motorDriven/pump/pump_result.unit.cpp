#include "motorDriven/pump/pump_result.h"

#include "catch.hpp"

using namespace Catch;
#include "motorDriven/pump/Pump.h"
#include "physics/constants.h"

namespace {

class PumpResultHarness {
  public:
    PumpResultHarness(Pump::Input pump_input, Motor motor, Pump::FieldData field_data, double operating_hours,
                      double unit_cost)
        : pump_input_(pump_input), motor_(motor), field_data_(field_data), operating_hours_(operating_hours),
          unit_cost_(unit_cost) {}

    pump_result::Result calculateExisting() const {
        return pump_result::calculateExisting({
            {
                pump_input_.style,
                pump_input_.drive,
                pump_input_.specifiedEfficiency,
                pump_input_.specificGravity,
                field_data_.flowRate,
                field_data_.head,
                pump_input_.differentialPressurePsi,
                motor_.motorRatedPower,
                motor_.motorRpm,
                motor_.lineFrequency,
                motor_.efficiencyClass,
                motor_.specifiedEfficiency,
                motor_.motorRatedVoltage,
                field_data_.voltage,
                operating_hours_,
                unit_cost_,
            },
            motor_.fullLoadAmps,
            field_data_.loadEstimationMethod,
            field_data_.motorPower,
            field_data_.motorAmps,
        });
    }

    pump_result::Result calculateModified() const {
        return pump_result::calculateModified({
            {
                pump_input_.style,
                pump_input_.drive,
                pump_input_.specifiedEfficiency,
                pump_input_.specificGravity,
                field_data_.flowRate,
                field_data_.head,
                pump_input_.differentialPressurePsi,
                motor_.motorRatedPower,
                motor_.motorRpm,
                motor_.lineFrequency,
                motor_.efficiencyClass,
                motor_.specifiedEfficiency,
                motor_.motorRatedVoltage,
                field_data_.voltage,
                operating_hours_,
                unit_cost_,
            },
            pump_input_.pumpEfficiency,
        });
    }

  private:
    Pump::Input pump_input_;
    Motor motor_;
    Pump::FieldData field_data_;
    double operating_hours_;
    double unit_cost_;
};

} // namespace

TEST_CASE("Pump results premium existing", "[pump_result]") {
    double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.0, margin = 0, operating_hours = 8760, cost_kw_hour = 0.05, flow_rate = 1840;
    double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
    double specified_efficiency = 1.0;

    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::PREMIUM);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex = pumpResult.calculateExisting();

    CHECK(ex.pump_efficiency * 100 == Approx(78.555319445));
    CHECK(ex.motor_rated_power == Approx(200));
    CHECK(ex.motor_shaft_power == Approx(103.385910304));
    CHECK(ex.mover_shaft_power == Approx(103.385910304));
    CHECK(ex.motor_efficiency * 100 == Approx(96.4073613585));
    CHECK(ex.motor_power_factor * 100 == Approx(75.3340317395));
    CHECK(ex.motor_current == Approx(127.7311762599));
    CHECK(ex.motor_power == Approx(80));
    CHECK(ex.annual_energy == Approx(700.8));
    CHECK(ex.annual_cost * 1000.0 == Approx(35040));
    CHECK(ex.drive_efficiency == Approx(1.0));
    CHECK(ex.load_factor > 0.0);
    CHECK(ex.estimated_full_load_amps > 0.0);
}

TEST_CASE("pump_result positive displacement existing", "[pump_result]") {
    double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    int    stages = 1;
    double motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.0, margin = 0, operating_hours = 8760, cost_kw_hour = 0.05, flow_rate = 100;
    double head = 999.0, differential_pressure_psi = 50.0, motor_field_power = 80, motor_field_current = 125.857;
    double motor_field_voltage = 480, specified_efficiency = 1.0;

    Pump::Style                 style(Pump::Style::POSITIVE_DISPLACEMENT);
    Motor::Drive                drive(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::PREMIUM);
    Motor::LoadEstimationMethod loadEstimationMethod(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style, pumpEfficiency, pump_rated_speed, drive, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency, differential_pressure_psi);
    Motor       motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency,
                      motor_rated_voltage, motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex = pumpResult.calculateExisting();

    const double hydraulicHp = flow_rate * differential_pressure_psi / physics::conversions::kPumpGpmPsiPerHp;
    CHECK(static_cast<int>(Pump::Style::POSITIVE_DISPLACEMENT) == 12);
    CHECK(pump.differentialPressurePsi == Approx(differential_pressure_psi));
    CHECK(ex.pump_efficiency == Approx(hydraulicHp / ex.mover_shaft_power));
    CHECK(ex.motor_power == Approx(motor_field_power));
    CHECK(ex.annual_energy == Approx(motor_field_power * operating_hours / 1000.0));
    CHECK(ex.annual_cost == Approx(ex.annual_energy * cost_kw_hour));
}

TEST_CASE("pump_result positive displacement modified", "[pump_result]") {
    double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    int    stages = 1;
    double motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 0.95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.0, margin = 0, operating_hours = 2000, cost_kw_hour = 0.05, flow_rate = 100;
    double head = 999.0, differential_pressure_psi = 50.0, motor_field_power = 80, motor_field_current = 125.857;
    double motor_field_voltage = 480, specified_efficiency = 1.0;

    Pump::Style                 style(Pump::Style::POSITIVE_DISPLACEMENT);
    Motor::Drive                drive(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
    Motor::LoadEstimationMethod loadEstimationMethod(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style, pumpEfficiency, pump_rated_speed, drive, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency, differential_pressure_psi);
    Motor       motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency,
                      motor_rated_voltage, motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& mod = pumpResult.calculateModified();

    const double expectedMoverShaftPower =
        flow_rate * differential_pressure_psi / (physics::conversions::kPumpGpmPsiPerHp * pumpEfficiency);
    CHECK(mod.pump_efficiency == Approx(pumpEfficiency));
    CHECK(mod.mover_shaft_power == Approx(expectedMoverShaftPower));
    CHECK(mod.motor_shaft_power == Approx(expectedMoverShaftPower));
    CHECK(mod.annual_energy == Approx(mod.motor_power * operating_hours / 1000.0));
    CHECK(mod.annual_cost == Approx(mod.annual_energy * cost_kw_hour));
}

TEST_CASE("pump_result existing and modified", "[pump_result]") {
    double pumpEfficiency = 0.80, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = .95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.0, margin = 0, operating_hours = 8760, cost_kw_hour = 0.05, flow_rate = 1840;
    double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
    double specified_efficiency = 1.0;

    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex  = pumpResult.calculateExisting();
    auto const& mod = pumpResult.calculateModified();

    CHECK(ex.pump_efficiency * 100 == Approx(80.2620381));
    CHECK(ex.motor_rated_power == Approx(200));
    CHECK(ex.motor_shaft_power == Approx(101.18747791246317));
    CHECK(ex.mover_shaft_power == Approx(101.18747791246317));
    CHECK(ex.motor_efficiency * 100 == Approx(94.35732315337191));
    CHECK(ex.motor_power_factor * 100 == Approx(76.45602656178534));
    CHECK(ex.motor_current == Approx(125.85671685040634));
    CHECK(ex.motor_power == Approx(80));
    CHECK(ex.annual_energy == Approx(700.8));
    CHECK(ex.annual_cost * 1000.0 == Approx(35040));

    CHECK(mod.pump_efficiency * 100 == Approx(80));
    CHECK(mod.motor_rated_power == Approx(200));
    CHECK(mod.motor_shaft_power == Approx(101.5189151255));
    CHECK(mod.mover_shaft_power == Approx(101.5189151255));
    CHECK(mod.motor_efficiency * 100 == Approx(94.3652462131));
    CHECK(mod.motor_power_factor * 100 == Approx(76.2584456388));
    CHECK(mod.motor_current == Approx(126.5852583329));
    CHECK(mod.motor_power == Approx(80.2551564807));
    CHECK(mod.annual_energy == Approx(703.0351707712));
    CHECK(mod.annual_cost * 1000.0 == Approx(35151.7585385623));
    CHECK(ex.drive_efficiency == Approx(1.0));
    CHECK(mod.drive_efficiency == Approx(1.0));

}

TEST_CASE("pump_result existing changed voltage", "[pump_result]") {
    double pumpEfficiency = 0.382, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
    double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
    double motor_rated_fla = 83, margin = 0.15, operating_hours = 8760, cost_kw_hour = 0.039, flow_rate = 2800;
    double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
    double specified_efficiency = 1.0;
    Pump::Style                 style1(Pump::Style::END_SUCTION_STOCK);
    Motor::Drive                drive1(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::STANDARD);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
    auto const&     ex = pumpResult.calculateExisting();
    CHECK(ex.pump_efficiency * 100 == Approx(21.4684857877));
    CHECK(ex.motor_rated_power == Approx(350));
    CHECK(ex.motor_shaft_power == Approx(338.9835681041));
    CHECK(ex.mover_shaft_power == Approx(338.9835681041));
    CHECK(ex.motor_efficiency * 100 == Approx(94.518008321));
    CHECK(ex.motor_power_factor * 100 == Approx(83.4292940632));
    CHECK(ex.motor_current == Approx(80.5));
    CHECK(ex.motor_power == Approx(267.548741554));
    CHECK(ex.annual_energy == Approx(2343.7));
    CHECK(ex.annual_cost * 1000.0 == Approx(91405.352064809));
    CHECK(ex.estimated_full_load_amps > 0.0);
}

TEST_CASE("pump_result modified changed voltage", "[pump_result]") {
    double pumpEfficiency = 0.204, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1;
    double stages = 1.0, motor_rated_power = 30, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 230;
    double motor_rated_fla = 71, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 500;
    double head = 60, motor_field_power = 30, motor_field_current = 80.5, motor_field_voltage = 236;
    double specified_efficiency = 1.0;
    Pump::Style                 style1(Pump::Style::END_SUCTION_STOCK);
    Motor::Drive                drive1(Motor::Drive::DIRECT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);
    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
    auto const&     ex  = pumpResult.calculateExisting();
    auto const&     mod = pumpResult.calculateModified();
    CHECK(ex.pump_efficiency * 100 == Approx(20.4308309532));
    CHECK(ex.motor_shaft_power == Approx(37.06710939));
    CHECK(ex.mover_shaft_power == Approx(37.06710939));
    CHECK(ex.motor_efficiency * 100 == Approx(92.1735453498));
    CHECK(ex.motor_power_factor * 100 == Approx(86.9792780871));
    CHECK(ex.motor_current == Approx(84.3786991404));
    CHECK(ex.motor_power == Approx(30.0));
    CHECK(mod.pump_efficiency * 100 == Approx(20.4));
    CHECK(mod.motor_shaft_power == Approx(37.1231296996));
    CHECK(mod.mover_shaft_power == Approx(37.1231296996));
    CHECK(mod.motor_efficiency * 100 == Approx(92.164816187));
    CHECK(mod.motor_power_factor * 100 == Approx(86.4617844857));
    CHECK(mod.motor_current == Approx(85.0201337882));
    CHECK(mod.motor_power == Approx(30.0482102275));
}

TEST_CASE("pump_result specified drive", "[pump_result]") {
    double pumpEfficiency = 0.382, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
    double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
    double motor_rated_fla = 83, margin = 0.15, operating_hours = 8760, cost_kw_hour = 0.039, flow_rate = 2800;
    double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
    double specified_efficiency = 0.95;
    Pump::Style                 style1(Pump::Style::END_SUCTION_STOCK);
    Motor::Drive                drive1(Motor::Drive::SPECIFIED); // SPEC
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::STANDARD);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
    auto const&     ex = pumpResult.calculateExisting();
    CHECK(ex.pump_efficiency * 100 == Approx(22.5984060923));
    CHECK(ex.motor_rated_power == Approx(350));
    CHECK(ex.motor_shaft_power == Approx(338.9835681041));
    CHECK(ex.mover_shaft_power == Approx(322.0343896989));
    CHECK(ex.motor_efficiency * 100 == Approx(94.518008321));
    CHECK(ex.motor_power_factor * 100 == Approx(83.4292940632));
    CHECK(ex.motor_current == Approx(80.5));
    CHECK(ex.motor_power == Approx(267.548741554));
    CHECK(ex.annual_energy == Approx(2343.7269760207537));
    CHECK(ex.annual_cost * 1000.0 == Approx(91405.352064809));
    CHECK(ex.drive_efficiency == Approx(specified_efficiency));
}

TEST_CASE("pump_result current-estimated existing and modified", "[pump_result]") {
    double pumpEfficiency = 0.382, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = .95, motor_rated_voltage = 460;
    double motor_rated_fla = 227.29, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
    double head = 277.0, motor_field_power = 150.0, motor_field_current = 125.857, motor_field_voltage = 480;
    double specified_efficiency = 1.0;
    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::V_BELT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);
    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);
    auto const&     ex  = pumpResult.calculateExisting();
    auto const&     mod = pumpResult.calculateModified();
    CHECK(ex.pump_efficiency * 100 == Approx(38.1094253534));
    CHECK(ex.motor_rated_power == Approx(200));
    CHECK(ex.motor_shaft_power == Approx(191.1541214642));
    CHECK(ex.mover_shaft_power == Approx(183.4851259332));
    CHECK(ex.motor_efficiency * 100 == Approx(95.0673164082));
    CHECK(ex.motor_power_factor * 100 == Approx(86.3561411197));
    CHECK(ex.motor_current == Approx(208.9277690995));
    CHECK(ex.motor_power == Approx(150.0));
    CHECK(ex.annual_energy == Approx(1314.0));
    CHECK(ex.annual_cost * 1000.0 == Approx(78840));
    CHECK(mod.pump_efficiency * 100 == Approx(38.2));
    CHECK(mod.motor_rated_power == Approx(200));
    CHECK(mod.motor_shaft_power == Approx(190.7010275392));
    CHECK(mod.mover_shaft_power == Approx(183.0500709481));
    CHECK(mod.motor_efficiency * 100 == Approx(95.0700964487));
    CHECK(mod.motor_power_factor * 100 == Approx(86.8975146434));
    CHECK(mod.motor_current == Approx(207.128014213));
    CHECK(mod.motor_power == Approx(149.6401247588));
    CHECK(mod.annual_energy == Approx(1310.8474928874));
    CHECK(mod.annual_cost * 1000.0 == Approx(78650.8495732458));
}

TEST_CASE("pump_result V-belt drive", "[pump_result]") {
    double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
    double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
    double specified_efficiency = 1.0;

    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::V_BELT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex  = pumpResult.calculateExisting();
    CHECK(ex.motor_power == Approx(150.0));

    auto const& mod = pumpResult.calculateModified();
    CHECK(mod.pump_efficiency * 100 == Approx(62.3));
    CHECK(mod.motor_rated_power == Approx(200));
    CHECK(mod.motor_shaft_power == Approx(200.507050278));
    CHECK(mod.mover_shaft_power == Approx(192.468232632));
    CHECK(mod.motor_efficiency * 100 == Approx(95.6211069257));
    CHECK(mod.motor_power_factor * 100 == Approx(86.7354953183));
    CHECK(mod.motor_current == Approx(226.3599309627));
    CHECK(mod.motor_power == Approx(156.4281376282));
    CHECK(mod.annual_energy == Approx(1370.3104856228));
    CHECK(mod.annual_cost * 1000.0 == Approx(82218.6291373691));
    CHECK(mod.drive_efficiency == Approx(mod.mover_shaft_power / mod.motor_shaft_power));

}

TEST_CASE("pump_result notched V-belt drive", "[pump_result]") {
    double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
    double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
    double specified_efficiency = 1.0;

    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::N_V_BELT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex  = pumpResult.calculateExisting();
    CHECK(ex.motor_power == Approx(150.0));

    auto const& mod = pumpResult.calculateModified();
    CHECK(mod.pump_efficiency * 100 == Approx(62.3));
    CHECK(mod.motor_rated_power == Approx(200));
    CHECK(mod.motor_shaft_power == Approx(198.2102452363));
    CHECK(mod.mover_shaft_power == Approx(192.468232632));
    CHECK(mod.motor_efficiency * 100 == Approx(95.6417064886));
    CHECK(mod.motor_power_factor * 100 == Approx(86.6915209945));
    CHECK(mod.motor_current == Approx(223.8322217984));
    CHECK(mod.motor_power == Approx(154.6029182589));
    CHECK(mod.annual_energy == Approx(1354.3215639476));
    CHECK(mod.annual_cost * 1000.0 == Approx(81259.2938368578));

}

TEST_CASE("pump_result synchronous-belt drive", "[pump_result]") {
    double pumpEfficiency = 0.623, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
    double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
    double motor_rated_fla = 225.8, margin = 0, operating_hours = 8760, cost_kw_hour = 0.06, flow_rate = 1000;
    double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
    double specified_efficiency = 1.0;

    Pump::Style                 style1(Pump::Style::END_SUCTION_ANSI_API);
    Motor::Drive                drive1(Motor::Drive::S_BELT_DRIVE);
    Pump::SpecificSpeed         fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
    Motor::LineFrequency        lineFrequency(Motor::LineFrequency::FREQ60);
    Motor::EfficiencyClass      efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
    Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

    Pump::Input pump(style1, pumpEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages,
                     fixed_speed, specified_efficiency);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage,
                motor_rated_fla, margin);
    Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current,
                       motor_field_voltage);
    PumpResultHarness pumpResult(pump, motor, fd, operating_hours, cost_kw_hour);

    auto const& ex  = pumpResult.calculateExisting();
    CHECK(ex.motor_power == Approx(150.0));

    auto const& mod = pumpResult.calculateModified();
    CHECK(mod.motor_shaft_power == Approx(194.767));
    CHECK(mod.mover_shaft_power == Approx(192.468232632));
    CHECK(mod.motor_power == Approx(151.8722277599));
}
