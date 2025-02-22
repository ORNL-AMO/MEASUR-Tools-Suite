#include <fstream>
#include <iostream>
#include <sqlite/SQLite.h>

#include <processHeat/losses/SolidLoadChargeMaterial.h>
#include <processHeat/losses/GasLoadChargeMaterial.h>
#include <processHeat/losses/LiquidLoadChargeMaterial.h>
#include <processHeat/losses/Atmosphere.h>
#include <processHeat/losses/WallLosses.h>
#include <processHeat/losses/GasFlueGasMaterial.h>
#include <motorDriven/motor/MotorData.h>
#include "motorDriven/pump/PumpData.h"
#include <processHeat/losses/SolidLiquidFlueGasMaterial.h>

#include <databases/SolidLiquidFlueGasMaterialData.h>
#include <databases/MotorData.h>
#include <databases/PumpData.h>
#include <databases/SolidLoadChargeMaterialData.h>
#include <databases/GasLoadChargeMaterialData.h>
#include <databases/LiquidLoadChargeMaterialData.h>
#include <databases/GasFlueGasMaterialData.h>
#include <databases/AtmosphereSpecificHeatData.h>
#include <databases/WallLossesSurfaceData.h>

SQLite::SQLite(std::string const &db_name, bool init_db)
    : SQLiteWrapper(db_name, init_db)
{
    execute_command("PRAGMA locking_mode = EXCLUSIVE;");
    execute_command("PRAGMA journal_mode = OFF;");
    execute_command("PRAGMA synchronous = OFF;");
    // Turn this to ON for Foreign Key constraints.
    // This must be turned ON for every connection
    execute_command("PRAGMA foreign_keys = ON;");

    if (init_db)
    {
        create_tables();
        create_insert_stmt();
        insert_default_data();
    }
    else
    {
        create_insert_stmt();
    }

    create_select_stmt();
    create_update_and_delete_stmt();
}

SQLite::~SQLite()
{
    sqlite3_finalize(m_solid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_select_custom_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_update_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_gas_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_custom_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_update_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_liquid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_custom_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_update_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_solid_liquid_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_single_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_custom_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_update_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_delete_stmt);

    sqlite3_finalize(m_gas_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_single_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_custom_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_update_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_delete_stmt);

    sqlite3_finalize(m_atmosphere_specific_heat_insert_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_single_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_custom_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_update_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_delete_stmt);

    sqlite3_finalize(m_wall_losses_surface_insert_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_single_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_custom_stmt);
    sqlite3_finalize(m_wall_losses_surface_update_stmt);
    sqlite3_finalize(m_wall_losses_surface_delete_stmt);

    sqlite3_finalize(m_motor_data_insert_stmt);
    sqlite3_finalize(m_motor_data_select_stmt);
    sqlite3_finalize(m_motor_data_select_single_stmt);
    sqlite3_finalize(m_motor_data_select_custom_stmt);
    sqlite3_finalize(m_motor_data_update_stmt);
    sqlite3_finalize(m_motor_data_delete_stmt);

    sqlite3_finalize(m_pump_data_insert_stmt);
    sqlite3_finalize(m_pump_data_select_stmt);
    sqlite3_finalize(m_pump_data_select_single_stmt);
    sqlite3_finalize(m_pump_data_select_custom_stmt);
    sqlite3_finalize(m_pump_data_update_stmt);
    sqlite3_finalize(m_pump_data_delete_stmt);
}

std::string SQLiteWrapper::convert_text(const unsigned char *text)
{
    return std::string(reinterpret_cast<const char *>(text));
}

Motor::EfficiencyClass SQLiteWrapper::convert_motor_efficiency_class(int efficiencyClass)
{
    if (efficiencyClass == 0)
    {
        return Motor::EfficiencyClass::STANDARD;
    }
    else if (efficiencyClass == 1)
    {
        return Motor::EfficiencyClass::ENERGY_EFFICIENT;
    }
    else if (efficiencyClass == 2)
    {
        return Motor::EfficiencyClass::PREMIUM;
    }
    else if (efficiencyClass == 3)
    {
        return Motor::EfficiencyClass::SPECIFIED;
    }

    return Motor::EfficiencyClass::STANDARD;
}

Motor::LineFrequency SQLiteWrapper::convert_motor_line_frequency(int lineFrequency)
{
    if (lineFrequency == 60)
    {
        return Motor::LineFrequency::FREQ60;
    }
    else if (lineFrequency == 50)
    {
        return Motor::LineFrequency::FREQ50;
    }

    return Motor::LineFrequency::FREQ60;
}

std::vector<SolidLoadChargeMaterial> SQLite::getSolidLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
        slcm.setID(ID);
        return slcm;
    };
    return get_all_objects<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_stmt, cb);
}

SolidLoadChargeMaterial SQLite::getSolidLoadChargeMaterialById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
        slcm.setID(id);
        return slcm;
    };
    return get_object<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<SolidLoadChargeMaterial> SQLite::getCustomSolidLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
        slcm.setID(ID);
        return slcm;
    };
    return get_all_objects<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_custom_stmt, cb);
}

std::vector<GasLoadChargeMaterial> SQLite::getGasLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_all_objects<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_stmt, cb);
}

GasLoadChargeMaterial SQLite::getGasLoadChargeMaterialById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_object<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<GasLoadChargeMaterial> SQLite::getCustomGasLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_all_objects<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_custom_stmt, cb);
}

std::vector<LiquidLoadChargeMaterial> SQLite::getLiquidLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_all_objects<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_stmt, cb);
}

LiquidLoadChargeMaterial SQLite::getLiquidLoadChargeMaterialById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_object<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<LiquidLoadChargeMaterial> SQLite::getCustomLiquidLoadChargeMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_all_objects<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_custom_stmt, cb);
}

std::vector<SolidLiquidFlueGasMaterial> SQLite::getSolidLiquidFlueGasMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                                o2 * 100, moisture * 100, nitrogen * 100);
        slfgm.setID(id);
        return slfgm;
    };
    return get_all_objects<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_stmt, cb);
}

std::vector<SolidLiquidFlueGasMaterial> SQLite::getCustomSolidLiquidFlueGasMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                                o2 * 100, moisture * 100, nitrogen * 100);
        slfgm.setID(id);
        return slfgm;
    };
    return get_all_objects<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_custom_stmt, cb);
}

SolidLiquidFlueGasMaterial SQLite::getSolidLiquidFlueGasMaterialById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                                o2 * 100, moisture * 100, nitrogen * 100);
        slfgm.setID(id);
        return slfgm;
    };
    return get_object<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_single_stmt, id, cb);
}

std::vector<GasCompositions> SQLite::getGasFlueGasMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_all_objects<GasCompositions>(m_gas_flue_gas_materials_select_stmt, cb);
}

GasCompositions SQLite::getGasFlueGasMaterialById(int id) const
{

    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_object<GasCompositions>(m_gas_flue_gas_materials_select_single_stmt, id, cb);
}

std::vector<GasCompositions> SQLite::getCustomGasFlueGasMaterials() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_all_objects<GasCompositions>(m_gas_flue_gas_materials_select_custom_stmt, cb);
}

std::vector<Atmosphere> SQLite::getAtmosphereSpecificHeat() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_all_objects<Atmosphere>(m_atmosphere_specific_heat_select_stmt, cb);
}

std::vector<Atmosphere> SQLite::getCustomAtmosphereSpecificHeat() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_all_objects<Atmosphere>(m_atmosphere_specific_heat_select_custom_stmt, cb);
}

Atmosphere SQLite::getAtmosphereSpecificHeatById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_object<Atmosphere>(m_atmosphere_specific_heat_select_single_stmt, id, cb);
}

std::vector<WallLosses> SQLite::getWallLossesSurface() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_all_objects<WallLosses>(m_wall_losses_surface_select_stmt, cb);
}

std::vector<WallLosses> SQLite::getCustomWallLossesSurface() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_all_objects<WallLosses>(m_wall_losses_surface_select_custom_stmt, cb);
}

WallLosses SQLite::getWallLossesSurfaceById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_object<WallLosses>(m_wall_losses_surface_select_single_stmt, id, cb);
}

std::vector<MotorData> SQLite::getMotorData() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // sid (secondary id denoting custom)
        auto const hp = sqlite3_column_double(stmt, 2);
        auto const synchronousSpeed = sqlite3_column_int(stmt, 3);
        auto const poles = sqlite3_column_int(stmt, 4);
        auto const nominalEfficiency = sqlite3_column_double(stmt, 5);
        auto const efficiencyClass = convert_motor_efficiency_class(sqlite3_column_int(stmt, 6));
        auto const nemaTable = convert_text(sqlite3_column_text(stmt, 7));
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 8));
        auto const lineFrequency = convert_motor_line_frequency(sqlite3_column_int(stmt, 9));
        auto const voltageLimit = sqlite3_column_int(stmt, 10);
        auto const catalog = convert_text(sqlite3_column_text(stmt, 11));

        auto m = MotorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyClass, nemaTable, enclosureType, lineFrequency, voltageLimit, catalog);
        m.setId(id);
        return m;
    };
    return get_all_objects<MotorData>(m_motor_data_select_stmt, cb);
}

std::vector<MotorData> SQLite::getCustomMotorData() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        auto const hp = sqlite3_column_double(stmt, 2);
        auto const synchronousSpeed = sqlite3_column_int(stmt, 3);
        auto const poles = sqlite3_column_int(stmt, 4);
        auto const nominalEfficiency = sqlite3_column_double(stmt, 5);
        auto const efficiencyClass = convert_motor_efficiency_class(sqlite3_column_int(stmt, 6));
        auto const nemaTable = convert_text(sqlite3_column_text(stmt, 7));
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 8));
        auto const lineFrequency = convert_motor_line_frequency(sqlite3_column_int(stmt, 9));
        auto const voltageLimit = sqlite3_column_int(stmt, 10);
        auto const catalog = convert_text(sqlite3_column_text(stmt, 11));

        auto m = MotorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyClass, nemaTable, enclosureType, lineFrequency, voltageLimit, catalog);
        m.setId(id);
        return m;
    };
    return get_all_objects<MotorData>(m_motor_data_select_custom_stmt, cb);
}

MotorData SQLite::getMotorDataById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const dbId = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        auto const hp = sqlite3_column_double(stmt, 2);
        auto const synchronousSpeed = sqlite3_column_int(stmt, 3);
        auto const poles = sqlite3_column_int(stmt, 4);
        auto const nominalEfficiency = sqlite3_column_double(stmt, 5);
        auto const efficiencyClass = convert_motor_efficiency_class(sqlite3_column_int(stmt, 6));
        auto const nemaTable = convert_text(sqlite3_column_text(stmt, 7));
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 8));
        auto const lineFrequency = convert_motor_line_frequency(sqlite3_column_int(stmt, 9));
        auto const voltageLimit = sqlite3_column_int(stmt, 10);
        auto const catalog = convert_text(sqlite3_column_text(stmt, 11));

        auto m = MotorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyClass, nemaTable, enclosureType, lineFrequency, voltageLimit, catalog);
        m.setId(dbId);
        return m;
    };
    return get_object<MotorData>(m_motor_data_select_single_stmt, id, cb);
}

std::vector<PumpData> SQLite::getPumpData() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // sid (secondary id denoting custom)
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const serialNumber = convert_text(sqlite3_column_text(stmt, 4));
        auto const status = convert_text(sqlite3_column_text(stmt, 5));
        auto const pumpType = convert_text(sqlite3_column_text(stmt, 6));
        auto const shaftOrientation = convert_text(sqlite3_column_text(stmt, 7));
        auto const shaftSealType = convert_text(sqlite3_column_text(stmt, 8));
        auto const fluidType = convert_text(sqlite3_column_text(stmt, 9));
        auto const priority = convert_text(sqlite3_column_text(stmt, 10));
        auto const driveType = convert_text(sqlite3_column_text(stmt, 11));
        auto const flangeConnectionClass = convert_text(sqlite3_column_text(stmt, 12));
        auto const flangeConnectionSize = convert_text(sqlite3_column_text(stmt, 13));
        auto const componentId = convert_text(sqlite3_column_text(stmt, 14));
        auto const system = convert_text(sqlite3_column_text(stmt, 15));
        auto const location = convert_text(sqlite3_column_text(stmt, 16));
        auto const motorEfficiencyClass = convert_text(sqlite3_column_text(stmt, 17));
        auto const speed = sqlite3_column_int(stmt, 18);
        auto const numStages = sqlite3_column_int(stmt, 19);
        auto const yearlyOperatingHours = sqlite3_column_int(stmt, 20);
        auto const yearInstalled = sqlite3_column_int(stmt, 21);
        auto const finalMotorRpm = sqlite3_column_int(stmt, 22);
        auto const motorRatedVoltage = sqlite3_column_int(stmt, 23);
        auto const inletDiameter = sqlite3_column_double(stmt, 24);
        auto const outletDiameter = sqlite3_column_double(stmt, 25);
        auto const staticSuctionHead = sqlite3_column_double(stmt, 26);
        auto const staticDischargeHead = sqlite3_column_double(stmt, 27);
        auto const fluidDensity = sqlite3_column_double(stmt, 28);
        auto const maxWorkingPressure = sqlite3_column_double(stmt, 29);
        auto const maxAmbientTemperature = sqlite3_column_double(stmt, 30);
        auto const maxSuctionLift = sqlite3_column_double(stmt, 31);
        auto const displacement = sqlite3_column_double(stmt, 32);
        auto const startingTorque = sqlite3_column_double(stmt, 33);
        auto const ratedSpeed = sqlite3_column_double(stmt, 34);
        auto const impellerDiameter = sqlite3_column_double(stmt, 35);
        auto const efficiency = sqlite3_column_double(stmt, 36);
        auto const lineFrequency = sqlite3_column_double(stmt, 37);
        auto const minFlowSize = sqlite3_column_double(stmt, 38);
        auto const pumpSize = sqlite3_column_double(stmt, 39);
        auto const designHead = sqlite3_column_double(stmt, 40);
        auto const designFlow = sqlite3_column_double(stmt, 41);
        auto const designEfficiency = sqlite3_column_double(stmt, 42);
        auto const motorRatedPower = sqlite3_column_double(stmt, 43);
        auto const motorFullLoadAmps = sqlite3_column_double(stmt, 44);
        auto const operatingFlowRate = sqlite3_column_double(stmt, 45);
        auto const operatingHead = sqlite3_column_double(stmt, 46);
        auto const measuredCurrent = sqlite3_column_double(stmt, 47);
        auto const measuredPower = sqlite3_column_double(stmt, 48);
        auto const measuredVoltage = sqlite3_column_double(stmt, 49);
        auto const motorEfficiency = sqlite3_column_double(stmt, 50);

        auto pump = PumpData(manufacturer, model, serialNumber, status, pumpType,
                             shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                             flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                             finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                             staticSuctionHead, staticDischargeHead, fluidDensity,
                             maxWorkingPressure, maxAmbientTemperature,
                             maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                             efficiency, lineFrequency, minFlowSize, pumpSize,
                             designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                             operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency);
        pump.setId(id);
        return pump;
    };
    return get_all_objects<PumpData>(m_pump_data_select_stmt, cb);
}

std::vector<PumpData> SQLite::getCustomPumpData() const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // sid (secondary id denoting custom)
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const serialNumber = convert_text(sqlite3_column_text(stmt, 4));
        auto const status = convert_text(sqlite3_column_text(stmt, 5));
        auto const pumpType = convert_text(sqlite3_column_text(stmt, 6));
        auto const shaftOrientation = convert_text(sqlite3_column_text(stmt, 7));
        auto const shaftSealType = convert_text(sqlite3_column_text(stmt, 8));
        auto const fluidType = convert_text(sqlite3_column_text(stmt, 9));
        auto const priority = convert_text(sqlite3_column_text(stmt, 10));
        auto const driveType = convert_text(sqlite3_column_text(stmt, 11));
        auto const flangeConnectionClass = convert_text(sqlite3_column_text(stmt, 12));
        auto const flangeConnectionSize = convert_text(sqlite3_column_text(stmt, 13));
        auto const componentId = convert_text(sqlite3_column_text(stmt, 14));
        auto const system = convert_text(sqlite3_column_text(stmt, 15));
        auto const location = convert_text(sqlite3_column_text(stmt, 16));
        auto const motorEfficiencyClass = convert_text(sqlite3_column_text(stmt, 17));
        auto const speed = sqlite3_column_int(stmt, 18);
        auto const numStages = sqlite3_column_int(stmt, 19);
        auto const yearlyOperatingHours = sqlite3_column_int(stmt, 20);
        auto const yearInstalled = sqlite3_column_int(stmt, 21);
        auto const finalMotorRpm = sqlite3_column_int(stmt, 22);
        auto const motorRatedVoltage = sqlite3_column_int(stmt, 23);
        auto const inletDiameter = sqlite3_column_double(stmt, 24);
        auto const outletDiameter = sqlite3_column_double(stmt, 25);
        auto const staticSuctionHead = sqlite3_column_double(stmt, 26);
        auto const staticDischargeHead = sqlite3_column_double(stmt, 27);
        auto const fluidDensity = sqlite3_column_double(stmt, 28);
        auto const maxWorkingPressure = sqlite3_column_double(stmt, 29);
        auto const maxAmbientTemperature = sqlite3_column_double(stmt, 30);
        auto const maxSuctionLift = sqlite3_column_double(stmt, 31);
        auto const displacement = sqlite3_column_double(stmt, 32);
        auto const startingTorque = sqlite3_column_double(stmt, 33);
        auto const ratedSpeed = sqlite3_column_double(stmt, 34);
        auto const impellerDiameter = sqlite3_column_double(stmt, 35);
        auto const efficiency = sqlite3_column_double(stmt, 36);
        auto const lineFrequency = sqlite3_column_double(stmt, 37);
        auto const minFlowSize = sqlite3_column_double(stmt, 38);
        auto const pumpSize = sqlite3_column_double(stmt, 39);
        auto const designHead = sqlite3_column_double(stmt, 40);
        auto const designFlow = sqlite3_column_double(stmt, 41);
        auto const designEfficiency = sqlite3_column_double(stmt, 42);
        auto const motorRatedPower = sqlite3_column_double(stmt, 43);
        auto const motorFullLoadAmps = sqlite3_column_double(stmt, 44);
        auto const operatingFlowRate = sqlite3_column_double(stmt, 45);
        auto const operatingHead = sqlite3_column_double(stmt, 46);
        auto const measuredCurrent = sqlite3_column_double(stmt, 47);
        auto const measuredPower = sqlite3_column_double(stmt, 48);
        auto const measuredVoltage = sqlite3_column_double(stmt, 49);
        auto const motorEfficiency = sqlite3_column_double(stmt, 50);

        auto pump = PumpData(manufacturer, model, serialNumber, status, pumpType,
                             shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                             flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                             finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                             staticSuctionHead, staticDischargeHead, fluidDensity,
                             maxWorkingPressure, maxAmbientTemperature,
                             maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                             efficiency, lineFrequency, minFlowSize, pumpSize,
                             designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                             operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency);
        pump.setId(id);
        return pump;
    };
    return get_all_objects<PumpData>(m_pump_data_select_custom_stmt, cb);
}

PumpData SQLite::getPumpDataById(int id) const
{
    auto cb = [](sqlite3_stmt *stmt) {
        auto const dbId = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // sid (secondary id denoting custom)
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const serialNumber = convert_text(sqlite3_column_text(stmt, 4));
        auto const status = convert_text(sqlite3_column_text(stmt, 5));
        auto const pumpType = convert_text(sqlite3_column_text(stmt, 6));
        auto const shaftOrientation = convert_text(sqlite3_column_text(stmt, 7));
        auto const shaftSealType = convert_text(sqlite3_column_text(stmt, 8));
        auto const fluidType = convert_text(sqlite3_column_text(stmt, 9));
        auto const priority = convert_text(sqlite3_column_text(stmt, 10));
        auto const driveType = convert_text(sqlite3_column_text(stmt, 11));
        auto const flangeConnectionClass = convert_text(sqlite3_column_text(stmt, 12));
        auto const flangeConnectionSize = convert_text(sqlite3_column_text(stmt, 13));
        auto const componentId = convert_text(sqlite3_column_text(stmt, 14));
        auto const system = convert_text(sqlite3_column_text(stmt, 15));
        auto const location = convert_text(sqlite3_column_text(stmt, 16));
        auto const motorEfficiencyClass = convert_text(sqlite3_column_text(stmt, 17));
        auto const speed = sqlite3_column_int(stmt, 18);
        auto const numStages = sqlite3_column_int(stmt, 19);
        auto const yearlyOperatingHours = sqlite3_column_int(stmt, 20);
        auto const yearInstalled = sqlite3_column_int(stmt, 21);
        auto const finalMotorRpm = sqlite3_column_int(stmt, 22);
        auto const motorRatedVoltage = sqlite3_column_int(stmt, 23);
        auto const inletDiameter = sqlite3_column_double(stmt, 24);
        auto const outletDiameter = sqlite3_column_double(stmt, 25);
        auto const staticSuctionHead = sqlite3_column_double(stmt, 26);
        auto const staticDischargeHead = sqlite3_column_double(stmt, 27);
        auto const fluidDensity = sqlite3_column_double(stmt, 28);
        auto const maxWorkingPressure = sqlite3_column_double(stmt, 29);
        auto const maxAmbientTemperature = sqlite3_column_double(stmt, 30);
        auto const maxSuctionLift = sqlite3_column_double(stmt, 31);
        auto const displacement = sqlite3_column_double(stmt, 32);
        auto const startingTorque = sqlite3_column_double(stmt, 33);
        auto const ratedSpeed = sqlite3_column_double(stmt, 34);
        auto const impellerDiameter = sqlite3_column_double(stmt, 35);
        auto const efficiency = sqlite3_column_double(stmt, 36);
        auto const lineFrequency = sqlite3_column_double(stmt, 37);
        auto const minFlowSize = sqlite3_column_double(stmt, 38);
        auto const pumpSize = sqlite3_column_double(stmt, 39);
        auto const designHead = sqlite3_column_double(stmt, 40);
        auto const designFlow = sqlite3_column_double(stmt, 41);
        auto const designEfficiency = sqlite3_column_double(stmt, 42);
        auto const motorRatedPower = sqlite3_column_double(stmt, 43);
        auto const motorFullLoadAmps = sqlite3_column_double(stmt, 44);
        auto const operatingFlowRate = sqlite3_column_double(stmt, 45);
        auto const operatingHead = sqlite3_column_double(stmt, 46);
        auto const measuredCurrent = sqlite3_column_double(stmt, 47);
        auto const measuredPower = sqlite3_column_double(stmt, 48);
        auto const measuredVoltage = sqlite3_column_double(stmt, 49);
        auto const motorEfficiency = sqlite3_column_double(stmt, 50);

        auto pump = PumpData(manufacturer, model, serialNumber, status, pumpType,
                             shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                             flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                             finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                             staticSuctionHead, staticDischargeHead, fluidDensity,
                             maxWorkingPressure, maxAmbientTemperature,
                             maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                             efficiency, lineFrequency, minFlowSize, pumpSize,
                             designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                             operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency);
        pump.setId(dbId);
        return pump;
    };
    return get_object<PumpData>(m_pump_data_select_single_stmt, id, cb);
}

void SQLite::create_select_stmt()
{
    std::string const select_solid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials)";

    prepare_statement(m_solid_load_charge_materials_select_stmt, select_solid_load_charge_materials);

    std::string const select_single_solid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_solid_load_charge_materials_select_single_stmt, select_single_solid_load_charge_materials);

    std::string const select_custom_solid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_solid_load_charge_materials_select_custom_stmt, select_custom_solid_load_charge_materials);

    std::string const select_gas_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials)";

    prepare_statement(m_gas_load_charge_materials_select_stmt, select_gas_load_charge_materials);

    std::string const select_single_gas_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_gas_load_charge_materials_select_single_stmt, select_single_gas_load_charge_materials);

    std::string const select_custom_gas_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_gas_load_charge_materials_select_custom_stmt, select_custom_gas_load_charge_materials);

    std::string const select_liquid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials)";

    prepare_statement(m_liquid_load_charge_materials_select_stmt, select_liquid_load_charge_materials);

    std::string const select_single_liquid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_liquid_load_charge_materials_select_single_stmt, select_single_liquid_load_charge_materials);

    std::string const select_custom_liquid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_liquid_load_charge_materials_select_custom_stmt, select_custom_liquid_load_charge_materials);

    std::string const select_solid_liquid_flue_gas_materials =
        R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_stmt, select_solid_liquid_flue_gas_materials);

    std::string const select_single_solid_liquid_flue_gas_materials =
        R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_single_stmt, select_single_solid_liquid_flue_gas_materials);

    std::string const select_custom_solid_liquid_flue_gas_materials =
        R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials
           WHERE sid = 1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_custom_stmt, select_custom_solid_liquid_flue_gas_materials);

    std::string const select_gas_flue_gas_materials =
        R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials)";

    prepare_statement(m_gas_flue_gas_materials_select_stmt, select_gas_flue_gas_materials);

    std::string const select_single_gas_flue_gas_materials =
        R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_gas_flue_gas_materials_select_single_stmt, select_single_gas_flue_gas_materials);

    std::string const select_custom_gas_flue_gas_materials =
        R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials
           WHERE sid = 1)";

    prepare_statement(m_gas_flue_gas_materials_select_custom_stmt, select_custom_gas_flue_gas_materials);

    std::string const select_atmosphere_specific_heat =
        R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat)";

    prepare_statement(m_atmosphere_specific_heat_select_stmt, select_atmosphere_specific_heat);

    std::string const select_single_atmosphere_specific_heat =
        R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat
           WHERE id = ?)";

    prepare_statement(m_atmosphere_specific_heat_select_single_stmt, select_single_atmosphere_specific_heat);

    std::string const select_custom_atmosphere_specific_heat =
        R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat
           WHERE sid = 1)";

    prepare_statement(m_atmosphere_specific_heat_select_custom_stmt, select_custom_atmosphere_specific_heat);

    std::string const select_wall_losses_surface =
        R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface)";

    prepare_statement(m_wall_losses_surface_select_stmt, select_wall_losses_surface);

    std::string const select_single_wall_losses_surface =
        R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface
           WHERE id = ?)";

    prepare_statement(m_wall_losses_surface_select_single_stmt, select_single_wall_losses_surface);

    std::string const select_custom_wall_losses_surface =
        R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface
           WHERE sid = 1)";

    prepare_statement(m_wall_losses_surface_select_custom_stmt, select_custom_wall_losses_surface);

    std::string const select_motor_data =
        R"(SELECT id, sid, hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, enclosureType, hz, 
                voltagelimit, catalog
            FROM motor_data)";

    prepare_statement(m_motor_data_select_stmt, select_motor_data);

    std::string const select_single_motor_data =
        R"(SELECT id, sid, hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, enclosureType, hz, 
                voltagelimit, catalog
           FROM motor_data
           WHERE id = ?)";

    prepare_statement(m_motor_data_select_single_stmt, select_single_motor_data);

    std::string const select_custom_motor_data =
        R"(SELECT id, sid, hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, enclosureType, hz, 
                voltagelimit, catalog
           FROM motor_data
           WHERE sid = 1)";

    prepare_statement(m_motor_data_select_custom_stmt, select_custom_motor_data);

// debugger
    std::string const select_pump_data =
        R"(SELECT id, sid, 
                      manufacturer, model, serialNumber, status, pumpType,
                      shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                      flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                      finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                      staticSuctionHead, staticDischargeHead, fluidDensity,
                      maxWorkingPressure, maxAmbientTemperature,
                      maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                      efficiency, lineFrequency, minFlowSize, pumpSize,
                      designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                      operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency
            FROM pump_data)";

    prepare_statement(m_pump_data_select_stmt, select_pump_data);

    std::string const select_single_pump_data =
        R"(SELECT id, sid, 
                      manufacturer, model, serialNumber, status, pumpType,
                      shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                      flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                      finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                      staticSuctionHead, staticDischargeHead, fluidDensity,
                      maxWorkingPressure, maxAmbientTemperature,
                      maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                      efficiency, lineFrequency, minFlowSize, pumpSize,
                      designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                      operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency
            FROM pump_data
            WHERE id = ?)";

    prepare_statement(m_pump_data_select_single_stmt, select_single_pump_data);

    std::string const select_custom_pump_data =
        R"(SELECT id, sid, 
            manufacturer, model, serialNumber, status, pumpType,
            shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
            flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
            finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
            staticSuctionHead, staticDischargeHead, fluidDensity,
            maxWorkingPressure, maxAmbientTemperature,
            maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
            efficiency, lineFrequency, minFlowSize, pumpSize,
            designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
            operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency
            FROM pump_data
            WHERE sid = 1)";

    prepare_statement(m_pump_data_select_custom_stmt, select_custom_pump_data);
}

void SQLite::create_update_and_delete_stmt()
{
    std::string const delete_solid_load_charge_materials =
        R"(DELETE from solid_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_solid_load_charge_materials_delete_stmt, delete_solid_load_charge_materials);

    std::string const update_custom_solid_load_charge_materials =
        R"(UPDATE solid_load_charge_materials
               SET substance=?, mean_specific_heat_of_solid=?, latent_heat_of_fusion=?, mean_specific_heat_of_liquid=?, melting_point=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_solid_load_charge_materials_update_stmt, update_custom_solid_load_charge_materials);

    std::string const delete_gas_load_charge_materials =
        R"(DELETE from gas_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_gas_load_charge_materials_delete_stmt, delete_gas_load_charge_materials);

    std::string const update_gas_load_charge_materials =
        R"(UPDATE gas_load_charge_materials
               SET substance=?, mean_specific_heat_of_vapor=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_gas_load_charge_materials_update_stmt, update_gas_load_charge_materials);

    std::string const delete_liquid_load_charge_materials =
        R"(DELETE from liquid_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_liquid_load_charge_materials_delete_stmt, delete_liquid_load_charge_materials);

    std::string const update_liquid_load_charge_materials =
        R"(UPDATE liquid_load_charge_materials
               SET substance=?, mean_specific_heat_of_liquid=?, latent_heat_of_vaporisation=?, mean_specific_heat_of_vapor=?, boiling_point=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_liquid_load_charge_materials_update_stmt, update_liquid_load_charge_materials);

    std::string const delete_solid_liquid_flue_gas_materials =
        R"(DELETE from solid_liquid_flue_gas_materials where id=? and sid=1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_delete_stmt, delete_solid_liquid_flue_gas_materials);

    std::string const update_solid_liquid_flue_gas_materials =
        R"(UPDATE solid_liquid_flue_gas_materials
               SET substance=?, carbon=?, hydrogen=?, nitrogen=?, sulfur=?, oxygen=?, moisture=?, ash=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_update_stmt, update_solid_liquid_flue_gas_materials);

    std::string const delete_gas_flue_gas_materials =
        R"(DELETE from gas_flue_gas_materials where id=? and sid=1)";

    prepare_statement(m_gas_flue_gas_materials_delete_stmt, delete_gas_flue_gas_materials);

    std::string const update_gas_flue_gas_materials =
        R"(UPDATE gas_flue_gas_materials
               SET substance=?, hydrogen=?, methane=?, ethylene=?, ethane=?, sulfur_dioxide=?, carbon_monoxide=?,
               carbon_dioxide=?, nitrogen=?, oxygen=?, hydrogen_sulfide=?, benzene=?, heatingValue=?,
               heatingValueVolume=?, specificGravity=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_gas_flue_gas_materials_update_stmt, update_gas_flue_gas_materials);

    std::string const delete_atmosphere_specific_heat =
        R"(DELETE from atmosphere_specific_heat where id=? and sid=1)";

    prepare_statement(m_atmosphere_specific_heat_delete_stmt, delete_atmosphere_specific_heat);

    std::string const update_atmosphere_specific_heat =
        R"(UPDATE atmosphere_specific_heat
               SET substance=?, specificHeat=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_atmosphere_specific_heat_update_stmt, update_atmosphere_specific_heat);

    std::string const delete_wall_losses_surface =
        R"(DELETE from wall_losses_surface where id=? and sid=1)";

    prepare_statement(m_wall_losses_surface_delete_stmt, delete_wall_losses_surface);

    std::string const update_wall_losses_surface =
        R"(UPDATE wall_losses_surface
               SET surface=?, conditionFactor=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_wall_losses_surface_update_stmt, update_wall_losses_surface);

    std::string const delete_motor_data =
        R"(DELETE from motor_data where id=? and sid=1)";

    prepare_statement(m_motor_data_delete_stmt, delete_motor_data);

    std::string const update_motor_data =
        R"(UPDATE motor_data
               SET hp=?, synchronousSpeed=?, poles=?, nominalEfficiency=?, efficiencyType=?, nemaTable=?, enclosureType=?,
               hz=?, voltageLimit=?, catalog=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_motor_data_update_stmt, update_motor_data);

    std::string const delete_pump_data =
        R"(DELETE from pump_data where id=? and sid=1)";

    prepare_statement(m_pump_data_delete_stmt, delete_pump_data);

    std::string const update_pump_data =
        R"(UPDATE pump_data
               SET manufacturer=?, model=?, serialNumber=?, status=?, pumpType=?,
               shaftOrientation=?, shaftSealType=?, fluidType=?, priority=?, driveType=?, flangeConnectionClass=?,
               flangeConnectionSize=?, componentId=?, system=?, location=?, motorEfficiencyClass=?, speed=?, numStages=?, yearlyOperatingHours=?, yearInstalled=?,
               finalMotorRpm=?, motorRatedVoltage=?, inletDiameter=?, outletDiameter=?, staticSuctionHead=?, staticDischargeHead=?, fluidDensity=?,
               maxWorkingPressure=?, maxAmbientTemperature=?,
               maxSuctionLift=?, displacement=?, startingTorque=?, ratedSpeed=?, impellerDiameter=?,
               efficiency=?, lineFrequency=?, minFlowSize=?, pumpSize=?, 
               designHead=?, designFlow=?, designEfficiency=?, motorRatedPower=?, motorFullLoadAmps=?, 
               operatingFlowRate=?, operatingHead=?, measuredCurrent=?, measuredPower=?, measuredVoltage=?, motorEfficiency=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_pump_data_update_stmt, update_pump_data);
}

void SQLite::create_insert_stmt()
{
    const std::string solid_load_charge_materials_insert_sql =
        R"(INSERT INTO solid_load_charge_materials(sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                                                   mean_specific_heat_of_liquid, melting_point)
           VALUES (?,?,?,?,?,?))";

    prepare_statement(m_solid_load_charge_materials_insert_stmt, solid_load_charge_materials_insert_sql);

    const std::string gas_load_charge_materials_insert_sql =
        R"(INSERT INTO gas_load_charge_materials(sid, substance,mean_specific_heat_of_vapor) VALUES (?,?,?))";

    prepare_statement(m_gas_load_charge_materials_insert_stmt, gas_load_charge_materials_insert_sql);

    const std::string liquid_load_charge_materials_insert_sql =
        R"(INSERT INTO liquid_load_charge_materials(sid, substance, mean_specific_heat_of_liquid,
                                                    latent_heat_of_vaporisation, mean_specific_heat_of_vapor,
                                                    boiling_point)
           VALUES (?,?,?,?,?,?))";

    prepare_statement(m_liquid_load_charge_materials_insert_stmt, liquid_load_charge_materials_insert_sql);

    const std::string solid_liquid_flue_gas_materials_insert_sql =
        R"(INSERT INTO solid_liquid_flue_gas_materials(sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen,
                                                       moisture, ash)
           VALUES (?,?,?,?,?,?,?,?,?))";

    prepare_statement(m_solid_liquid_flue_gas_materials_insert_stmt, solid_liquid_flue_gas_materials_insert_sql);

    const std::string gas_flue_gas_materials_insert_sql =
        R"(INSERT INTO gas_flue_gas_materials(sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity)
           VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?))";

    prepare_statement(m_gas_flue_gas_materials_insert_stmt, gas_flue_gas_materials_insert_sql);

    const std::string atmosphere_specific_heat_insert_sql =
        R"(INSERT INTO atmosphere_specific_heat(sid, substance, specificHeat)
           VALUES (?,?,?))";

    prepare_statement(m_atmosphere_specific_heat_insert_stmt, atmosphere_specific_heat_insert_sql);

    const std::string wall_losses_surface_insert_sql =
        R"(INSERT INTO wall_losses_surface(sid, surface, conditionFactor)
           VALUES (?,?,?))";

    prepare_statement(m_wall_losses_surface_insert_stmt, wall_losses_surface_insert_sql);

    const std::string motor_data_insert_sql =
        R"(INSERT INTO motor_data(sid, hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, enclosureType,
                hz, voltageLimit, catalog)
           VALUES (?,?,?,?,?,?,?,?,?,?,?))";

    // 11 entries

    prepare_statement(m_motor_data_insert_stmt, motor_data_insert_sql);

    const std::string pump_data_insert_sql =
         R"(INSERT INTO pump_data(
         sid, 
         manufacturer, 
         model, 
         serialNumber, 
         status, 
         pumpType, 
         shaftOrientation, 
         shaftSealType, 
         fluidType, 
         priority, 
         driveType, 
         flangeConnectionClass,
         flangeConnectionSize,
         componentId,
         system,
         location,
         motorEfficiencyClass,
         speed, 
         numStages, 
         yearlyOperatingHours, 
         yearInstalled,
         finalMotorRpm,
         motorRatedVoltage,
         inletDiameter, 
         outletDiameter, 
         staticSuctionHead, 
         staticDischargeHead, 
         fluidDensity,
         maxWorkingPressure, 
         maxAmbientTemperature,
         maxSuctionLift, 
         displacement, 
         startingTorque, 
         ratedSpeed, 
         impellerDiameter,
         efficiency, 
         lineFrequency, 
         minFlowSize, 
         pumpSize, 
         designHead, 
         designFlow, 
         designEfficiency, 
         motorRatedPower, 
         motorFullLoadAmps, 
         operatingFlowRate, 
         operatingHead, 
         measuredCurrent,
         measuredPower, 
         measuredVoltage,
         motorEfficiency)
           VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?))";


    prepare_statement(m_pump_data_insert_stmt, pump_data_insert_sql);
}

void SQLite::create_tables()
{
    const std::string solid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_load_charge_materials (
           id integer PRIMARY KEY AUTOINCREMENT,
           sid integer NOT NULL,
           substance text NOT NULL DEFAULT "" UNIQUE,
           mean_specific_heat_of_solid real NOT NULL, -- Btu/lb.F
           latent_heat_of_fusion real NOT NULL, -- Btu/lb.
           mean_specific_heat_of_liquid real NOT NULL, -- Btu/lb.F
           melting_point real NOT NULL, -- F.
           UNIQUE (substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                   mean_specific_heat_of_liquid, melting_point)
                  );)";

    execute_command(solid_load_charge_materials_table_sql);

    const std::string gas_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             UNIQUE (substance, mean_specific_heat_of_vapor)
            );)";

    execute_command(gas_load_charge_materials_table_sql);

    const std::string liquid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS liquid_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             mean_specific_heat_of_liquid real NOT NULL, -- kJ/kg.F
             latent_heat_of_vaporisation real NOT NULL, -- Btu/lb.
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             boiling_point real NOT NULL, -- F.
             UNIQUE (substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                     mean_specific_heat_of_vapor, boiling_point)
          );)";

    execute_command(liquid_load_charge_materials_table_sql);

    const std::string solid_liquid_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_liquid_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             carbon real NOT NULL, --C
             hydrogen real NOT NULL, -- H2
             nitrogen real NOT NULL, -- N2
             sulfur real NOT NULL, -- S
             oxygen real NOT NULL, -- O2
             moisture real NOT NULL, -- H20
             ash real NOT NULL, -- ash
             UNIQUE (substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash)
      );)";

    execute_command(solid_liquid_flue_gas_materials_table_sql);

    const std::string gas_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             hydrogen real NOT NULL, -- H2
             methane real NOT NULL, -- CH4
             ethylene real NOT NULL, -- C2H4
             ethane real NOT NULL, -- C2H6
             sulfur_dioxide real NOT NULL, -- SO2
             carbon_monoxide real NOT NULL, -- CO
             carbon_dioxide real NOT NULL, -- CO2
             nitrogen real NOT NULL, -- N2
             oxygen real NOT NULL, -- O2
             hydrogen_sulfide real NOT NULL, -- H2S
             benzene real NOT NULL, -- C2H4
             heatingValue real NOT NULL, -- HV
             heatingValueVolume real NOT NULL, -- HvVolume
             specificGravity real NOT NULL, -- specificGrav
             UNIQUE (substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide, carbon_monoxide, carbon_dioxide,
                     nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity)
      );)";

    execute_command(gas_flue_gas_materials_table_sql);

    const std::string atmosphere_specific_heat_table_sql =
        R"(CREATE TABLE IF NOT EXISTS atmosphere_specific_heat (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             specificHeat real NOT NULL, -- Btu/(scf.F)
             UNIQUE (substance, specificHeat)
      );)";

    execute_command(atmosphere_specific_heat_table_sql);

    const std::string wall_losses_surface_table_sql =
        R"(CREATE TABLE IF NOT EXISTS wall_losses_surface (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             surface text NOT NULL DEFAULT "" UNIQUE,
             conditionFactor real NOT NULL, -- unitless
             UNIQUE (surface, conditionFactor)
      );)";

    execute_command(wall_losses_surface_table_sql);

    const std::string motor_table_sql =
        R"(CREATE TABLE IF NOT EXISTS motor_data (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             hp integer NOT NULL DEFAULT 1,
             synchronousSpeed integer NOT NULL,
             poles integer NOT NULL,
             nominalEfficiency real NOT NULL,
             efficiencyType text NOT NULL,
             nemaTable text NOT NULL,
             enclosureType text NOT NULL,
             hz integer NOT NULL,
             voltageLimit integer NOT NULL,
             catalog text NOT NULL,
             UNIQUE (hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, enclosureType, hz, voltageLimit, catalog)
      );)";

    execute_command(motor_table_sql);

    const std::string pump_table_sql =
        R"(CREATE TABLE IF NOT EXISTS pump_data (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             manufacturer text NOT NULL,
             model text NOT NULL,
             serialNumber text NOT NULL,
             status text NOT NULL,
             pumpType text NOT NULL,
             shaftOrientation text NOT NULL,
             shaftSealType text NOT NULL,
             fluidType text NOT NULL,
             priority text NOT NULL,
             driveType text NOT NULL,
             flangeConnectionClass text NOT NULL,
             flangeConnectionSize text NOT NULL,
             componentId text NOT NULL,
             system text NOT NULL,
             location text NOT NULL,
             motorEfficiencyClass text NOT NULL,
             speed integer NOT NULL,
             numStages integer NOT NULL,
             yearlyOperatingHours integer NOT NULL,
             yearInstalled integer NOT NULL,
             finalMotorRpm integer NOT NULL,
             motorRatedVoltage integer NOT NULL,
             inletDiameter real NOT NULL,
             outletDiameter real NOT NULL,
             staticSuctionHead real NOT NULL,
             staticDischargeHead real NOT NULL,
             fluidDensity real NOT NULL,
             maxWorkingPressure real NOT NULL,
             maxAmbientTemperature real NOT NULL,
             maxSuctionLift real NOT NULL,
             displacement real NOT NULL,
             startingTorque real NOT NULL,
             ratedSpeed real NOT NULL,
             impellerDiameter real NOT NULL,
             efficiency real NOT NULL,
             lineFrequency real NOT NULL,
             minFlowSize real NOT NULL,
             pumpSize real NOT NULL,
             designHead real NOT NULL,
             designFlow real NOT NULL,
             designEfficiency real NOT NULL,
             motorRatedPower real NOT NULL,
             motorFullLoadAmps real NOT NULL,
             operatingFlowRate real NOT NULL,
             operatingHead real NOT NULL,
             measuredCurrent real NOT NULL,
             measuredPower real NOT NULL,
             measuredVoltage real NOT NULL,
             motorEfficiency real NOT NULL,
             UNIQUE (manufacturer, model, serialNumber, status, pumpType,
                    shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass,
                    flangeConnectionSize, componentId, system, location, motorEfficiencyClass, speed, numStages, yearlyOperatingHours, yearInstalled,
                    finalMotorRpm, motorRatedVoltage, inletDiameter, outletDiameter,
                    staticSuctionHead, staticDischargeHead, fluidDensity,
                    maxWorkingPressure, maxAmbientTemperature,
                    maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter,
                    efficiency, lineFrequency, minFlowSize, pumpSize,
                    designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, 
                    operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency)
      );)";

    execute_command(pump_table_sql);
}

void SQLite::insert_default_data()
{
    std::cout << std::flush;
    for (auto const &material : get_default_solid_load_charge_materials())
    {
        insert_solid_load_charge_materials(material);
    }
    for (auto const &material : get_default_gas_load_charge_materials())
    {
        insert_gas_load_charge_materials(material);
    }
    for (auto const &material : get_default_liquid_load_charge_materials())
    {
        insert_liquid_load_charge_materials(material);
    }
    for (auto const &material : get_default_solid_liquid_flue_gas_materials())
    {
        insert_solid_liquid_flue_gas_materials(material);
    }
    for (auto const &material : get_default_gas_flue_gas_materials())
    {
        insert_gas_flue_gas_materials(material);
    }
    for (auto const &material : get_default_atmosphere_specific_heat())
    {
        insert_atmosphere_specific_heat(material);
    }
    for (auto const &surface : get_default_wall_losses_surface())
    {
        insert_wall_losses_surface(surface);
    }
    for (auto const &motor : get_default_motor_data())
    {
        insert_motor_data(motor);
    }
    ///*
    // On Linux at least, if this ofstream variable is declared, pump table default data correctly populates. If it is not declared, the pump default
    // data does not populate. Note that this is true only for the bindings/JS unit tests. C++ unit tests work fine in any case.
    std::ofstream fout;
    //fout.open("debug.txt", std::ios::app);
    std::cout << std::flush;
    for (auto const &pump : get_default_pump_data())
    {  
        insert_pump_data(pump);
    }
    //*/
}

bool SQLite::insert_solid_load_charge_materials(SolidLoadChargeMaterial const &material)
{
    bind_value(m_solid_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_solid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 6, material.getMeltingPoint());

    int rc = step_command(m_solid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertSolidLoadChargeMaterials(SolidLoadChargeMaterial const &material)
{
    bind_value(m_solid_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_solid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 6, material.getMeltingPoint());

    int rc = step_command(m_solid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteSolidLoadChargeMaterial(const int id)
{
    if (isDefaultMaterial(id, get_default_solid_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_solid_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_solid_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateSolidLoadChargeMaterial(SolidLoadChargeMaterial const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_solid_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_solid_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_solid_load_charge_materials_update_stmt, 2, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_update_stmt, 3, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_update_stmt, 4, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_update_stmt, 5, material.getMeltingPoint());
    bind_value(m_solid_load_charge_materials_update_stmt, 6, material.getID());

    int rc = step_command(m_solid_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_gas_load_charge_materials(GasLoadChargeMaterial const &material)
{
    bind_value(m_gas_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_gas_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_gas_load_charge_materials_insert_stmt, 3, material.getSpecificHeatVapor());

    int rc = step_command(m_gas_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertGasLoadChargeMaterials(GasLoadChargeMaterial const &material)
{
    bind_value(m_gas_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_gas_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_gas_load_charge_materials_insert_stmt, 3, material.getSpecificHeatVapor());

    int rc = step_command(m_gas_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteGasLoadChargeMaterial(int const id)
{
    if (isDefaultMaterial(id, get_default_gas_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_gas_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_gas_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateGasLoadChargeMaterial(GasLoadChargeMaterial const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_gas_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_gas_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_gas_load_charge_materials_update_stmt, 2, material.getSpecificHeatVapor());
    bind_value(m_gas_load_charge_materials_update_stmt, 3, material.getID());

    int rc = step_command(m_gas_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_liquid_load_charge_materials(LiquidLoadChargeMaterial const &material)
{
    bind_value(m_liquid_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_liquid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 6, material.getVaporizingTemperature());

    int rc = step_command(m_liquid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertLiquidLoadChargeMaterials(LiquidLoadChargeMaterial const &material)
{
    bind_value(m_liquid_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_liquid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 6, material.getVaporizingTemperature());

    int rc = step_command(m_liquid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteLiquidLoadChargeMaterial(const int id)
{
    if (isDefaultMaterial(id, get_default_liquid_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_liquid_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_liquid_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateLiquidLoadChargeMaterial(LiquidLoadChargeMaterial const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_liquid_load_charge_materials().size()))
    {
        return false;
    }
    bind_value(m_liquid_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_update_stmt, 2, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_update_stmt, 3, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_update_stmt, 4, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_update_stmt, 5, material.getVaporizingTemperature());
    bind_value(m_liquid_load_charge_materials_update_stmt, 6, material.getID());

    int rc = step_command(m_liquid_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_solid_liquid_flue_gas_materials(SolidLiquidFlueGasMaterial const &material)
{
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 1, 0);
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 3, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 4, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 6, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 7, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 8, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 9, material.getNitrogen());

    int rc = step_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insertSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const &material) const
{
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 1, 1);
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 3, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 4, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 6, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 7, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 8, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 9, material.getNitrogen());

    int rc = step_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteSolidLiquidFlueGasMaterial(const int id)
{
    if (isDefaultMaterial(id, get_default_solid_liquid_flue_gas_materials().size()))
    {
        return false;
    }
    bind_value(m_solid_liquid_flue_gas_materials_delete_stmt, 1, id);
    int rc = step_command(m_solid_liquid_flue_gas_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_solid_liquid_flue_gas_materials().size()))
    {
        return false;
    }
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 2, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 3, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 4, material.getNitrogen());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 6, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 7, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 8, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 9, material.getID());

    int rc = step_command(m_solid_liquid_flue_gas_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_gas_flue_gas_materials(GasCompositions const &comps)
{
    bind_value(m_gas_flue_gas_materials_insert_stmt, 1, 0);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 2, comps.getSubstance());
    bind_value(m_gas_flue_gas_materials_insert_stmt, 3, comps.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 4, comps.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 5, comps.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 6, comps.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 7, comps.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 8, comps.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 9, comps.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 10, comps.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 11, comps.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 12, comps.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 13, comps.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 14, comps.heatingValue);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 15, comps.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 16, comps.specificGravity);

    int rc = step_command(m_gas_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertGasFlueGasMaterial(GasCompositions const &comps) const
{
    bind_value(m_gas_flue_gas_materials_insert_stmt, 1, 1);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 2, comps.getSubstance());
    bind_value(m_gas_flue_gas_materials_insert_stmt, 3, comps.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 4, comps.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 5, comps.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 6, comps.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 7, comps.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 8, comps.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 9, comps.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 10, comps.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 11, comps.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 12, comps.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 13, comps.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 14, comps.heatingValue);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 15, comps.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 16, comps.specificGravity);

    int rc = step_command(m_gas_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteGasFlueGasMaterial(const int id)
{
    if (isDefaultMaterial(id, get_default_gas_flue_gas_materials().size()))
    {
        return false;
    }
    bind_value(m_gas_flue_gas_materials_delete_stmt, 1, id);
    int rc = step_command(m_gas_flue_gas_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateGasFlueGasMaterial(GasCompositions const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_gas_flue_gas_materials().size()))
    {
        return false;
    }
    bind_value(m_gas_flue_gas_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_gas_flue_gas_materials_update_stmt, 2, material.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 3, material.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 4, material.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 5, material.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 6, material.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 7, material.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 8, material.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 9, material.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 10, material.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 11, material.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 12, material.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 13, material.heatingValue);
    bind_value(m_gas_flue_gas_materials_update_stmt, 14, material.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_update_stmt, 15, material.specificGravity);
    bind_value(m_gas_flue_gas_materials_update_stmt, 16, material.getID());

    int rc = step_command(m_gas_flue_gas_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_atmosphere_specific_heat(Atmosphere const &sh)
{
    bind_value(m_atmosphere_specific_heat_insert_stmt, 1, 0);
    bind_value(m_atmosphere_specific_heat_insert_stmt, 2, sh.getSubstance());
    bind_value(m_atmosphere_specific_heat_insert_stmt, 3, sh.getSpecificHeat());

    int rc = step_command(m_atmosphere_specific_heat_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_insert_stmt);
    return valid_insert;
}

// part of the public API used to insert custom materials
bool SQLite::insertAtmosphereSpecificHeat(Atmosphere const &material)
{
    bind_value(m_atmosphere_specific_heat_insert_stmt, 1, 1);
    bind_value(m_atmosphere_specific_heat_insert_stmt, 2, material.getSubstance());
    bind_value(m_atmosphere_specific_heat_insert_stmt, 3, material.getSpecificHeat());

    int rc = step_command(m_atmosphere_specific_heat_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteAtmosphereSpecificHeat(const int id)
{
    if (isDefaultMaterial(id, get_default_atmosphere_specific_heat().size()))
    {
        return false;
    }
    bind_value(m_atmosphere_specific_heat_delete_stmt, 1, id);
    int rc = step_command(m_atmosphere_specific_heat_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_delete_stmt);
    return valid_command;
}

bool SQLite::updateAtmosphereSpecificHeat(Atmosphere const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_atmosphere_specific_heat().size()))
    {
        return false;
    }
    bind_value(m_atmosphere_specific_heat_update_stmt, 1, material.getSubstance());
    bind_value(m_atmosphere_specific_heat_update_stmt, 2, material.getSpecificHeat());
    bind_value(m_atmosphere_specific_heat_update_stmt, 3, material.getID());

    int rc = step_command(m_atmosphere_specific_heat_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_update_stmt);
    return valid_insert;
}

bool SQLite::insert_wall_losses_surface(WallLosses const &cf)
{
    bind_value(m_wall_losses_surface_insert_stmt, 1, 0);
    bind_value(m_wall_losses_surface_insert_stmt, 2, cf.getSurface());
    bind_value(m_wall_losses_surface_insert_stmt, 3, cf.getConditionFactor());

    int rc = step_command(m_wall_losses_surface_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_insert_stmt);
    return valid_insert;
}

bool SQLite::insertWallLossesSurface(WallLosses const &material)
{
    bind_value(m_wall_losses_surface_insert_stmt, 1, 1);
    bind_value(m_wall_losses_surface_insert_stmt, 2, material.getSurface());
    bind_value(m_wall_losses_surface_insert_stmt, 3, material.getConditionFactor());

    int rc = step_command(m_wall_losses_surface_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteWallLossesSurface(int id)
{
    if (isDefaultMaterial(id, get_default_wall_losses_surface().size()))
    {
        return false;
    }
    bind_value(m_wall_losses_surface_delete_stmt, 1, id);
    int rc = step_command(m_wall_losses_surface_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_wall_losses_surface_delete_stmt);
    return valid_command;
}

bool SQLite::updateWallLossesSurface(WallLosses const &material)
{
    if (isDefaultMaterial(material.getID(), get_default_wall_losses_surface().size()))
    {
        return false;
    }
    bind_value(m_wall_losses_surface_update_stmt, 1, material.getSurface());
    bind_value(m_wall_losses_surface_update_stmt, 2, material.getConditionFactor());
    bind_value(m_wall_losses_surface_update_stmt, 3, material.getID());

    int rc = step_command(m_wall_losses_surface_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_update_stmt);
    return valid_insert;
}

//motor helpers
int getMotorEfficiencyClassNum(Motor::EfficiencyClass efficiencyClass)
{
    int motorEfficiencyClass = 0;
    if (efficiencyClass == Motor::EfficiencyClass::STANDARD)
    {
        motorEfficiencyClass = 0;
    }
    else if (efficiencyClass == Motor::EfficiencyClass::ENERGY_EFFICIENT)
    {
        motorEfficiencyClass = 1;
    }
    else if (efficiencyClass == Motor::EfficiencyClass::PREMIUM)
    {
        motorEfficiencyClass = 2;
    }
    else if (efficiencyClass == Motor::EfficiencyClass::SPECIFIED)
    {
        motorEfficiencyClass = 3;
    }
    return motorEfficiencyClass;
}

int getMotorLineFrequencyNum(Motor::LineFrequency lineFrequency)
{
    int lineFrequencyNum = 60;
    if (lineFrequency == Motor::LineFrequency::FREQ60)
    {
        lineFrequencyNum = 60;
    }
    else if (lineFrequency == Motor::LineFrequency::FREQ50)
    {
        lineFrequencyNum = 50;
    }
    return lineFrequencyNum;
}

bool SQLite::insert_motor_data(MotorData const &m)
{
    bind_value(m_motor_data_insert_stmt, 1, 0);
    bind_value(m_motor_data_insert_stmt, 2, m.hp);
    bind_value(m_motor_data_insert_stmt, 3, m.synchronousSpeed);
    bind_value(m_motor_data_insert_stmt, 4, m.poles);
    bind_value(m_motor_data_insert_stmt, 5, m.nominalEfficiency);
    bind_value(m_motor_data_insert_stmt, 6, getMotorEfficiencyClassNum(m.efficiencyClass));
    bind_value(m_motor_data_insert_stmt, 7, m.nemaTable);
    bind_value(m_motor_data_insert_stmt, 8, m.enclosureType);
    bind_value(m_motor_data_insert_stmt, 9, getMotorLineFrequencyNum(m.lineFrequency));
    bind_value(m_motor_data_insert_stmt, 10, m.voltageLimit);
    bind_value(m_motor_data_insert_stmt, 11, m.catalog);

    int rc = step_command(m_motor_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_insert_stmt);
    return valid_insert;
}

// public API for inserts
bool SQLite::insertMotorData(MotorData const &m)
{
    bind_value(m_motor_data_insert_stmt, 1, 1);
    bind_value(m_motor_data_insert_stmt, 2, m.hp);
    bind_value(m_motor_data_insert_stmt, 3, m.synchronousSpeed);
    bind_value(m_motor_data_insert_stmt, 4, m.poles);
    bind_value(m_motor_data_insert_stmt, 5, m.nominalEfficiency);

    bind_value(m_motor_data_insert_stmt, 6, getMotorEfficiencyClassNum(m.efficiencyClass));
    bind_value(m_motor_data_insert_stmt, 7, m.nemaTable);
    bind_value(m_motor_data_insert_stmt, 8, m.enclosureType);

    bind_value(m_motor_data_insert_stmt, 9, getMotorLineFrequencyNum(m.lineFrequency));
    bind_value(m_motor_data_insert_stmt, 10, m.voltageLimit);
    bind_value(m_motor_data_insert_stmt, 11, m.catalog);

    int rc = step_command(m_motor_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteMotorData(int id)
{
    if (isDefaultMaterial(id, get_default_motor_data().size()))
    {
        return false;
    }
    bind_value(m_motor_data_delete_stmt, 1, id);
    int rc = step_command(m_motor_data_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_motor_data_delete_stmt);
    return valid_command;
}

bool SQLite::updateMotorData(MotorData const &m)
{
    if (isDefaultMaterial(m.id, get_default_motor_data().size()))
    {
        return false;
    }
    bind_value(m_motor_data_update_stmt, 1, m.hp);
    bind_value(m_motor_data_update_stmt, 2, m.synchronousSpeed);
    bind_value(m_motor_data_update_stmt, 3, m.poles);
    bind_value(m_motor_data_update_stmt, 4, m.nominalEfficiency);
    int motorEfficiencyClass = 0;
    if (m.efficiencyClass == Motor::EfficiencyClass::STANDARD)
    {
        motorEfficiencyClass = 0;
    }
    else if (m.efficiencyClass == Motor::EfficiencyClass::ENERGY_EFFICIENT)
    {
        motorEfficiencyClass = 1;
    }
    else if (m.efficiencyClass == Motor::EfficiencyClass::PREMIUM)
    {
        motorEfficiencyClass = 2;
    }
    else if (m.efficiencyClass == Motor::EfficiencyClass::SPECIFIED)
    {
        motorEfficiencyClass = 3;
    }
    bind_value(m_motor_data_update_stmt, 5, motorEfficiencyClass);
    bind_value(m_motor_data_update_stmt, 6, m.nemaTable);
    bind_value(m_motor_data_update_stmt, 7, m.enclosureType);
    int lineFrequency = 0;
    if (m.lineFrequency == Motor::LineFrequency::FREQ60)
    {
        lineFrequency = 60;
    }
    else if (m.lineFrequency == Motor::LineFrequency::FREQ50)
    {
        lineFrequency = 50;
    }
    bind_value(m_motor_data_update_stmt, 8, lineFrequency);
    bind_value(m_motor_data_update_stmt, 9, m.voltageLimit);
    bind_value(m_motor_data_update_stmt, 10, m.catalog);
    bind_value(m_motor_data_update_stmt, 11, m.id);

    int rc = step_command(m_motor_data_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_update_stmt);
    return valid_insert;
}

bool SQLite::insertPumpData(PumpData const &pump)
{
    bind_value(m_pump_data_insert_stmt, 1, 1); // sid
    bind_value(m_pump_data_insert_stmt, 2, pump.manufacturer);
    bind_value(m_pump_data_insert_stmt, 3, pump.model);
    bind_value(m_pump_data_insert_stmt, 4, pump.serialNumber);
    bind_value(m_pump_data_insert_stmt, 5, pump.status);
    bind_value(m_pump_data_insert_stmt, 6, pump.pumpType);
    bind_value(m_pump_data_insert_stmt, 7, pump.shaftOrientation);
    bind_value(m_pump_data_insert_stmt, 8, pump.shaftSealType);
    bind_value(m_pump_data_insert_stmt, 9, pump.fluidType);
    bind_value(m_pump_data_insert_stmt, 10, pump.priority);
    bind_value(m_pump_data_insert_stmt, 11, pump.driveType);
    bind_value(m_pump_data_insert_stmt, 12, pump.flangeConnectionClass);
    bind_value(m_pump_data_insert_stmt, 13, pump.flangeConnectionSize);
    bind_value(m_pump_data_insert_stmt, 14, pump.componentId);
    bind_value(m_pump_data_insert_stmt, 15, pump.system);
    bind_value(m_pump_data_insert_stmt, 16, pump.location);
    bind_value(m_pump_data_insert_stmt, 17, pump.motorEfficiencyClass);
    bind_value(m_pump_data_insert_stmt, 18, pump.speed);
    bind_value(m_pump_data_insert_stmt, 19, pump.numStages);
    bind_value(m_pump_data_insert_stmt, 20, pump.yearlyOperatingHours);
    bind_value(m_pump_data_insert_stmt, 21, pump.yearInstalled);
    bind_value(m_pump_data_insert_stmt, 22, pump.finalMotorRpm);
    bind_value(m_pump_data_insert_stmt, 23, pump.motorRatedVoltage);
    bind_value(m_pump_data_insert_stmt, 24, pump.inletDiameter);
    bind_value(m_pump_data_insert_stmt, 25, pump.outletDiameter);
    bind_value(m_pump_data_insert_stmt, 26, pump.staticSuctionHead);
    bind_value(m_pump_data_insert_stmt, 27, pump.staticDischargeHead);
    bind_value(m_pump_data_insert_stmt, 28, pump.fluidDensity);
    bind_value(m_pump_data_insert_stmt, 29, pump.maxWorkingPressure);
    bind_value(m_pump_data_insert_stmt, 30, pump.maxAmbientTemperature);
    bind_value(m_pump_data_insert_stmt, 31, pump.maxSuctionLift);
    bind_value(m_pump_data_insert_stmt, 32, pump.displacement);
    bind_value(m_pump_data_insert_stmt, 33, pump.startingTorque);
    bind_value(m_pump_data_insert_stmt, 34, pump.ratedSpeed);
    bind_value(m_pump_data_insert_stmt, 35, pump.impellerDiameter);
    bind_value(m_pump_data_insert_stmt, 36, pump.efficiency);
    bind_value(m_pump_data_insert_stmt, 37, pump.lineFrequency);
    bind_value(m_pump_data_insert_stmt, 38, pump.minFlowSize);
    bind_value(m_pump_data_insert_stmt, 39, pump.pumpSize);
    bind_value(m_pump_data_insert_stmt, 40, pump.designHead);
    bind_value(m_pump_data_insert_stmt, 41, pump.designFlow);
    bind_value(m_pump_data_insert_stmt, 42, pump.designEfficiency);
    bind_value(m_pump_data_insert_stmt, 43, pump.motorRatedPower);
    bind_value(m_pump_data_insert_stmt, 44, pump.motorFullLoadAmps);
    bind_value(m_pump_data_insert_stmt, 45, pump.operatingFlowRate);
    bind_value(m_pump_data_insert_stmt, 46, pump.operatingHead);
    bind_value(m_pump_data_insert_stmt, 47, pump.measuredCurrent);
    bind_value(m_pump_data_insert_stmt, 48, pump.measuredPower);
    bind_value(m_pump_data_insert_stmt, 49, pump.measuredVoltage);
    bind_value(m_pump_data_insert_stmt, 50, pump.motorEfficiency);

    int rc = step_command(m_pump_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_pump_data_insert_stmt);
    return valid_insert;
}

bool SQLite::deletePumpData(int id)
{
    if (isDefaultMaterial(id, get_default_pump_data().size()))
    {
        return false;
    }
    bind_value(m_pump_data_delete_stmt, 1, id);
    int rc = step_command(m_pump_data_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_pump_data_delete_stmt);
    return valid_command;
}

bool SQLite::updatePumpData(PumpData const &pump)
{
    if (isDefaultMaterial(pump.id, get_default_pump_data().size()))
    {
        return false;
    }

    bind_value(m_pump_data_update_stmt, 1, pump.manufacturer);
    bind_value(m_pump_data_update_stmt, 2, pump.model);
    bind_value(m_pump_data_update_stmt, 3, pump.serialNumber);
    bind_value(m_pump_data_update_stmt, 4, pump.status);
    bind_value(m_pump_data_update_stmt, 5, pump.pumpType);
    bind_value(m_pump_data_update_stmt, 6, pump.shaftOrientation);
    bind_value(m_pump_data_update_stmt, 7, pump.shaftSealType);
    bind_value(m_pump_data_update_stmt, 8, pump.fluidType);
    bind_value(m_pump_data_update_stmt, 9, pump.priority);
    bind_value(m_pump_data_update_stmt, 10, pump.driveType);
    bind_value(m_pump_data_update_stmt, 11, pump.flangeConnectionClass);
    bind_value(m_pump_data_update_stmt, 12, pump.flangeConnectionSize);
    bind_value(m_pump_data_update_stmt, 13, pump.componentId);
    bind_value(m_pump_data_update_stmt, 14, pump.system);
    bind_value(m_pump_data_update_stmt, 15, pump.location);
    bind_value(m_pump_data_update_stmt, 16, pump.motorEfficiencyClass);
    bind_value(m_pump_data_update_stmt, 17, pump.speed);
    bind_value(m_pump_data_update_stmt, 18, pump.numStages);
    bind_value(m_pump_data_update_stmt, 19, pump.yearlyOperatingHours);
    bind_value(m_pump_data_update_stmt, 20, pump.yearInstalled);
    bind_value(m_pump_data_update_stmt, 21, pump.finalMotorRpm);
    bind_value(m_pump_data_update_stmt, 22, pump.motorRatedVoltage);
    bind_value(m_pump_data_update_stmt, 23, pump.inletDiameter);
    bind_value(m_pump_data_update_stmt, 24, pump.outletDiameter);
    bind_value(m_pump_data_update_stmt, 25, pump.staticSuctionHead);
    bind_value(m_pump_data_update_stmt, 26, pump.staticDischargeHead);
    bind_value(m_pump_data_update_stmt, 27, pump.fluidDensity);
    bind_value(m_pump_data_update_stmt, 28, pump.maxWorkingPressure);
    bind_value(m_pump_data_update_stmt, 29, pump.maxAmbientTemperature);
    bind_value(m_pump_data_update_stmt, 30, pump.maxSuctionLift);
    bind_value(m_pump_data_update_stmt, 31, pump.displacement);
    bind_value(m_pump_data_update_stmt, 32, pump.startingTorque);
    bind_value(m_pump_data_update_stmt, 33, pump.ratedSpeed);
    bind_value(m_pump_data_update_stmt, 34, pump.impellerDiameter);
    bind_value(m_pump_data_update_stmt, 35, pump.efficiency);
    bind_value(m_pump_data_update_stmt, 36, pump.lineFrequency);
    bind_value(m_pump_data_update_stmt, 37, pump.minFlowSize);
    bind_value(m_pump_data_update_stmt, 38, pump.pumpSize);
    bind_value(m_pump_data_update_stmt, 39, pump.designHead);
    bind_value(m_pump_data_update_stmt, 40, pump.designFlow);
    bind_value(m_pump_data_update_stmt, 41, pump.designEfficiency);
    bind_value(m_pump_data_update_stmt, 42, pump.motorRatedPower);
    bind_value(m_pump_data_update_stmt, 43, pump.motorFullLoadAmps);
    bind_value(m_pump_data_update_stmt, 44, pump.operatingFlowRate);
    bind_value(m_pump_data_update_stmt, 45, pump.operatingHead);
    bind_value(m_pump_data_update_stmt, 46, pump.measuredCurrent);
    bind_value(m_pump_data_update_stmt, 47, pump.measuredPower);
    bind_value(m_pump_data_update_stmt, 48, pump.measuredVoltage);
    bind_value(m_pump_data_update_stmt, 49, pump.motorEfficiency);
    bind_value(m_pump_data_update_stmt, 50, pump.id);

    int rc = step_command(m_pump_data_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_pump_data_update_stmt);
    return valid_insert;
}

bool SQLite::insert_pump_data(PumpData const &pump)
{
    if (pump.id && isDefaultMaterial(pump.id, get_default_pump_data().size()))
    {
        return false;
    }

    bind_value(m_pump_data_insert_stmt, 1, 0); // sid
    bind_value(m_pump_data_insert_stmt, 2, pump.manufacturer);
    bind_value(m_pump_data_insert_stmt, 3, pump.model);
    bind_value(m_pump_data_insert_stmt, 4, pump.serialNumber);
    bind_value(m_pump_data_insert_stmt, 5, pump.status);
    bind_value(m_pump_data_insert_stmt, 6, pump.pumpType);
    bind_value(m_pump_data_insert_stmt, 7, pump.shaftOrientation);
    bind_value(m_pump_data_insert_stmt, 8, pump.shaftSealType);
    bind_value(m_pump_data_insert_stmt, 9, pump.fluidType);
    bind_value(m_pump_data_insert_stmt, 10, pump.priority);
    bind_value(m_pump_data_insert_stmt, 11, pump.driveType);
    bind_value(m_pump_data_insert_stmt, 12, pump.flangeConnectionClass);
    bind_value(m_pump_data_insert_stmt, 13, pump.flangeConnectionSize);
    bind_value(m_pump_data_insert_stmt, 14, pump.componentId);
    bind_value(m_pump_data_insert_stmt, 15, pump.system);
    bind_value(m_pump_data_insert_stmt, 16, pump.location);
    bind_value(m_pump_data_insert_stmt, 17, pump.motorEfficiencyClass);
    bind_value(m_pump_data_insert_stmt, 18, pump.speed);
    bind_value(m_pump_data_insert_stmt, 19, pump.numStages);
    bind_value(m_pump_data_insert_stmt, 20, pump.yearlyOperatingHours);
    bind_value(m_pump_data_insert_stmt, 21, pump.yearInstalled);
    bind_value(m_pump_data_insert_stmt, 22, pump.finalMotorRpm);
    bind_value(m_pump_data_insert_stmt, 23, pump.motorRatedVoltage);
    bind_value(m_pump_data_insert_stmt, 24, pump.inletDiameter);
    bind_value(m_pump_data_insert_stmt, 25, pump.outletDiameter);
    bind_value(m_pump_data_insert_stmt, 26, pump.staticSuctionHead);
    bind_value(m_pump_data_insert_stmt, 27, pump.staticDischargeHead);
    bind_value(m_pump_data_insert_stmt, 28, pump.fluidDensity);
    bind_value(m_pump_data_insert_stmt, 29, pump.maxWorkingPressure);
    bind_value(m_pump_data_insert_stmt, 30, pump.maxAmbientTemperature);
    bind_value(m_pump_data_insert_stmt, 31, pump.maxSuctionLift);
    bind_value(m_pump_data_insert_stmt, 32, pump.displacement);
    bind_value(m_pump_data_insert_stmt, 33, pump.startingTorque);
    bind_value(m_pump_data_insert_stmt, 34, pump.ratedSpeed);
    bind_value(m_pump_data_insert_stmt, 35, pump.impellerDiameter);
    bind_value(m_pump_data_insert_stmt, 36, pump.efficiency);
    bind_value(m_pump_data_insert_stmt, 37, pump.lineFrequency);
    bind_value(m_pump_data_insert_stmt, 38, pump.minFlowSize);
    bind_value(m_pump_data_insert_stmt, 39, pump.pumpSize);
    bind_value(m_pump_data_insert_stmt, 40, pump.designHead);
    bind_value(m_pump_data_insert_stmt, 41, pump.designFlow);
    bind_value(m_pump_data_insert_stmt, 42, pump.designEfficiency);
    bind_value(m_pump_data_insert_stmt, 43, pump.motorRatedPower);
    bind_value(m_pump_data_insert_stmt, 44, pump.motorFullLoadAmps);
    bind_value(m_pump_data_insert_stmt, 45, pump.operatingFlowRate);
    bind_value(m_pump_data_insert_stmt, 46, pump.operatingHead);
    bind_value(m_pump_data_insert_stmt, 47, pump.measuredCurrent);
    bind_value(m_pump_data_insert_stmt, 48, pump.measuredPower);
    bind_value(m_pump_data_insert_stmt, 49, pump.measuredVoltage);
    bind_value(m_pump_data_insert_stmt, 50, pump.motorEfficiency);


    int rc = step_command(m_pump_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_pump_data_insert_stmt);
    return valid_insert;
}

SQLiteWrapper::SQLiteWrapper(std::shared_ptr<sqlite3> const &db)
    : m_db(db)
{
}

SQLiteWrapper::SQLiteWrapper(std::string const &db_name, bool init_db)
{
    bool ok = true;
    bool in_memory = (db_name == ":memory:");
    char *err_msg = 0;
    int rc;

    if (init_db)
    {
        // Test if we can create a new file named db_name
        if (!in_memory)
        {
            std::ofstream test(db_name, std::ofstream::out | std::ofstream::trunc);
            if (test.is_open())
            {
                test.close();
            }
            else
            {
                ok = false;
            }
        }

        // Test if we can write to the database
        // If we can't then there are probably locks on the database
        if (ok)
        {
            sqlite3_open_v2(db_name.c_str(), &m_connection, SQLITE_OPEN_READWRITE, nullptr);
            char *zErrMsg = nullptr;
            rc = sqlite3_exec(m_connection, "CREATE TABLE Test(x INTEGER PRIMARY KEY)", nullptr, 0, &zErrMsg);
            sqlite3_exec(m_connection, "DROP TABLE IF EXISTS Test", nullptr, 0, &zErrMsg);
            sqlite3_close(m_connection);
            if (rc)
            {
                std::cerr << "Non-exclusive lock on existing database: " << sqlite3_errmsg(m_connection) << std::endl;
                ok = false;
            }
            else
            {
                if (!in_memory)
                {
                    // Remove test db
                    rc = remove(db_name.c_str());
                    if (rc)
                    {
                        std::cerr << "Can't remove old database: " << sqlite3_errmsg(m_connection) << std::endl;
                        ok = false;
                    }
                }
            }
            sqlite3_free(zErrMsg);
        }
    }

    if (ok)
    {
        // Now open the output db for the duration of the simulation
        rc = sqlite3_open_v2(db_name.c_str(), &m_connection, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        m_db = std::shared_ptr<sqlite3>(m_connection, sqlite3_close);
        if (rc)
        {
            std::cerr << "Can't open new database: " << sqlite3_errmsg(m_connection) << std::endl;
            ok = false;
        }
    }

    if (!ok)
    {
        //        throw std::runtime_error("Failed to connect to SQLite database.");
        std::cerr << "Failed to connect to SQLite database." << err_msg << std::endl;
    }
}

int SQLiteWrapper::execute_command(std::string const &command_buffer) const
{
    char *err_msg = 0;
    int rc = sqlite3_exec(m_db.get(), command_buffer.c_str(), nullptr, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_exec failed: " << err_msg << std::endl;
    }
    sqlite3_free(err_msg);
    return rc;
}

int SQLiteWrapper::prepare_statement(sqlite3_stmt *&stmt, std::string const &stmt_buffer) const
{
    int rc = sqlite3_prepare_v2(m_db.get(), stmt_buffer.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_prepare_v2 failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt *stmt, int const stmt_insert_col_index, std::string const &text_buffer) const
{

    int rc = sqlite3_bind_text(stmt, stmt_insert_col_index, text_buffer.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_bind_text failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt *stmt, int const stmt_insert_col_index, int const int_to_insert) const
{
    int rc = sqlite3_bind_int(stmt, stmt_insert_col_index, int_to_insert);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_bind_int failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt *stmt, int const stmt_insert_col_index, double const double_to_insert) const
{
    // std::cout << "double to insert " << double_to_insert << std::endl;
    int rc = sqlite3_bind_double(stmt, stmt_insert_col_index, double_to_insert);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_bind_double failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt *stmt, int const stmt_insert_col_index) const
{
    int rc = sqlite3_bind_null(stmt, stmt_insert_col_index);
    if (rc != SQLITE_OK)
    {
        std::cerr << "sqlite3_bind_null failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt *stmt, int const stmt_insert_col_index, bool const value_to_insert) const
{
    return bind_value(stmt, stmt_insert_col_index, value_to_insert ? 1 : 0);
}

int SQLiteWrapper::bind_foreign_key(sqlite3_stmt *stmt, int const stmt_insert_col_index, int const int_to_insert) const
{
    int rc = -1;
    if (int_to_insert > 0)
    {
        rc = sqlite3_bind_int(stmt, stmt_insert_col_index, int_to_insert);
    }
    else
    {
        rc = sqlite3_bind_null(stmt, stmt_insert_col_index);
    }
    if (rc != SQLITE_OK)
    {
        std::cerr << "bind_foreign_key failed" << std::endl;
    }
    return rc;
}

bool SQLiteWrapper::step_validity(int const rc) const
{
    switch (rc)
    {
    case SQLITE_DONE:
    case SQLITE_OK:
    case SQLITE_ROW:
        return true;
    default:
        break;
    }
    return false;
}

int SQLiteWrapper::step_command(sqlite3_stmt *stmt) const
{
    int rc = sqlite3_step(stmt);
    switch (rc)
    {
    case SQLITE_DONE:
    case SQLITE_OK:
    case SQLITE_ROW:
        break;
    default:
        std::cerr << "sqlite3_step failed: " << sqlite3_errmsg(m_db.get()) << std::endl;
        break;
    }

    return rc;
}

int SQLiteWrapper::reset_command(sqlite3_stmt *stmt) const
{
    return sqlite3_reset(stmt);
}

void SQLiteWrapper::begin_transaction() const
{
    execute_command("BEGIN;");
}

void SQLiteWrapper::commit_transaction() const
{
    execute_command("COMMIT;");
}
