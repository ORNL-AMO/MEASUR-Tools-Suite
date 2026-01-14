#include <emscripten/bind.h>
#include "processHeat/losses/opening_heat_loss.h"

using namespace emscripten;
using namespace opening_heat_loss;

EMSCRIPTEN_BINDINGS(opening_heat_loss) {
    // Parameters for openingTotalHeatLossQuad:
    //   emissivity (unitless)
    //   length (in)
    //   width (in)
    //   ambientTemperature (°F)
    //   insideTemperature (°F)
    //   percentTimeOpen (%)
    //   viewFactor (unitless)
    function("openingTotalHeatLossQuad", &totalHeatLossQuad);

    // Parameters for openingTotalHeatLossCircular:
    //   emissivity (unitless)
    //   diameter (in)
    //   ambientTemperature (°F)
    //   insideTemperature (°F)
    //   percentTimeOpen (%)
    //   viewFactor (unitless)
    function("openingTotalHeatLossCircular", &totalHeatLossCircular);

    // Parameters for calculateViewFactorCircular:
    //   thickness (in)
    //   diameter (in)
    function("calculateViewFactorCircular", &calculateViewFactorCircular);

    // Parameters for calculateViewFactorQuad:
    //   thickness (in)
    //   length (in)
    //   height (in)
    function("calculateViewFactorQuad", &calculateViewFactorQuad);
}
