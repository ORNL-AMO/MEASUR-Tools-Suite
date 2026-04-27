#include <emscripten/bind.h>
#include "steam/steam_leak_survey.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(steam_leak_survey_class) {
    // Parameters for QuantifySteamLeakByPlumeLength Estimate function:
    //   Steam Pressure (psig)
    //   Plume Length (feet)
    //   Ambient Temp (F)
    class_<QuantifySteamLeakByPlumeLength>("QuantifySteamLeakByPlumeLength")
        .class_function("Estimate", &QuantifySteamLeakByPlumeLength::Estimate);

    enum_<SteamLeakSurvey::UtilityType>("UtilityType")
        .value("steam", SteamLeakSurvey::UtilityType::steam)
        .value("electric", SteamLeakSurvey::UtilityType::electric)
        .value("natural_gas", SteamLeakSurvey::UtilityType::natural_gas);

	class_<SteamLeakSurvey::SteamLeakSurveyResults>("SteamLeakSurveyResults")
        .property("leakRate", &SteamLeakSurvey::SteamLeakSurveyResults::leakRate)
        .property("steamLoss", &SteamLeakSurvey::SteamLeakSurveyResults::steamLoss)
        .property("energyLoss", &SteamLeakSurvey::SteamLeakSurveyResults::energyLoss)
        .property("leakCost", &SteamLeakSurvey::SteamLeakSurveyResults::leakCost);

    // Parameters for SteamLeakSurvey constructor when utility type is steam
    //   operatingTime (hours pre year), steamTemp (F), steamPressure (psig), costOfElectricity ($/kWh),
    //   leakPressure (psig), leakTemp (F), feedwaterTemp (F),
    //   steamCost ($/lb),
    // Parameters for SteamLeakSurvey constructor when utility type is electric
    //   operatingTime (hours pre year), steamTemp (F), steamPressure (psig), costOfElectricity ($/kWh),
    //   leakPressure (psig), leakTemp (F), feedwaterTemp (F),
    //   boilerEfficiency (0 - 100 %), systemEfficiency (0 - 100 %),
    // Parameters for SteamLeakSurvey constructor when utility type is natural gas
    //   operatingTime (hours pre year), steamTemp (F), steamPressure (psig), costOfElectricity ($/kWh),
    //   leakPressure (psig), leakTemp (F), feedwaterTemp (F),
    //   boilerEfficiency (0 - 100 %), systemEfficiency (0 - 100 %),
    //   fuelCost (per MCF, $), fuelEnergyFactor (MMBtu/MCF),
    // Parameters for SteamLeakSurvey constructor generic
    //   operatingTime (hours pre year), steamTemp (F), steamPressure (psig), costOfElectricity ($/kWh),
    //   leakPressure (psig), leakTemp (F), feedwaterTemp (F),
    //   boilerEfficiency (0 - 100 %), systemEfficiency (0 - 100 %), utility type,
    //   fuelCost (per MCF, $), fuelEnergyFactor (MMBtu/MCF), steamCost ($/lb)
    class_<SteamLeakSurvey>("SteamLeakSurvey")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, SteamLeakSurvey::UtilityType, double, double, double>()
        .function("costOfSteam", select_overload<double() const>(&SteamLeakSurvey::costOfSteam))
        .function("costOfSteam", select_overload<double(double) const>(&SteamLeakSurvey::costOfSteam))
        .function("estimateMethodPRVCalc", &SteamLeakSurvey::estimateMethodPRVCalc)
        .function("estimateMethodTurbineCalc", &SteamLeakSurvey::estimateMethodTurbineCalc)
        .function("orificeMethodCalc", &SteamLeakSurvey::orificeMethodCalc)
        .function("plumeMethodCalc", &SteamLeakSurvey::plumeMethodCalc);
}
