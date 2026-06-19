#include "catch.hpp"

#include "compressedAir/air_velocity.h"

#include <vector>

using namespace Catch;

namespace {

void compare(const pipe_data::PipeData& results, const std::vector<double>& expected) {
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
}

} // namespace

TEST_CASE("AirVelocity calculates velocities for all standard nominal pipe sizes", "[CompressedAir][AirVelocity]") {
    compare(air_velocity::calculate({1800, 100, 14.7}),
            {1845.5100261552, 1044.628316691, 643.7825672634, 369.102005231, 271.3985332581,
             164.7776809,     115.585179,     74.9192162174,  55.9810928055, 43.4919880476,
             27.6826503923,   19.164174726,   11.0686327038,  7.0215980703,  4.9477480594,
             4.0920399693,    3.1332937626,   2.4716652136,   1.9915575822,  1.3769037748});
    compare(air_velocity::calculate({1300, 80, 14.7}),
            {1614.361140443, 913.789324779, 563.149235038, 322.872228,    237.406050,   144.139387539, 101.108213388,
             65.53563493,    48.969498699,  38.044645886,  24.2154171067, 16.763874771, 9.6822939251,  6.1421476491,
             4.3280459529,   3.5795147238,  2.7408508327,  2.1620908131,  1.7421163386, 1.2044475059});
}
