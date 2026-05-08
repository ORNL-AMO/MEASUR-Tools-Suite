#include "treasureHunt/steam_reduction.h"

#include "catch.hpp"

using namespace Catch;
using namespace steam_reduction;

static SteamReductionInput makeInput(int hours_per_year, int utility_type, double utility_cost,
                                     int measurement_method, double system_efficiency, double pressure,
                                     FlowMeterMethodData flow_meter_data,
                                     MassFlowMethodData air_mass_flow_data,
                                     MassFlowMethodData water_mass_flow_data,
                                     OffsheetMethodData offsheet_data, int units, double boiler_efficiency,
                                     SteamProperties::ThermodynamicQuantity steam_variable_option,
                                     double steam_variable, double feed_water_temperature) {
    SteamReductionInput input;
    input.hours_per_year          = hours_per_year;
    input.utility_type            = static_cast<UtilityType>(utility_type);
    input.utility_cost            = utility_cost;
    input.measurement_method      = static_cast<SteamMeasurementMethod>(measurement_method);
    input.system_efficiency       = system_efficiency;
    input.pressure                = pressure;
    input.flow_meter_method_data  = flow_meter_data;
    input.air_mass_flow_method_data   = air_mass_flow_data;
    input.water_mass_flow_method_data = water_mass_flow_data;
    input.offsheet_method_data    = offsheet_data;
    input.units                   = units;
    input.boiler_efficiency       = boiler_efficiency;
    input.steam_variable_option   = steam_variable_option;
    input.steam_variable          = steam_variable;
    input.feed_water_temperature  = feed_water_temperature;
    return input;
}

TEST_CASE("Steam Reduction Flow Meter Method", "[steamReduction][util]") {
    MassFlowMeasuredData  measured{1.0, 100.0};
    MassFlowNameplateData nameplate_air{40000.0};
    MassFlowNameplateData nameplate_water{40000.0};

    std::vector<SteamReductionInput> input_vec = {
        makeInput(8000, 1, 5.5, 0, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{false, measured, nameplate_air, 25.0, 425.0},
                  MassFlowMethodData{true,  measured, nameplate_water, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(10000000.0));
    CHECK(output.energy_use  == Approx(38671503020.03));
    CHECK(output.energy_cost == Approx(212693266610.1651));
}

TEST_CASE("Steam Reduction Air Mass Flow - Measured", "[steamReduction][util]") {
    MassFlowMeasuredData  measured_air{1.0, 100.0};
    MassFlowNameplateData nameplate_air{4000.0};
    MassFlowMeasuredData  measured_water{1.0, 100.0};
    MassFlowNameplateData nameplate_water{40000.0};

    std::vector<SteamReductionInput> input_vec = {
        makeInput(8000, 1, 5.5, 1, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{false, measured_air, nameplate_air, 25.0, 425.0},
                  MassFlowMethodData{true,  measured_water, nameplate_water, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(9982.3376));
    CHECK(output.energy_use  == Approx(38603200.0));
    CHECK(output.energy_cost == Approx(212317600.0));
}

TEST_CASE("Steam Reduction Air Mass Flow - Nameplate", "[steamReduction][util]") {
    MassFlowMeasuredData  measured_air{1.0, 100.0};
    MassFlowNameplateData nameplate_air{4000.0};
    MassFlowMeasuredData  measured_water{1.0, 100.0};
    MassFlowNameplateData nameplate_water{40000.0};

    std::vector<SteamReductionInput> input_vec = {
        makeInput(8000, 1, 5.5, 1, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{true,  measured_air, nameplate_air, 25.0, 425.0},
                  MassFlowMethodData{true,  measured_water, nameplate_water, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(399293.5054));
    CHECK(output.energy_use  == Approx(1544127999.9999));
    CHECK(output.energy_cost == Approx(8492703999.9999));
}

TEST_CASE("Steam Reduction Water Mass Flow - Nameplate", "[steamReduction][util]") {
    MassFlowMeasuredData  measured_air{100.0, 5.0};
    MassFlowNameplateData nameplate_air{400.0};
    MassFlowMeasuredData  measured_water{1.0, 100.0};
    MassFlowNameplateData nameplate_water{1.0};

    std::vector<SteamReductionInput> input_vec = {
        makeInput(8000, 1, 5.5, 2, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{true,  measured_air, nameplate_air, 70.0, 200.0},
                  MassFlowMethodData{true,  measured_water, nameplate_water, 25.0, 225.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(173112830.1340));
    CHECK(output.energy_use  == Approx(669453333333.3332));
    CHECK(output.energy_cost == Approx(3681993333333.3330));
}

TEST_CASE("Steam Reduction Offsheet Method", "[steamReduction][util]") {
    MassFlowMeasuredData  measured{1.0, 100.0};
    MassFlowNameplateData nameplate{40000.0};

    std::vector<SteamReductionInput> input_vec = {
        makeInput(8000, 0, 5.5, 3, 0.8, 3.5,
                  FlowMeterMethodData{5000.0},
                  MassFlowMethodData{false, measured, nameplate, 25.0, 425.0},
                  MassFlowMethodData{true,  measured, nameplate, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(3361.6485));
    CHECK(output.energy_use  == Approx(13000000.0));
    CHECK(output.energy_cost == Approx(18489.0667));
}

TEST_CASE("Steam Reduction Multi Method", "[steamReduction][util]") {
    MassFlowMeasuredData  measured{1.0, 100.0};
    MassFlowNameplateData nameplate_large{40000.0};

    std::vector<SteamReductionInput> input_vec = {
        // Flow meter method
        makeInput(8000, 1, 5.5, 0, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{false, measured, nameplate_large, 25.0, 425.0},
                  MassFlowMethodData{true,  measured, nameplate_large, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15),
        // Water mass flow method
        makeInput(8000, 1, 5.5, 2, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{true, MassFlowMeasuredData{100.0, 5.0}, MassFlowNameplateData{400.0}, 70.0, 200.0},
                  MassFlowMethodData{true, MassFlowMeasuredData{1.0, 100.0}, MassFlowNameplateData{1.0}, 25.0, 225.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15),
        // Offsheet method
        makeInput(8000, 0, 5.5, 3, 0.8, 3.5,
                  FlowMeterMethodData{1000.0},
                  MassFlowMethodData{false, measured, nameplate_large, 25.0, 425.0},
                  MassFlowMethodData{true,  measured, nameplate_large, 25.0, 425.0},
                  OffsheetMethodData{13000000.0}, 1, 0.75,
                  SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560.0, 283.15)
    };

    auto output = steamReduction(input_vec);
    CHECK(output.steam_use   == Approx(183116191.7825));
    CHECK(output.energy_use  == Approx(708137836353.3633));
    CHECK(output.energy_cost == Approx(3894686618432.565));
}
