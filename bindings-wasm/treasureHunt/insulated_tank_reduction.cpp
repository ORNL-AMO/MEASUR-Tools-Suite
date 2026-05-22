#include <emscripten/bind.h>

#include "treasureHunt/insulated_tank_reduction.h"

using namespace emscripten;
using namespace insulated_tank_reduction;

EMSCRIPTEN_BINDINGS(insulated_tank_reduction_module) {
    value_object<InsulatedTankInput>("InsulatedTankInput")
        .field("operatingHours",         &InsulatedTankInput::operating_hours)
        .field("tankHeight",             &InsulatedTankInput::tank_height)
        .field("tankDiameter",           &InsulatedTankInput::tank_diameter)
        .field("tankThickness",          &InsulatedTankInput::tank_thickness)
        .field("tankEmissivity",         &InsulatedTankInput::tank_emissivity)
        .field("tankConductivity",       &InsulatedTankInput::tank_conductivity)
        .field("tankTemperature",        &InsulatedTankInput::tank_temperature)
        .field("ambientTemperature",     &InsulatedTankInput::ambient_temperature)
        .field("systemEfficiency",       &InsulatedTankInput::system_efficiency)
        .field("insulationThickness",    &InsulatedTankInput::insulation_thickness)
        .field("insulationConductivity", &InsulatedTankInput::insulation_conductivity)
        .field("jacketEmissivity",       &InsulatedTankInput::jacket_emissivity)
        .field("surfaceTemperature",     &InsulatedTankInput::surface_temperature);

    value_object<InsulatedTankOutput>("InsulatedTankOutput")
        .field("heatLoss",       &InsulatedTankOutput::heat_loss)
        .field("annualHeatLoss", &InsulatedTankOutput::annual_heat_loss);

    // insulatedTankReduction(input: InsulatedTankInput) -> InsulatedTankOutput
    //   input.operatingHours:        annual operating hours [hr/yr]
    //   input.tankHeight:            tank lateral height [ft]
    //   input.tankDiameter:          tank inner diameter [ft]
    //   input.tankThickness:         tank wall thickness [ft]
    //   input.tankEmissivity:        bare tank outer surface emissivity [0–1, dimensionless]
    //   input.tankConductivity:      tank wall thermal conductivity [BTU/(hr·ft·°F)]
    //   input.tankTemperature:       tank fluid (inner surface) temperature [°R]
    //   input.ambientTemperature:    ambient air temperature [°R]
    //   input.systemEfficiency:      heating system efficiency [0–1, dimensionless]
    //   input.insulationThickness:   insulation layer thickness [ft]; <= 0 = bare tank
    //   input.insulationConductivity:insulation thermal conductivity [BTU/(hr·ft·°F)]
    //   input.jacketEmissivity:      insulation jacket outer surface emissivity [0–1, dimensionless]
    //   input.surfaceTemperature:    outer surface temperature (jacket or bare tank) [°R]
    //   returns: heatLoss [BTU/hr per 10^5], annualHeatLoss [BTU per 10^6]
    function("insulatedTankReduction", &calculate);

    // insulatedTankHeatLoss(input: InsulatedTankInput) -> InsulatedTankOutput
    //   Same input fields as insulatedTankReduction. Computes heat loss for an insulated tank.
    //   returns: heatLoss [BTU/hr per 10^5], annualHeatLoss [BTU per 10^6]
    function("insulatedTankHeatLoss", &insulatedTankHeatLoss);

    // bareTankHeatLoss(input: InsulatedTankInput) -> InsulatedTankOutput
    //   Same input fields as insulatedTankReduction. Computes heat loss for a bare (uninsulated) tank.
    //   returns: heatLoss [BTU/hr per 10^5], annualHeatLoss [BTU per 10^6]
    function("bareTankHeatLoss", &bareTankHeatLoss);

    // insulatedTankRayleighNumber(thermal_expansion, surface_temperature, ambient_temperature,
    //                             diameter, kin_viscosity, thermal_diffusivity) -> double
    //   thermal_expansion:   volumetric thermal expansion coefficient of air (1/T_ambient) [1/°R]
    //   surface_temperature: outer surface temperature [°R]
    //   ambient_temperature: ambient air temperature [°R]
    //   diameter:            tank outer diameter [ft]
    //   kin_viscosity:       air kinematic viscosity [ft²/s]
    //   thermal_diffusivity: air thermal diffusivity [ft²/hr]
    //   returns: Rayleigh number [dimensionless]
    function("insulatedTankRayleighNumber", &rayleighNumber);

    // insulatedTankNaturalConvectionCoeff(rayleigh, conductivity, diameter) -> double
    //   rayleigh:     Rayleigh number [dimensionless]
    //   conductivity: air thermal conductivity [BTU/(hr·ft·°F)]
    //   diameter:     tank outer diameter [ft]
    //   returns: natural convection heat transfer coefficient [BTU/(hr·ft²·°F)]
    function("insulatedTankNaturalConvectionCoeff", &naturalConvectionCoefficient);
}
