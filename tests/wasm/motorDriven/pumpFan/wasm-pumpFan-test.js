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
    let instance = new Module.PumpEfficiency(pumpStyle, flowRate);
    let results = instance.calculate();
    instance.delete();
    testNumberValue(results.average, 83.97084437955112, "Pump Efficiency (average)");
    testNumberValue(results.max, 86.99584193768345, "Pump Efficiency (max)");
}

//execute tests
moverShaftPowerTest();
achievableEfficiency();
pumpEfficiency();
