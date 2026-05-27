#include "catch.hpp"

#include "compressedAir/AirSystemCapacity.h"
#include "compressedAir/AirVelocity.h"
#include "compressedAir/BagMethod.h"
#include "compressedAir/DecibelsMethod.h"
#include "compressedAir/EstimateMethod.h"
#include "compressedAir/OrificeMethod.h"
#include "compressedAir/PipeData.h"
#include "compressedAir/PipeSizing.h"

using namespace Catch;

TEST_CASE("Compressor Air System Capacity", "[CompressedAir][AirSystemCapacity]") {
    auto output = AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 0, 300, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {400, 500, 660, 1060})
                      .calculate();
    CHECK(output.totalPipeVolume == Approx(138.63));
    CHECK(output.totalReceiverVol == Approx(350.2432360737));
    CHECK(output.totalCapacityOfCompressedAirSystem == Approx(488.8732360737));

    auto output2 = AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {400, 500, 660, 1060})
                       .calculate();
    CHECK(output2.totalPipeVolume == Approx(155.28));
    CHECK(output2.totalReceiverVol == Approx(350.2432360737));
    CHECK(output2.totalCapacityOfCompressedAirSystem == Approx(505.5232360737));

    auto output3 = AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {600, 1500, 660, 1060})
                       .calculate();
    CHECK(output3.totalPipeVolume == Approx(155.28));
    CHECK(output3.totalReceiverVol == Approx(510.6599854205));
    CHECK(output3.totalCapacityOfCompressedAirSystem == Approx(665.9399854205));

    CHECK(output3.pipeLengths.oneHalf == Approx(6.3));
    CHECK(output3.pipeLengths.threeFourths == Approx(7.4));
    CHECK(output3.pipeLengths.one == Approx(6));
    CHECK(output3.pipeLengths.oneAndOneFourth == Approx(2.08));
    CHECK(output3.pipeLengths.oneAndOneHalf == Approx(1.41));
    CHECK(output3.pipeLengths.two == Approx(11.65));
    CHECK(output3.pipeLengths.twoAndOneHalf == Approx(16.65));
    CHECK(output3.pipeLengths.three == Approx(15.39));
    CHECK(output3.pipeLengths.threeAndOneHalf == Approx(0));
    CHECK(output3.pipeLengths.four == Approx(88.4));
    CHECK(output3.pipeLengths.five == Approx(0));
    CHECK(output3.pipeLengths.six == Approx(0));
    CHECK(output3.pipeLengths.eight == Approx(0));
    CHECK(output3.pipeLengths.ten == Approx(0));
    CHECK(output3.pipeLengths.twelve == Approx(0));
    CHECK(output3.pipeLengths.fourteen == Approx(0));
    CHECK(output3.pipeLengths.sixteen == Approx(0));
    CHECK(output3.pipeLengths.eighteen == Approx(0));
    CHECK(output3.pipeLengths.twenty == Approx(0));
    CHECK(output3.pipeLengths.twentyFour == Approx(0));
    CHECK(output3.receiverCapacities.at(0) == Approx(80.2083746734));
    CHECK(output3.receiverCapacities.at(1) == Approx(200.5209366834));
    CHECK(output3.receiverCapacities.at(3) == Approx(141.701461923));
}

TEST_CASE("Compressor Air Velocity", "[CompressedAir][AirVelocity]") {
    auto const compare = [](PipeData const& results, std::vector<double> const& expected) {
        CHECK(expected.at(0) == Approx(results.oneHalf));
        CHECK(expected.at(1) == Approx(results.threeFourths));
        CHECK(expected.at(2) == Approx(results.one));
        CHECK(expected.at(3) == Approx(results.oneAndOneFourth));
        CHECK(expected.at(4) == Approx(results.oneAndOneHalf));
        CHECK(expected.at(5) == Approx(results.two));
        CHECK(expected.at(6) == Approx(results.twoAndOneHalf));
        CHECK(expected.at(7) == Approx(results.three));
        CHECK(expected.at(8) == Approx(results.threeAndOneHalf));
        CHECK(expected.at(9) == Approx(results.four));
        CHECK(expected.at(10) == Approx(results.five));
        CHECK(expected.at(11) == Approx(results.six));
        CHECK(expected.at(12) == Approx(results.eight));
        CHECK(expected.at(13) == Approx(results.ten));
        CHECK(expected.at(14) == Approx(results.twelve));
        CHECK(expected.at(15) == Approx(results.fourteen));
        CHECK(expected.at(16) == Approx(results.sixteen));
        CHECK(expected.at(17) == Approx(results.eighteen));
        CHECK(expected.at(18) == Approx(results.twenty));
        CHECK(expected.at(19) == Approx(results.twentyFour));
    };

    compare(AirVelocity(1800, 100, 14.7).calculate(),
            {1845.5100261552, 1044.628316691, 643.7825672634, 369.102005231, 271.3985332581,
             164.7776809,     115.585179,     74.9192162174,  55.9810928055, 43.4919880476,
             27.6826503923,   19.164174726,   11.0686327038,  7.0215980703,  4.9477480594,
             4.0920399693,    3.1332937626,   2.4716652136,   1.9915575822,  1.3769037748});
    compare(AirVelocity(1300, 80, 14.7).calculate(),
            {1614.361140443, 913.789324779, 563.149235038, 322.872228,    237.406050,   144.139387539, 101.108213388,
             65.53563493,    48.969498699,  38.044645886,  24.2154171067, 16.763874771, 9.6822939251,  6.1421476491,
             4.3280459529,   3.5795147238,  2.7408508327,  2.1620908131,  1.7421163386, 1.2044475059});
}

TEST_CASE("Compressor Pipe Sizing", "[CompressedAir][PipeSizing]") {
    auto const compare = [](PipeSizing::Output const& results, PipeSizing::Output const& expected) {
        CHECK(expected.crossSectionalArea == Approx(results.crossSectionalArea));
        CHECK(expected.pipeDiameter == Approx(results.pipeDiameter));
    };

    compare(PipeSizing(1000, 90, 25, 14.5).calculate(), PipeSizing::Output(13.3205741627, 4.132512454));
    compare(PipeSizing(1400, 90, 25, 14.5).calculate(), PipeSizing::Output(18.648803827, 4.8896546766));
    compare(PipeSizing(1400, 110, 25, 14.5).calculate(), PipeSizing::Output(15.6530120482, 4.4797281351));
    compare(PipeSizing(1400, 110, 30, 14.5).calculate(), PipeSizing::Output(13.0441767068, 4.0894135851));
    compare(PipeSizing(1400, 110, 30, 11.5).calculate(), PipeSizing::Output(10.6008230453, 3.6865700558));
}

TEST_CASE("Bag Method", "[CompressedAir][BagMethod]") {
    auto const compare = [](BagMethod::Output const& results, BagMethod::Output const& expected) {
        CHECK(expected.flowRate == Approx(results.flowRate));
        CHECK(expected.annualConsumption == Approx(results.annualConsumption));
    };

    compare(BagMethod(8760, 50, 45, 1).calculate(), BagMethod::Output(54, 28382.4));
    compare(BagMethod(8760, 60, 50, 1).calculate(), BagMethod::Output(50, 26280));
    compare(BagMethod(8760, 120, 50, 1).calculate(), BagMethod::Output(25, 13140));
}

TEST_CASE("Estimate Method", "[CompressedAir][EstimateMethod]") {
    // auto const compare = [](EstimateMethod::Output const & results, EstimateMethod::Output const & expected) {
    // CHECK(expected.annualConsumption == Approx(results.annualConsumption));
    //};
    // compare(EstimateMethod(EstimateMethod::LeakEstimateType::Small, 115200 / 60.0).calculate(),
    // EstimateMethod::Output(5.25)); compare(EstimateMethod(EstimateMethod::LeakEstimateType::Small, 115200
    // / 60.0).calculate(), EstimateMethod::Output(1.092));
    CHECK(EstimateMethod(1280, 0.1).calculate().annualConsumption ==
          Approx(EstimateMethod::Output(7.68).annualConsumption));
    CHECK(EstimateMethod(1280, 1.429).calculate().annualConsumption ==
          Approx(EstimateMethod::Output(109.7472).annualConsumption));
}

TEST_CASE("Decibels Method", "[CompressedAir][DecibelsMethod]") {
    auto const compare = [](DecibelsMethod::Output const& results, DecibelsMethod::Output const& expected) {
        CHECK(expected.leakRateEstimate == Approx(results.leakRateEstimate));
        CHECK(expected.annualConsumption == Approx(results.annualConsumption));
    };

    compare(DecibelsMethod(1280, 130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65).calculate(),
            DecibelsMethod::Output(1.429, 109.7472));
}

TEST_CASE("Orifice Method", "[CompressedAir][OrificeMethod]") {
    auto const compare = [](OrificeMethod::Output const& results, OrificeMethod::Output const& expected) {
        CHECK(expected.standardDensity == Approx(results.standardDensity));
        CHECK(expected.sonicDensity == Approx(results.sonicDensity));
        CHECK(expected.leakVelocity == Approx(results.leakVelocity));
        CHECK(expected.leakRateLBMmin == Approx(results.leakRateLBMmin));
        CHECK(expected.leakRateScfm == Approx(results.leakRateScfm));
        CHECK(expected.leakRateEstimate == Approx(results.leakRateEstimate));
        CHECK(expected.annualConsumption == Approx(results.annualConsumption));
    };

    compare(OrificeMethod(115200 / 60.0, 250.0, 14.7, 1.0, 6.0, 6.2, 4).calculate(),
            OrificeMethod::Output(0.2256917885, 0.0153403857, 707.7792735027, 127.9131698485, 566.7604066752,
                                  2267.0416267007, 261163.1953959255));
}
