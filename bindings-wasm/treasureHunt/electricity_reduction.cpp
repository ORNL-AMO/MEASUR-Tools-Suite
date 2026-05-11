#include <emscripten/bind.h>

#include "treasureHunt/electricity_reduction.h"

using namespace emscripten;
using namespace electricity_reduction;

EMSCRIPTEN_BINDINGS(electricityReduction_module) {
    // Bind measurement method data structs
    value_object<MultimeterData>("MultimeterData")
        .field("numberOfPhases", &MultimeterData::number_of_phases)
        .field("supplyVoltage", &MultimeterData::supply_voltage)
        .field("averageCurrent", &MultimeterData::average_current)
        .field("powerFactor", &MultimeterData::power_factor);

    value_object<NameplateData>("NameplateData")
        .field("ratedMotorPower", &NameplateData::rated_motor_power)
        .field("variableSpeedMotor", &NameplateData::variable_speed_motor)
        .field("operationalFrequency", &NameplateData::operational_frequency)
        .field("lineFrequency", &NameplateData::line_frequency)
        .field("motorAndDriveEfficiency", &NameplateData::motor_and_drive_efficiency)
        .field("loadFactor", &NameplateData::load_factor);

    value_object<PowerMeterData>("PowerMeterData")
        .field("power", &PowerMeterData::power);

    value_object<ElectricityOtherMethodData>("ElectricityOtherMethodData")
        .field("energy", &ElectricityOtherMethodData::energy);

    enum_<ElectricityReductionMeasurementMethod>("ElectricityReductionMeasurementMethod")
        .value("Multimeter", ElectricityReductionMeasurementMethod::Multimeter)
        .value("Nameplate", ElectricityReductionMeasurementMethod::Nameplate)
        .value("PowerMeter", ElectricityReductionMeasurementMethod::PowerMeter)
        .value("Other", ElectricityReductionMeasurementMethod::Other);

    value_object<ElectricityReductionInput>("ElectricityReductionInput")
        .field("operatingHours", &ElectricityReductionInput::operating_hours)
        .field("electricityCost", &ElectricityReductionInput::electricity_cost)
        .field("measurementMethod", &ElectricityReductionInput::measurement_method)
        .field("multimeterData", &ElectricityReductionInput::multimeter_data)
        .field("nameplateData", &ElectricityReductionInput::nameplate_data)
        .field("powerMeterData", &ElectricityReductionInput::power_meter_data)
        .field("otherMethodData", &ElectricityReductionInput::other_method_data)
        .field("units", &ElectricityReductionInput::units);

    register_vector<ElectricityReductionInput>("ElectricityReductionInputV");

    value_object<ElectricityReductionOutput>("ElectricityReductionOutput")
        .field("energyUse", &ElectricityReductionOutput::energy_use)
        .field("energyCost", &ElectricityReductionOutput::energy_cost)
        .field("power", &ElectricityReductionOutput::power);

    // electricityReduction(input_vec: ElectricityReductionInputV) -> ElectricityReductionOutput
    //   input_vec: vector of ElectricityReductionInput structs, one per measure
    //   returns: ElectricityReductionOutput with total energy use, cost, and power
    function("electricityReduction", &electricityReduction);

    // multimeterReduction(data: MultimeterData, operating_hours: int, electricity_cost: double, units: int) -> ElectricityReductionOutput
    //   data: MultimeterData struct
    //   operating_hours: number of annual operating hours
    //   electricity_cost: cost per kWh
    //   units: quantity multiplier
    //   returns: ElectricityReductionOutput struct
    function("multimeterReduction", &multimeterReduction);

    // nameplateReduction(data: NameplateData, operating_hours: int, electricity_cost: double, units: int) -> ElectricityReductionOutput
    //   data: NameplateData struct
    //   operating_hours: number of annual operating hours
    //   electricity_cost: cost per kWh
    //   units: quantity multiplier
    //   returns: ElectricityReductionOutput struct
    function("nameplateReduction", &nameplateReduction);

    // powerMeterReduction(data: PowerMeterData, operating_hours: int, electricity_cost: double, units: int) -> ElectricityReductionOutput
    //   data: PowerMeterData struct
    //   operating_hours: number of annual operating hours
    //   electricity_cost: cost per kWh
    //   units: quantity multiplier
    //   returns: ElectricityReductionOutput struct
    function("powerMeterReduction", &powerMeterReduction);

    // otherReduction(data: ElectricityOtherMethodData, electricity_cost: double) -> ElectricityReductionOutput
    //   data: ElectricityOtherMethodData struct
    //   electricity_cost: cost per kWh
    //   returns: ElectricityReductionOutput struct
    function("electricityOtherReduction", &otherReduction);
}
