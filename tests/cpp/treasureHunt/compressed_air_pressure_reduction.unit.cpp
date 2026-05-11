#include "treasureHunt/compressed_air_pressure_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace compressed_air_pressure_reduction;

TEST_CASE("Compressed Air Pressure Reduction Baseline", "[compressedAirPressureReduction][util]") {
    std::vector<CompressedAirPressureReductionInput> input_vec = {
        CompressedAirPressureReductionInput {true, 8640, 0.005, 500, 150, 0, 0, 0}};

    CompressedAirPressureReductionOutput test_output = compressedAirPressureReduction(input_vec);
    CHECK(test_output.energy_use == Approx(4320000.0));
    CHECK(test_output.energy_cost == Approx(21600.0));
}

TEST_CASE("Compressed Air Pressure Reduction Modification", "[compressedAirPressureReduction][util]") {
    std::vector<CompressedAirPressureReductionInput> input_vec = {
        CompressedAirPressureReductionInput {false, 8760, 0.005, 200, 100, 90, 14.7, 100}};

    CompressedAirPressureReductionOutput test_output = compressedAirPressureReduction(input_vec);
    CHECK(test_output.energy_use == Approx(1650714.710542));
    CHECK(test_output.energy_cost == Approx(8253.57355271));
}

TEST_CASE("Compressed Air Pressure Reduction Baseline List", "[compressedAirPressureReduction][util]") {
    std::vector<CompressedAirPressureReductionInput> input_vec = {
        CompressedAirPressureReductionInput {true, 8640, 0.005, 500, 150, 0, 0, 0},
        CompressedAirPressureReductionInput {true, 8640, 0.005, 250, 150, 0, 0, 0},
        CompressedAirPressureReductionInput {true, 8640, 0.005, 500, 120, 120, 0, 0},
        CompressedAirPressureReductionInput {true, 8640, 0.005, 450, 170, 100, 0, 0}};

    CompressedAirPressureReductionOutput test_output = compressedAirPressureReduction(input_vec);
    CHECK(test_output.energy_use == 14688000.0);
    CHECK(test_output.energy_cost == 73440.0);
}

TEST_CASE("Compressed Air Pressure Reduction Modification List", "[compressedAirPressureReduction][util]") {
    std::vector<CompressedAirPressureReductionInput> input_vec = {
        CompressedAirPressureReductionInput {false, 8760, 0.005, 200, 100, 90, 14.7, 100},
        CompressedAirPressureReductionInput {false, 8760, 0.005, 200, 100, 90, 14.7, 100}};

    CompressedAirPressureReductionOutput test_output = compressedAirPressureReduction(input_vec);

    CHECK(test_output.energy_use == Approx(3301429.421084));
    CHECK(test_output.energy_cost == Approx(16507.14710542));
}
