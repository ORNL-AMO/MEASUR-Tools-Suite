#include "motorDriven/pump/pump_valve_power_loss.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(pump_valve_power_loss_class)
{
        class_<PumpValvePowerLoss::Output>("PumpValvePowerLossOutput")
                .property("pressure_drop", &PumpValvePowerLoss::Output::pressure_drop)
                .property("head_loss", &PumpValvePowerLoss::Output::head_loss)
                .property("power_loss_frictional", &PumpValvePowerLoss::Output::power_loss_frictional)
                .property("power_loss_electrical", &PumpValvePowerLoss::Output::power_loss_electrical)
                .property("annual_energy_loss", &PumpValvePowerLoss::Output::annual_energy_loss);

        class_<PumpValvePowerLoss>("PumpValvePowerLoss")
                .constructor<>()
                .function("calculate", &PumpValvePowerLoss::calculate);
}