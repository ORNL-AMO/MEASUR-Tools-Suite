#include <emscripten/bind.h>

#include "compressedAir/leak_survey/bag_method.h"

using namespace emscripten;
using namespace bag_method;

EMSCRIPTEN_BINDINGS(bag_method) {
    // ---- Bag Method ----
    // calculateBagMethod(BagMethodInput) -> BagMethodResult
    //   operatingTime  [hr]   - annual system operating time
    //   bagFillTime    [s]    - time for the measurement bag to fill with leaked air
    //   bagVolume      [ft³]  - pre-measured volume of the measurement bag
    //   numberOfUnits  [-]    - number of leak points measured simultaneously
    //   -> flowRate          [scfm]  - compressed air leak flow rate
    //   -> annualConsumption [kscf]  - estimated annual air loss from the leak
    value_object<Input>("BagMethodInput")
        .field("operatingTime", &Input::operating_time)
        .field("bagFillTime", &Input::bag_fill_time)
        .field("bagVolume", &Input::bag_volume);

    value_object<Result>("BagMethodResult")
        .field("flowRate", &Result::flow_rate)
        .field("annualConsumption", &Result::annual_consumption);

    function("calculateBagMethod", &calculate);
}
