#include "motorDriven/pump/pump_valve_power_loss.h"

#include "catch.hpp"

using namespace Catch;

auto validateValveLosses = [](PumpValvePowerLoss::Output const& results, PumpValvePowerLoss::Output expected) {
    CHECK(Approx(results.pressure_drop) == expected.pressure_drop);
    CHECK(Approx(results.head_loss) == expected.head_loss);
    CHECK(Approx(results.power_loss_frictional) == expected.power_loss_frictional);
    CHECK(Approx(results.power_loss_electrical) == expected.power_loss_electrical);
    CHECK(Approx(results.annual_energy_loss) == expected.annual_energy_loss);
};

TEST_CASE("Calculate Pump valve power loss and Annual Energy usage", "[Head Friction Electrical Losses]") {
    INFO("Test# 1 - Baseline");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.85, 0.95, 1, 5000, 50, 5, 45, 2),
            {6.300249778,  14.536245, 18.3763150298, 16.97, 148656.58 });

    INFO("Test# 2 - Broad Changes in Variables");
    validateValveLosses(PumpValvePowerLoss().calculate(6140, 0.87, 0.96, 1, 4000, 60, 5, 45, 2),
                        {16.300249778,  37.608735, 38.0351301032, 33.9592870186, 208510.0222943327 });

    INFO("Test# 3 - Hours of Operation");
    validateValveLosses(PumpValvePowerLoss().calculate(7000, 0.85, 0.95, 1, 5000, 50, 5, 45, 2),
                        {6.300249778,  14.536245, 18.3763150298, 16.97, 118789.5069030884 });

    // INFO("Test# 4 – Electrical Cost => Same as Baseline");

    INFO("Test# 5 – Pump Efficiency");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.89, 0.95, 1, 5000, 50, 5, 45, 2),
                        {6.300249778,  14.536245, 18.3763150298, 16.2072360943, 141975.3881862594 });

    INFO("Test# 6 – Motor Efficiency");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.85, 0.97, 1, 5000, 50, 5, 45, 2),
                        {6.300249778,  14.536245, 18.3763150298, 16.62, 145591.4987404273 });

    INFO("Test# 7 – Specific Gravity");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.85, 0.95, 2, 5000, 50, 5, 45, 2),
                        {7.600499556, 17.536245, 22.1688312601, 20.4721950101, 179336.4282884425 });

    INFO("Test# 8 – Pressure Differential");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.85, 0.95, 1, 5000, 60, 5, 40, 2),
                        {21.300249778, 49.14498, 62.1277114286, 57.3729218728, 502586.7956057265 });

    INFO("Test# 9 – Elevation Differential");
    validateValveLosses(PumpValvePowerLoss().calculate(8760, 0.85, 0.95, 1, 5000, 50, 15, 45, 2),
                        {10.6344157046, 24.536245, 31.0180357974, 28.6441477326, 250922.7341377905 });
}