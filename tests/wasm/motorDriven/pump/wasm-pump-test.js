function headToolSuctionTank() {
    let specificGravity = 1.0;
    let flowRate = 2000;
    let suctionPipeDiameter = 17.9;
    let suctionTankGasOverPressure = 115;
    let suctionTankFluidSurfaceElevation = 0;
    let suctionLineLossCoefficients = 1;
    let dischargePipeDiameter = 10;
    let dischargeGaugePressure = 124;
    let dischargeGaugeElevation = 0;
    let dischargeLineLossCoefficients = 1;
    let instance = new Module.HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure, suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter, dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
    let results = instance.calculate();
    instance.delete();

    testNumberValue(results.pumpHead, 22.972865551821844, 'Head Tool Suction Tank (pumpHead)');
    testNumberValue(results.differentialElevationHead, 0.0, 'Head Tool Suction Tank (differentialElevationHead)');
    testNumberValue(results.differentialPressureHead, 20.797226988336853, 'Head Tool Suction Tank (differentialPressureHead)');
    testNumberValue(results.differentialVelocityHead, 1.0372994352935365, 'Head Tool Suction Tank (differentialVelocityHead)');
    testNumberValue(results.estimatedDischargeFrictionHead, 1.0372994352935365, 'Head Tool Suction Tank (estimatedDischargeFrictionHead)');
    testNumberValue(results.estimatedSuctionFrictionHead, 0.10103969289791588, 'Head Tool Suction Tank (estimatedSuctionFrictionHead)');
}

function headTool() {
    let specificGravity = 1.0;
    let flowRate = 2000;
    let suctionPipeDiameter = 17.9;
    let suctionGaugePressure = 5;
    let suctionGaugeElevation = 5;
    let suctionLineLossCoefficients = 1;
    let dischargePipeDiameter = 15;
    let dischargeGaugePressure = 50;
    let dischargeGaugeElevation = 1;
    let dischargeLineLossCoefficients = 1;
    let instance = new Module.HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
        suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
        dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
    let results = instance.calculate();
    instance.delete();

    testNumberValue(results.pumpHead, 100.39593224945455, 'Head Tool (pumpHead)');
    testNumberValue(results.differentialElevationHead, -4, 'Head Tool (differentialElevationHead)');
    testNumberValue(results.differentialPressureHead, 103.98613494168427, 'Head Tool (differentialPressureHead)');
    testNumberValue(results.differentialVelocityHead, 0.10385896098722718, 'Head Tool (differentialVelocityHead)');
    testNumberValue(results.estimatedDischargeFrictionHead, 0.20489865388514306, 'Head Tool (estimatedDischargeFrictionHead)');
    testNumberValue(results.estimatedSuctionFrictionHead, 0.10103969289791588, 'Head Tool (estimatedSuctionFrictionHead)');
}

function resultsExisting() {
    //pump input
    let pumpStyle = Module.PumpStyle.END_SUCTION_STOCK;
    let pumpEfficiency = 90 / 100;
    let rpm = 1780;
    let drive = Module.Drive.SPECIFIED;
    let kviscosity = 1.0;
    let specificGravity = 1.0;
    let stageCount = 1;
    let speed = Module.SpecificSpeed.FIXED_SPEED;
    let specifiedEfficiency = 95 / 100;
    let pumpInput = new Module.PumpResultInput(pumpStyle, pumpEfficiency, rpm, drive, kviscosity, specificGravity, stageCount, speed, specifiedEfficiency);
    //motor
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedPower = 300;
    let motorRpm = 1780;
    let efficiencyClass = Module.MotorEfficiencyClass.STANDARD;
    let specifiedMotorEfficiency = .95;
    let motorRatedVoltage = 460;
    let fullLoadAmps = 337.3;
    let sizeMargin = 0;
    let motor = new Module.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedMotorEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
    //field data
    let flowRate = 1840;
    let head = 277.0;
    let loadEstimationMethod = Module.LoadEstimationMethod.POWER;
    let motorPower = 150;
    let motorAmps = 80.5;
    let voltage = 460;
    let fieldData = new Module.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
    let pumpResult = new Module.PumpResult(pumpInput, motor, fieldData, 8760, 0.06);
    let calculatedResults = pumpResult.calculateExisting();
    pumpResult.delete();
    fieldData.delete();
    motor.delete();
    pumpInput.delete();
    testNumberValue(calculatedResults.pump_efficiency * 100, 71.5541741283, "Pump Results Existing (pump_efficiency)");
    testNumberValue(calculatedResults.motor_shaft_power, 189.2746748003, "Pump Results Existing (motor_shaft_power)");
    testNumberValue(calculatedResults.mover_shaft_power, 179.8109410603, "Pump Results Existing (mover_shaft_power)");
    testNumberValue(calculatedResults.motor_efficiency * 100, 94.132604934, "Pump Results Existing (motor_efficiency)");
}

function resultsModified() {
    //pump input
    let pumpStyle = Module.PumpStyle.END_SUCTION_ANSI_API;
    let pumpEfficiency = 80 / 100;
    let rpm = 1780;
    let drive = Module.Drive.DIRECT_DRIVE;
    let kviscosity = 1.0;
    let specificGravity = 1.0;
    let stageCount = 2;
    let speed = Module.SpecificSpeed.NOT_FIXED_SPEED;
    let specifiedEfficiency = 80;
    let pumpInput = new Module.PumpResultInput(pumpStyle, pumpEfficiency, rpm, drive, kviscosity, specificGravity, stageCount, speed, specifiedEfficiency);
    //motor
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedPower = 100;
    let motorRpm = 1780;
    let efficiencyClass = Module.MotorEfficiencyClass.SPECIFIED;
    let specifiedMotorEfficiency = .95;
    let motorRatedVoltage = 460;
    let fullLoadAmps = 225;
    let sizeMargin = 0;
    let motor = new Module.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedMotorEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
    //field data
    let flowRate = 1840;
    let head = 174.85;
    let loadEstimationMethod = Module.LoadEstimationMethod.POWER;
    let motorPower = 80;
    let motorAmps = 125.857;
    let voltage = 480;
    let fieldData = new Module.PumpFieldData(flowRate, head, loadEstimationMethod, motorPower, motorAmps, voltage);
    let pumpResult = new Module.PumpResult(pumpInput, motor, fieldData, 8760, 0.05);
    let calculatedResults = pumpResult.calculateModified();
    pumpResult.delete();
    fieldData.delete();
    motor.delete();
    pumpInput.delete();

    testNumberValue(calculatedResults.pump_efficiency * 100, 80, "Pump Results Modified (pump_efficiency)");
    testNumberValue(calculatedResults.motor_rated_power, 100, "Pump Results Modified (motor_rated_power)");
    testNumberValue(calculatedResults.motor_shaft_power, 101.51891512553706, "Pump Results Modified (motor_shaft_power)");
    testNumberValue(calculatedResults.mover_shaft_power, 101.51891512553706, "Pump Results Modified (mover_shaft_power)");
    testNumberValue(calculatedResults.motor_efficiency * 100, 94.973283, "Pump Results Modified (motor_efficiency)");
    testNumberValue(calculatedResults.motor_power_factor * 100, 86.926875, "Pump Results Modified (motor_power_factor)");
    testNumberValue(calculatedResults.motor_current, 110.338892, "Pump Results Modified (motor_current)");
    testNumberValue(calculatedResults.motor_power, 79.741528, "Pump Results Modified (motor_power)");
    testNumberValue(calculatedResults.annual_energy, 698.535785, "Pump Results Modified (annual_energy)");
    testNumberValue(calculatedResults.annual_cost * 1000, 34926.789251, "Pump Results Modified (annual_cost)");
}

headToolSuctionTank();
headTool();
resultsExisting();
resultsModified();
