#include "catch.hpp"
#include <steamModeler/SaturatedProperties.h>

#include <steamModeler/SteamSystemModelerTool.h>

TEST_CASE( "Calculate the Saturated Temperature from Pressure", "[Saturated Temperature][steamModeler][Calculator]") {
    CHECK( SaturatedTemperature(20).calculate() == Approx(638.8959115457));
}

TEST_CASE( "Calculate the Saturated Pressure from Temperature", "[Saturated Pressure][steamModeler][Calculator]") {
    CHECK( SaturatedPressure(300).calculate() == Approx(0.0035365894));
}

TEST_CASE( "Calculate the Saturated Gas Specific Enthalpy", "[Gas Enthalpy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    auto const props = sp.calculate();
    CHECK( props.gasSpecificEnthalpy == Approx(2421.6805426877));
}

TEST_CASE( "Calculate the Saturated Gas Specific Entropy", "[Gas Entropy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    auto const props = sp.calculate();
    CHECK( props.gasSpecificEntropy == Approx(4.946));
}

TEST_CASE( "Calculate the Saturated Gas Specific Volume", "[Gas Volume][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    auto const props = sp.calculate();
    CHECK( props.gasSpecificVolume == Approx(0.0059368541));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Enthalpy (Region 1)", "[Liquid Enthalpy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificEnthalpy == Approx(112.5749908124));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Entropy (Region 1)", "[Liquid Entropy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificEntropy == Approx(0.3931236015));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Volume (Region 1)", "[Liquid Volume][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificVolume == Approx(0.001));
}

TEST_CASE( "Calculate the Evaporation Specific Volume", "[Evaporation Volume][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.evaporationSpecificVolume == Approx(39.081));
}

TEST_CASE( "Calculate the Evaporation Specific Enthalpy", "[Evaporation Enthalpy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.evaporationSpecificEnthalpy == Approx(2437.3));
}

TEST_CASE( "Calculate the Evaporation Specific Entropy", "[Evaporation Entropy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    auto const props = sp.calculate();
    CHECK( props.evaporationSpecificEntropy == Approx(8.1244130853));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Volume (Region 3)", "[Liquid Volume][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificVolume == Approx(0.0020763677));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Enthalpy (Region 3)", "[Liquid Enthalpy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificEnthalpy == Approx(1841.9862103902));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Entropy (Region 3)", "[Liquid Entropy][steamModeler][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    auto const props = sp.calculate();
    CHECK( props.liquidSpecificEntropy == Approx(4.0378047547));
}
