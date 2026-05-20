#include <emscripten/bind.h>

#include "treasureHunt/insulated_pipe_reduction.h"

using namespace emscripten;
using namespace insulated_pipe_reduction;

EMSCRIPTEN_BINDINGS(insulated_pipe_reduction_module) {
    value_object<InsulatedPipeInput>("InsulatedPipeInput")
        .field("operatingHours",                  &InsulatedPipeInput::operating_hours)
        .field("pipeLength",                       &InsulatedPipeInput::pipe_length)
        .field("pipeDiameter",                     &InsulatedPipeInput::pipe_diameter)
        .field("pipeThickness",                    &InsulatedPipeInput::pipe_thickness)
        .field("pipeTemperature",                  &InsulatedPipeInput::pipe_temperature)
        .field("ambientTemperature",               &InsulatedPipeInput::ambient_temperature)
        .field("windVelocity",                     &InsulatedPipeInput::wind_velocity)
        .field("systemEfficiency",                 &InsulatedPipeInput::system_efficiency)
        .field("insulationThickness",              &InsulatedPipeInput::insulation_thickness)
        .field("pipeEmissivity",                   &InsulatedPipeInput::pipe_emissivity)
        .field("jacketEmissivity",                 &InsulatedPipeInput::jacket_emissivity)
        .field("pipeMaterialCoefficients",         &InsulatedPipeInput::pipe_material_coefficients)
        .field("insulationMaterialCoefficients",   &InsulatedPipeInput::insulation_material_coefficients);

    value_object<InsulatedPipeOutput>("InsulatedPipeOutput")
        .field("heatLossPerLength", &InsulatedPipeOutput::heat_loss_per_length)
        .field("annualHeatLoss",    &InsulatedPipeOutput::annual_heat_loss);

    // insulatedPipeReduction(input: InsulatedPipeInput) -> InsulatedPipeOutput
    //   input.operatingHours:                annual operating hours [hr/yr]
    //   input.pipeLength:                    total pipe length [m]
    //   input.pipeDiameter:                  pipe outer diameter [m]
    //   input.pipeThickness:                 pipe wall thickness [m]
    //   input.pipeTemperature:               pipe inner surface (fluid) temperature [K]
    //   input.ambientTemperature:            surrounding air temperature [K]
    //   input.windVelocity:                  free-stream wind speed [m/s]
    //   input.systemEfficiency:              heating system efficiency [0–1, dimensionless]
    //   input.insulationThickness:           insulation layer thickness [m]; <= 0 = bare pipe
    //   input.pipeEmissivity:                pipe outer surface emissivity [0–1, dimensionless]
    //   input.jacketEmissivity:              insulation jacket outer surface emissivity [0–1, dimensionless]
    //   input.pipeMaterialCoefficients:      5 polynomial coefficients for pipe thermal conductivity vs. T [W/(m·K)]
    //   input.insulationMaterialCoefficients:5 polynomial coefficients for insulation thermal conductivity vs. T [W/(m·K)]
    //   returns: heatLossPerLength [W/m], annualHeatLoss [Wh/yr]
    function("insulatedPipeReduction", &calculate);

    // insulatedPipeHeatLoss(input: InsulatedPipeInput) -> InsulatedPipeOutput
    //   Same input fields and units as insulatedPipeReduction (see above).
    //   Runs the iterative solver for a pipe with insulation (insulationThickness > 0).
    //   returns: heatLossPerLength [W/m], annualHeatLoss [Wh/yr]
    function("insulatedPipeHeatLoss", &insulatedPipeHeatLoss);

    // bareInsulatedPipeHeatLoss(input: InsulatedPipeInput) -> InsulatedPipeOutput
    //   Same input fields and units as insulatedPipeReduction (see above).
    //   Runs the iterative solver for a bare pipe (insulationThickness <= 0).
    //   returns: heatLossPerLength [W/m], annualHeatLoss [Wh/yr]
    function("bareInsulatedPipeHeatLoss", &bareInsulatedPipeHeatLoss);

    // insulatedPipeThermalResistance(diameter_a: double, diameter_b: double, diameter_c: double, thermal_conductivity: double) -> double
    //   diameter_a: outer diameter of the shell [m]
    //   diameter_b: diameter used as the logarithm numerator [m]
    //   diameter_c: diameter used as the logarithm denominator (inner diameter) [m]
    //   thermal_conductivity: material thermal conductivity [W/(m·K)]
    //   returns: cylindrical thermal resistance per unit length [(m·K)/W]
    function("insulatedPipeThermalResistance", &thermalResistance);

    // insulatedPipeReynoldsNumber(diameter: double, wind_velocity: double, kinematic_viscosity: double) -> double
    //   diameter:            outer diameter of the surface [m]
    //   wind_velocity:       free-stream wind speed [m/s]
    //   kinematic_viscosity: air kinematic viscosity at film temperature [m²/s]
    //   returns: Reynolds number [dimensionless]
    function("insulatedPipeReynoldsNumber", &reynoldsNumber);

    // insulatedPipeRayleighNumber(expansion_coefficient, surface_temperature, ambient_temperature, diameter, kinematic_viscosity, alpha) -> double
    //   expansion_coefficient: volumetric thermal expansion coefficient of air (1/T_film) [1/K]
    //   surface_temperature:   outer surface temperature [K]
    //   ambient_temperature:   surrounding air temperature [K]
    //   diameter:              outer diameter of the surface [m]
    //   kinematic_viscosity:   air kinematic viscosity at film temperature [m²/s]
    //   alpha:                 air thermal diffusivity at film temperature [m²/s]
    //   returns: Rayleigh number [dimensionless]
    function("insulatedPipeRayleighNumber", &rayleighNumber);

    // insulatedPipeNusseltNumber(nusselt_forced: double, nusselt_free: double) -> double
    //   nusselt_forced: forced-convection Nusselt number [dimensionless]
    //   nusselt_free:   free-convection Nusselt number [dimensionless]
    //   returns: combined Nusselt number via fourth-power sum rule [dimensionless]
    function("insulatedPipeNusseltNumber", &nusseltNumber);

    // insulatedPipeNusseltForcedConvection(reynolds: double, prandtl: double) -> double
    //   reynolds: Reynolds number [dimensionless]
    //   prandtl:  Prandtl number of air at film temperature [dimensionless]
    //   returns: forced-convection Nusselt number (Churchill–Bernstein) [dimensionless]
    function("insulatedPipeNusseltForcedConvection", &nusseltForcedConvection);

    // insulatedPipeNusseltFreeConvection(rayleigh: double, prandtl: double) -> double
    //   rayleigh: Rayleigh number [dimensionless]
    //   prandtl:  Prandtl number of air at film temperature [dimensionless]
    //   returns: free-convection Nusselt number (Churchill–Chu) [dimensionless]
    function("insulatedPipeNusseltFreeConvection", &nusseltFreeConvection);

    // insulatedPipeRadiativeHeatTransferCoeff(emissivity: double, surface_temperature: double, ambient_temperature: double) -> double
    //   emissivity:           surface emissivity [0–1, dimensionless]
    //   surface_temperature:  outer surface temperature [K]
    //   ambient_temperature:  surrounding air temperature [K]
    //   returns: linearized radiative heat transfer coefficient [W/(m²·K)]
    function("insulatedPipeRadiativeHeatTransferCoeff", &radiativeHeatTransferCoefficient);

    // insulatedPipeConvectiveHeatTransferCoeff(nusselt: double, air_conductivity: double, diameter: double) -> double
    //   nusselt:          combined Nusselt number [dimensionless]
    //   air_conductivity: thermal conductivity of air at film temperature [W/(m·K)]
    //   diameter:         outer diameter of the surface [m]
    //   returns: convective heat transfer coefficient [W/(m²·K)]
    function("insulatedPipeConvectiveHeatTransferCoeff", &convectiveHeatTransferCoefficient);
}
