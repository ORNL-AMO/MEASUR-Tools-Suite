#include <emscripten/bind.h>

#include "compressedAir/receiver_tank.h"

using namespace emscripten;
using namespace receiver_tank;

EMSCRIPTEN_BINDINGS(receiver_tank) {
    // ---- Usable Capacity ----
    // calculateReceiverTankUsableCapacity(ReceiverTankUsableCapacityInput) -> ReceiverTankUsableCapacityResult
    //   tankSize       [gal]   - tank volume
    //   airPressureIn  [psia]  - charging (inlet) pressure
    //   airPressureOut [psia]  - cut-out (outlet) pressure
    //   -> usableCapacity [scf]
    value_object<UsableCapacityInput>("ReceiverTankUsableCapacityInput")
        .field("tankSize", &UsableCapacityInput::tank_size)
        .field("airPressureIn", &UsableCapacityInput::air_pressure_in)
        .field("airPressureOut", &UsableCapacityInput::air_pressure_out);

    value_object<UsableCapacityResult>("ReceiverTankUsableCapacityResult")
        .field("usableCapacity", &UsableCapacityResult::usable_capacity);

    function("calculateReceiverTankUsableCapacity", &calculateUsableCapacity);

    // ---- General Method ----
    // calculateReceiverTankGeneralSize(ReceiverTankGeneralInput) -> ReceiverTankSizeResult
    //   airDemand              [ft³]  - air demand drawn from the tank
    //   allowablePressureDrop  [psi]  - tolerable pressure drop
    //   atmosphericPressure    [psia] - local atmospheric pressure (default: 14.7)
    //   -> tankSize [gal]
    value_object<GeneralInput>("ReceiverTankGeneralInput")
        .field("airDemand", &GeneralInput::air_demand)
        .field("allowablePressureDrop", &GeneralInput::allowable_pressure_drop)
        .field("atmosphericPressure", &GeneralInput::atmospheric_pressure);

    value_object<SizeResult>("ReceiverTankSizeResult")
        .field("tankSize", &SizeResult::tank_size);

    function("calculateReceiverTankGeneralSize", &calculateGeneralSize);

    // ---- Dedicated Storage Method ----
    // calculateReceiverTankDedicatedStorageSize(ReceiverTankDedicatedStorageInput) -> ReceiverTankSizeResult
    //   lengthOfDemand       [min]   - duration of the air demand event
    //   airFlowRequirement   [cfm]   - required air flow during the event
    //   atmosphericPressure  [psia]  - local atmospheric pressure (default: 14.7)
    //   initialTankPressure  [psia]  - tank pressure before releasing air
    //   finalTankPressure    [psia]  - tank pressure after releasing air
    //   -> tankSize [gal]
    value_object<DedicatedStorageInput>("ReceiverTankDedicatedStorageInput")
        .field("lengthOfDemand", &DedicatedStorageInput::length_of_demand)
        .field("airFlowRequirement", &DedicatedStorageInput::air_flow_requirement)
        .field("atmosphericPressure", &DedicatedStorageInput::atmospheric_pressure)
        .field("initialTankPressure", &DedicatedStorageInput::initial_tank_pressure)
        .field("finalTankPressure", &DedicatedStorageInput::final_tank_pressure);

    function("calculateReceiverTankDedicatedStorageSize", &calculateDedicatedStorageSize);

    // ---- Metered Storage Method ----
    // calculateReceiverTankMeteredStorageSize(ReceiverTankMeteredStorageInput) -> ReceiverTankMeteredStorageResult
    //   lengthOfDemand       [min]   - duration of the air demand event
    //   airFlowRequirement   [cfm]   - required air flow during the event
    //   atmosphericPressure  [psia]  - local atmospheric pressure (default: 14.7)
    //   initialTankPressure  [psia]  - tank pressure before releasing air
    //   finalTankPressure    [psia]  - tank pressure after releasing air
    //   meteredFlowControl   [cfm]   - metering valve (needle valve) flow rate
    //   -> tankSize [gal], refillTime [sec]
    value_object<MeteredStorageInput>("ReceiverTankMeteredStorageInput")
        .field("lengthOfDemand", &MeteredStorageInput::length_of_demand)
        .field("airFlowRequirement", &MeteredStorageInput::air_flow_requirement)
        .field("atmosphericPressure", &MeteredStorageInput::atmospheric_pressure)
        .field("initialTankPressure", &MeteredStorageInput::initial_tank_pressure)
        .field("finalTankPressure", &MeteredStorageInput::final_tank_pressure)
        .field("meteredFlowControl", &MeteredStorageInput::metered_flow_control);

    value_object<MeteredStorageResult>("ReceiverTankMeteredStorageResult")
        .field("tankSize", &MeteredStorageResult::tank_size)
        .field("refillTime", &MeteredStorageResult::refill_time);

    function("calculateReceiverTankMeteredStorageSize", &calculateMeteredStorageSize);

    // ---- Bridging Compressor Reaction Delay Method ----
    // calculateReceiverTankBridgingSize(ReceiverTankBridgingInput) -> ReceiverTankSizeResult
    //   distanceToCompressorRoom  [ft]    - distance from demand event to compressor room
    //   speedOfAir                [ft/s]  - speed of compressed air in distribution piping
    //   atmosphericPressure       [psia]  - local atmospheric pressure (default: 14.7)
    //   airDemandCfm              [cfm]   - air demand at the event location
    //   allowablePressureDrop     [psi]   - tolerable pressure drop at the event
    //   -> tankSize [gal]
    value_object<BridgingInput>("ReceiverTankBridgingInput")
        .field("distanceToCompressorRoom", &BridgingInput::distance_to_compressor_room)
        .field("speedOfAir", &BridgingInput::speed_of_air)
        .field("atmosphericPressure", &BridgingInput::atmospheric_pressure)
        .field("airDemandCfm", &BridgingInput::air_demand_cfm)
        .field("allowablePressureDrop", &BridgingInput::allowable_pressure_drop);

    function("calculateReceiverTankBridgingSize", &calculateBridgingSize);
}
