#pragma once

#include <memory>
#include <vector>

#include <steamModeler/api/TurbineInput.h>
#include <steamModeler/Boiler.h>
#include <steamModeler/FlashTank.h>
#include <steamModeler/Header.h>
#include <steamModeler/HeatExchanger.h>
#include <steamModeler/PRV.h>
#include <steamModeler/Turbine.h>

class InletFactory {
  public:
    std::vector<Inlet> make(const Boiler& boiler) const;

    Inlet make(const std::shared_ptr<PrvWithoutDesuperheating>& prv) const;

    Inlet make(const std::shared_ptr<Turbine>& turbine) const;

    Inlet make(const std::shared_ptr<Turbine>& turbine, const double pressure) const;

    Inlet makeFromOutletGas(const std::shared_ptr<FlashTank>& flashTank) const;

    Inlet makeFromOutletLiquid(const std::shared_ptr<FlashTank>& flashTank) const;

    Inlet makeWithEnthalpy(const SteamSystemModelerTool::FluidProperties& properties) const;

    Inlet makeWithTemperature(const std::shared_ptr<HeatExchanger::Output>& output) const;
};

