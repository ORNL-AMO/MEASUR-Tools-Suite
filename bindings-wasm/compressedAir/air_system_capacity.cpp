#include <vector>

#include <emscripten/bind.h>

#include "compressedAir/air_system_capacity.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(air_system_capacity) {
    value_object<air_system_capacity::Input>("AirSystemCapacityInput")
        .field("pipeLengths", &air_system_capacity::Input::pipe_lengths)
        .field("receivers", &air_system_capacity::Input::receivers);

    value_object<air_system_capacity::Output>("AirSystemCapacityOutput")
        .field("totalPipeVolume", &air_system_capacity::Output::total_pipe_volume)
        .field("totalReceiverVolume", &air_system_capacity::Output::total_receiver_volume)
        .field("totalCapacityOfCompressedAirSystem",
               &air_system_capacity::Output::total_capacity_of_compressed_air_system)
        .field("receiverCapacities", &air_system_capacity::Output::receiver_capacities)
        .field("pipeLengths", &air_system_capacity::Output::pipe_lengths);

    function("calculateAirSystemCapacity", &air_system_capacity::calculate);
}
