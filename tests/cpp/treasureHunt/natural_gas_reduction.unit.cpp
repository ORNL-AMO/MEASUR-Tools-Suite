#include "treasureHunt/natural_gas_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace natural_gas_reduction;

TEST_CASE("Natural Gas Reduction Flow Meter Method", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::FlowMeter,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{true, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{10000}, 120, 200, 100},
                                 WaterMassFlowData{400, 120, 200, 100}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(88.992));
    CHECK(output.energy_cost == Approx(10.67904));
    CHECK(output.heat_flow == Approx(0.0));
    CHECK(output.total_flow == Approx(10.0));
}

TEST_CASE("Natural Gas Reduction Air Mass Flow Nameplate", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::AirMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{true, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(44.78976));
    CHECK(output.energy_cost == Approx(5.37477));
    CHECK(output.heat_flow == Approx(0.002592));
    CHECK(output.total_flow == Approx(60.0));
}

TEST_CASE("Natural Gas Reduction Air Mass Flow Measured", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::AirMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(14929.92));
    CHECK(output.energy_cost == Approx(1791.5904));
    CHECK(output.heat_flow == Approx(0.864));
    CHECK(output.total_flow == Approx(20000.0));
}

TEST_CASE("Natural Gas Reduction Water Mass Flow", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::WaterMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(276480.0));
    CHECK(output.energy_cost == Approx(33177.6));
    CHECK(output.heat_flow == Approx(16.0));
    CHECK(output.total_flow == Approx(800.0));
}

TEST_CASE("Natural Gas Reduction Other/Off Sheet", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::Other,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{2000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(2000.0));
    CHECK(output.energy_cost == Approx(240.0));
    CHECK(output.heat_flow == Approx(0.0));
    CHECK(output.total_flow == Approx(0.0));
}

TEST_CASE("Natural Gas Reduction All Methods", "[NaturalGasReduction][util]") {
    std::vector<NaturalGasReductionInput> input_vec = {
        // flow meter method
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::FlowMeter,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{true, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{10000}, 120, 200, 100},
                                 WaterMassFlowData{400, 120, 200, 100}, 2},
        // air mass flow nameplate
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::AirMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{true, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2},
        // air mass flow measured
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::AirMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2},
        // water mass flow method
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::WaterMassFlow,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{200000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2},
        // other/off sheet method
        NaturalGasReductionInput{8640, 0.12, NaturalGasMeasurementMethod::Other,
                                 FlowMeterMethodData{5}, NaturalGasOtherMethodData{2000},
                                 AirMassFlowData{false, AirMassFlowMeasuredData{50, 200},
                                                 AirMassFlowNameplateData{30}, 120, 200, 1},
                                 WaterMassFlowData{400, 120, 200, 1}, 2}};

    auto output = naturalGasReduction(input_vec);

    CHECK(output.energy_use == Approx(293543.70176));
    CHECK(output.energy_cost == Approx(35225.2442112));
    CHECK(output.heat_flow == Approx(16.866592));
    CHECK(output.total_flow == Approx(20870.0));
}

TEST_CASE("Natural Gas Reduction Flow Meter Method (standalone)", "[NaturalGasReduction][util]") {
    auto output = flowMeterMethodReduction(FlowMeterMethodData{5}, 8640, 0.12, 2);

    CHECK(output.energy_use == Approx(88.992));
    CHECK(output.energy_cost == Approx(10.67904));
    CHECK(output.heat_flow == Approx(0.0));
    CHECK(output.total_flow == Approx(10.0));
}

TEST_CASE("Natural Gas Reduction Air Mass Flow Method (standalone nameplate)", "[NaturalGasReduction][util]") {
    AirMassFlowData air_data{true, AirMassFlowMeasuredData{50, 200}, AirMassFlowNameplateData{30}, 120, 200, 1};
    auto            output = airMassFlowMethodReduction(air_data, 8640, 0.12, 2);

    CHECK(output.energy_use == Approx(44.78976));
    CHECK(output.energy_cost == Approx(5.37477));
    CHECK(output.heat_flow == Approx(0.002592));
    CHECK(output.total_flow == Approx(60.0));
}

TEST_CASE("Natural Gas Reduction Water Mass Flow Method (standalone)", "[NaturalGasReduction][util]") {
    auto output = waterMassFlowMethodReduction(WaterMassFlowData{400, 120, 200, 1}, 8640, 0.12, 2);

    CHECK(output.energy_use == Approx(276480.0));
    CHECK(output.energy_cost == Approx(33177.6));
    CHECK(output.heat_flow == Approx(16.0));
    CHECK(output.total_flow == Approx(800.0));
}

TEST_CASE("Natural Gas Reduction Other Method (standalone)", "[NaturalGasReduction][util]") {
    auto output = otherMethodReduction(NaturalGasOtherMethodData{2000}, 0.12);

    CHECK(output.energy_use == Approx(2000.0));
    CHECK(output.energy_cost == Approx(240.0));
    CHECK(output.heat_flow == Approx(0.0));
    CHECK(output.total_flow == Approx(0.0));
}
