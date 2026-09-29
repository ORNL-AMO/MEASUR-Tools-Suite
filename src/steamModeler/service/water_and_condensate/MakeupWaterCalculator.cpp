#include "steamModeler/service/water_and_condensate/MakeupWaterCalculator.h"

#include <steamModeler/SteamProperties.h>
#include "steamModeler/util/SteamModelerLogger.h"

SteamSystemModelerTool::SteamPropertiesOutput
MakeupWaterCalculator::calc(const OperationsInput& operationsInput) const {
    SM_LOG("MakeupWaterCalculator::calc: calculating makeupWater");
    const double                                 pressure      = .101325; // atmospheric pressure
    const SteamProperties::ThermodynamicQuantity quantity      = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
    const double                                 quantityValue = operationsInput.getMakeUpWaterTemperature();

    SteamProperties makeupWaterProperties = {pressure, quantity, quantityValue};

    return makeupWaterProperties.calculate();
}
