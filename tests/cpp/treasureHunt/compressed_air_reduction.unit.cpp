#include "treasureHunt/compressed_air_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air_reduction;

TEST_CASE("Compressed Air Reduction Flow Meter Method - Compressed Air Utility", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::CompressedAir,
        0.12,
        MeasurementMethod::FlowMeter,
        FlowMeterMethodData{200},
        BagMethodData{},
        PressureMethodData{},
        OtherMethodData{},
        CompressorElectricityData{},
        1}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.consumption           == Approx(103680000.0));
    CHECK(output.flow_rate             == Approx(200.0));
    CHECK(output.single_nozzle_flow_rate == Approx(0.0));
    CHECK(output.energy_use            == Approx(0.0));
    CHECK(output.energy_cost           == Approx(12441600.0));
}

TEST_CASE("Compressed Air Reduction Flow Meter Method - Electricity Utility", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::Electricity,
        0.12,
        MeasurementMethod::FlowMeter,
        FlowMeterMethodData{200000},
        BagMethodData{},
        PressureMethodData{},
        OtherMethodData{},
        CompressorElectricityData{100, 0.16},
        1}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.energy_use            == Approx(276480000.0));
    CHECK(output.energy_cost           == Approx(33177600.0));
    CHECK(output.flow_rate             == Approx(200000.0));
    CHECK(output.single_nozzle_flow_rate == Approx(0.0));
    CHECK(output.consumption           == Approx(103680000000.0));
}

TEST_CASE("Compressed Air Reduction Bag Method - Electricity Utility", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::Electricity,
        0.12,
        MeasurementMethod::Bag,
        FlowMeterMethodData{},
        BagMethodData{12, 8.68, 2},
        PressureMethodData{},
        OtherMethodData{},
        CompressorElectricityData{100, 0.16},
        2}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.energy_use            == Approx(239984.64));
    CHECK(output.energy_cost           == Approx(28798.1568));
    CHECK(output.flow_rate             == Approx(43.4));
    CHECK(output.single_nozzle_flow_rate == Approx(0.0));
    CHECK(output.consumption           == Approx(89994240.0));
}

TEST_CASE("Compressed Air Reduction Pressure Method - Electricity Utility", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::Electricity,
        0.12,
        MeasurementMethod::Pressure,
        FlowMeterMethodData{},
        BagMethodData{},
        PressureMethodData{0, 1, 80},
        OtherMethodData{},
        CompressorElectricityData{100, 0.16},
        1}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.energy_use            == Approx(2458.6094592));
    CHECK(output.energy_cost           == Approx(295.033135104));
    CHECK(output.flow_rate             == Approx(1.778508));
    CHECK(output.single_nozzle_flow_rate == Approx(1.778508));
    CHECK(output.consumption           == Approx(921978.5471999));
}

TEST_CASE("Compressed Air Reduction Pressure Method - Multiple Nozzles", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::Electricity,
        0.12,
        MeasurementMethod::Pressure,
        FlowMeterMethodData{},
        BagMethodData{},
        PressureMethodData{2, 4, 50},
        OtherMethodData{},
        CompressorElectricityData{100, 0.16},
        3}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.flow_rate             == Approx(363.9248));
    CHECK(output.single_nozzle_flow_rate == Approx(90.9812));
    CHECK(output.consumption           == Approx(188658616.32));
    CHECK(output.energy_use            == Approx(503089.64352));
    CHECK(output.energy_cost           == Approx(60370.7572224));
}

TEST_CASE("Compressed Air Reduction Other Method - Electricity Utility", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {CompressedAirReductionInput{
        8640,
        UtilityType::Electricity,
        0.12,
        MeasurementMethod::Other,
        FlowMeterMethodData{},
        BagMethodData{},
        PressureMethodData{},
        OtherMethodData{200000},
        CompressorElectricityData{100, 0.16},
        1}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.consumption           == Approx(200000.0));
    CHECK(output.energy_use            == Approx(533.33333333));
    CHECK(output.energy_cost           == Approx(64.0));
}

TEST_CASE("Compressed Air Reduction Combination - All Methods", "[CompressedAirReduction][util]") {
    std::vector<CompressedAirReductionInput> input_vec = {
        // Flow meter with electricity
        CompressedAirReductionInput{8640, UtilityType::Electricity, 0.066, MeasurementMethod::FlowMeter,
                                    FlowMeterMethodData{200000}, BagMethodData{}, PressureMethodData{},
                                    OtherMethodData{}, CompressorElectricityData{100, 0.16}, 1},
        // Bag method with electricity
        CompressedAirReductionInput{8640, UtilityType::Electricity, 0.12, MeasurementMethod::Bag,
                                    FlowMeterMethodData{}, BagMethodData{12, 8.68, 1}, PressureMethodData{},
                                    OtherMethodData{}, CompressorElectricityData{100, 0.16}, 1},
        // Pressure method with compressed air utility
        CompressedAirReductionInput{8640, UtilityType::CompressedAir, 0.12, MeasurementMethod::Pressure,
                                    FlowMeterMethodData{}, BagMethodData{}, PressureMethodData{0, 1, 80},
                                    OtherMethodData{}, CompressorElectricityData{100, 0.16}, 1},
        // Other method with electricity
        CompressedAirReductionInput{8640, UtilityType::Electricity, 0.12, MeasurementMethod::Other,
                                    FlowMeterMethodData{}, BagMethodData{}, PressureMethodData{},
                                    OtherMethodData{200000}, CompressorElectricityData{100, 0.16}, 1}};

    CompressedAirReductionOutput output = compressedAirReduction(input_vec);
    CHECK(output.consumption           == Approx(103703620538.55));
    CHECK(output.flow_rate             == Approx(200045.178508));
    CHECK(output.single_nozzle_flow_rate == Approx(1.778508));
    CHECK(output.energy_use            == Approx(276540529.49));
    CHECK(output.energy_cost           == Approx(18365580.96));
}
