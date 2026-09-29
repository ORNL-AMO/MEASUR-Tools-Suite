#include "catch.hpp"

#include "compressedAir/air_system_capacity.h"

using namespace Catch;

TEST_CASE("AirSystemCapacity calculates total pipe volume and receiver capacity", "[CompressedAir][AirSystemCapacity]") {
    const auto output = air_system_capacity::calculate({
        pipe_data::PipeData(3000, 2000, 1000, 200, 100, 500, 0, 300, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        {400, 500, 660, 1060}
    });

    CHECK(output.total_pipe_volume == Approx(138.63));
    CHECK(output.total_receiver_volume == Approx(350.2432360737));
    CHECK(output.total_capacity_of_compressed_air_system == Approx(488.8732360737));
}

TEST_CASE("AirSystemCapacity includes additional pipe and receiver volumes", "[CompressedAir][AirSystemCapacity]") {
    const auto output = air_system_capacity::calculate({
        pipe_data::PipeData(3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        {600, 1500, 660, 1060}
    });

    CHECK(output.total_pipe_volume == Approx(155.28));
    CHECK(output.total_receiver_volume == Approx(510.6599854205));
    CHECK(output.total_capacity_of_compressed_air_system == Approx(665.9399854205));

    CHECK(output.pipe_lengths.oneHalf == Approx(6.3));
    CHECK(output.pipe_lengths.threeFourths == Approx(7.4));
    CHECK(output.pipe_lengths.one == Approx(6));
    CHECK(output.pipe_lengths.oneAndOneFourth == Approx(2.08));
    CHECK(output.pipe_lengths.oneAndOneHalf == Approx(1.41));
    CHECK(output.pipe_lengths.two == Approx(11.65));
    CHECK(output.pipe_lengths.twoAndOneHalf == Approx(16.65));
    CHECK(output.pipe_lengths.three == Approx(15.39));
    CHECK(output.pipe_lengths.threeAndOneHalf == Approx(0));
    CHECK(output.pipe_lengths.four == Approx(88.4));
    CHECK(output.receiver_capacities.at(0) == Approx(80.2083746734));
    CHECK(output.receiver_capacities.at(1) == Approx(200.5209366834));
    CHECK(output.receiver_capacities.at(3) == Approx(141.701461923));
}
