import registeredVectorsModule from "./ts_def_modules/binding/registered_vectors";

import compressedAirModule from "./ts_def_modules/compressedAir/compressedAir";
import compressed_air_utilsModule from "./ts_def_modules/compressedAir/compressed_air_utils";
import compressorsCalcModule from "./ts_def_modules/compressedAir/compressorsCalc";
import dryer_operating_costModule from "./ts_def_modules/compressedAir/dryer_operating_cost";
import operating_costModule from "./ts_def_modules/compressedAir/operating_cost";
import pipe_sizingModule from "./ts_def_modules/compressedAir/pipe_sizing";
import pneumatic_air_requirementModule from "./ts_def_modules/compressedAir/pneumatic_air_requirement";
import pneumatic_valveModule from "./ts_def_modules/compressedAir/pneumatic_valve";
import receiver_tankModule from "./ts_def_modules/compressedAir/receiver_tank";

import bag_methodModule from "./ts_def_modules/compressedAir/leak_survey/bag_method";
import compressed_air_leak_surveyModule from "./ts_def_modules/compressedAir/leak_survey/compressed_air_leak_survey";
import decibels_methodModule from "./ts_def_modules/compressedAir/leak_survey/decibels_method";
import estimate_methodModule from "./ts_def_modules/compressedAir/leak_survey/estimate_method";
import orifice_methodModule from "./ts_def_modules/compressedAir/leak_survey/orifice_method";

import default_dataModule from "./ts_def_modules/databases/default_data";

import fanModule from "./ts_def_modules/motorDriven/fans/fan";
import fanEnumModule from "./ts_def_modules/motorDriven/fans/fanEnum";
import fan_affinity_lawsModule from "./ts_def_modules/motorDriven/fans/fan_affinity_laws";

import motorModule from "./ts_def_modules/motorDriven/motor/motor";
import motorEnumModule from "./ts_def_modules/motorDriven/motor/motorEnum";

import lighting_dataModule from "./ts_def_modules/other/lighting_data";

import steam_leak_surveyModule from "./ts_def_modules/steam/steam_leak_survey";

export default function MeasurToolsSuiteModule(): Promise<{
    registeredVectorsModule: typeof registeredVectorsModule;

    compressedAirModule: typeof compressedAirModule;
    compressed_air_utilsModule: typeof compressed_air_utilsModule;
    compressorsCalcModule: typeof compressorsCalcModule;
    dryer_operating_costModule: typeof dryer_operating_costModule;
    operating_costModule: typeof operating_costModule;
    pipe_sizingModule: typeof pipe_sizingModule;
    pneumatic_air_requirementModule: typeof pneumatic_air_requirementModule;
    pneumatic_valveModule: typeof pneumatic_valveModule;
    receiver_tankModule: typeof receiver_tankModule;

    bag_methodModule: typeof bag_methodModule;
    compressed_air_leak_surveyModule: typeof compressed_air_leak_surveyModule;
    decibels_methodModule: typeof decibels_methodModule;
    estimate_methodModule: typeof estimate_methodModule;
    orifice_methodModule: typeof orifice_methodModule;

    default_dataModule: typeof default_dataModule;
	
    fanModule: typeof fanModule;
    fanEnumModule: typeof fanEnumModule;
    fan_affinity_lawsModule: typeof fan_affinity_lawsModule;

    motorModule: typeof motorModule;
    motorEnumModule: typeof motorEnumModule;
	
	lighting_dataModule: typeof lighting_dataModule;

    steam_leak_surveyModule: typeof steam_leak_surveyModule;
}>;