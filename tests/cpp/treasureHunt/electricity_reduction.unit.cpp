#include "treasureHunt/electricity_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace electricity_reduction;

TEST_CASE("Electricity Reduction Multimeter Reading - 3 Phases", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::Multimeter,
        MultimeterData{3, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        1}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(407045.796185));
    CHECK(output.energy_cost == Approx(48845.495542));
    CHECK(output.power == Approx(47.111781));
}

TEST_CASE("Electricity Reduction Multimeter Reading - 1 Phase", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::Multimeter,
        MultimeterData{1, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        1}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(235008));
    CHECK(output.energy_cost == Approx(28200.96));
    CHECK(output.power == Approx(27.2));
}

TEST_CASE("Electricity Reduction Nameplate Data", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::Nameplate,
        MultimeterData{1, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        1}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(6950.9206));
    CHECK(output.energy_cost == Approx(834.11047));
    CHECK(output.power == Approx(0.804505));
}

TEST_CASE("Electricity Reduction Nameplate Data - Multiple Units", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::Nameplate,
        MultimeterData{1, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        2}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(13901.841605));
    CHECK(output.energy_cost == Approx(1668.220993));
    CHECK(output.power == Approx(0.804505));
}

TEST_CASE("Electricity Reduction Power Meter Method Test", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::PowerMeter,
        MultimeterData{3, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        2}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(864000));
    CHECK(output.energy_cost == Approx(103680));
    CHECK(output.power == Approx(50));
}

TEST_CASE("Electricity Reduction Other Method Test", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {ElectricityReductionInput{
        8640,
        0.12,
        ElectricityReductionMeasurementMethod::Other,
        MultimeterData{3, 800, 40, 0.85},
        NameplateData{100, false, 55, 60, 100, 1},
        PowerMeterData{50},
        ElectricityOtherMethodData{432000},
        2}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(432000));
    CHECK(output.energy_cost == Approx(51840));
    CHECK(output.power == Approx(0));
}

TEST_CASE("Electricity Reduction Combination", "[ElectricityReduction][util]") {
    std::vector<ElectricityReductionInput> input_vec = {
        // Multimeter method - 3 phase
        ElectricityReductionInput{8640, 0.12, ElectricityReductionMeasurementMethod::Multimeter,
                                  MultimeterData{3, 800, 40, 0.85}, NameplateData{100, false, 55, 60, 100, 1},
                                  PowerMeterData{50}, ElectricityOtherMethodData{432000}, 1},
        // Multimeter method - 1 phase
        ElectricityReductionInput{8640, 0.12, ElectricityReductionMeasurementMethod::Multimeter,
                                  MultimeterData{1, 800, 40, 0.85}, NameplateData{100, false, 55, 60, 100, 1},
                                  PowerMeterData{50}, ElectricityOtherMethodData{432000}, 1},
        // Nameplate data
        ElectricityReductionInput{8640, 0.12, ElectricityReductionMeasurementMethod::Nameplate,
                                  MultimeterData{1, 800, 40, 0.85}, NameplateData{100, false, 55, 60, 100, 1},
                                  PowerMeterData{50}, ElectricityOtherMethodData{432000}, 1},
        // Power meter method
        ElectricityReductionInput{8640, 0.12, ElectricityReductionMeasurementMethod::PowerMeter,
                                  MultimeterData{3, 800, 40, 0.85}, NameplateData{100, false, 55, 60, 100, 1},
                                  PowerMeterData{50}, ElectricityOtherMethodData{432000}, 2},
        // Other method
        ElectricityReductionInput{8640, 0.12, ElectricityReductionMeasurementMethod::Other,
                                  MultimeterData{3, 800, 40, 0.85}, NameplateData{100, false, 55, 60, 100, 1},
                                  PowerMeterData{50}, ElectricityOtherMethodData{432000}, 2}};

    ElectricityReductionOutput output = electricityReduction(input_vec);

    CHECK(output.energy_use == Approx(1945004.716785));
    CHECK(output.energy_cost == Approx(233400.566012));
    CHECK(output.power == Approx(125.116287));
}
