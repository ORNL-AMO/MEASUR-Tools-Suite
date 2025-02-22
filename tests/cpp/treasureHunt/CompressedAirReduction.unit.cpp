#include <catch.hpp>
#include "treasureHunt/CompressedAirReduction.h"

TEST_CASE("Compressed Air Reduction Flow Meter Method", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 0, 0.12, 0,
                                    CompressedAirFlowMeterMethodData(200),
                                    BagMethodData(10, 5, 30),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(1.428, 1.38233),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.consumption == Approx(103680000));
    CHECK(testOutput.flowRate == Approx(200.0));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.energyUse == Approx(0.0));
    CHECK(testOutput.energyCost == Approx(12441600.0));
}

TEST_CASE("Compressed Air Reduction Flow Meter Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 0,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(10, 5, 30),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(0.8, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(276480000));
    CHECK(testOutput.energyCost == Approx(33177600));
    CHECK(testOutput.flowRate == Approx(200000.0));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.consumption == Approx(103680000000.0));
}

TEST_CASE("Compressed Air Reduction Bag Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 1,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(0.40, 0.16),
                                    2)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(9424.779607694));
    CHECK(testOutput.energyCost == Approx(1130.9733552923));
    CHECK(testOutput.flowRate == Approx(3.408846));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.consumption == Approx(3534291.73528));
}

TEST_CASE("Compressed Air Reduction Orifice Pressure Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 2,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(2458.6094592));
    CHECK(testOutput.energyCost == Approx(295.033135104));
    CHECK(testOutput.flowRate == Approx(1.778508));
    CHECK(testOutput.singleNozzleFlowRate == Approx(1.778508));
    CHECK(testOutput.consumption == Approx(921978.5471999));
}

TEST_CASE("Compressed Air Reduction Orifice Pressure Method Multiple Nozzles", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 2,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(2, 4, 50),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(0.40, 0.16),
                                    3)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.flowRate == Approx(363.9248));
    CHECK(testOutput.singleNozzleFlowRate == Approx(90.9812));
    CHECK(testOutput.consumption == Approx(188658616.32));
    CHECK(testOutput.energyUse == Approx(503089.64352));
    CHECK(testOutput.energyCost == Approx(60370.7572224));
}

TEST_CASE("Compressed Air Reduction Other Method", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 3,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(2, 4, 50),
                                    CompressedAirOtherMethodData(200000),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.consumption == Approx(200000.00));
    CHECK(testOutput.energyUse == Approx(533.33333333));
    CHECK(testOutput.energyCost == Approx(64.0));
}