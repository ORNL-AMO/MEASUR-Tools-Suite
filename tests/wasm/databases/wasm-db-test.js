function solidLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatSolid() + ', ' +
        item.getLatentHeat() + ', ' + item.getSpecificHeatLiquid()  + ', ' + item.getMeltingPoint());
}

function solidLoadChargeMaterials(defaultData){
    logMessage('Solid Load Charge Materials', true);

    let listItems = defaultData.getSolidLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 40, "Select All Default Data");

    logMessage('Default Data (start - end):');
    solidLoadChargeMaterialsLog(listItems.get(0));
    solidLoadChargeMaterialsLog(listItems.get(count-1));
}

function gasLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatVapor());
}

function gasLoadChargeMaterials(defaultData){
    logMessage('Gas Load Charge Materials', true);

    let listItems = defaultData.getGasLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 10, "Select All Default Data");

    logMessage('Default Data (start - end):');
    gasLoadChargeMaterialsLog(listItems.get(0));
    gasLoadChargeMaterialsLog(listItems.get(count-1));
}

function liquidLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatLiquid() + ', ' +
        item.getSpecificHeatVapor() + ', ' + item.getVaporizingTemperature()  + ', ' + item.getLatentHeat());
}

function liquidLoadChargeMaterials(defaultData){
    logMessage('Liquid Load Charge Materials', true);

    let listItems = defaultData.getLiquidLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 13, "Select All Default Data");

    logMessage('Default Data (start - end):');
    liquidLoadChargeMaterialsLog(listItems.get(0));
    liquidLoadChargeMaterialsLog(listItems.get(count-1));
}

function solidLiquidFlueGasMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getCarbon() + ', ' +
        item.getHydrogen() + ', ' + item.getSulphur()  + ', ' + item.getInertAsh() + ', ' +
        item.getO2() + ', ' + item.getMoisture()  + ', ' + item.getNitrogen());
}

function solidLiquidFlueGasMaterials(defaultData){
    logMessage('Solid Liquid Flue Gas Materials', true);

    let listItems = defaultData.getSolidLiquidFlueGasMaterials();
    let count = listItems.size();
    testNumberValue(count, 6, "Select All Default Data");

    logMessage('Default Data (start - end):');
    solidLiquidFlueGasMaterialsLog(listItems.get(0));
    solidLiquidFlueGasMaterialsLog(listItems.get(count-1));
}

function gasFlueGasMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' +
        item.getGasByVol("CH4") + ', ' +
        item.getGasByVol("C2H6") + ', ' +
        item.getGasByVol("N2") + ', ' +
        item.getGasByVol("H2") + ', ' +
        item.getGasByVol("C3H8") + ', ' +
        item.getGasByVol("C4H10_CnH2n") + ', ' +
        item.getGasByVol("H2O") + ', ' +
        item.getGasByVol("CO") + ', ' +
        item.getGasByVol("CO2") + ', ' +
        item.getGasByVol("SO2") + ', ' +
        item.getGasByVol("O2") + ', ' +
        item.getHeatingValue() + ', ' + item.getHeatingValueVolume()  + ', ' + item.getSpecificGravity());
}

function gasFlueGasMaterials(defaultData){
    logMessage('Gas Flue Gas Materials', true);

    let listItems = defaultData.getGasFlueGasMaterials();
    let count = listItems.size();
    testNumberValue(count, 4, "Select All Default Data");

    logMessage('Default Data (start - end):');
    gasFlueGasMaterialsLog(listItems.get(0));
    gasFlueGasMaterialsLog(listItems.get(count-1));
}

function wallLossesSurfaceLog(item){
    logMessage(item.getID() + ', ' + item.getSurface() + ', ' + item.getConditionFactor());
}

function wallLossesSurface(defaultData){
    logMessage('Wall Losses', true);

    let listItems = defaultData.getWallLossesSurface();
    let count = listItems.size();
    testNumberValue(count, 7, "Select All Default Data");

    logMessage('Default Data (start - end):');
    wallLossesSurfaceLog(listItems.get(0));
    wallLossesSurfaceLog(listItems.get(count-1));
}

function atmosphereDataLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeat());
}

function atmosphereData(defaultData){
    logMessage('Atmosphere', true);

    let listItems = defaultData.getAtmosphereSpecificHeat();
    let count = listItems.size();
    testNumberValue(count, 6, "Select All Default Data");

    logMessage('Default Data (start - end):');
    atmosphereDataLog(listItems.get(0));
    atmosphereDataLog(listItems.get(count-1));
}

function motorDataLog(item){
    logMessage(item.getId() + ', ' + item.getHp() + ', ' + item.getSynchronousSpeed() + ', ' +
        item.getPoles() + ', ' + item.getNominalEfficiency()  + ', ' + item.getEfficiencyClass().value + ', ' +
        item.getNemaTable() + ', ' + item.getEnclosureType()  + ', ' + item.getLineFrequency().value + ', ' +
        item.getVoltageLimit() + ', ' + item.getCatalog());
}

function motorData(defaultData){
    logMessage('Motor Data', true);

    let listItems = defaultData.getMotorData();
    let count = listItems.size();
    testNumberValue(count, 954, "Select All Default Data");

    logMessage('Default Data (start - end):');
    motorDataLog(listItems.get(0));
    motorDataLog(listItems.get(count-1));
}

function compressorDataLog(item){
    logMessage(item.ID() + ', ' + ', ' + item.idCompType() + ', ' +
        item.model() + ', ' + item.hp()  + ', ' + item.ratedCapacity() + ', ' +
        item.ratedPressure() + ', ' + item.maxFullFlowPressure()  + ', ' + item.idControlType() + ', ' +
        item.unloadPoint() + ', ' + item.minULSumpPressure()  + ', ' + item.blowdownTime() + ', ' +
        item.unloadSteps() + ', ' + item.modulatingPressRange()  + ', ' + item.powerFLBHP() + ', ' +
        item.totPackageInputPower() + ', ' + item.specPackagePower()  + ', ' + item.noLoadPowerFM() + ', ' +
        item.noLoadPowerUL() + ', ' + item.maxSurgePressure()  + ', ' + item.maxPressSurgeFlow() + ', ' +
        item.minStonewallPressure() + ', ' + item.minPressStonewallFlow()  + ', ' + item.designSurgeFlow() + ', ' +
        item.designInTemp() + ', ' + item.designInPressure()  + ', ' + item.ampsFL() + ', ' +
        item.effFL());
}

function compressorsData(defaultData){
    logMessage('Compressors Data', true);

    let listItems = defaultData.getCompressorData();
    let count = listItems.size();
    testNumberValue(count, 1630, "Select All Default Data");

    logMessage('Default Data (start - end):');
    compressorDataLog(listItems.get(0));
    compressorDataLog(listItems.get(count-1));
}

function lightingDataLog(item){
    logMessage(item.ID() + ', ' + item.category() + ', ' + item.type() + ', ' +
        item.lampsPerFixture() + ', ' + item.lampWattage()  + ', ' + item.lampOutput() + ', ' +
        item.lampLife() + ', ' + item.lampCRI()  + ', ' + item.coefficientOfUtilization() + ', ' +
        item.ballastFactor() + ', ' + item.lumenDegradationFactor());
}

function lightingData(defaultData){
    logMessage('Lighting Data', true);

    let listItems = defaultData.getLightingData();
    let count = listItems.size();
    testNumberValue(count, 74, "Select All Default Data");

    logMessage('Default Data (start - end):');
    lightingDataLog(listItems.get(0));
    lightingDataLog(listItems.get(count-1));
}

function db(){
    logMessage('DB Default Data Test:', true);

    let instance = new Module.DefaultData();

    solidLoadChargeMaterials(instance);
    gasLoadChargeMaterials(instance);
    liquidLoadChargeMaterials(instance);
    solidLiquidFlueGasMaterials(instance);
    gasFlueGasMaterials(instance);
    wallLossesSurface(instance);
    atmosphereData(instance);
    motorData(instance);
    compressorsData(instance);
    lightingData(instance);

    instance.delete();

    logMessage('DB Default Data Test Complete', true);
}

db();