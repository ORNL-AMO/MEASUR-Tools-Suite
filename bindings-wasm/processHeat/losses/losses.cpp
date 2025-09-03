#include <emscripten/bind.h>

#include "processHeat/losses/atmosphere.h"
#include "processHeat/losses/auxiliary_power.h"
#include "processHeat/losses/energy_input_EAF.h"
#include "processHeat/losses/energy_input_exhaust_gas_losses.h"
#include "processHeat/losses/exhaust_gas_EAF.h"
#include "processHeat/losses/fixture_losses.h"
#include "processHeat/losses/gas_cooling_losses.h"
#include "processHeat/losses/gas_flue_gas_material.h"
#include "processHeat/losses/gas_load_charge_material.h"
#include "processHeat/losses/leakage_losses.h"
#include "processHeat/losses/liquid_cooling_losses.h"
#include "processHeat/losses/liquid_load_charge_material.h"
#include "processHeat/losses/load_charge_material.h"
#include "processHeat/losses/opening_losses.h"
#include "processHeat/losses/slag_other_material_losses.h"
#include "processHeat/losses/solid_liquid_flue_gas_material.h"
#include "processHeat/losses/solid_load_charge_material.h"
#include "processHeat/losses/wall_losses.h"
#include "processHeat/losses/water_cooling_losses.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(losses_enums) {
    enum_<LoadChargeMaterial::ThermicReactionType>("ThermicReactionType")
        .value("ENDOTHERMIC", LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC)
        .value("EXOTHERMIC", LoadChargeMaterial::ThermicReactionType::EXOTHERMIC)
        .value("NONE", LoadChargeMaterial::ThermicReactionType::NONE);
}

// atmosphere
// getTotalHeat()
EMSCRIPTEN_BINDINGS(atmosphere) {
    class_<Atmosphere>("Atmosphere")
        .constructor<>()
        .constructor<double, double, double, double, double>()
        .function("getTotalHeat", &Atmosphere::getTotalHeat)
        .function("getID", &Atmosphere::getID)
        .function("getSubstance", &Atmosphere::getSubstance)
        .function("getSpecificHeat", &Atmosphere::getSpecificHeat)
        .function("setID", &Atmosphere::setID)
        .function("setSubstance", &Atmosphere::setSubstance)
        .function("setSpecificHeat", &Atmosphere::setSpecificHeat);

    register_vector<Atmosphere>("AtmosphereV");
}

// auxiliaryPowerLoss
// getPowerUsed()
EMSCRIPTEN_BINDINGS(auxiliaryPowerLoss) {
    // motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime
    class_<AuxiliaryPower>("AuxiliaryPower")
        .constructor<double, double, double, double, double>()
        .function("getPowerUsed", &AuxiliaryPower::getPowerUsed);
}
// fixtureLosses
// getHeatLoss()
EMSCRIPTEN_BINDINGS(fixtureLosses) {
    // specificHeat, feedRate, initialTemperature, finalTemperature,
    // correctionFactor
    class_<FixtureLosses>("FixtureLosses")
        .constructor<double, double, double, double, double>()
        .function("getHeatLoss", &FixtureLosses::getHeatLoss);
}
// energyInputEAF
EMSCRIPTEN_BINDINGS(energyInputEAF) {
    // naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse,
    //    electrodeHeatingValue, otherFuels, electricityInput
    class_<EnergyInputEAF>("EnergyInputEAF")
        .constructor<double, double, double, double, double, double, double>()
        .function("getTotalChemicalEnergyInput", &EnergyInputEAF::getTotalChemicalEnergyInput)
        .function("getHeatDelivered", &EnergyInputEAF::getHeatDelivered);
}
// energyInputExhaustGasLosses
EMSCRIPTEN_BINDINGS(energyInputExhaustGasLosses) {
    class_<EnergyInputExhaustGasLosses>("EnergyInputExhaustGasLosses")
        .constructor<double, double, double, double>()
        .function("getHeatDelivered", &EnergyInputExhaustGasLosses::getHeatDelivered)
        .function("getExhaustGasLosses", &EnergyInputExhaustGasLosses::getExhaustGasLosses)
        .function("getAvailableHeat", &EnergyInputExhaustGasLosses::getAvailableHeat);
}
// exhaustGasEAF
EMSCRIPTEN_BINDINGS(exhaustGasEAF) {
    class_<ExhaustGasEAF>("ExhaustGasEAF")
        .constructor<double, double, double, double, double, double>()
        .function("getTotalHeatExhaust", &ExhaustGasEAF::getTotalHeatExhaust);
}
EMSCRIPTEN_BINDINGS(flueGasLosses) {
    class_<GasCompositions::ProcessHeatPropertiesResults>("ProcessHeatPropertiesResults")
        .property("stoichAir", &GasCompositions::ProcessHeatPropertiesResults::stoichAir)
        .property("excessAir", &GasCompositions::ProcessHeatPropertiesResults::excessAir)
        .property("availableHeat", &GasCompositions::ProcessHeatPropertiesResults::availableHeat)
        .property("specificHeat", &GasCompositions::ProcessHeatPropertiesResults::specificHeat)
        .property("density", &GasCompositions::ProcessHeatPropertiesResults::density)
        .property("flueGasO2", &GasCompositions::ProcessHeatPropertiesResults::flueGasO2);

    // flueGasByVolumeCalculateHeatingValue
    // flueGasCalculateExcessAir
    // flueGasCalculateO2
    class_<GasCompositions>("GasCompositions")
        .constructor<std::string, double, double, double, double, double, double, double, double, double, double,
                     double>()
        .function("getProcessHeatProperties", &GasCompositions::getProcessHeatProperties)
        .function("getHeatingValue", &GasCompositions::getHeatingValue)
        .function("getHeatingValueVolume", &GasCompositions::getHeatingValueVolume)
        .function("getSpecificGravity", &GasCompositions::getSpecificGravity)
        .function("calculateExcessAir", &GasCompositions::calculateExcessAir)
        .function("calculateO2", &GasCompositions::calculateO2)
        .function("getID", &GasCompositions::getID)
        .function("getSubstance", &GasCompositions::getSubstance)
        .function("getGasByVol", &GasCompositions::getGasByVol)
        .function("setID", &GasCompositions::setID);

    register_vector<GasCompositions>("GasCompositionsV");

    // flueGasLossesByVolume
    class_<GasFlueGasMaterial>("GasFlueGasMaterial")
        .constructor<double, double, double, GasCompositions, double>()
        .function("getHeatLoss", &GasFlueGasMaterial::getHeatLoss);

    // flueGasLossesByMass
    // flueGasByMassCalculateHeatingValue
    // flueGasByMassCalculateO2
    // flueGasByMassCalculateExcessAir
    class_<SolidLiquidFlueGasMaterial>("SolidLiquidFlueGasMaterial")
        .constructor<std::string, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double,
                     double, double, double>()
        .constructor()
        .function("getHeatLoss", &SolidLiquidFlueGasMaterial::getHeatLoss)
        .function("calculateHeatingValueFuel", &SolidLiquidFlueGasMaterial::calculateHeatingValueFuel)
        .function("calculateFlueGasO2", &SolidLiquidFlueGasMaterial::calculateFlueGasO2)
        .function("calculateExcessAirFromFlueGasO2", &SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2)
        .function("getID", &SolidLiquidFlueGasMaterial::getID)
        .function("getSubstance", &SolidLiquidFlueGasMaterial::getSubstance)
        .function("getCarbon", &SolidLiquidFlueGasMaterial::getCarbon)
        .function("getHydrogen", &SolidLiquidFlueGasMaterial::getHydrogen)
        .function("getSulphur", &SolidLiquidFlueGasMaterial::getSulphur)
        .function("getInertAsh", &SolidLiquidFlueGasMaterial::getInertAsh)
        .function("getO2", &SolidLiquidFlueGasMaterial::getO2)
        .function("getMoisture", &SolidLiquidFlueGasMaterial::getMoisture)
        .function("getNitrogen", &SolidLiquidFlueGasMaterial::getNitrogen)
        .function("setID", &SolidLiquidFlueGasMaterial::setID)
        .function("setSubstance", &SolidLiquidFlueGasMaterial::setSubstance)
        .function("setCarbon", &SolidLiquidFlueGasMaterial::setCarbon)
        .function("setHydrogen", &SolidLiquidFlueGasMaterial::setHydrogen)
        .function("setSulphur", &SolidLiquidFlueGasMaterial::setSulphur)
        .function("setInertAsh", &SolidLiquidFlueGasMaterial::setInertAsh)
        .function("setO2", &SolidLiquidFlueGasMaterial::setO2)
        .function("setMoisture", &SolidLiquidFlueGasMaterial::setMoisture)
        .function("setNitrogen", &SolidLiquidFlueGasMaterial::setNitrogen)
        .function("getAmbientAirTempF", &SolidLiquidFlueGasMaterial::getAmbientAirTempF)
        .function("setAmbientAirTempF", &SolidLiquidFlueGasMaterial::setAmbientAirTempF)
        .function("getHeatingValueFuel", &SolidLiquidFlueGasMaterial::getHeatingValueFuel);

    register_vector<SolidLiquidFlueGasMaterial>("SolidLiquidFlueGasMaterialV");
}

// gasCoolingLosses
EMSCRIPTEN_BINDINGS(gasCoolingLosses) {
    class_<GasCoolingLosses>("GasCoolingLosses")
        .constructor<double, double, double, double, double, double>()
        .function("getHeatLoss", &GasCoolingLosses::getHeatLoss);
}
// gasLoadChargeMaterial
EMSCRIPTEN_BINDINGS(gasLoadChargeMaterial) {
    class_<GasLoadChargeMaterial>("GasLoadChargeMaterial")
        .constructor<>()
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double,
                     double, double>()
        .function("getTotalHeat", &GasLoadChargeMaterial::getTotalHeat)
        .function("getID", &GasLoadChargeMaterial::getID)
        .function("getSubstance", &GasLoadChargeMaterial::getSubstance)
        .function("getSpecificHeatVapor", &GasLoadChargeMaterial::getSpecificHeatVapor)
        .function("setID", &GasLoadChargeMaterial::setID)
        .function("setSubstance", &GasLoadChargeMaterial::setSubstance)
        .function("setSpecificHeatVapor", &GasLoadChargeMaterial::setSpecificHeatVapor);

    register_vector<GasLoadChargeMaterial>("GasLoadChargeMaterialV");
}
// leakageLosses
EMSCRIPTEN_BINDINGS(leakageLosses) {
    class_<LeakageLosses>("LeakageLosses")
        .constructor<double, double, double, double, double, double, double>()
        .function("getExfiltratedGasesHeatContent", &LeakageLosses::getExfiltratedGasesHeatContent);
}
// liquidCoolingLosses
EMSCRIPTEN_BINDINGS(liquidCoolingLosses) {
    class_<LiquidCoolingLosses>("LiquidCoolingLosses")
        .constructor<double, double, double, double, double, double>()
        .function("getHeatLoss", &LiquidCoolingLosses::getHeatLoss);
}
// liquidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(liquidLoadChargeMaterial) {
    class_<LiquidLoadChargeMaterial>("LiquidLoadChargeMaterial")
        .constructor<>()
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double,
                     double, double, double, double>()
        .function("getTotalHeat", &LiquidLoadChargeMaterial::getTotalHeat)
        .function("getID", &LiquidLoadChargeMaterial::getID)
        .function("getSubstance", &LiquidLoadChargeMaterial::getSubstance)
        .function("getSpecificHeatLiquid", &LiquidLoadChargeMaterial::getSpecificHeatLiquid)
        .function("getSpecificHeatVapor", &LiquidLoadChargeMaterial::getSpecificHeatVapor)
        .function("getVaporizingTemperature", &LiquidLoadChargeMaterial::getVaporizingTemperature)
        .function("getLatentHeat", &LiquidLoadChargeMaterial::getLatentHeat)
        .function("setID", &LiquidLoadChargeMaterial::setID)
        .function("setSubstance", &LiquidLoadChargeMaterial::setSubstance)
        .function("setSpecificHeatLiquid", &LiquidLoadChargeMaterial::setSpecificHeatLiquid)
        .function("setSpecificHeatVapor", &LiquidLoadChargeMaterial::setSpecificHeatVapor)
        .function("setVaporizingTemperature", &LiquidLoadChargeMaterial::setVaporizingTemperature)
        .function("setLatentHeat", &LiquidLoadChargeMaterial::setLatentHeat);

    register_vector<LiquidLoadChargeMaterial>("LiquidLoadChargeMaterialV");
}
// openingLossesCircular
// openingLossesQuad
// viewFactorCalculation
EMSCRIPTEN_BINDINGS(openingLosses) {
    class_<OpeningLosses>("OpeningLosses")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor()
        .function("getHeatLoss", &OpeningLosses::getHeatLoss)
        .function("calculateViewFactorQuad",
                  select_overload<double(double, double, double)>(&OpeningLosses::calculateViewFactor))
        .function("calculateViewFactorCircular",
                  select_overload<double(double, double)>(&OpeningLosses::calculateViewFactor));
}
// slagOtherMaterialLosses
EMSCRIPTEN_BINDINGS(slagOtherMaterialLosses) {
    class_<SlagOtherMaterialLosses>("SlagOtherMaterialLosses")
        .constructor<double, double, double, double, double>()
        .function("getHeatLoss", &SlagOtherMaterialLosses::getHeatLoss);
}
// solidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(solidLoadChargeMaterial) {
    class_<SolidLoadChargeMaterial>("SolidLoadChargeMaterial")
        .constructor<>()
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double,
                     double, double, double, double, double, double, double>()
        .function("getTotalHeat", &SolidLoadChargeMaterial::getTotalHeat)
        .function("getID", &SolidLoadChargeMaterial::getID)
        .function("getSubstance", &SolidLoadChargeMaterial::getSubstance)
        .function("getSpecificHeatSolid", &SolidLoadChargeMaterial::getSpecificHeatSolid)
        .function("getLatentHeat", &SolidLoadChargeMaterial::getLatentHeat)
        .function("getSpecificHeatLiquid", &SolidLoadChargeMaterial::getSpecificHeatLiquid)
        .function("getMeltingPoint", &SolidLoadChargeMaterial::getMeltingPoint)
        .function("setID", &SolidLoadChargeMaterial::setID)
        .function("setSubstance", &SolidLoadChargeMaterial::setSubstance)
        .function("setSpecificHeatSolid", &SolidLoadChargeMaterial::setSpecificHeatSolid)
        .function("setLatentHeat", &SolidLoadChargeMaterial::setLatentHeat)
        .function("setSpecificHeatLiquid", &SolidLoadChargeMaterial::setSpecificHeatLiquid)
        .function("setMeltingPoint", &SolidLoadChargeMaterial::setMeltingPoint);

    register_vector<SolidLoadChargeMaterial>("SolidLoadChargeMaterialV");
}
// wallLosses
EMSCRIPTEN_BINDINGS(wallLosses) {
    class_<WallLosses>("WallLosses")
        .constructor<>()
        .constructor<double, double, double, double, double, double, double>()
        .function("totalHeatLoss", &WallLosses::totalHeatLoss)
        .function("id", &WallLosses::id)
        .function("surfaceDescription", &WallLosses::surfaceDescription)
        .function("shapeFactor", &WallLosses::shapeFactor)
        .function("setID", &WallLosses::setID)
        .function("setSurfaceDescription", &WallLosses::setSurfaceDescription)
        .function("setShapeFactor", &WallLosses::setShapeFactor);

    register_vector<WallLosses>("WallLossesV");
}
// waterCoolingLosses
EMSCRIPTEN_BINDINGS(waterCoolingLosses) {
    class_<WaterCoolingLosses>("WaterCoolingLosses")
        .constructor<double, double, double, double>()
        .function("getHeatLoss", &WaterCoolingLosses::getHeatLoss);
}
