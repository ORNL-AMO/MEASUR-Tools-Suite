#include "catch.hpp"

#include "compressedAir/pipe_data.h"

using namespace Catch;

TEST_CASE("PipeData converts pipe lengths to contained volume", "[CompressedAir][PipeData]") {
    const pipe_data::PipeData results(3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0);

    CHECK(results.oneHalf == Approx(6.3));
    CHECK(results.threeFourths == Approx(7.4));
    CHECK(results.one == Approx(6));
    CHECK(results.oneAndOneFourth == Approx(2.08));
    CHECK(results.oneAndOneHalf == Approx(1.41));
    CHECK(results.two == Approx(11.65));
    CHECK(results.twoAndOneHalf == Approx(16.65));
    CHECK(results.three == Approx(15.39));
    CHECK(results.threeAndOneHalf == Approx(0));
    CHECK(results.four == Approx(88.4));
    CHECK(results.five == Approx(0));
    CHECK(results.six == Approx(0));
    CHECK(results.eight == Approx(0));
    CHECK(results.ten == Approx(0));
    CHECK(results.twelve == Approx(0));
    CHECK(results.fourteen == Approx(0));
    CHECK(results.sixteen == Approx(0));
    CHECK(results.eighteen == Approx(0));
    CHECK(results.twenty == Approx(0));
    CHECK(results.twentyFour == Approx(0));
    CHECK(results.totalPipeVolume == Approx(155.28));
}

TEST_CASE("PipeData applies velocity function to nominal pipe internal areas", "[CompressedAir][PipeData]") {
    const pipe_data::PipeData results([](const double pipe_area) { return pipe_area; });

    CHECK(results.oneHalf == Approx(0.3));
    CHECK(results.threeFourths == Approx(0.53));
    CHECK(results.one == Approx(0.86));
    CHECK(results.oneAndOneFourth == Approx(1.5));
    CHECK(results.oneAndOneHalf == Approx(2.04));
    CHECK(results.two == Approx(3.36));
    CHECK(results.twoAndOneHalf == Approx(4.79));
    CHECK(results.three == Approx(7.39));
    CHECK(results.threeAndOneHalf == Approx(9.89));
    CHECK(results.four == Approx(12.73));
    CHECK(results.five == Approx(20));
    CHECK(results.six == Approx(28.89));
    CHECK(results.eight == Approx(50.02));
    CHECK(results.ten == Approx(78.85));
    CHECK(results.twelve == Approx(111.9));
    CHECK(results.fourteen == Approx(135.3));
    CHECK(results.sixteen == Approx(176.7));
    CHECK(results.eighteen == Approx(224));
    CHECK(results.twenty == Approx(278));
    CHECK(results.twentyFour == Approx(402.10));
    CHECK(results.totalPipeVolume == Approx(0));
}
