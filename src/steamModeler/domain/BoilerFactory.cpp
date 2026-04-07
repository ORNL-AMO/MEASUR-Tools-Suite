#include "steamModeler/domain/BoilerFactory.h"

Boiler BoilerFactory::make(const HeaderInput& headerInput, const BoilerInput& boilerInput, double massFlow) const {
    double                                 deaeratorPressure    = boilerInput.getDeaeratorPressure();
    double                                 combustionEfficiency = boilerInput.getCombustionEfficiency();
    double                                 blowdownRate         = boilerInput.getBlowdownRate();
    //I think we locked the steam pressure in the high pressure header to the boiler pressure
    double                                 steamPressure        = headerInput.getHighPressureHeader().getPressure();
    SteamProperties::ThermodynamicQuantity quantityType         = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
    double                                 quantityValue        = boilerInput.getSteamTemperature();

    return {deaeratorPressure, combustionEfficiency, blowdownRate, steamPressure,
            quantityType,      quantityValue,        massFlow};
}
