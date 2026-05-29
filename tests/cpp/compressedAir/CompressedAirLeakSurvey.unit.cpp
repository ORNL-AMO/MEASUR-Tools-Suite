#include "compressedAir/CompressedAirLeakSurvey.h"

#include "catch.hpp"

using namespace Catch;

TEST_CASE("Compressed Air Leak Survey Estimate Method and Electricity", "[CompressedAirLeakSurvey][Util]") {
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        8640, 1, 0.12, 0, estimate_method::Input {8640, 0.1},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {8760, 12, 8.68, 1},
        orifice_method::Input {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4},
        compressed_air_utils::CompressorElectricityData {0.40, 0.16}, 1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(138.24));
    CHECK(testOutput.annualTotalElectricityCost == Approx(16.5888));
    CHECK(testOutput.totalFlowRate == Approx(0.1));
    CHECK(testOutput.annualTotalFlowRate == Approx(51840));

    compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        3840, 1, 0.12, 0, estimate_method::Input {3840, 0.1},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {3840, 12, 8.68, 1},
        orifice_method::Input {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4},
        compressed_air_utils::CompressorElectricityData {0.25, 0.16}, 1)};

    compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(61.44));
    CHECK(testOutput.annualTotalElectricityCost == Approx(7.3728));
    CHECK(testOutput.totalFlowRate == Approx(0.1));
    CHECK(testOutput.annualTotalFlowRate == Approx(23040));

    compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        8760, 1, 0.12, 0, estimate_method::Input {8760, 100},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {8760, 12, 8.68, 1},
        orifice_method::Input {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4},
        compressed_air_utils::CompressorElectricityData {0.25, 0.16}, 1)};

    compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(140160.0));
    CHECK(testOutput.annualTotalElectricityCost == Approx(16819.2));
    CHECK(testOutput.totalFlowRate == Approx(100));
    CHECK(testOutput.annualTotalFlowRate == Approx(52560000));
}

TEST_CASE("Compressed Air Leak Survey Decibels Method and Electricity", "[CompressedAirLeakSurvey][Util]") {
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        8640, 1, 0.12, 1, estimate_method::Input {8640, 0.1},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {15, 10, 12, 1},
        orifice_method::Input {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4},
        compressed_air_utils::CompressorElectricityData {0.40, 0.16}, 1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(1975.4496));
    CHECK(testOutput.annualTotalElectricityCost == Approx(237.053952));
    CHECK(testOutput.totalFlowRate == Approx(1.429));
    CHECK(testOutput.annualTotalFlowRate == Approx(740793.6));
}

TEST_CASE("Compressed Air Leak Survey Bag Method and Electricity", "[CompressedAirLeakSurvey][Util]") {
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        8640, 1, 0.12, 2, estimate_method::Input {8640, 0.1},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {15, 10, 12, 1},
        orifice_method::Input {0.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4},
        compressed_air_utils::CompressorElectricityData {0.40, 0.16}, 2)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(0.3456));
    CHECK(testOutput.annualTotalElectricityCost == Approx(0.041472));
    CHECK(testOutput.totalFlowRate == Approx(144.0));
    CHECK(testOutput.annualTotalFlowRate == Approx(129.6));
}

TEST_CASE("Compressed Air Leak Survey Orifice Method and Electricity", "[CompressedAirLeakSurvey][Util]") {
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {CompressedAirLeakSurveyInput(
        8640, 1, 0.12, 3, estimate_method::Input {8640, 0.1},
        DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65), bag_method::Input {15, 10, 12, 1},
        orifice_method::Input {0.0, 550, 14.7, 1.0, .375, 100, 4},
        compressed_air_utils::CompressorElectricityData {0.40, 0.16}, 1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput              = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.annualTotalElectricity == Approx(1790380.8424647334));
    CHECK(testOutput.annualTotalElectricityCost == Approx(214845.701095768));
    CHECK(testOutput.totalFlowRate == Approx(1295.1250307181));
    CHECK(testOutput.annualTotalFlowRate == Approx(671392815.9242750406));
}
