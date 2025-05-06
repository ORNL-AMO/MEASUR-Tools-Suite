function moverShaftPowerTest() {
    let instance = new Module.MoverShaftPower(50, Module.Drive.N_V_BELT_DRIVE, 0);
    let moverShaftPower = instance.calculate().moverShaftPower;
    instance.delete();
    testNumberValue(moverShaftPower, 48.4814329723, 'Mover Shaft Power');
}

function achievableEfficiency() {
    let pumpStyle = Module.PumpStyle.END_SUCTION_SLURRY;
    let specificSpeed = 1170;
    let instance = new Module.OptimalSpecificSpeedCorrection(pumpStyle, specificSpeed);
    let achievableEfficiency = instance.calculate() * 100;
    instance.delete();
    testNumberValue(achievableEfficiency, 1.8942771852074485, 'Achievable Pump Efficiency');
}

function pumpEfficiency(){
    let pumpStyle = Module.PumpStyle.END_SUCTION_ANSI_API;
    let flowRate = 2000;
    let pumpEfficiency = .90;
    let rpm = 2000;
    let kinematicViscosity = 1.107;
    let stageCount = 1;
    let head = 137; 

    let instance = new Module.PumpEfficiency(
        pumpStyle,
        pumpEfficiency,
        rpm,
        kinematicViscosity,
        stageCount,
        flowRate,
        head,  
    );
    let results = instance.calculate();
    instance.delete();

    const average = Number(results.average.toFixed(2));
    const max = Number(results.max.toFixed(3));
    testNumberValue(average, .84, "Pump Efficiency (average)");
    testNumberValue(max, .868, "Pump Efficiency (max)");
}

//execute tests
moverShaftPowerTest();
achievableEfficiency();
pumpEfficiency();
